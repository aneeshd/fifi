#! /usr/bin/env python
# encoding: utf-8

import os

import waflib.extras.bundle_dependency as bundle

APPNAME = 'fifi'
VERSION = '1.0.1'

bundle.add_dependency('boost', 'git://github.com/steinwurf/external-boost.git',
                      '1.1.2-boost_1_48_0')

bundle.add_dependency('gtest', 'git://github.com/steinwurf/external-gtest.git',
                      '1.0.3-gtest_1_6_0')

bundle.add_dependency('sak', 'git://github.com/steinwurf/sak.git',
                      '1.1.1')


def load_helper(ctx, name):
    if not ctx.has_dependency_path(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        p = ctx.dependency_path(name)
        ctx.recurse(p)


def options(opt):

    opt.load('toolchain_cxx')
    opt.load('bundle_dependency')


def configure(conf):

    conf.load('toolchain_cxx')
    conf.load('bundle_dependency')

    load_helper(conf, 'boost')
    load_helper(conf, 'gtest')
    load_helper(conf, 'sak')


def build(bld):

    bld.load('bundle_dependency')

    load_helper(bld, 'boost')
    load_helper(bld, 'gtest')
    load_helper(bld, 'sak')

    # Export own includes
    bld(includes = '.',
        export_includes = '.',
        name = 'fifi_includes')


    bld.recurse('test')
    bld.recurse('benchmark/basic_operations')
    bld.recurse('benchmark/arithmetic')


