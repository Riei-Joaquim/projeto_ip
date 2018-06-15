serverFile=demoServer
clientFile=demoClient
serverName=SERVER
clientName=CLIENT

LIBS := -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec 

all: compServer compClient

server: compServer runServer

client: compClient runClient

compClient:
	gcc -std=c99 -o $(clientName) $(clientFile).c libAllegro/AllegroCore.c libSocket/server.c libSocket/client.c $(LIBS) -Wall

compServer:
	gcc -std=c99 -o $(serverName) $(serverFile).c libAllegro/AllegroCore.c libSocket/server.c libSocket/client.c $(LIBS)

runClient:
	./$(clientName)

runServer:
	./$(serverName)