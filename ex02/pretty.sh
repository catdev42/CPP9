#!/bin/bash

# Set destination directory
DEST="$HOME/gcc_libstdcxx_printers"

# Clone only the pretty-printers directory from GCC (shallow clone for speed)
git clone --depth 1 https://gcc.gnu.org/git/gcc.git "$DEST"

# Path to the pretty-printers
PRINTER_PATH="$DEST/libstdc++-v3/python"

# Add pretty-printer config to ~/.gdbinit if not already present
if ! grep -q "register_libstdcxx_printers" "$HOME/.gdbinit" 2>/dev/null; then
    cat <<EOF >> "$HOME/.gdbinit"

# Enable libstdc++ pretty-printers (added by setup_pretty_printers.sh)
python
import sys
sys.path.insert(0, '$PRINTER_PATH')
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end
EOF
    echo "Pretty-printer configuration added to ~/.gdbinit"
else
    echo "Pretty-printer configuration already present in ~/.gdbinit"
fi

echo "Setup complete. Restart VS Code and debug your C++ program!"