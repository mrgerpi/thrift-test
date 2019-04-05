var vm = new Vue({
    el: "#submitData",
    data: {
        email: "",
        password: "",
        checked: false
    },
    methods: {
        "login": function () {
            var baseurl = "http://120.79.247.113:8080/static";
            axios.get(baseurl + "/user", {
                params: {
                    email: this.email,
                    password: this.password
                }
            })
            .then(function(response) {
                var res = JSON.stringify(response);
                console.log("res: " + res);
                console.log("response: " + JSON.parse(res));
            })
            .catch(function(error) {
                console.log("error: " + error)
            })
        }
    },
})