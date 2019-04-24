package main

import (
	_ "cgi/routers"
	"github.com/astaxie/beego"
	"github.com/astaxie/beego/context"
)

func init() {
	var FilterNoCache = func(ctx *context.Context) {
		ctx.Output.Header("Cache-Control", "no-cache, no-store, must-revalidate")
		ctx.Output.Header("Pragma", "no-cache")
		ctx.Output.Header("Expires", "0")
	}

	beego.InsertFilter("/static/*", beego.BeforeStatic, FilterNoCache)
}

func main() {
	beego.BConfig.CopyRequestBody = true
	beego.Run()
}
