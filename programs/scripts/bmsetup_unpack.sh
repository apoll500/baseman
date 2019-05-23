#!/bin/bash

# param 0:
# param 1: output path
# param 2: package name

gpg_fingerprint="9FDBCA29215F491AD9C3B81AF038C1708DE08C89"

cd $1
tar -xaf $2.tar.gz
out=$(gpg --status-fd 1 --verify $2.tar.gz.sig $2.tar.gz 2> /dev/null)

if ! echo "$out" | grep -qs "^\[GNUPG:\] VALIDSIG $gpg_fingerprint "; then
  rm -R $2
  printf "\033[%d;2;%d;%d;%dm\033[%dm" 38 255 255 200 41
  echo "                                                         "
  echo "  +------------------------------------+                 "
  echo "  | PGP-Signature missing or invalid ! |                 "
  echo "  +------------------------------------+                 "
  echo "  Installation canceled for                              "
  echo "  package                                                "
  echo "                                                         "
  printf "\033[1A"
  echo "    $2"
  echo "                                                         "
  echo "  Do not ignore this!                                    "
  echo "                                                         "
  printf "\033[0m"
fi
