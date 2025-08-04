#!/bin/bash

set -e
#Ensure that shell exit immediately if any command fails
#-------------------------------------------------------------------- Start MariaDB -----#

#---------------------------------------------------------------------- Creation DB -----#

echo "========== MariaDB: container started =========="
chown -R mysql:mysql /var/lib/mysql
mkdir -p /run/mysqld
chown mysql:mysql /run/mysqld

if [ ! -d "/var/lib/mysql/mysql" ]; then

    echo "========== MariaDB: Initializing =========="

    mysql_install_db --user=mysql --datadir=/var/lib/mysql

    echo "========== MariaDB: Starting for setup =========="

    mysqld_safe --user=mysql --bind-address=0.0.0.0 &

    until mysqladmin ping --silent; do
        echo "Waiting for MariaDB to start..."
        sleep 1
    done

    echo "========== MariaDB: Creating DB & Users =========="

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

    echo "========== MariaDB: Restarting =========="

    mysqladmin --host=127.0.0.1 --user=root --password="${DB_ROOT_PASSWD}" shutdown

    while pgrep mysqld > /dev/null; do
        echo "Waiting for db shutdown ..."
        sleep 1
    done
else
    echo "========== MariaDB: DB already initialized =========="
fi
#----------------------------------------------------------------------- Restart DB -----#

echo "========== MariaDB: Launching DB Daemon =========="
# exec mariadb --user=mysql --port=3306 --bind-address=0.0.0.0 --datadir='/var/lib/mysql'
exec mysqld --user=mysql --port=3306 --datadir=/var/lib/mysql --bind-address=0.0.0.0
