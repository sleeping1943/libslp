#!/bin/bash
#
#此程序用于在不同工程中创建rpm包时，
#修改~/.rpmmacros文件，使rpm包产生于该工程的RPMS目录中
#
#author  :  sleeping
#date    :  2016-05-12
#email   :  csleeping@163.com
#

#rpm包配置文件
rpm_conf=".rpmmacros"
if [ ! -f $HOME/$rpm_conf ];then
	echo -e "\033[0;032;031m文件$HOME/${rpm_conf}不存在！\033[m"	
	exit -1
fi

#rpm包输入路径
rpm_home=$(awk '$1 == "%_topdir" {printf $2}' $HOME/$rpm_conf)
echo -e "\033[0;032;032mThe rpm_home is :$rpm_home!\033[m"

if [ "$rpm_home" == "$PWD" ];then
	echo -e "\033[0;032;031mThe path rpm_home:$rpm_home is same as the PWD:$PWD!\033[m"
	exit 0
fi
#转义路径中的"/"
rpm_home=$(echo $rpm_home | sed 's/\//\\\//g')
echo -e "\033[0;032;032mThe rpm_home is :$rpm_home!\033[m"

#转义路径中的"/"为"\/"
cwd=$(echo $PWD | sed 's/\//\\\//g')
echo -e "\033[0;032;032mThe cwd is :$cwd!\033[m"

#使用eval在sed调用前替换掉参数
eval sed -in 's/$rpm_home/$cwd/g' $HOME/$rpm_conf
