"""Helper functions for generating gz-msgs compatible messages"""

load("@rules_proto//proto:defs.bzl", "ProtoInfo")
load(
    "@gz//bazel/skylark:protobuf.bzl",
    "declare_out_files",
    "get_include_directory",
    "get_out_dir",
    "protos_from_context",
)

def _filter_files_impl(ctx):
    """Filter the files in DefaultInfo."""
    return [DefaultInfo(
        files = depset([
            file
            for file in ctx.attr.target.files.to_list()
            if file.extension in ctx.attr.extensions
        ]),
    )]

filter_files = rule(
    implementation = _filter_files_impl,
    attrs = {
        "target": attr.label(
            doc = "The source target to filter",
            mandatory = True,
        ),
        "extensions": attr.string_list(
            doc = "The extensions of the files to keep eg. ['h']",
            mandatory = True,
        ),
    },
)

def get_proto_headers(protos):
    """
    Get headers for a set of proto files
    """
    out = []
    for proto in protos:
        split = proto.split("/")[1:]
        split[2] = split[2].replace(".proto", ".pb.h")
        out.append("/".join(split))
    return out

def _gz_proto_factory_impl(ctx):
    """
    Implementation of gz_proto_factory rule
    """
    protos = protos_from_context(ctx)
    out_dir = get_out_dir(protos, ctx)
    in_protos = []
    include_dirs = depset([get_include_directory(proto) for proto in protos])

    for src in ctx.attr.deps:
        for proto in src[ProtoInfo].direct_sources:
            in_protos.append(proto)

    in_protos = depset(in_protos).to_list()
    arguments = [
        "--cc-output=" + ctx.outputs.cc_output.path,
        "--hh-output=" + ctx.outputs.hh_output.path,
    ]

    for include_dir in include_dirs.to_list():
        arguments.append("--proto-path=" + include_dir)

    arguments.append("--proto-include-path=" + out_dir.path)
    arguments.append("--protos")
    for proto in in_protos:
        arguments.append(proto.path)

    ctx.actions.run(
        inputs = protos,
        outputs = [ctx.outputs.cc_output, ctx.outputs.hh_output],
        arguments = arguments,
        executable = ctx.executable.gz_msgs_generate_factory_py,
    )

    compilation_context = cc_common.create_compilation_context(
        headers = depset([ctx.outputs.hh_output]),
        system_includes = depset([ctx.outputs.hh_output.dirname]),
    )

    return [
        CcInfo(compilation_context = compilation_context),
    ]

_gz_proto_factory = rule(
    attrs = {
        "deps": attr.label_list(
            mandatory = True,
            allow_empty = False,
            providers = [ProtoInfo],
        ),
        "cc_output": attr.output(mandatory = True),
        "hh_output": attr.output(mandatory = True),
        "gz_msgs_generate_factory_py": attr.label(
            default = Label("@gz//msgs/tools:gz_msgs_generate_factory_py"),
            executable = True,
            cfg = "host",
        ),
    },
    implementation = _gz_proto_factory_impl,
)

def gz_proto_factory(
        deps,
        **kwargs):
    """
    gz_proto_factory rule implementation wrapper
    """
    _gz_proto_factory(
        deps = deps,
        **kwargs
    )

def _gz_proto_library_impl(ctx):
    """
    Implementation of the gz_proto_library rule
    """
    protos = protos_from_context(ctx)
    out_dir = get_out_dir(protos, ctx)

    arguments = []

    in_protos = []
    out_protos = []
    include_dirs = []

    for src in ctx.attr.deps:
        for proto in src[ProtoInfo].direct_sources:
            in_protos.append(proto)
            include_dirs.append(get_include_directory(proto))
            out_protos.append(proto)

        for proto in src[ProtoInfo].transitive_sources.to_list():
            in_protos.append(proto)
            include_dirs.append(get_include_directory(proto))

    in_protos = depset(in_protos).to_list()
    out_protos = depset(out_protos).to_list()
    include_dirs = depset(include_dirs).to_list()

    for include_dir in include_dirs:
        arguments.append("--proto_path=" + include_dir)

    arguments.append("--plugin=protoc-gen-gzmsgs=" + ctx.executable._gz_gen_bin.path)
    arguments.append("--cpp_out=" + out_dir.path)
    arguments.append("--gzmsgs_out=" + out_dir.path)

    for proto in in_protos:
        arguments.append(proto.path)

    cc_files = declare_out_files(out_protos, ctx, "{}.pb.cc")
    hh_files = declare_out_files(out_protos, ctx, "{}.pb.h")
    out_files = cc_files + hh_files

    ctx.actions.run(
        inputs = in_protos,
        outputs = out_files,
        arguments = arguments,
        executable = ctx.executable._protoc,
        tools = [ctx.executable._protoc, ctx.executable._gz_gen_bin],
    )

    compilation_context = cc_common.create_compilation_context(
        headers = depset(hh_files),
        system_includes = depset([out_dir.path]),
    )

    return [
        DefaultInfo(files = depset(out_files)),
        CcInfo(compilation_context = compilation_context),
    ]

_gz_proto_library = rule(
    attrs = {
        "deps": attr.label_list(
            mandatory = True,
            allow_empty = False,
            providers = [ProtoInfo],
        ),
        "_protoc": attr.label(
            default = Label("@com_google_protobuf//:protoc"),
            executable = True,
            cfg = "host",
        ),
        "_gz_gen_bin": attr.label(
            default = Label("@gz//msgs:gz_msgs_gen"),
            executable = True,
            cfg = "host",
        ),
    },
    implementation = _gz_proto_library_impl,
)

def gz_proto_library(
        name,
        proto_deps,
        **kwargs):
    """
    gz_proto_library rule implementation wrapper
    """
    _gz_proto_library(name = name + "_pb", deps = proto_deps)

    filter_files(name = name + "_srcs", target = ":" + name + "_pb", extensions = ["cc"])
    filter_files(name = name + "_hdrs", target = ":" + name + "_pb", extensions = ["h"])
    kwargs["deps"].append(":" + name + "_pb")

    native.cc_library(
        name = name,
        srcs = [name + "_srcs"],
        hdrs = [name + "_hdrs"],
        **kwargs
    )
