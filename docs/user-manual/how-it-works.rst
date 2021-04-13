.. _how_it_works:

How it works
============

This section describes how library works from the basic perspective.

LwSHELL is designed to accept *computer-command-like* input, in format of ``cmdname param1 "param 2 with space"``,
parse it properly and search for function callback that is assigned for specific ``cmdname``.

Library starts processing input line on *line-feed* or *carriage-return* characters.
It splits tokens by space character:

* Tokens must not include ``space`` character or it will be considered as multi-token input
* To use *space* character as token input, encapsulate character in *double-quotes*

Command structure
^^^^^^^^^^^^^^^^^

Every command has assigned dedicated name and must start with it.
Application must take care to input exact command name since commands are case-sensitive, ``mycmd`` is a different command than ``Mycmd``.

Command structure looks like:

* It must start with command name and has at least one (``1``) parameter, eg. ``mycommand``. Command name is counted as first parameter
* It may have additional parameters split with *space* character
* Every input is parsed as string, even if parameter is string

.. tip::
    To use space as an input, encapsulate it with *double quotes*, eg. ``mycmd param1 "param 1 has spaces"``

Register command
^^^^^^^^^^^^^^^^

Application must register command(s) to be used by the system.
This can be done using :cpp:func:`lwshell_register_cmd` function which accepts
*command name*, *command function* and optional *command description*

Command description
^^^^^^^^^^^^^^^^^^^

Every command can have assigned its very simple description text, know as *help text*.
Description is later accessible with special command input that has ``2`` parameters in total and second is ``-h``, ``cmdname -h``.

Data output
^^^^^^^^^^^

To properly work with the library, application must input data to process by using :cpp:func:`lwshell_input` function.
Thanks to the library implementation, it is possible to get data feedback and be able to implement OS-like console.

To enable data-output feature, define your output callback function and assign it with :cpp:func:`lwshell_set_output_fn` function.

Data outputs works on:

* Special characters for *carriage return* and *line-feed*
* Special character *backspace* that returns set of characters to implement backspace-like event on your output
* Actual input character printed back for user feedback
* ``cmdname -h`` feature works to print simple help text

.. toctree::
    :maxdepth: 2