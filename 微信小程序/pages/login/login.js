//index.js
const app = getApp()

Page({
  data: {
    userName: "",
    userPwd: ""
  },
  //获取用户输入的用户名
  userNameInput: function (e) {
    this.setData({
      userName: e.detail.value
    })
  },
  passWdInput: function (e) {
    this.setData({
      userPwd: e.detail.value
    })
  },
  //获取用户输入的密码
  loginBtnClick: function (e) {
    var that = this;
    wx.request({
      url: 'http://192.168.1.101:8080/IAMSServer/LoginServlet',
      data: { "username": this.data.userName, "password": this.data.userPwd },
      method: "POST",
      header: {"content-type":"application/json"},
      success:function(res){
        console.log(res.data)
        if(res.data.resCode == 0){
          wx.showToast({
            title: '登录成功！', // 标题
            icon: 'success',  // 图标类型，默认success
            duration: 1500  // 提示窗停留时间，默认1500ms
          })
          wx.navigateTo({
            url: '../query/query',
          })
        }
        else{
          wx.showToast({
            title: '登录失败！', // 标题
            icon: 'warn',  // 图标类型，默认success
            duration: 1500  // 提示窗停留时间，默认1500ms
          })
        }
      }
    })
    console.log("用户名：" + this.data.userName + " 密码：" + this.data.userPwd);
  },
  
  // 用户点击右上角分享
  onShareAppMessage: function () {

  }
})