// pages/query/query.js
Page({
  data: {
    list: [],
    color: "#fe00332f",
    warntext: "正常",
    fantext: "OFF"
  },
  //风扇换挡
  queryBtnClick0: function (e) {
    var that = this;
    if (that.data.list.list[0].warn == 0){
      wx.request({
        url: 'http://192.168.1.101:8080/IAMSServer/SystemMode?mode=0',
        success: function (res) {
          wx.showToast({
            title: '关闭风扇！', // 标题
            icon: 'success',  // 图标类型，默认success
            duration: 800  // 提示窗停留时间，默认1500ms
          })
        }
      })
    }else{
      wx.showToast({
        title: '报警中不可操作！', // 标题
        icon: 'success',  // 图标类型，默认success
        duration: 800  // 提示窗停留时间，默认1500ms
      })
    }
  },
  queryBtnClick1: function (e) {
    var that = this;
    if (that.data.list.list[0].warn == 0) {
      wx.request({
        url: 'http://192.168.1.101:8080/IAMSServer/SystemMode?mode=1',
        success: function (res) {
          wx.showToast({
            title: '风扇一挡！', // 标题
            icon: 'success',  // 图标类型，默认success
            duration: 800  // 提示窗停留时间，默认1500ms
          })
        }
      })
    } else {
      wx.showToast({
        title: '报警中不可操作！', // 标题
        icon: 'success',  // 图标类型，默认success
        duration: 800  // 提示窗停留时间，默认1500ms
      })
    }
  },
  queryBtnClick2: function (e) {
    var that = this;
    if (that.data.list.list[0].warn == 0) {
      wx.request({
        url: 'http://192.168.1.101:8080/IAMSServer/SystemMode?mode=2',
        success: function (res) {
          wx.showToast({
            title: '风扇二挡！', // 标题
            icon: 'success',  // 图标类型，默认success
            duration: 800  // 提示窗停留时间，默认1500ms
          })
        }
      })
    } else {
      wx.showToast({
        title: '报警中不可操作！', // 标题
        icon: 'success',  // 图标类型，默认success
        duration: 800  // 提示窗停留时间，默认1500ms
      })
    }
  },
  queryBtnClick3: function (e) {
    var that = this;
    if (that.data.list.list[0].warn == 0) {
      wx.request({
        url: 'http://192.168.1.101:8080/IAMSServer/SystemMode?mode=3',
        success: function (res) {
          wx.showToast({
            title: '风扇三挡！', // 标题
            icon: 'success',  // 图标类型，默认success
            duration: 800  // 提示窗停留时间，默认1500ms
          })
        }
      })
    } else {
      wx.showToast({
        title: '报警中不可操作！', // 标题
        icon: 'success',  // 图标类型，默认success
        duration: 800  // 提示窗停留时间，默认1500ms
      })
    }
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this;
    setInterval(function () {
      //that.selectPageShufflingText();
      
      wx.request({
        url: 'http://192.168.1.101:8080/IAMSServer/ReadServlet',
        data: {},
        method: "POST",
        header: { "content-type": "application/json" },
        success: function (res) {
          console.log(res.data)
          that.setData({
            list: res.data
          })
          if (res.data.list[0].warn == 0) {
            that.setData({
              color: "#fe00332f",
              warntext: "正常"
            })
          }
          else if (res.data.list[0].warn == 3) {
            that.setData({
              color: "#fe0033",
              warntext: "亮度报警"
            })
          }
          else if (res.data.list[0].warn == 4) {
            that.setData({
              color: "#fe0033",
              warntext: "烟雾报警"
            })
          }
          else if (res.data.list[0].warn == 5) {
            that.setData({
              color: "#fe0033",
              warntext: "PM2.5报警"
            })
          }

          if (res.data.list[0].fan == 0) {
            that.setData({
              fantext: "OFF"
            })
          }
          else if (res.data.list[0].fan == 1) {
            that.setData({
              fantext: "ONE"
            })
          }
          else if (res.data.list[0].fan == 2) {
            that.setData({
              fantext: "TWO"
            })
          }
          else if (res.data.list[0].fan == 3) {
            that.setData({
              fantext: "THREE"
            })
          }
        }
      })
      //console.log("轮播请求1秒触发一次");
    }, 1000)    //代表1秒钟发送一次请求
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {
    var that = this;
    wx.showNavigationBarLoading()
    wx.request({
      url: 'http://192.168.1.101:8080/IAMSServer/ReadServlet',
      data: {},
      method: "POST",
      header: { "content-type": "application/json" },
      success: function (res) {
        console.log(res.data)
        that.setData({
          list: res.data
        })
      }
    })
    wx.hideNavigationBarLoading()
    wx.stopPullDownRefresh()
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})