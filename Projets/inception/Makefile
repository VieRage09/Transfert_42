# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 15:17:35 by tlebon            #+#    #+#              #
#    Updated: 2025/07/31 19:36:02 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#=========================         DEFINITIONS        =========================#
	NAME		=	inception
	USERNAME	=	tlebon
	ALPINE_IMG	=	alpine:3.18
	DEBIAN_IMG	=	debian:12.10
#==============================================================================#

#------------------------------------------------------------- PATHS ----------#
	SRC_PATH	=	srcs/
	REQ_PATH	=	$(SRC_PATH)requirements/

	DB_DIR		=	/home/$(USERNAME)/data/mariadb
	WP_DIR		=	/home/$(USERNAME)/data/wordpress

	WP_V_NAME	=	wordpress
	MDB_V_NAME	=	mariadb

	ENV			=	$(SRC_PATH).env
	DKR_CMP		=	$(SRC_PATH)docker-compose.yml
#------------------------------------------------------------------------------#

#----------------------------------------------------------- MariaDB ----------#
	MDB_PATH		= 	$(REQ_PATH)mariadb/

	MDB_CONT_NAME	=	$(MDB_IMG_NAME):$(USERNAME)
	MDB_IMG_NAME	=	mariadb
#------------------------------------------------------------------------------#

#--------------------------------------------------------- Wordpress ----------#
	WP_PATH			=	$(REQ_PATH)wordpress/

	WP_CONT_NAME	=	$(WP_IMG_NAME):$(USERNAME)
	WP_IMG_NAME		=	wordpress
#------------------------------------------------------------------------------#

#------------------------------------------------------------- NGinx ----------#
	NGX_PATH		=	$(REQ_PATH)nginx/

	NGX_CONT_NAME	=	$(NGX_IMG_NAME):$(USERNAME)
	NGX_IMG_NAME	=	nginx
#------------------------------------------------------------------------------#

all: up

up: build
	@make --silent folie
	mkdir -p $(WP_DIR)
	mkdir -p $(DB_DIR)
	sudo docker compose -f $(DKR_CMP) up -d

down:
	sudo docker compose -f $(DKR_CMP) down

start:
	sudo docker compose -f $(DKR_CMP) start

stop:
	sudo docker compose -f $(DKR_CMP) stop

build:
	sudo docker compose -f $(DKR_CMP) build

info:
	sudo docker ps -a
	sudo docker images
	sudo docker volume ls 
	sudo docker network ls
#----------------------------------------------------------- MariaDB ----------#
mdb: buildmdb runmdb

runmdb:
	sudo docker run --env-file=$(ENV) --name $(MDB_CONT_NAME) -d $(MDB_IMG_NAME)

stopmdb:
	sudo docker stop $(MDB_CONT_NAME)

buildmdb: $(MDB_PATH)Dockerfile $(MDB_PATH)db_conf.sh
	sudo docker build -f $(MDB_PATH)/Dockerfile -t $(MDB_IMG_NAME) $(MDB_PATH)
#------------------------------------------------------------------------------#

#--------------------------------------------------------- Wordpress ----------#
wp: buildwp runwp

runwp:
	sudo docker run --name $(WP_CONT_NAME) -d $(WP_IMG_NAME) --env-file=$(ENV) 

stopwp:
	sudo docker stop $(WP_CONT_NAME)

buildwp: $(WP_PATH)Dockerfile $(WP_PATH)wp_conf.sh
	sudo docker build -f $(WP_PATH)/Dockerfile -t $(WP_IMG_NAME) $(WP_PATH)
#------------------------------------------------------------------------------#

#------------------------------------------------------------- NGinx ----------#
ngx: buildngx runngx

runngx:
	sudo docker run --name $(NGX_CONT_NAME) -d $(NGX_IMG_NAME) 

stopngx:
	sudo docker stop $(NGX_CONT_NAME)

buildngx: $(NGX_PATH)Dockerfile $(NGX_PATH)nginx.conf
	sudo docker build -f $(NGX_PATH)/Dockerfile -t $(NGX_IMG_NAME) $(NGX_PATH)
#------------------------------------------------------------------------------#

clean:
	@make --silent sweep
	@sudo docker stop $$(sudo docker ps -qa) || true
	@sudo docker rm $$(sudo docker ps -qs) || true
	@sudo docker rmi -f $$(sudo docker images -qa) || true
	@sudo docker network rm $$(sudo docker network ls -q) || true
	@sudo docker rmi -f $(ALPINE_IMG) $(DEBIAN_IMG) || true

fclean: clean
	@sudo docker volume rm -f $$(sudo docker volume ls -q) || true
	@sudo rm -rf $(WP_DIR) $(DB_DIR) || true

re: clean up

#-------------------------------------------------------JOIE EPHEMERE----------#

BLUE	= \033[94m
RED		= \033[95;52m
RESET	= \033[0m

folie:
	@printf "$(RED)_________                        ___________      __________                                    ________     __________      \n"
	@printf "$(RED)__  ____/____________ ______________(_)__  /_____ __  /___(_)____________     ____________      ___  __/________  /__(_)____ \n"
	@printf "$(RED)_  /    _  __ \\_  __ \`__ \\__  __ \\_  /__  /_  __ \`/  __/_  /_  __ \\_  __ \\    _  _ \\_  __ \\     __  /_ _  __ \\_  /__  /_  _ \\ \n"
	@printf "$(RED)/ /___  / /_/ /  / / / / /_  /_/ /  / _  / / /_/ // /_ _  / / /_/ /  / / /    /  __/  / / /     _  __/ / /_/ /  / _  / /  __/ \n"
	@printf "$(RED)\\____/  \\____//_/ /_/ /_/_  .___//_/  /_/  \\__,_/ \\__/ /_/  \\____//_/ /_/     \\___//_/ /_/      /_/    \\____//_/  /_/  \\___/  \n"
	@printf "$(RED)                         /_/                                                                                                  $(RESET)\n"

sweep:
	@printf "${BLUE}           ______           __  __                                                          \n"
	@printf "          / ____/__  ____  / /_/ /__  ____ ___  ____ _____     ______      _____  ___  ____ \n"
	@printf "         / / __/ _ \/ __ \/ __/ / _ \/ __ \`__ \/ __ \`/_ __ \  / ___/ | /| / / _ \/ _ \/ __ \\ \n"
	@printf "        / /_/ /  __/ / / / /_/ /  __/ / / / / / /_/ / / / /  (__  )| |/ |/ /  __/  __/ /_/ / \n"
	@printf "        \\____/\\___/_/ /_/\\__/_/\\___/_/ /_/ /_/\\__,_/ / /_/  /____/ |__/|__/\\___/\\___/ .___/ \n"
	@printf "                                                                                   /_/       ${RESET}\n"
#------------------------------------------------------------------------------#

.PHONY: all clean fclean re folie sweep buildmdb runmdb mdb