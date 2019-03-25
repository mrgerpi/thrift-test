package controllers

import (
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
	/*
		c.Data["name"] = "WeiYafeng"
		c.TplName = "index.tpl"
	*/
}
func (c *UserController) Get() {
	c.Ctx.WriteString("user")
}

func (c *MainController) Get() {
	c.Data["Website"] = "beego.me"
	c.Data["Email"] = "astaxie@gmail.com"
	c.TplName = "index.tpl"
}
