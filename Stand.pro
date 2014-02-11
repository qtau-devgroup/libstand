TEMPLATE = subdirs

SUBDIRS = \
    StandCore.pro \
    StandTest.pro

Core.subdir = StandCore.pro

Test.subdir = StandTest.pro
Test.depends = Core
