set -e

if [ -z "$1" ]; then
    echo "Must supply message"
    return 1
fi

# Get the latest tag matching vM.m.p
latest_tag=$(git tag --list "v*.*.*" --sort=-v:refname | head -n1)

if [ -z "$latest_tag" ]; then
    echo "No tags found. Exiting..."
    return 1
else

version=${latest_tag#v}
IFS='.' read -r major minor patch <<< "$version"

# Increment patch
patch=$((patch + 1))

new_tag="v$major.$minor.$patch"

git tag -a "$new_tag" -m $1
git push origin $new_tag
