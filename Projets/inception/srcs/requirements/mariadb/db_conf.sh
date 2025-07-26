#!/bin/bash


#-------------------------------------------------------------------- Start MariaDB -----#

service mariadb start

#---------------------------------------------------------------------- Creation DB -----#

mariadb -e "CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\`;"
echo "Db created"

mariadb -e "CREATE USER IF NOT EXISTS \`${DB_USER}\`@localhost IDENTIFIED BY '${DB_PASSWD}';"
echo "User created"

mariadb -e "GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO \`${DB_USER}\`@localhost;"
echo "privileges granted"

mariadb -e "FLUSH PRIVILEGES;"
echo "privileges flushed"

#----------------------------------------------------------------------- Restart DB -----#

mysqladmin -u root -p"$DB_ROOT_PASSWD" shutdown
echo "shutdown, launching again yeyo"

mysqld_safe --port=3306 --bind-address=0.0.0.0 --datadir='/var/lib/mysql'