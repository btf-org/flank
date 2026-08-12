#!/usr/bin/env bash
set -euo pipefail

# Install Microsoft's Go sqlcmd on Ubuntu/Debian.

if [ "$(id -u)" -ne 0 ]; then
    echo "Please run this script with sudo."
    exit 1
fi

if ! command -v apt-get >/dev/null 2>&1; then
    echo "Error: apt-get not found. This installer currently supports Ubuntu/Debian."
    exit 1
fi

# Get distro/version information.
. /etc/os-release

case "${ID:-}" in
    ubuntu)
        repo_url="https://packages.microsoft.com/config/ubuntu/${VERSION_ID}/packages-microsoft-prod.deb"
        ;;
    debian)
        repo_url="https://packages.microsoft.com/config/debian/${VERSION_ID}/packages-microsoft-prod.deb"
        ;;
    *)
        echo "Error: unsupported distribution: ${ID:-unknown}"
        exit 1
        ;;
esac

tmp_deb="$(mktemp)"
trap 'rm -f "$tmp_deb"' EXIT

echo "Adding Microsoft package repository..."
curl -fsSL "$repo_url" -o "$tmp_deb"
dpkg -i "$tmp_deb"

echo "Installing sqlcmd..."
apt-get update
apt-get install -y sqlcmd

echo
echo "sqlcmd installed successfully:"
sqlcmd --version
