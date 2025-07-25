#!/bin/bash


#-------------------------------------------------------------------- Start MariaDB -----#

service mariadb start

#---------------------------------------------------------------------- Creation DB -----#

mariadb -e "CREATE DATABASE IF NOT EXISTS \`${DB_NAME};\`"

mariadb -e "CREATE USER IF NOT EXISTS \`${DB_USER}\`@localhost IDENTIFIED BY '${DB_PASSWD}'"

mariadb -e "GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO \`${DB_USER}\`@localhost;"

mariadb -e "FLUSH PRIVILEGES;"

#----------------------------------------------------------------------- Restart DB -----#

mysqladmin -u root -p$DB_ROOT_PASSWD shutdown

mysqld_safe --port=3306 --bind-address=0.0.0.0 --datadir='/var/lib/mysql'