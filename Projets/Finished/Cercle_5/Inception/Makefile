# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 15:17:35 by tlebon            #+#    #+#              #
#    Updated: 2025/08/06 01:22:39 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#=========================         DEFINITIONS        =========================#

	NAME		=	inception
	USERNAME	=	tlebon
#==============================================================================#

#------------------------------------------------------------- PATHS ----------#

	SRC_PATH	=	srcs/
	REQ_PATH	=	$(SRC_PATH)requirements/

	DB_DIR		=	/home/$(USERNAME)/data/mariadb
	WP_DIR		=	/home/$(USERNAME)/data/wordpress

	ENV			=	$(SRC_PATH).env
	DKR_CMP		=	$(SRC_PATH)docker-compose.yml
#------------------------------------------------------------------------------#

#----------------------------------------------------------- COMMANDS----------#

all: up

up: build
	mkdir -p $(WP_DIR)
	mkdir -p $(DB_DIR)
	sudo docker compose -f $(DKR_CMP) up -d

build:
	sudo docker compose -f $(DKR_CMP) build

down:
	sudo docker compose -f $(DKR_CMP) down

start:
	sudo docker compose -f $(DKR_CMP) start

stop:
	sudo docker compose -f $(DKR_CMP) stop

logs:
	sudo docker compose -f $(DKR_CMP) logs -f

info:
	@echo "========== Containers =========="
	sudo docker ps -a
	@echo "========== Images =========="
	sudo docker images
	@echo "========== Volumes =========="
	sudo docker volume ls
	@echo "========== Networks =========="
	sudo docker network ls

restart: down up

rebuild: fclean up

clean:
	@make --silent sweep
	sudo docker compose -f $(DKR_CMP) down --rmi all --volumes

fclean: clean
	sudo rm -rf $(WP_DIR) $(DB_DIR) || true
	sudo docker image prune -af
	sudo docker volume prune -f

re: fclean up
#------------------------------------------------------------------------------#

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

.PHONY: all up build down start stop logs info restart rebuild clean fclean re folie sweep