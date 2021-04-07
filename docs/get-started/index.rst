.. _getting_started:

Getting started
===============

.. _download_library:

Download library
^^^^^^^^^^^^^^^^

Library is primarly hosted on `Github <https://github.com/MaJerle/lwshell>`_.

* Download latest release from `releases area <https://github.com/MaJerle/lwshell/releases>`_ on Github
* Clone `develop` branch for latest development

Download from releases
**********************

All releases are available on Github `releases area <https://github.com/MaJerle/lwshell/releases>`_.

Clone from Github
*****************

First-time clone
""""""""""""""""

* Download and install ``git`` if not already
* Open console and navigate to path in the system to clone repository to. Use command ``cd your_path``
* Clone repository with one of available ``3`` options

  * Run ``git clone --recurse-submodules https://github.com/MaJerle/lwshell`` command to clone entire repository, including submodules
  * Run ``git clone --recurse-submodules --branch develop https://github.com/MaJerle/lwshell`` to clone `development` branch, including submodules
  * Run ``git clone --recurse-submodules --branch master https://github.com/MaJerle/lwshell`` to clone `latest stable` branch, including submodules

* Navigate to ``examples`` directory and run favourite example

Update cloned to latest version
"""""""""""""""""""""""""""""""

* Open console and navigate to path in the system where your resources repository is. Use command ``cd your_path``
* Run ``git pull origin master --recurse-submodules`` command to pull latest changes and to fetch latest changes from submodules
* Run ``git submodule foreach git pull origin master`` to update & merge all submodules

.. note::
	This is preferred option to use when you want to evaluate library and run prepared examples.
	Repository consists of multiple submodules which can be automatically downloaded when cloning and pulling changes from root repository.

Add library to project
^^^^^^^^^^^^^^^^^^^^^^

At this point it is assumed that you have successfully download library, either cloned it or from releases page.

* Copy ``lwshell`` folder to your project
* Add ``lwshell/src/include`` folder to `include path` of your toolchain
* Add source files from ``lwshell/src/`` folder to toolchain build
* Copy ``lwshell/src/include/lwshell/lwshell_opts_template.h`` to project folder and rename it to ``lwshell_opts.h``
* Build the project

Configuration file
^^^^^^^^^^^^^^^^^^

Library comes with template config file, which can be modified according to needs.
This file shall be named ``lwshell_opts.h`` and its default template looks like the one below.

.. note::
    Default configuration template file location: ``lwshell/src/include/lwshell/lwshell_opts_template.h``.
    File must be renamed to ``lwshell_opts.h`` first and then copied to the project directory (or simply renamed in-place) where compiler
    include paths have access to it by using ``#include "lwshell_opts.h"``.

.. tip::
    Check :ref:`api_lwshell_opt` section for possible configuration settings

.. literalinclude:: ../../lwshell/src/include/lwshell/lwshell_opts_template.h
    :language: c
    :linenos:
    :caption: Template options file

Minimal example code
^^^^^^^^^^^^^^^^^^^^

Run below example to test and verify library

.. literalinclude:: ../examples_src/example_minimal.c
    :language: c
    :linenos:
    :caption: Absolute minimum example