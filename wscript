#! /usr/bin/env python
# encoding: utf-8

import os

APPNAME = 'fifi'
VERSION = '1.0.2'


def recurse_helper(ctx, name):
    if not ctx.has_dependency_path(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        p = ctx.dependency_path(name)
        ctx.recurse(p)


def options(opt):

    opt.load('toolchain_cxx')
    opt.load('dependency_bundle')

    import waflib.extras.dependency_bundle as bundle
    import waflib.extras.dependency_resolve as resolve

    bundle.add_dependency(opt,
        resolve.ResolveGitMajorVersion(
            name = 'gtest',
            git_repository = 'git://github.com/steinwurf/external-gtest.git',
            major_version = 1))

    bundle.add_dependency(opt,
        resolve.ResolveGitMajorVersion(
            name = 'boost',
            git_repository = 'git://github.com/steinwurf/external-boost.git',
            major_version = 1))

    bundle.add_dependency(opt,
        resolve.ResolveGitMajorVersion(
            name = 'sak',
            git_repository = 'git://github.com/steinwurf/sak.git',
            major_version = 1))


def configure(conf):

    if conf.is_toplevel():

        conf.load('toolchain_cxx')
        conf.load('dependency_bundle')

        recurse_helper(conf, 'boost')
        recurse_helper(conf, 'gtest')
        recurse_helper(conf, 'sak')


def build(bld):

    if bld.is_toplevel():

        bld.load('dependency_bundle')

        recurse_helper(bld, 'boost')
        recurse_helper(bld, 'gtest')
        recurse_helper(bld, 'sak')

        # Only build test and benchmarks when executed from the
        # top-level wscript i.e. not when included as a dependency
        # in a recurse call

        bld.recurse('test')
        bld.recurse('benchmark/basic_operations')
        bld.recurse('benchmark/arithmetic')

    # Export own includes
    bld(includes = '.',
        export_includes = '.',
        name = 'fifi_includes')



