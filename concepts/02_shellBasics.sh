#!/bin/bash

# Shebang
    # Starting with '#!' called she bang line
    # Absulute path to bash interpreter
    # default is usually the /bin/sh

# Comment
    # multiple line comment
<<COMMENT_SAMPLE
    multiple line comment
    sample
COMMENT_SAMPLE

# Debug a script
<<DEBUG
    1 Run script with option -x
        $ bash -x sample_script
    2 Modify shebang with -x
        #!/bin/bash -x
    3 Builtin command
        # Debugging options
            set -x : Display commands and their arguments as they are executed.
            set -v : Display shell input lines as they are read.
            set -n : Read commands but do not execute them. used for syntax error.
DEBUG
# Example
set -xv  # Turn on debugging mode
echo "Hello world"
set +xv # Turn off debugging mode
echo "bye world"
set -vn
echo "Test -n"
set +vn

