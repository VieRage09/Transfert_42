#!/bin/bash


#-------------------------------------------------------------------- Start MariaDB -----#

service mariadb start

#---------------------------------------------------------------------- Creation DB -----#

mariadb -e "CREATE DATABASE IF NOT EXISTS \`${DB_NAME};\`"

mariadb -e "CREATE USER IF NOT EXISTS \`${DB_USER}\`@localhost IDENTIFIED BY '${DB_PASSWD}'"

mariadb -e "GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO \`${DB_USER}\`@localhost;"

mariadb -e "FLUSH PRIVILEGES;"

mariadb -e "show databases;"

#----------------------------------------------------------------------- Restart DB -----#