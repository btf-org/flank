if [ -z "$1" ]; then
    echo "Must supply message"
    return 1
fi

# Get the latest tag matching vM.m.p
latest_tag=$(git tag --list "v*.*.*" --sort=-v:refname | head -n1)

if [ -z "$latest_tag" ]; then
    echo "No tags found. Exiting..."
    return 1
fi


version=${latest_tag#v}
IFS='.' read -r major minor patch <<< "$version"

# Increment patch
patch=$((patch + 1))

new_tag="v$major.$minor.$patch"

echo "Latest Tag: $latest_tag"
echo "Da New Tag: $new_tag"
echo "Annotation: $1"
echo ""
read -rp "Hit enter to tag and replace in iflank" choice
git tag -a "$new_tag" -m "$1"
sed -i '' 's/to iflank v.*\..*\..*!/to iflank '$new_tag'!/' iflank.c
git status
read -rp "Hit enter to add in working tree and push" choice
git commit -am 'update to '$new_tag
git push
git push origin "$new_tag"
