#-------------------------------------------------
# http://github.com/qtau-devgroup/libstand
#-------------------------------------------------
TEMPLATE = subdirs

SUBDIRS = \
    libstandcore.pro \
    libstandtest.pro

Core.subdir = libstandcore.pro

Test.subdir = libstandtest.pro
Test.depends = Core
