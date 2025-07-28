#!/bin/bash
#-------------------------------------------------------------------- Start MariaDB -----#

service mariadb start
sleep 5
#---------------------------------------------------------------------- Creation DB -----#

mariadb -e "CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\`;"
echo "Db created"


mariadb -e "CREATE USER IF NOT EXISTS \`${DB_USER}\`@'%' IDENTIFIED BY '${DB_PASSWD}';"
echo "User created"

mariadb -e "GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO \`${DB_USER}\`@'%';"
echo "privileges granted"

mariadb -e "FLUSH PRIVILEGES;"
echo "privileges flushed"

mariadb -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWD}';"
echo "Root passwd updated"
#---------------------------------------------------------------------- Shutdown DB -----#
sleep 1

mysqladmin --host=127.0.0.1 --user=root --password="${DB_ROOT_PASSWD}" shutdown

while pgrep mysqld > /dev/null; do
    echo "Waiting for db shutdown ..."
    sleep 1
done

#----------------------------------------------------------------------- Restart DB -----#
# mkdir -p /run/mysqld
# chown mysql:mysql /run/mysqld
# Seems to be optional

exec mysqld_safe --user=mysql --port=3306 --bind-address=0.0.0.0 --datadir='/var/lib/mysql'
