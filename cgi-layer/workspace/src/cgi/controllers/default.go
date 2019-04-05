package controllers

import (
	"fmt"
	"github.com/astaxie/beego"
)

type MainController struct {
	beego.Controller
}

type HelloController struct {
	beego.Controller
}

type UserController struct {
	beego.Controller
}

func (c *HelloController) Get() {
	c.Ctx.WriteString("helloWorld")
}
func (c *UserController) Get() {
	fmt.Println("hello User")
	email := c.GetString("email")
	password := c.GetString("password")
	beego.Informational("email: " + email)
	beego.Informational("password: " + password)
	c.Ctx.WriteString("user login")
}

func (c *MainController) Get() {
	c.Data["Website"] = "beego.me"
	c.Data["Email"] = "astaxie@gmail.com"
	c.TplName = "index.tpl"
}
