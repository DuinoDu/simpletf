# cargo install cargo-watch
# cargo watch -- bash auto.sh
cd build && make -j4 && ctest --output-on-failure
