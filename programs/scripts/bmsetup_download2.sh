#!/bin/bash

# param 0:
# param 1: output path
# param 2: package name
# param 3: username
# param 4: userpass

login_url="https://www.andreaspollhammer.com/sys/index.php"
download_url="https://www.andreaspollhammer.com/sys/index.php?c=baseman&f="
#login_url="http://localhost/sites/admin/sys/index.php"
#download_url="http://localhost/sites/admin/sys/index.php?c=baseman&f="

logininfo_status () {
    echo $1
}
logininfo_user () {
    echo $2
}
logininfo_ukey () {
    echo $3
}

cd $1

# -- login ------------------
postdata="site=100&lang=de-at&area=public&comm=user_login&username=${3}&userpass=${4}"
response=$(wget --post-data="$postdata" -q --show-progress -O - $login_url | tr "|" " ")

status=$(logininfo_status $response)
userid=$(logininfo_user $response)
ukey=$(logininfo_ukey $response)

# -- check ------------------
if [ $status == "[OK]" ]
then
    postdata="site=100&lang=de-at&area=user&comm=user_download&user=${userid}&ukey=${ukey}"
    check=$(wget --post-data="$postdata" -q --show-progress -O - ${download_url}check_$2.tar.gz)
    if [ $check != "[OK]" ]
    then
        echo "DOWNLOAD FAILED! FILE NOT AVAILABLE! $check"
    fi
else
    echo "FALSE LOGIN: $x"
fi

# -- download ---------------
if [ $status == "[OK]" ] && [ $check == "[OK]" ]
then
    wget --post-data="$postdata" -q --show-progress -O $2.tar.gz.sig ${download_url}$2.tar.gz.sig
    wget --post-data="$postdata" -q --show-progress -O $2.tar.gz ${download_url}$2.tar.gz
fi
