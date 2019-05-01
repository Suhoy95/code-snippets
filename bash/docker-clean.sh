docker container rm $(docker ps -aq)
docker rmi -f $(docker images -q)

