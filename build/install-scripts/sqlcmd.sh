#!/usr/bin/env bash
set -euo pipefail

# Install Microsoft's Go sqlcmd on Linux.

if [ "$(id -u)" -ne 0 ]; then
    echo "Please run this script with sudo."
    exit 1
fi

if ! command -v bzip2 >/dev/null 2>&1; then
    echo "Installing bzip2..."
    apt-get update
    apt-get install -y bzip2
fi

SQLCMD_VERSION="1.10.0"
url="https://github.com/microsoft/go-sqlcmd/releases/download/v${SQLCMD_VERSION}/sqlcmd-linux-amd64.tar.bz2"

tmp_dir="$(mktemp -d)"
trap 'rm -rf "$tmp_dir"' EXIT

echo "Downloading sqlcmd ${SQLCMD_VERSION}..."
curl -fsSL "$url" -o "$tmp_dir/sqlcmd.tar.bz2"

echo "Installing sqlcmd..."
tar -xjf "$tmp_dir/sqlcmd.tar.bz2" -C "$tmp_dir"
install -m 755 "$tmp_dir/sqlcmd" /usr/local/bin/sqlcmd

echo
echo "sqlcmd installed successfully:"
sqlcmd --version
