# It's necessary to install the python modules for the test.
make install
# Test gz command
export GZ_CONFIG_PATH=/usr/local/share/gz
gz msg
