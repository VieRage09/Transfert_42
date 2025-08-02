#!/bin/bash

set -e
#Ensure that shell exit immediately if any command fails
#-------------------------------------------------------------------- Start MariaDB -----#

#---------------------------------------------------------------------- Creation DB -----#

echo "Check if MariaDB is initialized..."
echo "Files in/var/lib/mysql:"
ls -l /var/lib/mysql || true
if [ ! -s "/var/lib/mysql/mysql" ]; then

    echo "MariaDB not initialized, initialization..."

    mysqld_safe --skip-networking &

    until mysqladmin ping --silent; do
        sleep 1
    done

    mariadb -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWD}';"
    echo "Root passwd updated"

    mariadb -u root -p"${DB_ROOT_PASSWD}" -e "FLUSH PRIVILEGES;"
    echo "privileges flushed"

    mariadb -u root -p"${DB_ROOT_PASSWD}" -e "CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\`;"
    echo "Db created"

    mariadb -u root -p"${DB_ROOT_PASSWD}" -e "CREATE USER IF NOT EXISTS \`${DB_USER}\`@'%' IDENTIFIED BY '${DB_PASSWD}';"
    echo "User created"

    mariadb -u root -p"${DB_ROOT_PASSWD}" -e "GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO \`${DB_USER}\`@'%';"
    echo "privileges granted"

    mariadb -u root -p"${DB_ROOT_PASSWD}" -e "FLUSH PRIVILEGES;"
    echo "privileges flushed"

#---------------------------------------------------------------------- Shutdown DB -----#
    sleep 1

    mysqladmin --host=127.0.0.1 --user=root --password="${DB_ROOT_PASSWD}" shutdown

    while pgrep mysqld > /dev/null; do
        echo "Waiting for db shutdown ..."
        sleep 1
    done
else
    echo "MariaDB data directory found. skipping setup."
fi
#----------------------------------------------------------------------- Restart DB -----#
mkdir -p /run/mysqld
chown mysql:mysql /run/mysqld

# exec mariadb --user=mysql --port=3306 --bind-address=0.0.0.0 --datadir='/var/lib/mysql'
exec mysqld_safe --user=mysql --port=3306 --datadir=/var/lib/mysql --bind-address=0.0.0.0
