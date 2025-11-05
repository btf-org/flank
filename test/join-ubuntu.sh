count=$(docker ps --filter "ancestor=ubuntu-tester" --format "{{.Names}}" | wc -l)
if [ $count -eq 0 ]; then 
    echo 'No containers running!'
    return
elif [ $count -gt 1 ]; then
    echo 'More than 1 container running!'
    return
fi
name=$(docker ps --filter "ancestor=ubuntu-tester" --format "{{.Names}}")
docker exec -it $name bash
