load("@rules_proto//proto:defs.bzl", "ProtoInfo")
load(
    "@gz//bazel/skylark:protobuf.bzl",
    "declare_out_files",
    "get_include_directory",
    "get_out_dir",
    "proto_path_to_generated_filename",
    "protos_from_context",
)

_VIRTUAL_IMPORTS = "/_virtual_imports/"

def _get_detail_directory(hh_file, ctx):
    base = hh_file.path[hh_file.path.index(_VIRTUAL_IMPORTS) + 1:]
    base = base.split("/")
    base.insert(-1, "details")
    return ctx.actions.declare_file("/".join(base))

def get_proto_headers(protos):
    out = []
    for proto in protos:
        split = proto.split("/")[1:]
        split[2] = split[2].replace(".proto", ".pb.h")
        out.append("/".join(split))
    return out

def _gz_msgs_generate_impl(ctx):
    protos = protos_from_context(ctx)
    out_dir = get_out_dir(protos, ctx)

    include_dirs = depset([get_include_directory(proto) for proto in protos])

    arguments = [
        "--protoc-exec=" + ctx.executable._protoc.path,
        "--gz-generator-bin=" + ctx.executable._gz_gen_bin.path,
        "--generate-cpp",
        "--output-cpp-path=" + out_dir.path,
    ]

    for proto in protos:
        arguments.append("--input-path=" + proto.path)

    for include_dir in include_dirs.to_list():
        arguments.append("--proto-path=" + include_dir)

    out_protos = [proto for proto in protos if proto.path.find("gz/msgs") > 0]

    cc_files = declare_out_files(out_protos, ctx, "{}.pb.cc")
    hh_files = declare_out_files(out_protos, ctx, "{}.pb.h")
    detail_hh_files = [_get_detail_directory(file, ctx) for file in hh_files]
    out_files = cc_files + hh_files + detail_hh_files

    ctx.actions.run(
        inputs = protos,
        outputs = out_files,
        arguments = arguments,
        executable = ctx.executable.gz_msgs_generate_py,
        tools = [ctx.executable._protoc, ctx.executable._gz_gen_bin, ctx.executable.gz_msgs_generate_py],
    )

    compilation_context = cc_common.create_compilation_context(
        headers = depset(out_files),
        system_includes = depset([out_dir.path]),
    )

    return [
        DefaultInfo(files = depset(out_files)),
        CcInfo(compilation_context = compilation_context),
    ]

_gz_msgs_generate_gen = rule(
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
        "gz_msgs_generate_py": attr.label(
            default = Label("@gz//msgs/tools:gz_msgs_generate_py"),
            executable = True,
            cfg = "host",
        ),
    },
    output_to_genfiles = True,
    implementation = _gz_msgs_generate_impl,
)

def gz_msgs_generate(
        deps,
        **kwargs):
    _gz_msgs_generate_gen(
        deps = deps,
        **kwargs
    )
