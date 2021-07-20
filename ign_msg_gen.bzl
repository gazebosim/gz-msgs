load("@rules_proto//proto:defs.bzl", "ProtoInfo")
load(
    ":protobuf.bzl",
    "declare_out_files",
    "get_include_directory",
    "get_out_dir",
    "proto_path_to_generated_filename",
    "protos_from_context",
)

def ign_msg_gen_impl(ctx):
    protos = protos_from_context(ctx)
    dir_out = get_out_dir(protos, ctx)

    cc_files = declare_out_files(protos, ctx, "{}.pb.cc")
    hh_files = declare_out_files(protos, ctx, "{}.pb.h")
    out_files = cc_files + hh_files

    include_dirs = depset([get_include_directory(proto) for proto in protos])

    args = [
        "--cpp_out=" + dir_out.path,
        "--plugin=protoc-gen-ignmsgs=" + ctx.executable._plugin.path,
        "--ignmsgs_out=" + dir_out.path,
    ]

    for include_dir in include_dirs.to_list():
        args.append("--proto_path=" + include_dir)

    ctx.actions.run(
        outputs = out_files,
        inputs = protos,
        tools = [ctx.executable._plugin, ctx.executable._protoc],
        executable = ctx.executable._protoc,
        arguments = args + [proto.path for proto in protos],
    )

    compilation_context = cc_common.create_compilation_context(
        includes = depset([dir_out.path]),
    )

    return [
        DefaultInfo(files = depset(out_files)),
        CcInfo(compilation_context = compilation_context),
    ]

ign_msg_gen = rule(
    attrs = {
        "deps": attr.label_list(
            mandatory = True,
            allow_empty = False,
            providers = [ProtoInfo],
        ),
        "_plugin": attr.label(
            default = Label("//ign_msgs:ign_msgs_gen"),
            executable = True,
            cfg = "host",
        ),
        "_protoc": attr.label(
            default = Label("@com_google_protobuf//:protoc"),
            executable = True,
            cfg = "host",
        ),
    },
    # We generate .h files, so we need to output to genfiles.
    output_to_genfiles = True,
    implementation = ign_msg_gen_impl,
)

def get_proto_headers(protos):
    out = []
    for proto in protos:
        split = proto.split("/")[1:]
        split[2] = split[2].replace(".proto", ".pb.h")
        out.append("/".join(split))
    return out
