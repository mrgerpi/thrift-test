package dao

import (
	"github.com/astaxie/beego/logs"
	"github.com/astaxie/beego/orm"
	"strings"
	"unsafe"
)

func GetUserInfo(userName string) (*User, error) {
	log := logs.NewLogger()
	o := orm.NewOrm()
	var user User

	log.Debug("Sizeof(User{})= %d", unsafe.Sizeof(User{}))

	r := o.Raw("Select userId, userName, password from User where userName = ?", userName)
	err := r.QueryRow(&user)
	if err != nil {
		if strings.Compare(err.Error(), "<QuerySeter> no row found") == 0 {
			log.Error("GetUserInfo||user login failed, no user found")
			return nil, nil
		} else {
			log.Error("GetUserInfo||user login failed, db error")
			return nil, err
		}
	} else {
		return &user, nil
	}
}
