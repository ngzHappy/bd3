; /*!searchresult:widget/ui/app/pagemodel.js*/
define('searchresult:widget/ui/app/pagemodel', function (e) {
  function n() {
    r.apply(this, arguments)
  }
  var t = e('common:widget/ui/base/base'),
  o = e('common:widget/ui/utils/utils'),
  r = e('common:widget/ui/arch/pagemodel');
  return t.extend(n.prototype, r.prototype, {
    load: function () {
      r.prototype.load.call(this);
      var e = t.extend({
      }, this.uri.query.getAll(), this.uri.hash.getAll());
      for (var n in e) e.hasOwnProperty(n) && e[n] && (e[n] = o.tryDecodeURIComponent(e[n]));
      e.pn = 1 * (e.pn || 0),
      e.spn && (e.spn = 1 * (e.spn || 0)),
      e.pn < 0 && e.spn < 0 && (e.spn = 0),
      this.set(e)
    },
    parseHash: function (e) {
      var n = {
      };
      if (e) {
        var n = o.decodeJsonForQuery(o.queryToJson(e, !0));
        if ('undefined' == typeof n.pn) {
          var t,
          r = e.split('&'),
          i = /(pn|di|objURL|fromURLW|H|S|TP)(.*)/;
          n = {
          };
          for (var p = 0; p < r.length; p++) t = r[p].match(i),
          t && t.length && (n[t[1]] = o.escapeHTML(o.tryDecodeURIComponent(t[2] || '')), 'pn' == t[1] && (n.spn = o.escapeHTML(o.tryDecodeURIComponent(r[p + 1] || 0))))
        }
      }
      return n
    },
    getCurrentPageSize: function () {
      var e = t(window);
      return {
        viewW: Math.max(600, e.width() - 85),
        viewH: e.height()
      }
    }
  }),
  new n
});
; /*!searchresult:widget/ui/app/history.js*/
define('searchresult:widget/ui/app/history', function (t) {
  function e(t) {
    s.apply(this),
    this.pageModel = t,
    this._isLockUrl = !1,
    this._lockedState = null
  }
  var i = t('common:widget/ui/base/base'),
  s = t('common:widget/ui/arch/history');
  return i.extend(e.prototype, s.prototype, {
    urlParamKeys: {
      ct: 'ct',
      z: 'z',
      s: 's',
      tn: 'tn',
      ipn: 'ipn',
      word: 'word',
      step_word: 'step_word',
      pn: 'pn',
      istype: 'istype',
      ie: 'ie',
      oe: 'oe',
      cl: 'cl',
      lm: 'lm',
      st: 'st',
      ln: 'ln',
      fr: 'fr',
      fmq: 'fmq',
      ic: 'ic',
      se: 'se',
      sme: 'sme',
      width: 'width',
      height: 'height',
      face: 'face'
    },
    hashParamKeys: {
      step_word: 'step_word',
      pn: 'pn',
      spn: 'spn',
      di: 'di',
      pi: 'pi',
      stepWord: 'stepWord',
      objurl: 'objurl',
      fromurl: 'fromurl',
      width: 'imgData.width',
      height: 'imgData.height',
      S: 'imgData.filesize',
      TP: 'imgData.type'
    },
    init: function () {
      s.prototype.init.call(this),
      this.pageModel.addEventListener('changed', this._pageModelChangedHandler.bind(this))
    },
    lockState: function () {
      this._isLockUrl = !0
    },
    unlockState: function () {
      this._isLockUrl = !1,
      this._lockedState && (this.forward(this._lockedState), this._lockedState = null)
    },
    forward: function (t) {
      this._popState || (this._isLockUrl ? this._lockedState = t : s.prototype.forward.call(this, t))
    },
    buildStateParams: function (t) {
      var e,
      i = this.pageModel,
      s = {
      };
      for (var a in t) t.hasOwnProperty(a) && (e = i.get(t[a] || a), 'undefined' != typeof e && (s[a] = null == e ? '' : e));
      return s
    },
    _pageModelChangedHandler: function (t) {
      for (var e = t.keys, i = this.urlParamKeys, s = e.length - 1; s >= 0; s--) if ('undefined' != typeof i[e[s]]) {
        this.forward(this.buildStateParams(this.supportPushState ? this.urlParamKeys : this.hashParamKeys));
        break
      }
    }
  }),
  e
});
; /*!searchresult:widget/ui/utils/lib.js*/
define('searchresult:widget/ui/utils/lib', function (e) {
  var t = e('common:widget/ui/base/base'),
  n = function () {
    var e = {
      w: 'a',
      k: 'b',
      v: 'c',
      1: 'd',
      j: 'e',
      u: 'f',
      2: 'g',
      i: 'h',
      t: 'i',
      3: 'j',
      h: 'k',
      s: 'l',
      4: 'm',
      g: 'n',
      5: 'o',
      r: 'p',
      q: 'q',
      6: 'r',
      f: 's',
      p: 't',
      7: 'u',
      e: 'v',
      o: 'w',
      8: '1',
      d: '2',
      n: '3',
      9: '4',
      c: '5',
      m: '6',
      0: '7',
      b: '8',
      l: '9',
      a: '0',
      _z2C$q: ':',
      '_z&e3B': '.',
      AzdH3F: '/'
    },
    t = /([a-w\d])/g,
    n = /(_z2C\$q|_z&e3B|AzdH3F)/g;
    return {
      compile: function (e) {
        if (!e) return '';
        for (var t = (e.charCodeAt(0) + e.length).toString(16), n = 1; n < e.length; n++) t += 'g' + (e.charCodeAt(n) + e.charCodeAt(n - 1)).toString(16);
        return t
      },
      uncompile: function (r) {
        if (!r) return '';
        var o = r.replace(n, function (t, n) {
          return e[n]
        });
        return o.replace(t, function (t, n) {
          return e[n]
        })
      },
      uncompileURL: function (e) {
        return /^(http|https)/.test(e) ? e : this.uncompile(e)
      }
    }
  }(),
  r = function () {
    var e = [
      'a',
      'c',
      'e',
      'g',
      'i',
      'k',
      'z',
      'b',
      'w',
      'o'
    ];
    return {
      encodeTime: function (t) {
        for (var n = t + '', r = '', o = 0, i = n.length; i > o; o++) r += e[parseInt(n.charAt(o), 10)];
        return r
      }
    }
  }(),
  o = t.extend({
    getBaiduId: function (e) {
      var n = t.cookie('BAIDUID');
      return n && (e ? n.substr(0, e)  : n)
    },
    getHost: function (e) {
      var t = e.match(/^(https?:\/\/[^\/]+)(\/|$)/i);
      return t && t.length && t[1]
    },
    getUniqId: function () {
      var e = 0,
      t = 'imgdetailpg_';
      return function (n) {
        return (n || t) + ++e
      }
    }(),
    parseResponse: function (e) {
      if ('string' == typeof e) try {
        e = t.json.parse(t.trim(e))
      } catch (n) {
        e = null
      }
      return e
    },
    getRedirectUrl: function (e) {
      var t = Math.round((new Date).getTime() / 1000);
      return '/search/redirect?tn=redirect&word=j&juid=' + encodeURIComponent(o.getBaiduId(6)) + '&sign=' + encodeURIComponent(o.encodeTime(t)) + '&url=' + encodeURIComponent(e)
    },
    logTime: function (e, t, n, r) {
      r = r || 'http://webclick.baidu.com/';
      var o,
      i = r + '6.gif?for=detailtime&hostfr=imgstat&_dev=pc';
      o = window[n] = new Image,
      o.onload = o.onerror = function () {
        o.onload = o.onerror = null,
        o = null,
        window[n] = null
      },
      o.src = i + '&type=' + e + '&totaltime=' + (n - t) + '&' + new Date * Math.random()
    }
  }, n, r);
  return o
});
; /*!searchresult:widget/ui/app/sizemanager.js*/
define('searchresult:widget/ui/app/sizemanager', function (e) {
  var i = e('common:widget/ui/base/base'),
  t = (e('common:widget/ui/utils/utils'), e('common:widget/ui/base/subject')),
  n = {
  };
  return i.extend(n, t, {
    elements: {
      wrapper: '#imgid'
    },
    init: function () {
      var e = this.elements;
      for (var t in e) e.hasOwnProperty(t) && (this.elements[t] = i(e[t]))
    },
    update: function () {
      {
        var e = i(window);
        e.width(),
        e.height(),
        this.elements
      }
      this.notify()
    }
  }),
  n
});
; /*!searchresult:widget/ui/utils/scroller.js*/
define('searchresult:widget/ui/utils/scroller', function (i) {
  var t = i('common:widget/ui/base/base'),
  n = i('common:widget/ui/base/events'),
  s = {
    _timer: null,
    _isInit: !1,
    _lastNotifyTime: - 1,
    _lastCheckTime: - 1,
    _scrollTop: 0,
    _isRunning: !1,
    tick: 0,
    duration: 0,
    init: function (i) {
      var n = t.extend({
        tick: 200,
        duration: 400
      }, i);
      return this._isInit ? this : (this.tick = n.tick, this.duration = n.duration, this._isInit = !0, this)
    },
    isInited: function () {
      return this._isInit
    },
    start: function () {
      this._isRunning || (t(window).bind('scroll', this.scrolling), this._isRunning = !0)
    },
    stop: function () {
      t(window).unbind('scroll', this.scrolling),
      this._isRunning = !1
    },
    scrolling: function () {
      var i = new Date;
      s._timer ? ( - 1 != s._lastCheckTime && i - s._lastCheckTime >= s.tick / 2 && (clearTimeout(s._timer), s._timer = setTimeout(s.scrollFinished, s.tick), s._lastCheckTime = i), - 1 != s._lastNotifyTime && i - s._lastNotifyTime >= s.duration && s.notifyScrolling(i))  : (s.dispatchEvent('scrollBegin'), s._timer = setTimeout(s.scrollFinished, s.tick), s._lastNotifyTime = i, s._lastCheckTime = i)
    },
    scrollFinished: function () {
      s.notifyScrolling(),
      s.emit('scrollEnd'),
      s._lastNotifyTime = - 1,
      s._timer = null
    },
    notifyScrolling: function (i) {
      this.emit('scrolling'),
      this._lastNotifyTime = i
    },
    emit: function (i) {
      var n = t(window).scrollTop();
      this.dispatchEvent(i, {
        scrollTop: n,
        scrollingDown: n > this._scrollTop
      }),
      this._scrollTop = n
    }
  };
  return t.extend(s, n),
  s
});
; /*!searchresult:widget/ui/utils/utils.js*/
define('searchresult:widget/ui/utils/utils', function (t) {
  var e = t('common:widget/ui/base/base'),
  n = 360,
  r = 100,
  i = function () {
    var t = {
      w: 'a',
      k: 'b',
      v: 'c',
      1: 'd',
      j: 'e',
      u: 'f',
      2: 'g',
      i: 'h',
      t: 'i',
      3: 'j',
      h: 'k',
      s: 'l',
      4: 'm',
      g: 'n',
      5: 'o',
      r: 'p',
      q: 'q',
      6: 'r',
      f: 's',
      p: 't',
      7: 'u',
      e: 'v',
      o: 'w',
      8: '1',
      d: '2',
      n: '3',
      9: '4',
      c: '5',
      m: '6',
      0: '7',
      b: '8',
      l: '9',
      a: '0',
      _z2C$q: ':',
      '_z&e3B': '.',
      AzdH3F: '/'
    },
    n = /([a-w\d])/g,
    r = /(_z2C\$q|_z&e3B|AzdH3F)/g;
    return {
      compile: function (t) {
        if (!t) return '';
        for (var e = (t.charCodeAt(0) + t.length).toString(16), n = 1; n < t.length; n++) e += 'g' + (t.charCodeAt(n) + t.charCodeAt(n - 1)).toString(16);
        return e
      },
      uncompile: function (e) {
        if (!e) return '';
        var i = e.replace(r, function (e, n) {
          return t[n]
        });
        return i.replace(n, function (e, n) {
          return t[n]
        })
      },
      uncompileURL: function (t) {
        return /^(http|https)/.test(t) ? t : this.uncompile(t)
      },
      trimTags: function (t, n) {
        var r = '';
        return n && n.length && (r = function (t, r) {
          return e.inArray(r, n) < 0 ? '' : t
        }),
        String(t).replace(/<\/?([^>]*)>/g, r)
      }
    }
  }(),
  o = function () {
    var t = [
      'a',
      'c',
      'e',
      'g',
      'i',
      'k',
      'z',
      'b',
      'w',
      'o'
    ];
    return {
      encodeTime: function (e) {
        for (var n = e + '', r = '', i = 0, o = n.length; o > i; i++) r += t[parseInt(n.charAt(i), 10)];
        return r
      }
    }
  }(),
  a = e.extend({
    format: function (t, e) {
      t = String(t);
      var n = Array.prototype.slice.call(arguments, 1),
      r = Object.prototype.toString;
      return n.length ? (n = 1 == n.length && null !== e && /\[object Array\]|\[object Object\]/.test(r.call(e)) ? e : n, t.replace(/#\{(.+?)\}/g, function (t, e) {
        var i = n[e];
        return '[object Function]' == r.call(i) && (i = i(e)),
        'undefined' == typeof i ? '' : i
      }))  : t
    },
    decodeURIComponent: function (t) {
      try {
        return decodeURIComponent(t)
      } catch (e) {
        return t
      }
    },
    trim: function (t) {
      if ('string' == typeof t) return t.replace(/^\s*|\s*$/g, '');
      if ('object' == typeof t) {
        for (var e in t) t[e] = a.trim(t[e]);
        return t
      }
      return t
    },
    query2Json: function (t) {
      if (null == t || 'string' != typeof t) return t;
      for (var e = {
      }, n = t.split('&'), r = 0, i = n.length; i > r; r++) {
        var o = n[r].split('=');
        e[o[0]] = o[1]
      }
      return e
    },
    json2Query: function (t) {
      if (null == t || 'object' != typeof t) return t;
      var e = [
      ];
      for (var n in t) '' != n && (e[e.length] = n + '=' + t[n]);
      return e.join('&')
    },
    zoom: function (t, e, n) {
      t = t || 140,
      e = e || 140,
      n = Math.min(Math.max(t, e), n);
      var r = n / t,
      i = n / e,
      o = e,
      a = t;
      return i > r ? (a = n, o = e * r)  : (a = t * i, o = n),
      {
        width: a,
        height: o
      }
    },
    zoomLimit: function (t, e, n, r) {
      var i = this.zoom(t, e, n),
      o = i.width,
      a = i.height;
      return r > 0 && r > o && (o = r, a = a * o / i.width),
      {
        width: parseInt(o),
        height: parseInt(a)
      }
    },
    zoomByHeightLimit: function (t, e, i, o, a) {
      o = o || n,
      a = a || r,
      (0 == t || 0 == e) && (t = e = o);
      var h = e,
      f = this.zoomByHeight(t, e, i);
      if (f.width > t || f.width > o || f.width < a) {
        var u = Math.min(o, Math.max(a, f.width));
        i = Math.min(e * u / t, i),
        h = i,
        t = u
      } else t = f.width,
      h = f.height;
      return {
        width: parseInt(t),
        height: parseInt(h)
      }
    },
    setMaxWidthLimit: function (t) {
      n = t || 360
    },
    zoomByHeight: function (t, e, n) {
      return (0 == t || 0 == e) && (t = e = 220),
      n > e ? (n = Math.min(e, n), t = n * t / e)  : t = n * t / e,
      {
        width: parseInt(t),
        height: parseInt(n)
      }
    },
    str2dom: function () {
      var t;
      return function (e) {
        return e ? (t || (t = document.createElement('div')), t.innerHTML = e, t.childNodes[0])  : !1
      }
    }(),
    zoomLi: function (t, e) {
      var i = t.width || t.width || 140,
      o = t.height || t.height || 140;
      return maxWidth = t.maxWidth || n,
      minWidth = t.minWidth || r,
      2 === t.hasLarge ? this.zoomLimit(i, o, maxWidth, minWidth)  : this.zoomByHeightLimit(i, o, e)
    },
    zoomLiIE6: function (t) {
      var e = t.width || t.width || 140,
      n = t.height || t.height || 140;
      maxWidth = t.maxWidth || 140,
      minWidth = t.minWidth || 130;
      var r;
      return r = e > 1.15 * n && 0 === t.hasLarge ? this.zoomLimit(e, n, 220, 145)  : this.zoomLimit(e, n, 140, 130)
    },
    zoomImg: function (t, e) {
      var r,
      e = e || n;
      return 2 === t.hasLarge ? r = this.zoom(t.width, t.height, 140)  : (r = this.zoomByHeight(t.width, t.height, Math.min(t.lineH, t.height)), r = this.zoom(r.width, r.height, e)),
      r
    },
    zoomLimitMax: function (t, e, n, r) {
      (isNaN(t) || 1 > t) && (t = n),
      (isNaN(e) || 1 > e) && (e = r);
      var i,
      o,
      a,
      h;
      return t >= e ? (i = Math.min(t, n), o = i * e / t)  : (o = Math.min(e, r), i = o * t / e),
      a = (n - i) / 2,
      h = (r - o) / 2,
      {
        width: parseInt(i),
        height: parseInt(o),
        left: parseInt(a),
        top: parseInt(h)
      }
    },
    zoomImgIE6: function (t) {
      var e,
      n = parseInt(t.lwidth);
      return e = 2 === t.hasLarge ? this.zoom(t.width, t.height, 140)  : t.width >= t.height ? n > 190 ? this.zoom(t.width, t.height, 220)  : n > 150 ? this.zoom(t.width, t.height, 170)  : this.zoom(t.width, t.height, 140)  : this.zoomByHeight(t.width, t.height, 170)
    },
    getOffsetTop: function (t) {
      var e = 0;
      return e = t.offsetTop,
      t.offsetParent && t.offsetParent != t && 'BODY' != t.offsetParent.nodeName && (e += this.getOffsetTop(t.offsetParent)),
      e
    },
    getOffsetLeft: function (t) {
      var e = 0;
      return e = t.offsetLeft,
      t.offsetParent && t.offsetParent != t && 'BODY' != t.offsetParent.nodeName && (e += this.getOffsetLeft(t.offsetParent)),
      e
    },
    getParentNode: function (t, e) {
      var n = t;
      for (e = e.toLowerCase(); n && n.nodeName.toLowerCase() != e && 'BODY' != n.nodeName; ) n = n.parentNode;
      return n && 'BODY' != n.nodeName || (n = null),
      n
    },
    escapeXSS: function (t) {
      return t.replace(/[<>]/g, function (t) {
        return encodeURIComponent(t)
      }).replace(/"/g, '%22').replace(/'/g, '%27')
    },
    escapeHTML: function (t) {
      return t ? ('' + t).replace(/&/g, '&amp;').replace(/>/g, '&gt;').replace(/</g, '&lt;').replace(/"/g, '&#34;').replace(/'/g, '&#39;')  : ''
    },
    fmqValueSet: function () {
      var t = new Date;
      return function () {
        var e = a.query2Json(a.escapeXSS(window.location.search.substring(1))),
        n = t.getTime();
        if ('undefined' == typeof e.fmq && (e.fmq = ''), void 0 == e.fmq || '' == e.fmq) e.fmq = n + '_R';
         else if (e.fmq.indexOf('m') > - 1 && - 1 == e.fmq.indexOf('_m') && - 1 == e.fmq.indexOf('_R')) {
          var r = e.fmq;
          e.fmq = n + '_' + r + '_R'
        } else if ( - 1 == e.fmq.indexOf('_R')) {
          var r = e.fmq;
          e.fmq = r + '_R'
        }
        return e.fmq
      }
    }(),
    zoomImageLimitMin: function (t, e, n, r) {
      var i,
      o,
      a,
      h;
      return t / e >= n / r ? (o = r, i = o * t / e)  : (i = n, o = i * e / t),
      a = (n - i) / 2,
      h = (r - o) / 2,
      {
        width: parseInt(i),
        height: parseInt(o),
        left: parseInt(a),
        top: parseInt(h)
      }
    },
    getBaiduId: function (t) {
      var n = e.cookie('BAIDUID');
      return n && (t ? n.substr(0, t)  : n)
    },
    getHost: function (t) {
      var e = t.match(/^(https?:\/\/[^\/]+)(\/|$)/i);
      return e && e.length && e[1]
    },
    getUniqId: function () {
      var t = 0,
      e = 'imgdetailpg_';
      return function (n) {
        return (n || e) + ++t
      }
    }(),
    parseResponse: function (t) {
      if ('string' == typeof t) try {
        t = e.json.parse(e.trim(t))
      } catch (n) {
        t = null
      }
      return t
    },
    getRedirectUrl: function (t) {
      var e = Math.round((new Date).getTime() / 1000);
      return '/search/redirect?tn=redirect&word=j&juid=' + encodeURIComponent(a.getBaiduId(6)) + '&sign=' + encodeURIComponent(a.encodeTime(e)) + '&url=' + encodeURIComponent(t)
    },
    logTime: function (t, e, n, r) {
      r = r || 'http://webclick.baidu.com/';
      var i,
      o = r + '6.gif?for=detailtime&hostfr=imgstat&_dev=pc';
      i = window[n] = new Image,
      i.onload = i.onerror = function () {
        i.onload = i.onerror = null,
        i = null,
        window[n] = null
      },
      i.src = o + '&type=' + t + '&totaltime=' + (n - e) + '&' + new Date * Math.random()
    }
  }, i, o);
  return a
});
; /*!searchresult:widget/ui/statistic/statistic.js*/
define('searchresult:widget/ui/statistic/statistic', function (t, e, r) {
  {
    var s = t('common:widget/ui/base/base'),
    n = (t('common:widget/ui/EventEmitter/EventEmitter'), t('common:widget/ui/monitorRequest/monitorRequest')),
    a = t('searchresult:widget/ui/app/pagemodel'),
    i = t('searchresult:widget/ui/utils/utils'),
    o = t('common:widget/ui/utils/utils');
    t('common:widget/ui/base/events'),
    r.exports = function () {
      function t(t, e, n) {
        var o = pe + '1.gif',
        u = {
        };
        'undefined' == typeof e.sr && (e.sr = ''),
        u.p = e.p,
        '2' == n.button && (u.p = 496),
        u.sr = e.sr,
        u.fmq = void 0 == a.data.fmq ? i.fmqValueSet()  : a.data.fmq,
        a.data.fm && (u.fm = a.data.fm),
        a.data.oriquery && (u.oriquery = a.data.oriquery),
        u.q = a.data.word,
        u.hostfr = 'imgstat',
        u.cl = a.data.cl || '',
        u.pv = a.data.pv || '',
        u.x = screen.width + 'x' + screen.height,
        u.s = a.data.s || '',
        1 === e.asp && (u.asp = 1),
        u.tabindex = he;
        var d = e.u,
        p = i.uncompile(e.f);
        if (u.u = encodeURIComponent(d), u.t = e.t, u.f = encodeURIComponent(p), u.ist = e.ist, u.rts = e.rts, 1 == u.p && t.href) {
          var f = s.cookie.get('BAIDUID'),
          q = Math.round((new Date).getTime() / 1000);
          q = i.encodeTime(q),
          f = f ? f.substring(0, 6)  : '',
          t.href = '/search/redirect?tn=redirect&ipn=rdt&word=j&juid=' + encodeURIComponent(f) + '&sign=' + encodeURIComponent(q) + '&url=' + encodeURIComponent(p)
        }
        if ( - 1 == u.fmq.indexOf('_D_R') && - 1 == u.fmq.indexOf('_R_D') && me && 0 == e.p && (u.ict = (new Date).getTime() - me, me = 0), 10 == e.sr) {
          var y = {
            w: '',
            h: '',
            s: '',
            t: '',
            id: '',
            cs: '',
            pn: e.pn,
            lm: a.data.lm || '',
            z: a.data.z || ''
          };
          for (var m in y) u[m] = y[m]
        } else try {
          r(t, u)
        } catch (n) {
        }
        return u.cs = e.cs || 0,
        a.data.isseed && (u.isseed = 1),
        u.personalized = e.personalized ? e.personalized : '',
        e.pn && (u.pn = e.pn),
        e.isset && (u.isset = e.isset),
        u.fr = a.get('fr') || '',
        {
          host: o,
          query: u,
          isAsyn: !1
        }
      }
      function e() {
      }
      function r(t, e) {
        var r = t.name,
        s = 'f' + r,
        n = document.getElementById(s);
        u(n, e);
        for (var a = document.getElementsByName(r), i = 0, o = a.length; o > i; i++) {
          var f = a[i],
          q = f.nodeName.toLowerCase(),
          y = f.href;
          'a' == q && /word=/.test(y) ? d(f, e)  : 'a' == q && /jn=/.test(y) && p(f, e)
        }
      }
      function u(t, e) {
        if (null != t) {
          var r,
          s,
          n,
          a,
          i,
          o,
          u,
          d,
          p = t.innerHTML.replace(/(^\s*)|(\s*$)/g, ''),
          f = p.split(' ');
          if (3 == f.length) {
            var q = f[0].split('x');
            r = q[0],
            s = q[1],
            n = f[1].substring(0, f[1].length - 1),
            a = f[2]
          } else 4 == f.length && (i = f[0], o = f[1], u = f[2], d = f[3]);
          e.w = r || i || '',
          e.h = s || o || '',
          e.s = n || u || '',
          e.lm = a || d || ''
        }
      }
      function d(t, e) {
        for (var r = t.childNodes, s = null, n = 0, a = r.length; a > n; n++) {
          var o = r[n];
          if ('img' == o.nodeName.toLowerCase()) {
            s = o;
            break
          }
        }
        var u = t.href,
        d = s.src,
        p = u.substring(u.indexOf('?') + 1, u.length),
        f = '';
        f = - 1 == d.indexOf('?') ? d.substring(d.lastIndexOf('/') + 1, d.length)  : d.substring(d.indexOf('?') + 1, d.length);
        var q = i.query2Json(p),
        y = i.query2Json(f);
        e.q = q.word || '',
        e.qs = i.fmqValueSet(),
        e.id = q.di || '',
        e.pn = q.pn || '',
        e.z = q.z || '',
        e.cs = y.u || ''
      }
      function p(t, e) {
        var r = t.href,
        s = r.substring(r.indexOf('?') + 1, r.length),
        n = i.query2Json(s);
        e.u = n.u || '',
        e.f = n.f || '',
        e.t = n.t || ''
      }
      function f(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        29 == n ? (s.vtime = e.vtime, s.pn = e.pn, s.cs = e.cs || '', s.u = encodeURIComponent(e.u), s.f = encodeURIComponent(e.f || ''), {
          host: r,
          query: s,
          isAsyn: !1
        })  : 2 == n ? {
          host: r,
          query: s,
          isAsyn: !1
        }
         : {
          host: r,
          query: s,
          isAsyn: !0
        }
      }
      function q(t, e) {
        var r = pe + '1.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.zt = e.zt,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function y(t, e) {
        var r = a.data;
        'undefined' != typeof ge.pageTurnIndex && (r.n = ge.pageTurnIndex);
        var n = s.cookie('fb');
        return r.fb = n ? 1 : 0,
        r.pn = void 0 === e.pn ? '' : e.pn,
        r.t = 1,
        r.qs = i.fmqValueSet(),
        r.hostfr = 'imgstat',
        r.tn = 'baiduimage',
        r.imgN = e.imgN,
        {
          host: fe,
          query: r,
          isAsyn: !1
        }
      }
      function m(t, e) {
        var r = pe + '2.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.r = e.r || '',
        s.rq = e.rq || '',
        s.tp = e.tp || '',
        s.ps = e.ps || '',
        s.pagepos = e.pagepos || '',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function g(t, e) {
        var r = pe + '9.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.length = e.length,
        s.content = e.content,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.r = e.r || '',
        s.rq = e.rq || '',
        s.tp = e.tp || '',
        s.ps = e.ps || '',
        s.pagepos = e.pagepos || '',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function c(t, e) {
        var r = pe + '2.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.r = e.r || '',
        s.rq = e.rq || '',
        s.tp = e.tp || '',
        s.ps = e.ps || '',
        s.etc = 'tops',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function h(t, e) {
        var r = pe + '2.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.r = e.r || '',
        s.rq = e.rq || '',
        s.tp = e.tp || '',
        s.ps = e.ps || '',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function l(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.ic = e.ic || '0',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function w(t, e) {
        var r = pe + '4.gif',
        n = a.data,
        o = {
        };
        s.extend(o, n),
        delete o.word;
        var u = e.p,
        d = s(window).scrollTop();
        return o.filterpos = d > 50 ? 'pull' : 'top',
        o.p = u,
        o.currf = e.currf,
        o.onnum = e.onnum,
        o.pt = 'pull',
        o.q = a.data.word,
        o.hostfr = 'imgstat',
        o.qs = i.fmqValueSet(),
        o.fb = 'undefined' == typeof e.fb || null == e.fb ? '' : e.fb,
        {
          host: r,
          query: o,
          isAsyn: !1
        }
      }
      function v(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.out = e.out,
        s.pn = e.pn || a.data.pn,
        s.times = e.times || - 1,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function A(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.qs = i.fmqValueSet(),
        s.err = e.err,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function b(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.wpaperTab = e.wpaperTab,
        s.q = a.data.word,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function S(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.wpsizeType = e.wpsizeType,
        s.q = a.data.word,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function V(t, e) {
        var r = pe + '1.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.qs = i.fmqValueSet(),
        s.url = e.url,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function T(t, e) {
        var r = pe + '1.gif',
        s = {
        },
        n = e.p;
        return isNaN(parseInt(e.showTime)) && (e.showTime = - 2),
        s.p = n,
        s.index = e.index,
        s.po = e.po,
        s.showTime = e.showTime,
        s.type = e.type,
        s.action = e.action,
        s.qs = i.fmqValueSet(),
        s.url = encodeURIComponent(e.url),
        s.imgN = e.imgN || - 1,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function x(t, e) {
        var r = pe + '1.gif',
        s = {
        },
        n = e.p;
        return isNaN(parseInt(e.showTime)) && (e.showTime = - 2),
        s.p = n,
        s.index = e.index,
        s.pn = e.pn,
        s.po = e.po,
        s.showTime = e.showTime,
        s.type = e.type,
        s.action = e.action,
        s.qs = i.fmqValueSet(),
        s.url = encodeURIComponent(e.url),
        s.imgN = e.imgN || - 1,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function I(t, e) {
        var r,
        s = pe + '1.gif',
        n = {
        },
        o = e.p;
        return r = isNaN(parseInt(e.showTime)) ? - 2 : e.showTime,
        n.p = o,
        n.qs = i.fmqValueSet(),
        n.url = encodeURIComponent(e.url),
        n.pos = e.pos,
        n.action = e.action,
        n.type = e.type,
        n.showTime = r,
        n.q = a.data.word,
        n.hostfr = 'imgstat',
        {
          host: s,
          query: n,
          isAsyn: !1
        }
      }
      function N(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.qs = i.fmqValueSet(),
        s.saved = e.saved,
        s.pn = e.pn,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.cs = e.cs,
        s.u = e.u,
        s.f = e.f,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function D(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.qs = i.fmqValueSet(),
        s.saved = e.saved,
        s.pn = e.pn,
        s.q = a.data.word,
        s.hostfr = 'imgstat',
        s.cs = e.cs,
        s.u = e.u,
        s.f = e.f,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function C(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.etc = void 0 !== e.etc ? e.etc : '',
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function R(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.type = e.type,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function U(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.type = e.type,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.tprn = e.tprn,
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function z(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.type = e.type,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function E(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.type = e.type,
        s.g = e.g,
        s.l = e.l,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function k(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.type = e.type,
        s.g = e.g,
        s.l = e.l,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function O(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.type = e.type,
        s.g = e.g,
        s.l = e.l,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function W(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.type = e.type,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function P(t, e) {
        var r = pe + '4.gif',
        s = {
        },
        n = e.p;
        return s.p = n,
        s.hostfr = 'imgstat',
        s.qs = i.fmqValueSet(),
        s.q = a.data.word,
        s.to = e.to,
        e.isAsyn && t ? {
          host: r,
          query: s,
          isAsyn: !0
        }
         : {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function j(t, e) {
        var r = pe + '4.gif',
        n = {
        },
        o = e.p;
        return s.extend(n, e),
        n.p = o,
        n.qs = i.fmqValueSet(),
        n.q = a.data.word,
        n.hostfr = 'imgstat',
        {
          host: r,
          query: n,
          isAsyn: !1
        }
      }
      function B(t, e) {
        var r = pe + '5.gif',
        s = {
        };
        return s.p = '12',
        s.qs = i.fmqValueSet(),
        s.tp = '2',
        s.click = 'hotq',
        s.keyb = '',
        s.word = ce,
        s.hotq = e.hotq,
        s.hostfr = 'imgstat',
        {
          host: r,
          query: s,
          isAsyn: !0
        }
      }
      function _(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.reachbottom = e.reachbottom,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function F(t, e) {
        var r = pe + '4.gif',
        n = {
        };
        return s.extend(n, e),
        n.p = e.p,
        n.q = a.data.word,
        n.fr = e.fr || '',
        a.data.isseed && (n.isseed = 1),
        a.data.fm && (n.fm = a.data.fm),
        a.data.oriquery && (n.oriquery = a.data.oriquery),
        {
          host: r,
          query: n,
          isAsyn: !1
        }
      }
      function L(t, e) {
        var r = pe + '3.gif',
        n = {
        };
        return s.extend(n, e),
        n.format = e.format,
        n.cs = e.cs,
        n.pn = e.pn,
        n.q = a.data.word,
        n.personalized = e.personalized,
        {
          host: r,
          query: n,
          isAsyn: !1
        }
      }
      function J(t, e) {
        var r = pe + '4.gif',
        n = {
        };
        return s.extend(n, e),
        n.p = e.p,
        n.q = a.data.word,
        {
          host: r,
          query: n,
          isAsyn: e.isAsyn === !0
        }
      }
      function H(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.p = e.p,
        s.q = a.data.word,
        s.rtt = e.rtt || '',
        s.bw1 = e.bw1 || '',
        s.bw2 = e.bw2 || '',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function M(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.p = e.p,
        s.pn = e.pn,
        s.u = e.u,
        s.q = a.data.word,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function G(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.p = e.p,
        s.q = a.data.word,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function K(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.p = e.p,
        s.type = e.type || '',
        s.action = e.action || '',
        s.pos = e.pos || '',
        s.q = a.data.word,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function Q(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.p = e.p,
        s.q = a.data.word,
        s.imgN = e.imgN || '',
        s.retN = e.retN || '',
        s.state = e.state || '',
        s.tm = e.tm || '',
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function $(t, e) {
        var r = pe + '5.gif',
        n = {
        };
        return s.extend(n, e),
        n.p = e.p,
        n.q = a.data.word,
        {
          host: r,
          query: n,
          isAsyn: e.isAsyn === !0
        }
      }
      function X(t, e) {
        var r = pe + '4.gif',
        n = {
        };
        return s.extend(n, e),
        n.p = e.p,
        n.q = a.data.word,
        {
          host: r,
          query: n,
          isAsyn: !1
        }
      }
      function Y(t, e) {
        var r = pe + '10.gif',
        n = {
        };
        return s.extend(n, e),
        n.p = e.p,
        n.q = a.data.word,
        n.timestamp = + new Date,
        {
          host: r,
          query: n,
          isAsyn: !1
        }
      }
      function Z(t, e) {
        var r = pe + '10.gif',
        n = {
        };
        return s.extend(n, e),
        n.p = e.p,
        n.q = a.data.word,
        {
          host: r,
          query: n,
          isAsyn: !1
        }
      }
      function te(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.p = e.p,
        s.fm = e.fm,
        s.pos = e.pos,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function ee(t, e) {
        var r = pe + '4.gif';
        return {
          host: r,
          query: e,
          isAsyn: !1
        }
      }
      function re(t, e) {
        var r = pe + '16.gif',
        n = {
        };
        return s.extend(n, e),
        n.p = e.p,
        {
          host: r,
          query: n,
          isAsyn: !1
        }
      }
      function se(t, e) {
        var r = pe + '3.gif',
        s = {
        };
        return s.oriquery = e.oriquery,
        s.rstr = e.rstr,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function ne(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.s = e.s,
        s.p = e.p,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function ae(t, e) {
        var r = pe + '4.gif',
        s = {
        };
        return s.p = e.p,
        s.q = a.data.word,
        {
          host: r,
          query: s,
          isAsyn: !1
        }
      }
      function ie(t, e) {
        var r = {
        };
        return r.tp = e.tp,
        e.attr && (r.attr = e.attr),
        e.hasOwnProperty('float') && (r.float = e.float),
        e.hasOwnProperty('aw') && (r.aw = e.aw),
        r.pn = void 0 === e.pn ? '' : e.pn,
        r.t = e.t,
        r.qs = i.fmqValueSet(),
        r.hostfr = 'imgstat',
        r.query = r.word,
        r.nb = e.nb,
        r.tab = e.tab,
        r.fm = e.fm,
        r.f = e.f,
        r.u = e.u,
        r.fr = e.fr,
        r.tag = e.tag,
        r.oriword = e.oriword,
        r.query = e.query,
        {
          host: pe + '4.gif',
          query: r,
          isAsyn: !1
        }
      }
      function oe(t, e) {
        var r = {
          type: 'avatar',
          app: 'pc',
          page: 'result',
          wd: ce,
          adid: e.adid,
          etype: 'pv'
        };
        return {
          host: qe + '/7.gif',
          query: r,
          isAsyn: !1
        }
      }
      function ue(t, e) {
        var r = {
          type: 'avatar',
          app: 'pc',
          page: 'result',
          wd: ce,
          adid: e.adid,
          etype: 'clk'
        };
        return {
          host: qe + '/7.gif',
          query: r,
          isAsyn: !1
        }
      }
      function de(t, e, r) {
        if (null != t) for (var o = t || window.event, u = o.srcElement || o.target; u.parentNode != document.body && u.tagName && 'a' != u.tagName.toLowerCase(); ) u = u.parentNode;
         else var u = document.body;
        'undefined' == typeof r && (r = {
        });
        var d = be[e];
        if ('undefined' != typeof d) {
          r.p = e;
          var p = d.apply(this, [
            u,
            r,
            o
          ]),
          f = p.host,
          q = s.extend({
          }, p.query);
          r.newp && (r.p = r.newp, q.p = r.newp),
          r.adPicId && (q.adPicId = r.adPicId, q.strategy = r.strategy),
          a.data.tab && (q.tab = a.data.tab),
          a.data.tag && (q.avtag = a.data.tag),
          q.tn = 'baiduimage',
          window.imgTempData && imgTempData.fcData && (q.fcType = imgTempData.fcType),
          window.vsid && (q.vs = window.vsid),
          a.data.aspSID && (q.aspSID = a.data.aspSID),
          q.q && (q.q = a.data.queryWordEnc ? a.data.queryWordEnc : encodeURIComponent(q.q), q.ie = 'utf-8'),
          q.word && (q.word = a.data.queryWordEnc),
          ge.queryFlag && ge.queryFlag.length > 0 && (q.qf = ge.queryFlag),
          le && (q.qcf = le),
          window.recommendData && recommendData.length > 0 && (q.rd = recommendData.length),
          window.recommendCategory && (q.rc = recommendCategory),
          ge.BrowserHotRs && (q.bhr = 'true'),
          q.qpagetype = we,
          q.userid = ge.encodeUserNumId,
          q.logid = window.logid,
          window.samplekey && '' !== window.samplekey && (q.samplekey = encodeURIComponent(window.samplekey)),
          ge.hs - 0 && (q.ishttps = ge.hs - 0),
          390 === + e && (q.q = a.data.queryWord, q.cl = a.data.cl, q.lm = a.data.lm, q.ct = a.data.ct, q.width = a.data.width, q.height = a.data.height, q.ic = a.data.ic),
          (391 === + e || 392 === + e) && (q = p.query, q.wd = a.data.queryWordEnc),
          'object' == typeof q && (q = i.json2Query(q));
          var y = p.isAsyn,
          m = n(f + '?' + q);
          return y && (o.returnValue = !1, o.preventDefault && o.preventDefault(), setTimeout(function () {
            var t = u && s(u).attr('target'),
            e = !t || '_self' == t;
            e ? location.href = r.href || u.href : window.open(r.href || u.href)
          }, ye)),
          m
        }
      }
      var pe = '//imgstat.baidu.com/',
      fe = '//image.baidu.com/pv/pv.gif',
      qe = o.ihttpsAgent('http://bzclk.baidu.com'),
      ye = 100,
      me = (new Date).getTime(),
      ge = a.data || {
      },
      ce = (a.data.ie, a.data.queryWordEnc),
      he = (a.data.queryWordGBKEnc, - 9),
      le = a.data.queryClassFlag || '',
      we = a.data.queryPageType || '0',
      ve = ge.encodeUserNumId || '',
      Ae = new Date;
      ve && (Ae.setTime(Ae.getTime() + 6048000000), s.cookie('userid', ve, {
        expires: Ae
      }));
      var be = {
        0: t,
        1: t,
        2: f,
        3: f,
        4: f,
        5: f,
        6: y,
        7: t,
        9: g,
        10: m,
        14: h,
        16: l,
        24: q,
        25: w,
        27: C,
        29: f,
        30: f,
        31: f,
        38: v,
        39: A,
        44: b,
        45: S,
        46: V,
        47: V,
        48: V,
        50: C,
        51: C,
        52: P,
        53: j,
        54: B,
        55: C,
        56: F,
        57: L,
        60: E,
        61: k,
        62: O,
        63: W,
        64: C,
        65: C,
        66: R,
        69: U,
        70: z,
        99: N,
        200: T,
        201: I,
        202: J,
        210: x,
        211: _,
        300: C,
        301: C,
        302: C,
        303: H,
        304: Q,
        390: ie,
        391: oe,
        392: ue,
        492: M,
        493: G,
        494: K,
        495: D,
        496: e,
        497: c,
        498: $,
        499: X,
        500: X,
        501: re,
        502: se,
        503: ne,
        1101001: X,
        1101002: X,
        1101101: X,
        1101102: ee,
        1101103: X,
        1101104: X,
        1102101: ae,
        1111101: te,
        1111102: te,
        1111103: te,
        1101004: Y,
        1101005: Y,
        1010100: Z,
        1010101: Z,
        1101006: Y,
        1101007: Y,
        1120000: F
      };
      return window.p = de,
      de
    }()
  }
});
; /*!searchresult:widget/ui/controls/morePageBox/morePageBox.js*/
define('searchresult:widget/ui/controls/morePageBox/morePageBox', function (i, s, t) {
  function e(i) {
    this.model = i,
    this.$container = null,
    this.$loadCon = null,
    this.isEnd = !1,
    this.$resultInfo = '',
    this.hasSend = !1,
    this.$body = n('body'),
    this.loadPic = '//img2.bdstatic.com/static/searchresult/img/loading_circle_40b82ef.gif'
  }
  {
    var n = i('common:widget/ui/base/base'),
    o = (i('searchresult:widget/ui/utils/utils'), i('common:widget/ui/base/events'));
    i('common:widget/ui/base/EventDispatcher').eventCenter,
    i('searchresult:widget/ui/statistic/statistic')
  }
  n.extend(e.prototype, o, {
    init: function () {
      this.$loadCon = n('#loading'),
      this.$container = n('#pageMore'),
      this.$resultInfo = n('#resultInfo'),
      this.$loadCon.children('img').attr('src', this.loadPic),
      this._bindEvent()
    },
    _bindEvent: function () {
      var i = this;
      this.$container.on('click', function () {
        i.hasSend && (i.hasSend = !1),
        i.clickMorePage()
      })
    },
    showLoad: function () {
      'visible' == this.$container.css('visibility') || this.isEnd || (this.$loadCon.show(), this.$body.addClass('cms-area-hidden'))
    },
    hideLoad: function () {
      this.$loadCon && this.$loadCon.hide()
    },
    setMorePage: function () {
      this.show(),
      this.isEnd && this.$resultInfo.css('visibility', 'visible'),
      this.isEnd && this.$body.removeClass('cms-area-hidden')
    },
    clickMorePage: function () {
      this.hide(),
      this.showLoad(),
      this.trigger('clickMorePage')
    },
    show: function () {
      this.$container.css('visibility', 'visible'),
      this.$resultInfo.css('visibility', 'visible')
    },
    hide: function () {
      this.$container.css('visibility', 'hidden'),
      this.$resultInfo.css('visibility', 'visible')
    }
  }),
  t.exports = e
});
; /*!searchresult:widget/ui/app/scrollmanager.js*/
define('searchresult:widget/ui/app/scrollmanager', function (e, t, n) {
  var i,
  a,
  o,
  r,
  p,
  s,
  d,
  c,
  u,
  g,
  l = e('common:widget/ui/base/base'),
  h = (e('common:widget/ui/utils/utils'), e('searchresult:widget/ui/utils/scroller')),
  f = e('common:widget/ui/base/subject'),
  m = e('common:widget/ui/base/EventDispatcher').eventCenter,
  w = e('common:widget/ui/EventEmitter/EventEmitter'),
  P = e('searchresult:widget/ui/statistic/statistic'),
  v = e('searchresult:widget/ui/controls/morePageBox/morePageBox'),
  _ = [
  ],
  b = 0,
  y = !0,
  H = {
  },
  S = 0,
  N = 1,
  E = l.extend(f, {
    init: function (e, t, n) {
      i = t,
      a = n,
      H = n.tempData.get('rpData'),
      c = l(e),
      h.init({
        tick: 10,
        duration: 20
      }),
      h.on('scrolling', this._scrollingHandler),
      h.on('scrollEnd', this._scrollEndHandler),
      'flip' != n.get('tpl') && (i.on('panelAppendStart', this._appendPosStartHandler), i.on('panelAppendPosUpdated', this._appendPosUpdatedHandler), i.on('panelAppendPosUpdated', l.proxy(this._checkPageHeight, this)), i.on('panelAppendRPUpdated', this._appendRPUpdatedHandler), this.updateWinHeight())
    },
    update: function () {
      this.updateState()
    },
    run: function () {
      h.start()
    },
    pause: function () {
      h.stop()
    },
    updateState: function () {
      o = c.offset().top
    },
    updateWinHeight: function () {
      s = l(window).height()
    },
    notify: function (e) {
      for (var t, n = this.observers, i = 0; i < n.length; i++) t = n[i],
      this._callObserver(t.ob, t.func, e)
    },
    _callObserver: function (e, t, n) {
      if ('string' == typeof t) {
        if ('refresh' == t) return;
        t = e[t]
      }
      void 0 === n ? t.apply(e)  : t.apply(e, n)
    },
    _checkPageHeight: function (e) {
      var t,
      n;
      n = e.height,
      (window.ActiveXObject || 'ActiveXObject' in window) && this.updateState(),
      t = o + n,
      s > t && i.append(),
      H && H.data && H.data.length && e.pageNum < window.rpPageNum && i.append()
    },
    _appendPosStartHandler: function (e) {
      S = e.pageNum,
      a.set('curSPn', e.curSPn, !0),
      E._loadStrategy(S, e.state)
    },
    _appendPosUpdatedHandler: function (e) {
      r = e.height,
      S = e.pageNum,
      E._setPageSize(e),
      E._loadStrategy(S, e.state)
    },
    _appendRPUpdatedHandler: function (e) {
      p = {
        pageNum: e.pageNum,
        y: e.height,
        rpHeight: e.rpHeight
      }
    },
    _setPageSize: function (e) {
      var t = e.pageNum,
      n = a.get('curSPn'),
      i = e.curEPn,
      o = e.height;
      _[t] = {
        pageNum: t,
        sPn: n,
        ePn: i || n,
        y: o
      },
      a.set('curEPn', i, !0)
    },
    _scrollingHandler: function (e) {
      var t = e.scrollTop,
      n = e.scrollingDown,
      p = 2 * s,
      d = o + r;
      p >= d - t - s && n && y && i.append();
      var c = a.get('cg');
      ('head' === c || 'wallpaper' === c) && (t > o - 56 ? w.eventCenter.trigger('search-box-switch', {
        state: 'fixed'
      })  : w.eventCenter.trigger('search-box-switch', {
        state: 'top'
      }))
    },
    autoPosition: function () {
    },
    _scrollEndHandler: function (e) {
      for (var t, n = _.length - 1; n >= 0; n--) {
        if (p && window.rpPageNum === n && e.scrollTop + p.rpHeight >= p.y) {
          t = p;
          break
        }
        if (e.scrollTop + _[0].y >= _[n].y) {
          t = _[n];
          break
        }
      }
      if (g != t) {
        g = t,
        a.set('curPageInfo', t, !0),
        t.pageNum + 1 >= 10 && 80 <= window.bid && window.bid <= 89 && m.dispatchEvent('passportAction:2'),
        N && 0 === + t.pageNum ? N = 0 : P(null, 56, {
          type: 'pageturn',
          curr: t.pageNum + 1,
          fr: a.get('fr'),
          picnum: t.ePn - t.sPn
        });
        var i = a.get('word'),
        o = a.get('ic') + a.get('width') + a.get('height') + a.get('z') + a.get('st') + a.get('face') + a.get('lm') + a.get('s');
        l.cookie('BDqhfp', i + '&&' + o + '&&' + (t.y - _[0].y) + '&&' + (t.pageNum + 1))
      }
      var r = e.scrollTop,
      s = r > b ? !0 : !1;
      E.notify([r,
      s]),
      b = r
    },
    bindScrollEvent: function (e, t) {
      h.on(e, t)
    },
    setPos: function (e) {
      this.pos = e
    },
    getPos: function () {
      return this.pos
    },
    setDirect: function (e) {
      this.direct = e
    },
    getDirect: function () {
      return d
    },
    _loadStrategy: function (e, t) {
      l('#pnlAfterContent');
      return u = new v,
      u.init(),
      u.on('clickMorePage', function () {
        i.append(),
        y = !0
      }),
      'done' === t ? void u.hideLoad(e)  : 1 > e ? (y = !0, void u.hide())  : void u.showLoad(e)
    }
  });
  n.exports = E
});
; /*!searchresult:widget/ui/models/filtermodel.js*/
define('searchresult:widget/ui/models/filtermodel', function (e) {
  function t(e) {
    l(f).each(function (t, l) {
      a[l] = e.get(l) || ''
    }),
    r.call(this, l.extend({
      tn: e.get('datatn') || 'resultjson_com',
      is: e.get('statNum') ? e.get('is')  : null,
      fp: 'result',
      queryWord: e.get('queryWord') || '',
      stepWord: e.get('step_word') || '',
      size: {
        width: 0,
        height: 0,
        level: 0
      },
      color: 0,
      imgType: '',
      fileFormat: - 1,
      ipn: 'rj',
      ct: '201326592'
    }, a)),
    this.filterConf = l.extend(i, {
    }),
    this.defaultFilterValue = null,
    this.model = e
  }
  var l = e('common:widget/ui/base/base'),
  u = (e('common:widget/ui/utils/utils'), e('common:widget/ui/base/events')),
  r = e('common:widget/ui/arch/model'),
  i = {
    ic: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    width: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    height: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    z: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    st: {
      defaultValue: '-1',
      currValue: '-1',
      emptyValue: '-1'
    },
    face: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    lm: {
      defaultValue: '-1',
      currValue: '-1',
      emptyValue: '-1'
    },
    s: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    tab: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    }
  },
  a = {
  },
  f = [
    'cl',
    'lm',
    'ie',
    'oe',
    'adpicid',
    'st',
    'word',
    'z',
    'ic',
    's',
    'se',
    'tab',
    'width',
    'height',
    'face',
    'istype',
    'qc',
    'nc',
    'fr',
    'se',
    'needIE',
    'jit',
    'showHot',
    'hasResult',
    'thirdLogo',
    'rpstart',
    'rpnum'
  ];
  return l.extend(t.prototype, r.prototype, u, {
    set: function (e, t, l) {
      var u = r.prototype.set.call(this, e, t);
      if (l && (u = [
        e
      ]), u && u.length) for (var i = 0; i < u.length; i++) this.dispatchEvent(u[i] + ':changed')
    },
    getKey: function () {
      var e = this.get('imgData');
      return e && e.key
    },
    getCurPage: function () {
      return this.model.get('curPageInfo')
    },
    getCurrFilterConf: function () {
      var e = {
      },
      t = this.filterConf;
      for (var l in t) e[l] = '0' === this.model.get(l) ? this.model.get(l)  : this.model.get(l) || this.defaultFilterValue && this.defaultFilterValue[l] || t[l].defaultValue;
      return e
    },
    getDefaultFilterConf: function () {
      this.defaultFilterValue;
      if (!this.defaultFilterValue) {
        this.defaultFilterValue = {
        };
        var e = (this.defaultFilterValue, this.filterConf);
        for (var t in e) this.defaultFilterValue[t] = e[t].defaultValue
      }
      return this.defaultFilterValue.tab = this.model.get('tab') || '0',
      this.defaultFilterValue
    },
    checkISDefaultFilter: function (e, t) {
      e = e || this.getCurrFilterConf(),
      t = t || this.getDefaultFilterConf();
      for (var l in t) if (t[l] !== e[l]) return !1;
      return !0
    },
    getFilterState: function () {
      var e = this.getCurrFilterConf(),
      t = this.getDefaultFilterConf(),
      l = this.checkISDefaultFilter(e, t);
      return {
        currFilterConf: e,
        deFaultFilterConf: t,
        isShowFilterBar: !0,
        isDefaultFilter: l
      }
    }
  }),
  t
});
; /*!searchresult:widget/ui/collections/imgcollection.js*/
define('searchresult:widget/ui/collections/imgcollection', function (t) {
  function e() {
    this.url = '/search/acjson',
    this.total = - 1,
    this.lastTotal = 0,
    this.bdFmtDispNum = 0,
    this.resOffsetAdjust = 0,
    this.reqParams = null,
    this.fixedPn = - 1,
    this.requestPool = {
    },
    this.requestedMinOffset = 1 / 0,
    this.fieldsMap = null,
    this.conditions = null,
    this.FETCH_NUM = 30
  }
  function n(t) {
    t = t || new e,
    a.call(this, t),
    this.configCache({
      primaryKey: 'key'
    }),
    this.imgSetCollections = {
    },
    this.fixedData = [
    ];
    var n = this;
    s(['beforeFetch',
    'afterFetch']).each(function (e, i) {
      t.on(i, function (t) {
        n.fire(i, t)
      })
    }),
    this.imgSetParams = !1
  }
  function i(t, i) {
    var r = this,
    a = new e,
    o = i.imgSetParams || i.dataProxy.reqParams;
    a.on('afterFetch', function (e) {
      var n = r.getTotal();
      if (2 > n) t.isSet = !1;
       else {
        for (var i, s = e.responseData.dataSet || [
        ], a = 0, o = 0, f = s.length; f > o; o++) if (i = s[o], i.objURL == t.objURL) {
          a = o;
          break
        }
        if (a > 0) {
          for (var l, o = a - 1; o >= 0; ) l = s[o],
          l.offset += 1,
          o -= 1;
          var u = s.splice(a, 1) [0];
          u.bigImgUrl = t.bigImgUrl,
          u.offset = 0,
          s.unshift(u)
        }
      }
      t.bdSetImgNum = n
    }),
    this.albumImgInfo = t,
    n.call(this, a),
    this.setReqParams(s.extend({
    }, o, {
      is: t.is,
      istype: 1
    })),
    this.setFieldMap(i.dataProxy.fieldsMap)
  }
  var s = t('common:widget/ui/base/base'),
  r = t('common:widget/ui/base/events'),
  a = t('common:widget/ui/arch/collection'),
  o = t('searchresult:widget/ui/app/pagemodel'),
  f = t('searchresult:widget/ui/utils/lib');
  return s.extend(e.prototype, r, {
    _putRequest: function (t, e, n) {
      var i = this;
      n.then(function (n) {
        return i._completeRequest(t, e),
        n
      }),
      this.requestPool[t] = {
        rn: e,
        promise: n
      }
    },
    _completeRequest: function (t, e) {
      t < this.requestedMinOffset && (this.requestedMinOffset = t);
      var n = this.requestPool[t];
      n && n.rn == e && delete this.requestPool[t]
    },
    _getRequest: function (t, e) {
      var n = this.requestPool[t];
      return n && e <= n.rn ? n.promise : null
    },
    hasMore: function (t, e) {
      var n = e ? e.length : 0;
      return fixedCount = this.resOffsetAdjust - t,
      fixedCount > 0 && (n -= fixedCount),
      this.total < 0 || t + n < this.total
    },
    fetch: function (t, e, n, i) {
      var r = this.fetchSingle(t, e, n, i),
      a = r.param;
      if (r.hasMore && r.validPn && a.pn + a.rn < e + n + this.FETCH_NUM) {
        var o = 0,
        f = {
          dataSet: [
          ]
        },
        l = s.Deferred(),
        u = this.fetchSingle(t, a.pn + this.FETCH_NUM, this.FETCH_NUM, [
        ]);
        return r.pro ? r.pro.then(function (t) {
          return o += 1,
          f.offset = t.offset,
          f.total = t.total,
          f.dataSet = t.dataSet.concat(f.dataSet),
          2 == o && l.resolve(f),
          t
        })  : o += 1,
        u.pro ? u.pro.then(function (t) {
          return o += 1,
          f.dataSet = f.dataSet.concat(t.dataSet),
          2 == o && l.resolve(f),
          t
        })  : o += 1,
        2 == o && l.resolve(f),
        l
      }
      return r.pro
    },
    fetchSingle: function (t, e, n, i) {
      var r = this.parseReqParam(t, e, n, i),
      a = this,
      f = {
        param: r,
        offset: e,
        limit: n,
        existDataSet: i
      };
      if (o.data && o.data.itg && (r.itg = o.data.itg), e + i.length >= r.pn + r.rn) return {
        pro: null,
        param: r,
        validPn: !0,
        hasMore: !0
      };
      if (!r.rn || !this.hasMore(e, i)) {
        var l = new s.Deferred;
        return l.resolve({
          offset: e
        }),
        r.pn = r.pn + this.FETCH_NUM,
        {
          pro: l,
          param: r,
          validPn: !0,
          hasMore: !1
        }
      }
      var u = this._getRequest(r.pn, r.rn);
      if (!u) {
        if (this.fire('beforeFetch', f), r.gsm = o.data.gsm, r[(new Date).getTime()] = '', this.fixedPn === r.pn) {
          var l = new s.Deferred;
          return l.resolve({
            offset: e
          }),
          r.pn = r.pn + this.FETCH_NUM,
          {
            pro: l,
            param: r,
            validPn: !1,
            hasMore: !0
          }
        }
        this.fixedPn = r.pn,
        u = s.get(this.url, r, null, 'text').then(function (t) {
          var e = a.parseResponse(t, r.pn);
          return a.bdFmtDispNum = e.bdFmtDispNum,
          o.data.tmpGsm = o.data.gsm || 0,
          o.data.gsm = e.gsm,
          a.total = e.dataSet.length < r.rn ? Math.min(e.total, r.pn + e.dataSet.length)  : e.total,
          a.fire('afterFetch', s.extend({
            responseData: e
          }, f)),
          e
        }),
        this._putRequest(r.pn, r.rn, u)
      }
      return {
        pro: u,
        param: r,
        validPn: !0,
        hasMore: !0
      }
    },
    parseResponse: function (t, e) {
      t = f.parseResponse(t);
      var n = t && t.data,
      i = t && t.bdFmtDispNum || 0,
      s = t && t.gsm,
      r = t && (t.displayNum || t.listNum);
      return i = 0 === + i ? r : i,
      this.lastTotal < r ? this.lastTotal = r : r = this.lastTotal,
      n && n.length && (r = Math.max(r, e + n.length - 1)),
      {
        offset: e + this.resOffsetAdjust,
        total: r,
        gsm: s,
        bdFmtDispNum: i,
        dataSet: n && n.length && null != n[0] ? this.mapList(n.splice(0, n.length - 1), e)  : [
        ]
      }
    },
    mapList: function (t, e) {
      for (var n, i = 'undefined' != typeof e, s = t.length - 1; s >= 0; s--) n = this.mapField(t[s]),
      i && (n.pn = e + s, n.offset = n.pn + this.resOffsetAdjust);
      return t
    },
    mapField: function (t) {
      if (t && this.fieldsMap) {
        var e = this.fieldsMap || {
        };
        for (var n in e) e.hasOwnProperty(n) && (fieldValConf = e[n], t[n] = 'function' == typeof fieldValConf ? fieldValConf(t)  : t[fieldValConf])
      }
      return t
    },
    parseReqParam: function (t, e) {
      var n = s.extend({
        tn: 'resultjson_com'
      }, this.reqParams, t);
      return e = e || 0,
      n.pn = Math.floor(e / this.FETCH_NUM) * this.FETCH_NUM,
      n.rn = this.FETCH_NUM,
      n.pn <= this.requestedMinOffset && n.pn + n.rn > this.requestedMinOffset && n.pn < 0 && (n.pn = 0, n.rn = this.requestedMinOffset),
      n
    }
  }),
  s.extend(n.prototype, a.prototype, r, {
    setReqParams: function (t) {
      this.dataProxy.reqParams = t
    },
    getReqParams: function () {
      return this.dataProxy.reqParams
    },
    setFieldMap: function (t) {
      this.dataProxy.fieldsMap = t
    },
    getFixDataLength: function () {
      return this.dataProxy.resOffsetAdjust
    },
    putFixData: function (t) {
      if (t && t.length) {
        for (var e, n = this.dataProxy.resOffsetAdjust, i = this.getTotal(), s = 0, r = t.length; r > s; s++) e = t[s],
        n += 1,
        e.srcType = e.srcType || 'rec',
        this.dataProxy.mapField(e),
        e.key = - 1 * n,
        e.offset = i + s,
        this.put(e);
        this.dataProxy.resOffsetAdjust += n
      }
    },
    mapField: function (t) {
      return this.dataProxy.mapField(t)
    },
    get: function (t, e, n) {
      return 'undefined' != typeof e && (e = 1 * e, e += this.dataProxy.resOffsetAdjust),
      a.prototype.get.call(this, t, e, n)
    },
    getByOffset: function (t, e) {
      return a.prototype.get.call(this, {
      }, t, e)
    },
    getByKeyOffset: function (t, e) {
      var n = this.conditions ? {
        key: this.conditions
      }
       : {
      };
      return a.prototype.get.call(this, n, t, e)
    },
    getByIndex: function (t, e) {
      return this.get({
      }, t, e)
    },
    getByKey: function (t) {
      var e = {
        key: t
      };
      return this.get(e).then(function (t) {
        return t.length ? t[0] : null
      })
    },
    getByMiddle: function (t, e) {
      var n = Math.ceil((e - 1) / 2),
      i = Math.max(t - n, - 1 * this.getFixDataLength()),
      s = t - i + 1 + n,
      r = this;
      return this.getByIndex(i, s).then(function (t) {
        return {
          offset: i + r.getFixDataLength(),
          reqCount: s,
          result: t
        }
      })
    },
    getDispNum: function () {
      return this.dataProxy.bdFmtDispNum
    },
    getTotal: function () {
      return Math.max(this.dataProxy.total, 0) + this.dataProxy.resOffsetAdjust
    },
    getSubImg: function (t, e, n) {
      n = n || 1;
      var i = new s.Deferred,
      r = this;
      return this.getByIndex(t, 1).then(function (t) {
        var s = t[0],
        a = r._getImgSetCollectionIns(s);
        a ? a.getByIndex(e, n).then(function (t) {
          i.resolve({
            imgData: s,
            subList: t
          })
        })  : i.resolve({
          imgData: s,
          subList: null
        })
      }),
      i
    },
    getImgSetCollection: function (t) {
      var e = s.isPlainObject(t) ? t : null;
      return e || this.getByKey(t).then(function (t) {
        e = t
      }),
      e && this._getImgSetCollectionIns(e)
    },
    _getImgSetCollectionIns: function (t) {
      var e = t && this.imgSetCollections[t.key];
      return e || (e = this._createImgSetCollection(t), e && (this.imgSetCollections[t.key] = e), e && this.fire('newImgSetCollection', {
        imgSetCollection: e
      })),
      e
    },
    _createImgSetCollection: function (t) {
      return t && t.isSet ? new i(t, this)  : null
    },
    setImgSetReqParams: function (t) {
      this.imgSetParams = t
    },
    getIterator: function (t) {
      var e = this,
      n = t,
      i = 0,
      s = 0;
      if (!t) {
        if (this.iterators) for (var r in this.iterators) if (this.iterators.hasOwnProperty(r)) {
          var a = this.iterators[r];
          a.cancel && a.cancel()
        }
        this.iterators = {
        }
      }
      if (this.iterators[t]) return null;
      var o = function (t, r, a) {
        s && a && a('already canceled'),
        window.samplekey.match(/UI_PC_FAST_SCROLL:[12]/) && !s && e.getByOffset(n, 30),
        !s && e.getByOffset(n++, 1).then(function (e) {
          e.length && t && t(e[0]),
          !e.length && (i = 1) && r && r()
        }).fail(function (t) {
          !i && n--,
          a && a(t)
        })
      },
      f = function (t, r, a, o) {
        s && o && o('already canceled'),
        !s && e.getByOffset(n, t).then(function (e) {
          e.length && r && r(e),
          e.length < t && (i = 1) && a && a()
        }).fail(function (t) {
          o && o(t)
        })
      },
      l = {
        nextN: f,
        next: o,
        index: function () {
          return n
        },
        prev: function () {
          return i ? n : --n
        },
        cancel: function () {
          s = 1
        }
      };
      return this.iterators[t] = l,
      l
    }
  }),
  s.extend(i.prototype, n.prototype, {
    getImgSetCollection: function () {
      return null
    }
  }),
  n
});
; /*!searchresult:widget/ui/strategy/imglayoutstrategy.js*/
define('searchresult:widget/ui/strategy/imglayoutstrategy', function (i) {
  function e(i, e) {
    this.model = i,
    this.width = i.getCurrentPageSize().viewW,
    this.options = e,
    this.insertTmp = [
    ],
    this.insertMidTmp = [
    ]
  }
  var t = i('common:widget/ui/base/base'),
  n = i('searchresult:widget/ui/utils/utils');
  return t.extend(e.prototype, {
    process: function (i, e) {
      var t = this.model.getCurrentPageSize();
      this.width = t.viewW - e.leftMenu,
      this.options = e,
      this.insertStrategy = e.insertStrategy;
      var n = [
      ],
      s = [
      ],
      h = this.options.asyAdNum,
      a = [
      ];
      if (0 !== h) {
        var a = i.slice(0, h);
        i = i.slice(h, i.length - 1),
        a = this.layoutAdImg(a)
      }
      return n = this.layoutOnePage(i, 0, e.curPage),
      n = this.adjustCells(n),
      s.push({
        full: !0,
        imgList: n,
        asyAdList: a
      }),
      window.pulletime = new Date,
      s
    },
    lazyProcess: function (i, e) {
      var s = this,
      h = new t.Deferred,
      a = this.model.getCurrentPageSize();
      this.width = a.viewW - e.leftMenu,
      this.options = e,
      this.insertStrategy = e.insertStrategy;
      var r = [
      ],
      g = this.options.asyAdNum;
      return n.setMaxWidthLimit(e.maxImgWidth),
      s.lazyProcessAdImg(i, g).then(function (t) {
        s.lazyProcessNormalImg(i, e.curPage).then(function (i, e) {
          r.push({
            full: !0,
            imgList: i,
            asyAdList: t,
            insertedNum: e
          }),
          window.pulletime = new Date,
          h.resolve(r)
        })
      }),
      h
    },
    lazyProcessAdImg: function (i, e) {
      var n = t.Deferred();
      return e ? (i.nextN(e, function (i) {
        n.resolve(this.layoutAdImg(i))
      }, function (i) {
        n.reject(i)
      }), n)  : n.resolve([])
    },
    lazyProcessNormalImg: function (i, e) {
      for (var n = t.Deferred(), s = this, h = this.options, a = 0.8, r = 0, g = 1, l = h.margin, o = h.padding, m = 0, d = h.minBaseLineHeight, u = (h.pageLineNum, h.lineHeight), p = 0, W = h.pageImgLimit, L = 0, f = [
      ], c = [
      ], H = this.insertStrategy.insertCellOneLine(), v = H.insertDatas.length, b = 0; v > b; b++) this.insertTmp[b] = H.insertDatas[v - b - 1];
      for (var y = H.insertMidData.length, b = 0; y > b; b++) this.insertMidTmp[b] = H.insertMidData[y - b - 1];
      this.initOneLine(e, r),
      f.isNotFull = !0;
      var M = function (i) {
        i = i || {
        },
        c.length > 0 && (! + i.personalized || s.lineW > a * s.baseLineW) && (c.lineW = Math.max(s.lineW, s.baseLineW), c.baseLineW = s.baseLineW, c.baseLineH = s.baseLineH, f.push(c), s.lineConf = s.getbaseLineConf(e, r), c.left = s.lineConf.left, f.isNotFull = !0, c = [
        ], s.lineW = 0);
        var t = s.adjustCells(f);
        n.resolve(t, p)
      },
      w = 0,
      N = function () {
        w++ < 30 ? i.next(I, M, function (i) {
          n.reject(i)
        })  : (w = 0, setTimeout(function () {
          i.next(I, M, function (i) {
            n.reject(i)
          })
        }, 0))
      },
      I = function (t) {
        var n = s.insertTmp.length,
        h = s.insertMidTmp.length,
        a = !1,
        b = 14,
        w = 6,
        I = 13,
        x = e % b === I && e > 1,
        C = e % b === w;
        if (n > 0 && r == H.lineNum && x ? t = s.insertTmp.pop()  : h > 0 && r === H.lineNum && C && (a = !0, t = s.insertMidTmp.pop()), t.curPage = e, s.resizeOneObj(t), s.averageHeight = s.calcAveHeight(s.averageHeight, s.m, t), s.delta += Math.max(0, (t.imgBaseHeight - s.averageHeight) / t.imgBaseHeight * t.imgBaseWidth), s.baseLineW = s.calcLineWidth(g, s.baseLineW, s.tmpbaseLineW, s.lineConf), m = s.averageHeight, s.checkLine(s.baseLineW, s.lineW, t.imgBaseWidth, s.delta, s.averageHeight)) s.lineW += t.imgBaseWidth * s.baseLineH / u + l + 2 * o,
        t.imgBaseHeight >= d && t.imgBaseHeight < s.imgMinHeight && (s.imgMinHeight = t.imgBaseHeight),
        c.push(t),
        a && (i.prev(), p++),
        s.m++,
        N();
         else {
          i.prev(),
          c.lineW = s.lineW,
          c.baseLineW = s.baseLineW,
          g++,
          s.lineConf.isFixedHeight ? c.baseLineH = s.baseLineH : (s.averageHeight = Math.min(s.baseLineH, s.averageHeight / s.lineW * (s.baseLineW + s.delta)), c.baseLineH = s.averageHeight);
          var B;
          v > 0 && 1 == H.order && r == H.lineNum && x ? (B = c.splice(0, v), Array.prototype.push.apply(c, B))  : y > 0 && 1 === H.order && r === H.lineNum && C && (B = c.splice(0, y), Array.prototype.push.apply(c, B)),
          f.push(c),
          L += c.length,
          c = [
          ],
          f.isNotFull = !1,
          r++,
          s.initOneLine(e, r),
          L >= W ? (v > 0 && f.length > H.lineNum + 1 && x ? f.push(f.splice(H.lineNum, 1) [0])  : y > 0 && f.length > H.lineNum + 1 && C && f.push(f.splice(H.lineNum, 1) [0]), M(t))  : N()
        }
      };
      return N(),
      n
    },
    layoutOnePage: function (i, e, t) {
      var n = i.length,
      s = this.options,
      h = 0.8,
      a = 0,
      r = 0,
      g = 1,
      l = s.margin,
      o = s.padding,
      m = 0,
      d = s.minBaseLineHeight,
      u = (s.pageLineNum, s.lineHeight),
      p = s.pageImgLimit,
      W = 0,
      L = [
      ],
      f = [
      ],
      c = this.insertStrategy.insertCellOneLine(),
      H = c.insertDatas.length;
      if (H) for (var v = 0; H > v; v++) this.insertTmp[v] = c.insertDatas[v];
      for (this.initOneLine(t, r), L.isNotFull = !0, a = e, this.m = 0; n > a; ) {
        var b = i[a],
        y = this.insertTmp.length;
        if (!b) break;
        if (y > 0 && r == c.lineNum && t % 10 === 9 && t > 1 && (i[a] = this.insertTmp.pop(), b = i[a]), b.width > s.rawWidthLimit) a++;
         else if (this.resizeOneObj(b), this.averageHeight = this.calcAveHeight(this.averageHeight, this.m, b), this.delta += Math.max(0, (b.imgBaseHeight - this.averageHeight) / b.imgBaseHeight * b.imgBaseWidth), this.baseLineW = this.calcLineWidth(g, this.baseLineW, this.tmpbaseLineW, this.lineConf), m = this.averageHeight, this.checkLine(this.baseLineW, this.lineW, b.imgBaseWidth, this.delta, this.averageHeight) ? (this.lineW += b.imgBaseWidth * this.baseLineH / u + l + 2 * o, b.imgBaseHeight >= d && b.imgBaseHeight < this.imgMinHeight && (this.imgMinHeight = b.imgBaseHeight), f.push(b), a++, this.m++)  : (f.lineW = this.lineW, f.baseLineW = this.baseLineW, g++, this.lineConf.isFixedHeight ? f.baseLineH = this.baseLineH : (this.averageHeight = Math.min(this.baseLineH, this.averageHeight / this.lineW * (this.baseLineW + this.delta)), f.baseLineH = this.averageHeight), H > 0 && 1 == c.order && r == c.lineNum && t % 10 === 9 && (f = f.reverse()), L.push(f), W += f.length, f = [
        ], L.isNotFull = !1, r++, this.initOneLine(t, r)), W >= p) {
          H > 0 && L.length > c.lineNum + 1 && t % 10 === 9 && L.push(L.splice(c.lineNum, 1) [0]);
          break
        }
      }
      return f.length > 0 && (!b.personalized || this.lineW > h * this.baseLineW) && (f.lineW = Math.max(this.lineW, this.baseLineW), f.baseLineW = this.baseLineW, f.baseLineH = this.baseLineH, L.push(f), this.lineConf = this.getbaseLineConf(t, r), f.left = this.lineConf.left, L.isNotFull = !0, f = [
      ], this.lineW = 0),
      L
    },
    initOneLine: function (i, e) {
      this.lineConf = this.getbaseLineConf(i, e),
      this.tmpbaseLineW = this.lineConf.lineWidth || this.width,
      this.baseLineH = this.lineConf.lineHeight,
      this.imgMinHeight = this.baseLineH,
      this.averageHeight = 0,
      this.delta = 0,
      this.lineW = 0,
      this.m = 0
    },
    resizeOneObj: function (i) {
      var e = n.zoomLi(i, this.options.lineHeight);
      i.imgBaseWidth = parseInt(Math.min(parseInt(e.width), this.options.maxImgWidth)),
      i.imgBaseHeight = parseInt(e.height),
      i.margin = this.options.margin
    },
    calcOneCell: function () {
    },
    calcLineWidth: function (i, e, t, n) {
      return this.options.curPage == this.insertStrategy.pageNum && i >= this.insertStrategy.startLine && i <= this.insertStrategy.endLine ? (n.isFixedHeight = !0, t - this.insertStrategy.width)  : (n.isFixedHeight = !1, t)
    },
    calcAveHeight: function (i, e, t) {
      return i = (i * e + t.imgBaseHeight) / (e + 1)
    },
    getbaseLineConf: function () {
      var i = this.options,
      e = {
      };
      return e.lineWidth = i.lineWidth,
      e.lineHeight = i.lineHeight,
      e.isFixedHeight = !1,
      e
    },
    checkLine: function (i, e, t, n, s) {
      var h = this.options,
      a = t + h.margin + 2 * h.padding;
      return i + n + s > e + a
    },
    adjustCells: function (i) {
      for (var e = (this.options, !1), t = 0, n = i.length; n > t; t++) e = t == n - 1 && 1 == i.isNotFull ? !0 : !1,
      this.analyseLine(i[t], e);
      return this.connectArray(i)
    },
    analyseLine: function (i, e) {
      for (var t = [
      ], n = [
      ], s = 0, h = 0, a = '', r = 0, g = i.length; g > r; r++) {
        var l = i[r];
        delete l.marginRight,
        l.liHeight = l.imgBaseHeight,
        l.liWidth = l.imgBaseWidth,
        l.liWidth > l.liHeight ? (t.push(l), s += l.liWidth)  : (n.push(l), h += l.liWidth),
        'SME' == l.type && (a = 'SME')
      }
      l && (l.marginRight = 0),
      i.lineH = i.baseLineH,
      i.lineWimgs = t,
      i.lineWimgWidth = s,
      i.lineHimgs = n,
      i.lineHimgWidth = h,
      i.type = a,
      1 == e && (i.lineW = Math.max(i.lineW, i.baseLineW), i.isNotFull = !0)
    },
    connectArray: function (i) {
      for (var e = [
      ], t = i.length, n = (this.options.margin, this.options.padding, 0); t > n; n++) {
        var s = i[n];
        this.fixWidth(s),
        this.fixLines(s);
        for (var h = 0; h < s.length; h++) {
          var a = s[h];
          e.push(a)
        }
      }
      return e
    },
    fixHight: function (i) {
      for (var e = this.options, t = 0, n = 0, s = 0; s < i.length; s++) t += (i[s].baseLineW + Math.max(i[s].lineHimgWidth * n - 0.5 * i[s].baseLineW, 0)) * (2 * i[s].baseLineW - i[s].lineW) / (i[s].baseLineW * i[s].baseLineW);
      for (var h = e.lineHeight * i.length, a = h / t, s = 0; s < i.length; s++) i[s].lineH = parseInt((i[s].baseLineW + Math.max(i[s].lineHimgWidth * n - 0.5 * i[s].baseLineW, 0)) * (2 * i[s].baseLineW - i[s].lineW) / (i[s].baseLineW * i[s].baseLineW) * a)
    },
    fixWidth: function (i) {
      for (var e = this.options, t = i.lineH, s = 0, h = i.length, a = (i.sme || 0, 0), r = 0; h > r; r++) i[r].lineH = t,
      i[r].liWidth = n.zoomImg(i[r]).width,
      i[r].liHeight = t,
      s += i[r].liWidth + e.margin + 2 * e.padding,
      a += i[r].liWidth;
      i.lineW = s,
      i.pureWidth = a
    },
    fixLines: function (i) {
      var e = i.baseLineW - i.lineW;
      if (i.isNotFull && (e = Math.min(0, e)), e > 0) this.averageLiWidth(i, e, !1);
       else {
        var t = i.lineWimgs;
        (!t || 0 == t.length || Math.abs(e / t.length) > 30) && (t = i),
        this.averageLiWidth(t, e)
      }
      this.fixImgDisplay(i)
    },
    averageLiWidth: function (i, e) {
      var t,
      n = 0;
      for (t = 0; t < i.length; t++) {
        var s = i[t];
        'SME' != s.type && (n += i[t].liWidth)
      }
      var h = e / n;
      for (t = 0; t < i.length; t++) {
        var a = i[t];
        'SME' != a.type && (a.liWidth = parseInt(a.liWidth + a.liWidth * h))
      }
    },
    fixImgDisplay: function (i) {
      for (var e = i.length, t = this.options.maxImgWidth, s = 0; e > s; s++) {
        var h = i[s],
        a = h.liWidth,
        r = Math.max(h.lineH, parseInt(a * h.height / h.width));
        h.lineH = h.height / h.width > h.liHeight / h.liWidth ? Math.min(1.2 * h.lineH, r)  : Math.min(1.15 * h.lineH, r);
        var g = h.offset = n.zoomImg(h, t);
        h.matchURL = this._pickURL(g.width, g.height, h)
      }
    },
    _pickURL: function (i, e, n) {
      var s = e,
      h = n.largeTnImageUrl;
      return window.samplekey.match('UI_PC_THUMBURL_300:1') ? h = n.thumbURL : (s >= 230 && n.hoverURL ? h = n.hoverURL : (s >= 140 && 170 >= s || '' === h) && n.middleURL && (h = n.middleURL), (140 > s || '' === h) && (h = n.thumbURL)),
      1 == t.browser.chrome && 0 == n.bdSrcType && (h = h.replace(/fm=21(&|\.|$)/i, function (i, e) {
        return 'fm=200' + e
      }).replace(/\.(jpg|jpeg|png|gif)$/, '.webp')),
      h
    },
    scaleImg: function (i, e) {
      var t = {
        width: i.width,
        height: i.height
      };
      return t.height > e.height && (t.height = e.height, t.width = t.width / t.height * e.height),
      t
    },
    layoutAdImg: function (i) {
      for (var e = [
      ], t = 0; t < i.length; t++) {
        var n = i[t];
        n.liHeight = 200,
        n.liWidth = 200,
        n.imgMarginTop = 0,
        n.imgMarginLeft = 0,
        n.margin = 5,
        n.width > n.height ? (n.scaleHeight = 200, n.scaleWidth = parseInt(n.width / n.height * 200), n.imgMarginLeft = parseInt((200 - n.scaleWidth) / 2))  : (n.scaleWidth = 200, n.scaleHeight = parseInt(n.height / n.width * 200), n.imgMarginTop = parseInt((200 - n.scaleHeight) / 2)),
        e.push(n)
      }
      return e
    }
  }),
  e
});
; /*!searchresult:widget/ui/strategy/insertstrategy.js*/
define('searchresult:widget/ui/strategy/insertstrategy', function (t) {
  function i() {
    this.startLine = '',
    this.endLine = '',
    this.pageNum = '',
    this.width = '',
    this.height = ''
  }
  {
    var e = t('common:widget/ui/base/base');
    t('searchresult:widget/ui/utils/utils')
  }
  return e.extend(i.prototype, {
    init: function (t) {
      this.startLine = t.startLine,
      this.endLine = t.endLine,
      this.pageNum = t.pageNum,
      this.width = t.width,
      this.height = t.height
    },
    set: function () {
    },
    get: function () {
    },
    _paintArea: function (t, i, n) {
      var s = n || '';
      return e('<div style="float:left;width:' + t + 'px;height:' + i + 'px;' + s + '"></div>')
    },
    putItem: function (t) {
      this.width && t.append(this._paintArea(this.width, this.height, ''))
    },
    insertCellOneLine: function () {
      return {
        lineNum: 2,
        order: 1,
        insertMidData: window.fcMidData || [
        ],
        insertDatas: window.fcBtData || [
        ]
      }
    }
  }),
  i
});
; /*!searchresult:widget/ui/config/base/config.js*/
define('searchresult:widget/ui/config/base/config', function (e, i, g) {
  e('common:widget/ui/base/base'),
  g.exports = function () {
    var e = window.ecom && window.ecom.ma && ecom.ma.image.ald ? ecom.ma.image.ald.getArea().height : 190,
    i = {
      normal: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 200,
        maxBaseLineHeight: 220,
        minBaseLineHeight: 200,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 0
      },
      comic: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 190,
        maxBaseLineHeight: 210,
        minBaseLineHeight: 190,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 0
      },
      ald: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: e,
        maxBaseLineHeight: 210,
        minBaseLineHeight: 190,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 0
      },
      star: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 260,
        maxBaseLineHeight: 280,
        minBaseLineHeight: 250,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 0
      },
      avatar_brand: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 300,
        maxBaseLineHeight: 320,
        minBaseLineHeight: 280,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 500,
        pageMoreNum: 10,
        leftMenu: 0
      },
      avatar_star: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 260,
        maxBaseLineHeight: 280,
        minBaseLineHeight: 250,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 0
      },
      avatar_head: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 200,
        maxBaseLineHeight: 210,
        minBaseLineHeight: 190,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 165
      },
      avatar_wallpaper: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 180,
        maxBaseLineHeight: 200,
        minBaseLineHeight: 160,
        pageLineNum: 3,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 165
      },
      single: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 200,
        maxBaseLineHeight: 220,
        minBaseLineHeight: 200,
        pageLineNum: 1,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 0
      },
      personalized: {
        margin: 5,
        padding: 0,
        pageNumHeight: 33,
        lineHeight: 200,
        maxBaseLineHeight: 220,
        minBaseLineHeight: 200,
        pageLineNum: 2,
        pageImgLimit: 20,
        imgDigestHeight: 0,
        maxImgWidth: 400,
        pageMoreNum: 10,
        leftMenu: 0
      }
    };
    return {
      get: function (e, g) {
        return i[e][g]
      },
      setConfs: function (e) {
        i = e
      },
      getAll: function (e) {
        return i[e]
      }
    }
  }()
});
; /*!searchresult:widget/ui/statistic/bdgstat.js*/
define('searchresult:widget/ui/statistic/bdgstat', function (e, t, i) {
  var s = e('common:widget/ui/base/base'),
  a = e('common:widget/ui/monitorRequest/monitorRequest'),
  o = e('searchresult:widget/ui/utils/utils'),
  d = e('searchresult:widget/ui/app/pagemodel'),
  n = {
    host: '//imgstat.baidu.com/10.gif?'
  };
  s.extend(n, {
    sendLog: function (e) {
      e = s.extend({
      }, e, this._getBaseParams()),
      a(this.host + o.json2Query(e))
    },
    _getBaseParams: function () {
      if (!this._defaultParams) {
        var e = s.cookie('BAIDUID') || '';
        this._defaultParams = {
          query: d.data.queryWordEnc || '',
          baiduid: e.slice(0, - 5),
          logid: window.logid || '',
          samplekey: encodeURIComponent(window.samplekey || '')
        }
      }
      return s.extend(this._defaultParams, {
        timestamp: (new Date).getTime()
      })
    }
  }),
  i.exports = n
});
; /*!searchresult:widget/ui/controls/postpone/postpone.js*/
define('searchresult:widget/ui/controls/postpone/postpone', function (n, t, e) {
  var o = n('common:widget/ui/base/base'),
  u = function () {
    return Date.now && Date.now() || + new Date
  },
  i = 200,
  l = null,
  a = [
  ],
  c = u(),
  r = {
    timeRemaining: i
  },
  m = function () {
    return null === l
  },
  s = function () {
    r.timeRemaining = 0,
    c = u(),
    l || (l = setTimeout(f, i))
  },
  d = function () {
    clearTimeout(l),
    l = null;
    for (var n = a.length - 1; n >= 0; n--) w(a[n])
  },
  f = function () {
    var n = c + i,
    t = n - u();
    t > 0 ? l = setTimeout(f, t)  : d()
  },
  w = function (n) {
    n.end || (n.end = u(), n.callback(r), n.timeoutId && (clearTimeout(n.timeoutId), n.timeoutId = null))
  },
  p = function (n, t) {
    var e = {
      callback: n,
      timeoutId: null,
      start: u(),
      end: 0
    };
    return e.timeoutId = null !== t ? setTimeout(function () {
      w(e)
    }, t)  : null,
    e
  },
  v = function (n) {
    a.push(n)
  };
  o(window).on('scroll', s);
  var b = function (n, t) {
    var e = t && t.timeout || null,
    o = p(n, e);
    m() || Math.random() < 0.1 ? w(o)  : v(o)
  };
  b.callbacks = a,
  e.exports = b
});
; /*!searchresult:widget/ui/controls/imgpagelist/cellBox/cellBox.js*/
define('searchresult:widget/ui/controls/imgpagelist/cellBox/cellBox', function (t) {
  function a() {
    this.tpl = {
      imgItemTpl: [
        '<li class="imgitem" style="">',
        '<div class="imgbox"><a href="" target="_blank" style="display: block;">',
        '<img class="main_img img-hover" />',
        '</a></div>',
        '</li>'
      ].join(''),
      ItemTimeTpl: [
        '<span class="img-hover img-time img-timebg" ></span>'
      ].join(''),
      ItemSetTpl: [
        '<div class="album-box"><div class="paper-one paper" style="top:0;left:0;z-index:1;"></div><div class="paper-two paper" style="top:4px;left:4px;"></div></div>'
      ].join(''),
      ItemStarTpl: [
        '<div class="img-hover img-star img-starbg" ></div>'
      ].join('')
    },
    this._pageModel = null
  }
  var e = t('common:widget/ui/base/base'),
  i = (t('common:widget/ui/base/events'), t('common:widget/ui/utils/utils')),
  r = t('searchresult:widget/ui/statistic/statistic'),
  s = (t('searchresult:widget/ui/utils/lib'), t('searchresult:widget/ui/statistic/bdgstat')),
  n = t('searchresult:widget/ui/controls/postpone/postpone');
  return e.extend(a.prototype, {
    init: function () {
    },
    render: function (t, a) {
      this._pageModel = a;
      var i = e(this.tpl.imgItemTpl),
      r = i.find('img'),
      s = i.find('.imgbox'),
      d = i.find('.imgbox a'),
      o = 0,
      g = Math.max((t.liHeight - t.margin - t.offset.height) / 2, 0),
      l = this;
      t.marginRight = void 0 === t.marginRight ? t.margin : t.marginRight,
      i.width(t.liWidth).height(t.liHeight).css('marginRight', t.marginRight + 'px').css('marginBottom', t.margin + 'px'),
      l.setDomAttr(i, t);
      var p = t.matchURL;
      return t.base64 && 'brand' !== this._pageModel.get('cg') && (p = t.base64, r.one('error', function () {
        r.attr('src', t.matchURL)
      })),
      r.attr('data-imgurl', t.matchURL),
      r.css('background-color', l.randomColor()).width(t.offset.width).height(t.offset.height),
      !t.base64 && window.samplekey.match('UI_PC_FAST_SCROLL:2') ? n(function () {
        r.attr('src', p)
      })  : r.attr('src', p),
      d.attr('href', t.detailUrl).attr('name', 'pn' + t.pageNum).width(t.offset.width).height(t.offset.height),
      d.addClass('div_' + t.cs),
      l.bindEvent(d, t),
      l.patch(t, a, i, d, s, r, o, g),
      i
    },
    decorate: function (t, a) {
      this._pageModel = a;
      var i = e('.imgitem'),
      r = t.cs,
      s = r.replace(',', '-');
      s || (s = t.pageNum);
      var n = i.find('.div_0_' + s);
      if (n.addClass('div_' + s).removeClass('div_0_' + s), 0 == n.length) return this.render(t, a);
      var d = this,
      o = 0,
      g = 0;
      n.attr('href', t.detailUrl).attr('name', 'pn' + t.pageNum),
      d.bindEvent(n, t);
      var l = n.parents('.imgitem'),
      p = l.find('.imgbox'),
      c = l.find('img');
      d.setDomAttr(l, t),
      d.patch(t, a, l, n, p, c, o, g)
    },
    setDomAttr: function (t, a) {
      t.attr('data-objURL', a.objURL).attr('data-thumbURL', a.thumbURL).attr('data-fromURL', a.fromURL).attr('data-fromURLHost', a.fromURLHost).attr('data-ext', a.type).attr('data-saved', 0).attr('pn', a.pn).attr('data-pi', a.pi).attr('data-specialType', a.adType || '').attr('data-cs', a.cs).attr('data-width', a.width).attr('data-height', a.height).attr('data-title', i.trimTags(a.fromPageTitle, [
        'strong'
      ])).attr('data-personalized', a.personalized);
      var r = a.decorationData;
      r && ('string' == typeof r && (r = e.parseJSON(r)), t.data('decoration', r.type), t.data('desc', r.desc), t.data('tags', r.tags), t.data('adPicId', a.adPicId), t.data('strategy', r.strategy), t.data('author', r.author_name), t.data('authorUrl', r.author_avatar_url), 2 === + r.type && ((new Image).src = r.author_avatar_url))
    },
    patch: function (t, a, i, s, n, d, o, g) {
      if (t.bdSetImgNum > 0) {
        var l = t.bdSetImgNum + '张';
        if (l) {
          var p = e(this.tpl.ItemTimeTpl).html(l).addClass('img-set-label');
          n.addClass('album'),
          n.width(n.find('img').width()),
          n.append(p);
          var c = n.parent(),
          m = Math.abs(c.height() - n.find('img').height()),
          h = n.find('.img-set-label');
          !isNaN(m) && m > 5 ? h.css('bottom', 20 + m + 'px')  : h.css('bottom', '20px'),
          r(null, 1120000, {
            isset: encodeURIComponent(t.is || ''),
            pn: t.pn || t.pageNum
          })
        }
      } else t.width / t.height > 1.5 && (o = (t.liWidth - t.margin - t.offset.width) / 2),
      g > 0 && s.css('marginTop', g),
      o > 0 && s.css('marginLeft', o);
      if ('starfans_star' === t.type);
       else if ('starfans_fans' === t.type);
       else if ('ugc' === t.type) {
        var u = e(this.tpl.ItemStarTpl).html('<div class="img-star-desc">用户上传</div>').addClass('user');
        i.append(u)
      } else if (t.bdImgnewsDate) {
        var f = this._timeCalculate(((new Date).getTime() - this.parseDate(t.bdImgnewsDate.replace(/-/g, '/')).getTime()) / 3600000);
        if (f && 1 * t.di != 0) {
          var b = e(this.tpl.ItemTimeTpl).html(f);
          i.append(b)
        }
      }
    },
    rc: function (t) {
      var a = t.imgid || '',
      i = t.category,
      r = t.tag,
      s = t.prfix || 'click';
      a && e.getJSON('/counter/picture' + s, {
        picture_id: a,
        category: i,
        tag: r,
        sortlog: 0,
        times: (new Date).getTime()
      }, function () {
      })
    },
    parseDate: function (t) {
      var a = new RegExp('^\\d+(\\-|\\/)\\d+(\\-|\\/)\\d+$');
      if ('string' == typeof t) {
        if (a.test(t) || isNaN(Date.parse(t))) {
          var e = t.split(/ |T/),
          i = e.length > 1 ? e[1].split(/[^\d]/)  : [
            0,
            0,
            0
          ],
          r = e[0].split(/[^\d]/);
          return new Date(r[0] - 0, r[1] - 1, r[2] - 0, i[0] - 0, i[1] - 0, i[2] - 0)
        }
        return new Date(t)
      }
      return new Date
    },
    _timeCalculate: function (t) {
      var a;
      return 1 > t ? a = '1小时内' : 24 > t ? a = Math.round(t) + '小时前' : 192 > t && (a = Math.round((t - t % 24) / 24) + '天前'),
      a
    },
    randomColor: function () {
      var t = [
        '#c3b19d',
        '#8fa3a7',
        '#b1c5a3',
        '#bdaba9',
        '#dbbfb2',
        '#c8bc98',
        '#b6adad',
        '#af9ab2',
        '#a3a6b9',
        '#8fb2bf'
      ];
      return t[Math.floor(Math.random() * t.length)]
    },
    clickStatistics: function (t, a) {
      var i = {
        ist: a.source_type,
        sr: a.bdSrcType,
        u: a.objURL,
        f: a.fromURL,
        pn: a.pageNum,
        cs: a.cs,
        t: 1,
        asp: a.aspSign,
        rts: a.rts,
        personalized: a.personalized
      };
      a.decorationData && (i.adPicId = encodeURIComponent(a.adPicId), 'string' == typeof a.decorationData && (a.decorationData = e.parseJSON(a.decorationData)), i.strategy = encodeURIComponent(a.decorationData.strategy)),
      + a.bdSetImgNum > 0 && (i.isset = encodeURIComponent(a.is || '')),
      r(t, 0, i)
    },
    bindEvent: function (t, a) {
      var i = this;
      t.on('click', function (r) {
        t.attr('href', a.detailUrl),
        r.preventDefault();
        var s = + new Date,
        n = e(window),
        d = n.width() + 'X' + n.height();
        window.open(a.detailUrl + '&ctd=' + s + '^3_' + d + '%1'),
        i.clickStatistics(r, a),
        i.sendBdgStat(a);
        var o = i._pageModel.get('cg');
        if ('brand' === o && '1' === a.adType && i.sendAvatarClk(a), 'head' === o || 'wallpaper' === o || 'girl' === o) {
          var g = {
            imgid: a.pi,
            category: o,
            tag: i._pageModel.data.queryWord,
            prfix: 'click'
          };
          i.rc(g)
        }
        return !1
      })
    },
    getQueryString: function (t) {
      var a = new RegExp('[\\?&]' + t + '=([^&#]*)', 'i'),
      e = a.exec(location.href);
      return e ? e[1] : ''
    },
    sendAvatarClk: function (t) {
      var a = t.adid || '';
      r(null, 392, {
        adid: a
      })
    },
    sendBdgStat: function (t) {
      '4' === t.adType && s.sendLog({
        as: 'yingshi',
        p: 1010101,
        pos: 'pc_result_images_tabs',
        subpos: t.pageNum || 0,
        matcont: this._pageModel && this._pageModel.get('tabName') || '全部',
        picurl: encodeURIComponent(t.objURL || '')
      }),
      '3' === t.adType && s.sendLog({
        as: t.brandName,
        p: 1010101,
        pos: 'pc_result_before_insert',
        subpos: t.pageNum || 0,
        matcont: t.imgUrl,
        tgTo: 1
      })
    }
  }),
  new a
});
; /*!searchresult:widget/ui/controls/imgpagelist/TJADBox/TJADBox.js*/
define('searchresult:widget/ui/controls/imgpagelist/TJADBox/TJADBox', function (t) {
  function i() {
    this.titleTemplate = '品牌广告',
    this.promoteTemplate = '<a href="http://e.baidu.com/" target="_blank">商业推广</a>',
    this.tipTemplate = '<div class="tj-ad-tip"><h3>' + this.titleTemplate + '</h3>本搜索结果为' + this.promoteTemplate + '信息，请注意可能的风险。百度推出<a href="http://baozhang.baidu.com/guarantee/" target="_blank">网民权益保障计划</a>，<a href="https://passport.baidu.com" target="_blank">登录</a>搜索有保障。<div class="c-tip-arrow" style="left: 25px;"><em></em><ins></ins></div></div>',
    this.tipTemplateNew = '<div class="tj-ad-tip"><h3>' + this.titleTemplate + '</h3>本搜索结果为' + this.promoteTemplate + '信息，请注意可能的风险。百度推出<a href="http://baozhang.baidu.com/guarantee/" target="_blank">网民权益保障计划</a>，<a href="https://passport.baidu.com" target="_blank">登录</a>搜索有保障。<div class="c-tip-arrow" style="left: 25px;"></div></div>',
    this.descTemplate = '<div class="tj-summary-txt"><span class="tj-info-tag"></span><span class="tj-info-abs" hovercls="tj-abs-hover"></span></div>';
    var t = this;
    this.tpl = {
      clean: function () {
        delete this._cached
      },
      itemTpl: function (i) {
        return this._cached = s.match('UI_PC_TJAD:2') && i.tags.length > 0 ? this._cached || [
          '<li class="tjImgli">',
          '<div class="tj-link">',
          '<div class="tj-img">',
          '<a target="_blank" onclick="return false;">',
          '<img />',
          '</a>',
          '</div>',
          '<div class="tjNew">',
          '<span class="tj-tg-icon">' + t.titleTemplate + '</span>',
          t.tipTemplateNew,
          '<div class="tjad-message">',
          '<span class="tjad-desc" title="${adDesc}">${adDesc}</span>',
          '{@each tags as item}<span class="tjad-tag">${item}</span>{@/each}',
          '<span class="price">${price}</span>',
          '</div>',
          '<div class="tjad-logo" title="${adlink}"><img src="${logoUrl}"></div>',
          '</div>',
          '</div>',
          '</li>'
        ].join('')  : s.match('UI_PC_TJAD:1') && i.tags.length > 0 ? this._cached || [
          '<li class="tjImgli">',
          '<div class="tj-link">',
          '<div class="tj-img">',
          '<a target="_blank" onclick="return false;">',
          '<img />',
          '</a>',
          '</div>',
          '<div class="tjNew">',
          '<span class="tj-tg-icon">' + t.titleTemplate + '</span>',
          t.tipTemplateNew,
          '<div class="tjad-message">',
          '<span class="tjad-desc" title="${adDesc}">${adDesc}</span>',
          '{@each tags as item}<span class="tjad-tag">${item}</span>{@/each}',
          '<span class="price">${price}</span>',
          '</div>',
          '</div>',
          '</div>',
          '</li>'
        ].join('')  : this._cached || [
          '<li class="tjImgli">',
          '<div class="tj-link">',
          '<div class="tj-img">',
          '<a target="_blank" onclick="return false;">',
          '<img />',
          '</a>',
          '</div>',
          '<div class="tj-bg" data-height="100" data-hover-height="120"></div>',
          '<div class="tj-img-bt">',
          '<span class="tj-tg-icon">' + t.titleTemplate + '</span>',
          '<div class="tj-bt-right"></div></div>',
          '<div class="tj-info">',
          '<div class="tj-info-tit" >',
          '<span class="tj-tg-icon">' + t.titleTemplate + '</span>',
          '<span class="tj-tit-txt" ',
          'hovercls="tj-tit-hover"></span></div>',
          t.descTemplate,
          '<span class="tj-info-host" hovercls="tj-host-hover"></span>',
          '</div>',
          t.tipTemplate,
          '</div>',
          '</li>'
        ].join(''),
        e(this._cached, i)
      },
      logoTpl: [
        '<div class="tj-logo"><img src="" ></div>'
      ].join('')
    }
  }
  var a = t('common:widget/ui/base/base'),
  e = (t('common:widget/ui/base/events'), t('common:widget/ui/utils/utils'), t('searchresult:widget/ui/statistic/statistic'), t('common:widget/ui/juicer/juicer')),
  s = window.samplekey || '',
  n = !1,
  l = 0;
  return a.extend(i.prototype, {
    init: function () {
    },
    render: function (t) {
      var i = {
      },
      e = [
      ];
      !!t.tag_list && (e = t.tag_list.split(',')),
      !!t && (i = {
        adDesc: t.fromPageTitle,
        imgUrl: t.base64 || t.matchURL,
        targetUrl: t.fromURL,
        adlink: t.fromURL,
        logoUrl: t.logoUrl,
        price: t.price || 0,
        tags: e
      });
      var s = a(this.tpl.itemTpl(i)),
      n = this;
      t.marginRight = void 0 === t.marginRight ? t.margin : t.marginRight,
      s.width(t.liWidth).height(t.liHeight).css('marginRight', t.marginRight + 'px').css('marginBottom', t.margin + 'px');
      var l = s.find('.tj-img img'),
      d = t.matchURL;
      return t.base64 && (d = t.base64, l.one('error', function () {
        l.attr('src', t.matchURL)
      }), l.attr('data-imgurl', t.matchURL)),
      l.width(t.liWidth).height(t.liHeight).attr('src', d),
      s.find('.tj-link').addClass(t.cellClass || ''),
      n.patch(t, s),
      this.bindEvent(s, t),
      s
    },
    decorate: function (t, i) {
      var e = this,
      n = a('.tjImgli');
      s.match('UI_PC_LAYOUT_DECOUPLE:2') && (n = a('.imgitem'));
      var l = t.width + '_' + t.height + '_' + t.pageNum,
      d = n.find('.li_0_' + l);
      return d.removeClass('li_0_' + l),
      0 === d.length ? this.render(t, i)  : (s.match('UI_PC_LAYOUT_DECOUPLE:2') ? (n = d.parents('.imgitem'), this.prePatch(t, n), n.removeClass('imgitem').addClass('tjImgli'))  : n = d.parents('.tjImgli'), this.replaceTip(n), e.patch(t, n), this.bindEvent(n, t), void 0)
    },
    updateTipTemplate: function () {
      var t = this,
      i = '<h3>' + t.titleTemplate + '</h3>本搜索结果为' + t.promoteTemplate + '信息，请注意可能的风险。您当前为登录状态，已参加<a href="http://baozhang.baidu.com/guarantee/" target="_blank">网民权益保障计划</a>。';
      this.tipTemplate = '<div class="tj-ad-tip">' + i + '</div>',
      this.tpl.clean(),
      a('.tj-link').each(function (e, s) {
        t.replaceTip(a(s), i)
      })
    },
    replaceTip: function (t, i) {
      var a = t.find('.tj-ad-tip');
      i ? (a.empty(), a.append(i))  : a.replaceWith(this.tipTemplate)
    },
    prePatch: function (t, i) {
      var e = '<div class="tj-link ' + (t.cellClass || '') + '"></div>',
      s = i.find('.imgbox');
      s.wrap(e);
      var n = a(this.tpl.itemTpl());
      n.find('.tj-img').remove();
      var l = i.find('.tj-link'),
      d = n.find('.tj-link').children();
      l.append(d),
      s.removeClass('imgbox').addClass('tj-img'),
      s.find('img').attr('class', '')
    },
    patch: function (t, i) {
      i.data('imgInfo', t),
      i.find('.tj-img a').attr('href', t.fromURL || t.fromURLHost),
      i.find('.tj-link').attr('data-fcpos', t.fcPos),
      i.find('.tj-link').attr('ecom-index', t.pageNum),
      i.find('.tj-bt-right').html(t.fromPageTitle);
      try {
        t.adStylesReserve = a.json.parse(t.adStylesReserve)
      } catch (e) {
      }
      i.find('.tj-tit-txt').html(t.adStylesReserve.image_native && t.adStylesReserve.image_native.dynamic_title && null !== t.adStylesReserve.image_native.dynamic_title.title && '' !== t.adStylesReserve.image_native.dynamic_title.title ? '<span class="dynamic-title">' + t.adStylesReserve.image_native.dynamic_title.title + '</span>' : '<span class="dynamic-title">' + t.fromPageTitle + '</span>'),
      '' !== t.adShortSummary ? (i.find('.tj-info-abs').html(t.adShortSummary), '' !== t.adTag && i.find('.tj-info-tag').html('[' + t.adTag + ']'))  : i.find('.tj-info-abs').html(t.fromPageAbs),
      i.find('.tj-info-host').html(t.fromURLHost),
      t.largeTnImageUrl && - 1 === t.largeTnImageUrl.slice( - 4).indexOf('.jpg') && - 1 === t.largeTnImageUrl.slice( - 4).indexOf('.gif') && (t.largeTnImageUrl = t.largeTnImageUrl + '&gp=0.jpg')
    },
    bindEvent: function (t, i) {
      var e = null,
      d = 4000,
      o = this;
      t.find('.tj-tg-icon').on('click', function (i) {
        i.stopPropagation(),
        t.find('.tj-ad-tip').show()
      }),
      t.find('.tj-ad-tip').on('click', function (i) {
        i.stopPropagation(),
        t.find('.tj-ad-tip').hide()
      }),
      t.find('.tj-ad-tip').on('mouseenter', function () {
        clearTimeout(e)
      }),
      t.find('.tj-ad-tip').on('mouseleave', function () {
        clearTimeout(e),
        e = setTimeout(function () {
          t.find('.tj-ad-tip').is(':hidden') || t.find('.tj-ad-tip').hide()
        }, d)
      }),
      t.find('.tj-link').on('mouseleave', function () {
        t.find('.tj-ad-tip').hide()
      });
      var c = function () {
        var t = (new Date).getTime() + '-',
        i = 0;
        return function () {
          return t + i++
        }
      }(),
      r = function (t) {
        var i = window.tjAdLog || (window.tjAdLog = {
        }),
        a = c(),
        e = i[a] = new Image;
        e.onload = e.onerror = function () {
          e.onload = e.onerror = null,
          e = null,
          delete i[a]
        },
        e.src = t + '&_uid=' + a
      },
      m = t.find('.tj-link'),
      h = {
      },
      g = [
      ];
      !!i.tag_list && (g = i.tag_list.split(',')),
      !!i && (h = {
        tags: g
      }),
      (s.match('UI_PC_TJAD:1') || s.match('UI_PC_TJAD:2')) && h.tags.length > 0 ? (n = !1, l = s.match('UI_PC_TJAD:1') ? 1 : 2)  : (n = !0, l = 0),
      'TJNAD' === i.type && n && (m.append(this.tpl.logoTpl), o.$linkNode = m, o.imgInfo = i, o._fixSize(), m.find('.tj-logo img').attr('src', i.logoUrl), a(window).on('resize', a.proxy(o._fixSize, o))),
      m.on('mouseenter', function () {
        r(i.tjUrl + '&actionid=1&attach=' + i.fcPos + '|src=result|render_type=' + l)
      }),
      m.on('click', function () {
        window.open(i.fromURL || i.fromURLHost, '_blank'),
        r(i.tjUrl + '&actionid=2&attach=' + i.fcPos + '|src=result|render_type=' + l)
      })
    },
    _fixSize: function () {
      var t = this.$linkNode,
      i = (this.imgInfo.liHeight - 110) / 2,
      a = this.imgInfo.liWidth - 12 - i;
      t.find('.tj-info-host').css('width', a + 'px'),
      t.find('.tj-logo').css({
        width: i + 'px',
        height: i + 'px'
      })
    },
    hover: function (t) {
      this.tbgId && clearTimeout(this.tbgId),
      this.tbgId = setTimeout(function () {
        var i = t.find('.tj-bg').attr('data-hover-height');
        t.find('.tj-bg').stop(!0).animate({
          height: i + 'px'
        }, 150)
      }, 150),
      this.tinfoId && clearTimeout(this.tinfoId),
      this.tinfoId = setTimeout(function () {
        t.find('.tj-info').stop(!0).animate({
          height: '55px'
        }, 150)
      }, 150)
    },
    leave: function (t) {
      var i = t.find('.tj-bg').attr('data-height');
      t.find('.tj-bg').animate({
        height: i + 'px'
      }, 150),
      t.find('.tj-info').animate({
        height: '26px'
      }, 150)
    }
  }),
  new i
});
; /*!searchresult:widget/ui/controls/fakeCK/fakeCK.js*/
define('searchresult:widget/ui/controls/fakeCK/fakeCK', function (i, e, t) {
  function n() {
    function i() {
      if (m._url) {
        for (var i = u * m.timeSign % 99 + 9, t = 0, n = 0; i > n; n++) t += m._url.charCodeAt(o * n % m._url.length);
        e = t
      }
    }
    var e,
    t,
    n,
    u = 0,
    o = 0,
    l = 0,
    s = 0,
    c = 0,
    h = 0,
    a = 0,
    f = 0,
    m = this;
    this.gather = function () {
      var i = this._url && [
        e,
        u,
        o,
        l,
        s,
        t,
        n,
        c
      ].join('.');
      return i ? this.url + '&ck=' + i : this.url
    },
    this.bind = function (e, m, d) {
      if (this.url) return !1;
      this.timeSign = d,
      this.url = m;
      var g = /link\?url\=([^\&]+)/.exec(this.url) || /\?url\=([^\.]+)\./.exec(this.url);
      this._url = g ? g[1] : void 0,
      r(e).on('mouseover', function (i) {
        u++,
        void 0 === t && (t = i.clientX),
        void 0 === n && (n = i.clientY),
        h = (new Date).getTime()
      }),
      r(e).on('mousedown', function (e) {
        a = (new Date).getTime(),
        o = 9999,
        l = e.clientX,
        s = e.clientY,
        c = 0 === h ? 0 : a - h,
        i()
      }),
      r(e).on('mouseup', function () {
        f = (new Date).getTime(),
        o = f - a,
        i()
      })
    }
  }
  var r = i('common:widget/ui/base/base');
  t.exports = n
});
; /*!searchresult:widget/ui/controls/imgpagelist/FCADBox/FCADBox.js*/
define('searchresult:widget/ui/controls/imgpagelist/FCADBox/FCADBox', function (i) {
  function t() {
    this.titleTemplate = '广告',
    this.promoteTemplate = '<a href="http://e.baidu.com/" target="_blank">商业推广</a>',
    this.tipTemplate = '<div class="fc-ad-tip"><h3>' + this.titleTemplate + '</h3>本搜索结果为' + this.promoteTemplate + '信息，请注意可能的风险。百度推出<a href="http://baozhang.baidu.com/guarantee/" target="_blank">网民权益保障计划</a>，<a href="https://passport.baidu.com" target="_blank">登录</a>搜索有保障。<div class="c-tip-arrow" style="left: 25px;"><em></em><ins></ins></div></div>';
    var i = this;
    this.tpl = {
      clean: function () {
        delete this._cached
      },
      itemTpl: function () {
        return this._cached = this._cached || [
          '<li class="fcImgli">',
          '<div class="fc-link">',
          '<div class="fc-img">',
          '<a target="_blank" onclick="return false;">',
          '<img />',
          '</a>',
          '</div>',
          '<div class="fc-bg" data-height="100" data-hover-height="120"></div>',
          '<div class="fc-img-bt">',
          '<span class="fc-tg-icon">' + i.titleTemplate + '</span>',
          '<div class="fc-bt-right"></div></div>',
          '<div class="fc-info">',
          '<div class="fc-info-tit" >',
          '<span class="fc-tg-icon">' + i.titleTemplate + '</span>',
          '<span class="fc-tit-txt" ',
          'hovercls="fc-tit-hover"></span></div>',
          '<span class="fc-info-host" hovercls="fc-host-hover"></span>',
          '</div>',
          i.tipTemplate,
          '</a>',
          '</li>'
        ].join(''),
        this._cached
      }
    }
  }
  var e = i('common:widget/ui/base/base'),
  a = (i('common:widget/ui/base/events'), i('common:widget/ui/utils/utils'), i('searchresult:widget/ui/controls/fakeCK/fakeCK')),
  n = i('searchresult:widget/ui/statistic/statistic'),
  c = window.samplekey || '';
  return e.extend(t.prototype, {
    init: function () {
    },
    render: function (i) {
      var t = e(this.tpl.itemTpl()),
      a = this;
      i.marginRight = void 0 === i.marginRight ? i.margin : i.marginRight,
      t.width(i.liWidth).height(i.liHeight).css('marginRight', i.marginRight + 'px').css('marginBottom', i.margin + 'px');
      var n = t.find('.fc-img img'),
      c = i.matchURL;
      return i.base64 && (c = i.base64, n.one('error', function () {
        n.attr('src', i.matchURL)
      }), n.attr('data-imgurl', i.matchURL)),
      n.width(i.liWidth).height(i.liHeight).attr('src', c),
      t.find('.fc-link').addClass(i.cellClass || ''),
      a.patch(i, t),
      this.bindEvent(t, i),
      this.appendCK(i),
      this.appendFakeCK(t, i),
      t
    },
    decorate: function (i, t) {
      var a = this,
      n = e('.fcImgli');
      c.match('UI_PC_LAYOUT_DECOUPLE:2') && (n = e('.imgitem'));
      var o = i.width + '_' + i.height + '_' + i.pageNum,
      d = n.find('.li_0_' + o);
      return d.removeClass('li_0_' + o),
      0 == d.length ? this.render(i, t)  : (c.match('UI_PC_LAYOUT_DECOUPLE:2') ? (n = d.parents('.imgitem'), this.prePatch(i, n), n.removeClass('imgitem').addClass('fcImgli'))  : n = d.parents('.fcImgli'), this.replaceTip(n), a.patch(i, n), this.bindEvent(n, i), this.appendCK(i), this.appendFakeCK(n, i), void 0)
    },
    updateTipTemplate: function () {
      var i = this,
      t = '<h3>' + i.titleTemplate + '</h3>本搜索结果为' + i.promoteTemplate + '信息，请注意可能的风险。您当前为登录状态，已参加<a href="http://baozhang.baidu.com/guarantee/" target="_blank">网民权益保障计划</a>。';
      this.tipTemplate = '<div class="fc-ad-tip">' + t + '</div>',
      this.tpl.clean(),
      e('.fc-link').each(function (a, n) {
        i.replaceTip(e(n), t)
      })
    },
    replaceTip: function (i, t) {
      var e = i.find('.fc-ad-tip');
      t ? (e.empty(), e.append(t))  : e.replaceWith(this.tipTemplate)
    },
    prePatch: function (i, t) {
      var a = '<div class="fc-link ' + (i.cellClass || '') + '"></div>',
      n = t.find('.imgbox');
      n.wrap(a);
      var c = e(this.tpl.itemTpl());
      c.find('.fc-img').remove();
      var o = t.find('.fc-link'),
      d = c.find('.fc-link').children();
      o.append(d),
      n.removeClass('imgbox').addClass('fc-img'),
      n.find('img').attr('class', '')
    },
    patch: function (i, t) {
      t.data('imgInfo', i),
      t.find('.fc-img a').attr('href', i.fromURL || i.fromURLHost),
      t.find('.fc-link').attr('data-fcpos', i.fcPos),
      t.find('.fc-link').attr('ecom-index', i.pageNum),
      t.find('.fc-bt-right').html(i.fromPageTitle);
      try {
        i.adStylesReserve = e.json.parse(i.adStylesReserve)
      } catch (a) {
      }
      var n = '';
      if ('FCAD' === i.type && i.adSellPointTag && window.samplekey.match(/UI_PC_AD_DESC/)) {
        var c = window.samplekey.match(/UI_PC_AD_DESC:(\d)/),
        o = c && c[1],
        d = i.adSellPointTag;
        switch (o) {
          case '1':
          case '4':
            n = d + '&nbsp;|&nbsp;';
            break;
          case '2':
            n = '［' + d + '］';
            break;
          case '3':
            n = d + '－'
        }
      }
      t.find('.fc-tit-txt').html(i.adStylesReserve.image_native && i.adStylesReserve.image_native.dynamic_title && null !== i.adStylesReserve.image_native.dynamic_title.title && '' !== i.adStylesReserve.image_native.dynamic_title.title ? '<span class="dynamic-title">' + n + i.adStylesReserve.image_native.dynamic_title.title + '</span>' : '<span class="dynamic-title">' + n + i.fromPageTitle + '</span>'),
      '' !== i.adShortSummary ? (t.find('.fc-info-abs').html(i.adShortSummary), '' !== i.adTag && t.find('.fc-info-tag').html('[' + i.adTag + ']'))  : t.find('.fc-info-abs').html(i.fromPageAbs),
      t.find('.fc-info-host').html(i.fromURLHost),
      i.largeTnImageUrl && - 1 === i.largeTnImageUrl.slice( - 4).indexOf('.jpg') && - 1 === i.largeTnImageUrl.slice( - 4).indexOf('.gif') && (i.largeTnImageUrl = i.largeTnImageUrl + '&gp=0.jpg'),
      i.fcPos > 3 && t.find('.fc-link').attr('data-picId', i.picId)
    },
    bindEvent: function (i, t) {
      var e = null,
      a = 4000,
      c = 0,
      o = 0,
      d = window.imgTempData,
      s = window.fcBtData,
      l = t.fcPos,
      r = t.posType,
      f = this,
      p = function () {
        i.find('.fc-ad-tip').is(':hidden') || (i.find('.fc-ad-tip').hide(), o = new Date, n && n(null, 1101006, {
          adtype: d.adType,
          fcpos: l,
          pos: r,
          picid: t.picId,
          adflag: t.adFlag,
          url: t.fromURLHost,
          curr: t.curPage,
          time: o - c
        }))
      };
      i.find('.fc-tg-icon').on('click', function (o) {
        c = new Date,
        o.stopPropagation();
        var s = i.find('.fc-ad-tip');
        s.show();
        var l = {
          adtype: d.adType,
          fcpos: t.fcPos,
          pos: r,
          picid: t.picId,
          adflag: t.adFlag,
          url: t.fromURLHost,
          curr: t.curPage,
          adpos: 'icon'
        };
        'FBAD' === t.type && (l.maincont = encodeURIComponent(t.fromPageTitle), l.landpage = encodeURIComponent(t.fromURLHost), l.picurl = encodeURIComponent(t.thumbURL), l.as = t.adTag),
        n && n(null, 1101005, l),
        clearTimeout(e);
        var f = s.offset();
        (o.pageX < f.left || o.pageX > f.left + s.width() || o.pageY < f.top || o.pageY > f.top + s.height()) && (e = setTimeout(p, a))
      }),
      i.find('.fc-ad-tip').on('click', function (e) {
        e.stopPropagation(),
        o = new Date,
        i.find('.fc-ad-tip').hide(),
        n && n(null, 1101006, {
          adtype: d.adType,
          fcpos: l,
          pos: r,
          picid: t.picId,
          adflag: t.adFlag,
          url: t.fromURLHost,
          curr: t.curPage,
          time: o - c
        }),
        n && n(null, 1101007, {
          adtype: d.adType,
          fcpos: l,
          pos: r,
          picid: t.picId,
          adflag: t.adFlag,
          curr: t.curPage,
          url: t.fromURLHost
        })
      }),
      i.find('.fc-ad-tip').on('mouseenter', function () {
        clearTimeout(e)
      }),
      i.find('.fc-ad-tip').on('mouseleave', function () {
        clearTimeout(e),
        e = setTimeout(p, a)
      }),
      i.find('.fc-link').on('click', function (i) {
        f.bindClickEvent(i, t);
        var e = t.fakeCK.gather(),
        a = window.open(e, '_blank');
        a.opener = null
      }),
      i.find('.fc-link').on('mouseenter', function () {
        f.st = (new Date).getTime(),
        n && n(null, 1101103, {
          adtype: d.adType,
          index: l,
          pos: r,
          url: t.fromURLHost,
          picid: t.picId,
          adflag: t.adFlag,
          picnum: s.length,
          curr: t.curPage,
          fcpos: l
        })
      }),
      i.find('.fc-link').on('mouseleave', function () {
        var e = (new Date).getTime() - f.st;
        n && n(null, 1101103, {
          adtype: d.adType,
          index: l,
          pos: r,
          url: t.fromURLHost,
          picid: t.picId,
          adflag: t.adFlag,
          picnum: s.length,
          hovertime: e,
          curr: t.curPage,
          fcpos: l
        }),
        3 === d.adType && i.find('.fc-ad-tip').hide()
      })
    },
    _fixSize: function () {
      var i = this.$linkNode,
      t = (this.imgInfo.liHeight - 110) / 2,
      e = this.imgInfo.liWidth - 12 - t;
      i.find('.fc-info-host').css('width', e + 'px'),
      i.find('.fc-logo').css({
        width: t + 'px',
        height: t + 'px'
      })
    },
    appendCK: function (i) {
      if ('FCAD' === i.type) this.bindEcomTimer && clearTimeout(this.bindEcomTimer),
      this.bindEcomTimer = setTimeout(function () {
        var t = window.ecom && window.ecom.pl && window.ecom.pl.run;
        t && window.ecom.pl.run(function (t) {
          for (var e = t.q('fcImgli'), a = 0; a < e.length; a++) {
            var n = e[a],
            c = n.getElementsByTagName('A'),
            o = i.timeSign ? + i.timeSign : window.ecom.pl.imTimesign;
            t.ck(c, o)
          }
        }, !1)
      }, 500);
       else {
        var t = i.adCkjs;
        if ('' === t) return;
        e.ajax({
          url: t,
          dataType: 'script',
          cache: !0
        }).done(function () {
          var t = ecom && ecom.ma && ecom.ma.ck;
          if (t) for (var a = e('.fcImgli'), n = 0; n < a.length; n++) {
            var c = a[n],
            o = c.getElementsByTagName('A');
            ecom.ma.ck(o, + i.timeSign)
          }
        })
      }
    },
    appendFakeCK: function (i, t) {
      var e = + t.timeSign;
      !e && window.ecom && window.ecom.pl && (e = window.ecom.pl.imTimesign);
      var n = t.fromURL || t.fromURLHost;
      '' !== t.adShortSummary && (n = t.adNativeUrl),
      t.fakeCK = new a,
      t.fakeCK.bind(i, n, e)
    },
    bindClickEvent: function (i, t) {
      var a = t.posType,
      c = window.imgTempData;
      if (e(i.target).closest('.fcimgpage').size()) {
        var o;
        window.xgMidData && window.xgMidData.mapXgMidData && (o = window.xgMidData.mapXgMidData, n && n(null, 1101101, {
          index: 0,
          curr: 5,
          url: o[t.fcPos].fromURLHost,
          picid: o[t.fcPos].picId,
          adflag: o[t.fcPos].adFlag,
          fcpos: t.fcPos
        }))
      } else {
        var d = '';
        d = e(i.target).closest('.fc-info-tit').size() ? 'title' : 'img',
        n && n(null, 1101101, {
          adtype: c.adType,
          index: 0,
          pos: a,
          url: t.fromURLHost,
          picid: t.picId,
          adflag: t.adFlag,
          curr: t.curPage,
          fcpos: t.fcPos
        });
        var s = {
          adtype: c.adType,
          fcpos: t.fcPos,
          pos: a,
          picid: t.picId,
          adflag: t.adFlag,
          url: t.fromURLHost,
          curr: t.curPage,
          adpos: d
        };
        'FBAD' === t.type && (s.maincont = encodeURIComponent(t.fromPageTitle), s.landpage = encodeURIComponent(t.fromURLHost), s.picurl = encodeURIComponent(t.thumbURL), s.as = t.adTag),
        n && n(null, 1101005, s)
      }
    },
    hover: function (i) {
      this.tbgId && clearTimeout(this.tbgId),
      this.tbgId = setTimeout(function () {
        var t = i.find('.fc-bg').attr('data-hover-height');
        i.find('.fc-bg').stop(!0).animate({
          height: t + 'px'
        }, 150)
      }, 150),
      this.tinfoId && clearTimeout(this.tinfoId),
      this.tinfoId = setTimeout(function () {
        i.find('.fc-info').stop(!0).animate({
          height: '55px'
        }, 150)
      }, 150)
    },
    leave: function (i) {
      var t = i.find('.fc-bg').attr('data-height');
      i.find('.fc-bg').animate({
        height: t + 'px'
      }, 150),
      i.find('.fc-info').animate({
        height: '26px'
      }, 150)
    }
  }), new t
});
; /*!searchresult:widget/ui/controls/imgpagelist/imgpagelist.js*/
define('searchresult:widget/ui/controls/imgpagelist/imgpagelist', function (t) {
  function e(t, e, a) {
    if (this.container = t, this.imgCollection = null, this.layoutStrategy = null, this.pageModel = e, this.state = {
      tailIndex: - 1,
      lastIndex: 0,
      tailPageNum: - 1
    }, this.storeData = [
    ], this.pageNum = 1, this.pageNumFirst = 0, this.pageNumSecond = 0, this.startTime = new Date, this.rpData = e.tempData.get('rpData'), this.checked = !1, this.options = i.extend({
      pageTpl: [
        '<div class="imgpage">',
        '<h6 class="note"></h6>',
        '<ul class="imglist clearfix" style="position: relative;"></ul>',
        '</div>'
      ].join(''),
      xgPageTpl: [
        '<div class="fcimgpage imgpage">',
        '<p class="bordertop"></p>',
        '<h6>相关推广</h6>',
        '<ul class="imglist clearfix" style="position: relative;"></ul>',
        '<p class="borderbottom"></p>',
        '</div>'
      ].join(''),
      rpPageTpl: [
        '<div class="rpimgpage imgpage">',
        '<p class="bordertop"></p>',
        '<h6>为您推荐</h6>',
        '<ul class="imglist clearfix" style="position: relative;"></ul>',
        '</div>'
      ].join(''),
      insertContainerTpl: [
        '<ul style="position: absolute;left:0;top:0;">',
        '</ul>'
      ].join('')
    }, a), h.match('UI_PC_LAYOUT_DECOUPLE:2')) {
      var s = e.tempData.get('jsConfs');
      s && n.setConfs(s)
    }
    if (this.isNewFcAd = !1, this.fcAdLineNum = 2, 'brand' === e.get('cg')) {
      var o = e.tempData.get('imgData'),
      r = o && o.data && o.data[0];
      g(null, 391, {
        adid: r && r.adid
      })
    }
  }
  var i = t('common:widget/ui/base/base'),
  a = t('common:widget/ui/base/events'),
  s = t('searchresult:widget/ui/utils/utils'),
  n = (t('searchresult:widget/ui/utils/lib'), t('searchresult:widget/ui/config/base/config')),
  g = t('searchresult:widget/ui/statistic/statistic'),
  o = t('searchresult:widget/ui/controls/imgpagelist/cellBox/cellBox'),
  r = t('searchresult:widget/ui/controls/imgpagelist/TJADBox/TJADBox'),
  d = t('searchresult:widget/ui/controls/imgpagelist/FCADBox/FCADBox'),
  p = t('common:widget/ui/utils/utils'),
  h = window.samplekey || '';
  return i.extend(e.prototype, a, {
    getLayoutOptions: function () {
      var t = this.pageModel.get('strategyType') || 'normal';
      return {
        minHeight: n.get(t, 'minBaseLineHeight'),
        pageLineNum: n.get(t, 'pageLineNum'),
        pageImgLimit: n.get(t, 'pageImgLimit'),
        margin: n.get(t, 'margin'),
        padding: n.get(t, 'padding'),
        imgDigestHeight: 0,
        maxBaseLineHeight: n.get(t, 'maxBaseLineHeight'),
        minBaseLineHeight: n.get(t, 'minBaseLineHeight'),
        leftMenu: n.get(t, 'leftMenu'),
        maxImgWidth: n.get(t, 'maxImgWidth') || 400,
        pageMoreNum: 10,
        lineHeight: n.get(t, 'lineHeight'),
        rawWidthLimit: 4096
      }
    },
    getSingleLayoutOptions: function () {
      var t = 'single';
      return {
        minHeight: n.get(t, 'minBaseLineHeight'),
        pageLineNum: n.get(t, 'pageLineNum'),
        margin: n.get(t, 'margin'),
        padding: n.get(t, 'padding'),
        imgDigestHeight: 0,
        maxBaseLineHeight: n.get(t, 'maxBaseLineHeight'),
        minBaseLineHeight: n.get(t, 'minBaseLineHeight'),
        leftMenu: n.get(t, 'leftMenu'),
        maxImgWidth: 400,
        pageMoreNum: 10,
        lineHeight: n.get(t, 'lineHeight'),
        rawWidthLimit: 4096
      }
    },
    getPersonalizedLayoutOptions: function () {
      var t = 'personalized';
      return {
        minHeight: n.get(t, 'minBaseLineHeight'),
        pageLineNum: n.get(t, 'pageLineNum'),
        margin: n.get(t, 'margin'),
        padding: n.get(t, 'padding'),
        imgDigestHeight: 0,
        maxBaseLineHeight: n.get(t, 'maxBaseLineHeight'),
        minBaseLineHeight: n.get(t, 'minBaseLineHeight'),
        leftMenu: n.get(t, 'leftMenu'),
        maxImgWidth: 400,
        pageMoreNum: 10,
        lineHeight: n.get(t, 'lineHeight'),
        rawWidthLimit: 4096
      }
    },
    setLayoutOption: function () {
    },
    mark: function () {
      return window.performance && window.performance.now() || Date && Date.now && Date.now() || + new Date
    },
    append: function () {
      var t = this,
      e = this.imgCollection.getIterator(this.state.tailIndex + 1);
      e && e.next(function () {
        e.prev(),
        i('#resultInfo').hide();
        var a = t.getLayoutOptions();
        if (t.trigger('panelAppendStart', {
          pageNum: t.state.tailPageNum + 1,
          opt: a,
          curSPn: t.state.tailIndex + 1,
          state: 'start'
        }), t.isNewFcAd) {
          var s = i(window).width();
          6 === t.options.asyAdNum && (t.fcAdLineNum = 615 > s ? 3 : 2);
          var n = {
            startLine: 0,
            pageNum: 0,
            endLine: 2,
            width: 205 * t.options.asyAdNum / t.fcAdLineNum,
            height: 205 * t.fcAdLineNum
          };
          t.insertStrategy.init(n)
        }
        t.layoutStrategy.lazyProcess(e, i.extend(a, {
          curPage: t.state.tailPageNum + 1,
          insertStrategy: t.insertStrategy,
          asyAdNum: t.isNewFcAd ? t.options.asyAdNum : 0
        })).then(function (e) {
          t._renderBlocks(e)
        }).fail(function () {
        })
      }, function () {
        t.imgCollection.getDispNum() <= 0 && (t.pageModel.set('bdFmtDispNum', 0), t.noPage(), t.trigger('firstload', {
        })),
        t.trigger('panelAppendPosUpdated', {
          state: 'done'
        }),
        i('#resultInfo').show()
      })
    },
    _isEmpotyCon: function (t) {
      if (!t.length) {
        {
          this.imgCollection.getDispNum()
        }
        return this.imgCollection.getDispNum() <= 0 ? (this.pageModel.set('bdFmtDispNum', 0), this.noPage(), this.trigger('firstload', {
        }), !1)  : !1
      }
      return !0
    },
    _renderBlocks: function (t) {
      for (var e, a = this.state.tailPageNum, s = this.state.tailIndex, n = this.imgCollection, g = i('<div></div>'), o = 0, r = t.length; r > o; o++) e = t[o],
      (e.full || s + e.imgList.length >= n.getTotal()) && (s += e.imgList.length - (e.insertedNum || 0), a += 1, this._renderPage(i.extend({
        pageNum: a
      }, e)).appendTo(g));
      this.state.tailPageNum = a,
      this.state.tailIndex = s,
      0 === a && i('.imgpage').length || this.container.append(g.children());
      var d = this.pageModel.get('adBigPicPos');
      + d > - 1 && this.firstPageData && this.turnAdPage(this.firstPageData, d);
      var p = this.container.find('.rpimgpage').height();
      if (a === window.rpPageNum && this.rpData && this.rpData.data && this.rpData.data.length) {
        try {
          this.trigger('panelAppendRPUpdated', {
            height: this.container.height(),
            rpHeight: p,
            pageNum: 'specialimg',
            state: 'end'
          })
        } catch (h) {
        }
        try {
          this.trigger('panelAppendPosUpdated', {
            height: this.container.height() - p,
            curEPn: this.state.tailIndex + 1,
            pageNum: a,
            state: 'end'
          })
        } catch (h) {
        }
      } else try {
        this.trigger('panelAppendPosUpdated', {
          height: this.container.height(),
          curEPn: this.state.tailIndex + 1,
          pageNum: a,
          state: 'end'
        })
      } catch (h) {
      }
      if (0 === a) {
        this._showPage(),
        this.setDisNum(),
        i('#lastPage').hide();
        try {
          this.trigger('firstload', {
          })
        } catch (h) {
        }
        this.checked || (this.checkIsBlocked(), this.checked = !0)
      }
      this.sendCsLog(this.storeData, a),
      this.storeData = [
      ]
    },
    turnAdPage: function (t, e) {
      var a = t[e];
      if (a) {
        var s = this.container.find('.pageNum0'),
        n = s.width(),
        g = 800,
        o = (a.width - n) / 2,
        r = (a.height - g) / 2,
        d = p.httpsTimg({
          imgUrl: a.objURL
        }),
        h = '#f3f2f3';
        (window.samplekey || '').match(/UI_PC_NAV_EXP:1/) && (h = '#fff'),
        s.find('.imgitem').each(function (e) {
          var a = i(this),
          s = t[e];
          a.append('<div class="adMask" style="background:' + h + ' url(\'' + d + '\') no-repeat ' + ( - o - a.position().left) + 'px ' + ( - r - a.position().top) + 'px ;width:' + s.liWidth + 'px;height:' + (s.liHeight + 1) + 'px;"></div>')
        }),
        setTimeout(function () {
          i('.adMask').each(function (t) {
            var e = this;
            setTimeout(function () {
              i(e).fadeOut(500)
            }, 150 * t)
          })
        }, 2000),
        this.pageModel.set('adBigPicPos', - 1)
      }
    },
    checkIsBlocked: function () {
      var t = this;
      setTimeout(function () {
        var e = t.container.find('.imglist .fcImgli').eq(0);
        e && e.length && e.is(':hidden') && g && g(null, 1101101, {
          blk: !0
        })
      }, 3000)
    },
    _renderPage: function (t) {
      var e = i(this.options.pageTpl),
      a = e.find('.imglist'),
      n = this;
      if (this.isNewFcAd) {
        var g = i(this.options.insertContainerTpl);
        a.append(g),
        g.width(205 * this.options.asyAdNum / this.fcAdLineNum),
        g.height(205 * this.fcAdLineNum)
      }
      0 === t.pageNum && e.find('.note').addClass('firstPage'),
      t.pageNum == n.insertStrategy.pageNum && n.insertStrategy.putItem(a),
      i(t.imgList).each(function (e, i) {
        if (i.detailUrl) {
          var g = s.trim(s.query2Json(s.escapeXSS(i.detailUrl)));
          n.rpData && n.rpData.data && n.rpData.data.length && '0' === g.rpstart && (i = n.imgCollection.mapField(i))
        }
        a.append(n._renderImgItem(e, i)),
        a.addClass('pageNum' + t.pageNum),
        n.storeData.push(i)
      });
      var o = this.pageModel.get('adBigPicPos');
      if (0 === t.pageNum && + o > - 1 && (this.firstPageData = t.imgList), 0 === t.pageNum && i(t.asyAdList).each(function (t, e) {
        g.append(n._renderImgItem(t, e))
      }), 0 === t.pageNum && (this.pageNumFirst = t.imgList.length, this.pageContentFirst = t.imgList), t.pageNum === window.rpPageNum && this.rpData && this.rpData.data && this.rpData.data.length) {
        e = this.renderRpPage(t, e);
        var r = [
        ],
        d = [
        ];
        i(this.pageContentFirst).each(function (t, e) {
          r[t] = n.imgCollection.mapField(e),
          n._renderImgItem(t, r[t])
        }),
        i(t.imgList).each(function (t, e) {
          d[t] = n.imgCollection.mapField(e),
          n._renderImgItem(t, d[t])
        })
      }
      if (4 == t.pageNum && this.pageModel.tempData.get('xgMidData') && this.pageModel.tempData.get('xgMidData').mapXgMidData && this.pageModel.tempData.get('xgMidData').mapXgMidData.length) {
        var p = i(this.options.xgPageTpl),
        h = p.find('.imglist'),
        l = i('<div></div>'),
        m = this.pageModel.tempData.get('xgMidData').mapXgMidData,
        u = this.layoutStrategy.process(m, i.extend(this.getSingleLayoutOptions(), {
          insertStrategy: this.insertStrategy
        }));
        this.xgMidImgList = u[0].imgList;
        var c = 0;
        i(u[0].imgList).each(function (t, e) {
          c += t < u[0].imgList.length - 1 ? parseInt(e.liWidth) + parseInt(e.margin)  : parseInt(e.liWidth);
          var i = n._renderImgItem(t, e);
          i.find('a').attr('picid', e.picId),
          h.append(i)
        }),
        p.find('.bordertop, .borderbottom').css('width', c),
        e.appendTo(l),
        p.appendTo(l),
        e = l.children()
      }
      return e
    },
    renderRpPage: function (t, e) {
      var a = this,
      s = i(this.options.rpPageTpl),
      n = s.find('.imglist'),
      g = i('<div></div>'),
      o = this.layoutStrategy.process(this.pageModel.tempData.get('rpData').data, i.extend(this.getPersonalizedLayoutOptions(), {
        insertStrategy: this.insertStrategy
      }));
      this.pageNumSecond = t.imgList.length;
      var r = this.pageModel.get('fInsertNum') || 0;
      if (this.pageNumFirst + this.pageNumSecond - r >= 0) {
        this.pageModel.tempData.get('fcadData') && this.pageModel.tempData.get('fcadData').fcData && 0 !== this.pageModel.tempData.get('fcadData').fcData.length ? this.pageModel.set('rpstart', this.pageNumFirst + this.pageNumSecond - this.pageModel.tempData.get('fcadData').fcData.length - r)  : this.pageModel.set('rpstart', this.pageNumFirst + this.pageNumSecond - r),
        this.rpImgList = o[0].imgList,
        i(o[0].imgList).each(function (t, e) {
          var i = a._renderImgItem(t, e);
          i.find('a').attr('picid', e.picId),
          n.append(i),
          a.storeData.push(e)
        });
        var d = i('#imgid').width();
        s.find('.bordertop').css('left', (d - 500) / 2),
        s.find('h6').css('left', d / 2),
        e.appendTo(g),
        s.appendTo(g),
        e = g.children(),
        0 === s.find('li').length && s.hide(),
        this.pageModel.set('rpnum', s.find('li').length);
        var p = [
        ];
        return i(this.rpImgList).each(function (t, e) {
          p[t] = a.imgCollection.mapField(e),
          a._renderImgItem(t, p[t])
        }),
        e
      }
    },
    _renderImgItem: function (t, e) {
      var i = null;
      return 'FCAD' === e.type || 'FBAD' === e.type ? (e.fcPos = e.pageNum, i = - 1 === this.state.tailPageNum ? d.decorate(e)  : d.render(e))  : 'TJAD' === e.type || 'TJNAD' === e.type ? (e.fcPos = e.pageNum, i = - 1 === this.state.tailPageNum ? r.decorate(e)  : r.render(e))  : i = - 1 === this.state.tailPageNum ? o.decorate(e, this.pageModel)  : o.render(e, this.pageModel),
      window.speed && e && parseInt(e.__idx_) < 6 && i && i.find('img').bind('load', function () {
        window.speed.firstScCount < 6 && window.speed && window.speed.mark('fs'),
        window.speed.firstScCount++
      }),
      i
    },
    noPage: function () {
      this.setDisNum(),
      i('#noPage').show(),
      i('#pageMore').css('visibility', 'hidden'),
      i('#imgid').css('minHeight', 0)
    },
    _showPage: function () {
      i('#noPage').hide()
    },
    _setPageNum: function (t) {
      this.pageNum = t
    },
    _getPageNum: function () {
      return this.pageNum
    },
    setDisNum: function () {
      this.pageModel.set('bdFmtDispNum', 0 == this.imgCollection.getDispNum() ? this.pageModel.get('bdFmtDispNum')  : this.imgCollection.getDispNum()),
      i('#resultInfo').html('找到相关图片约' + this.pageModel.get('bdFmtDispNum') + '张')
    },
    reset: function (t, e, i, a) {
      this.imgCollection = t,
      this.layoutStrategy = e,
      this.insertStrategy = i || null,
      this.isFirst = a || !1
    },
    refresh: function () {
      this.isFirst || this.clear(),
      this.append(),
      this.preload(),
      this.isFirst = !1
    },
    preload: function () {
      var t = i('#relsearch').offset() ? i('#relsearch').offset()  : i(window).height();
      i(window).height() > t.top && this.append()
    },
    clear: function () {
      this.state.tailIndex = - 1,
      this.state.tailPageNum = - 1,
      this.state.pageNum = - 1,
      this.container.empty()
    },
    sendBdgLog: function () {
      for (var t = 7, e = i(window).scrollTop() + i(window).height(), a = this.container.children('.imgpage'), s = this._bdgNextSent || t - 1, n = [
      ], o = 0; o < a.length && 200 > o; o++) {
        var r = i(a[o]);
        r.children('ul').attr('class').match('pageNum') && n.push(r)
      }
      for (; s < n.length && 200 >= s; ) {
        var r = n[s],
        d = r.find('.fcImgli'),
        p = i(d[d.length - 1]);
        if (s += t, p.length && r.offset().top + r.height() - p.height() < e) {
          for (var h, l = [
          ], m = [
          ], u = [
          ], o = 0; o < d.length; o++) h = i(d[o]).data('imgInfo'),
          h && l.push(h.fromURLHost),
          h && m.push(h.picId),
          h && u.push(h.adFlag);
          g && g(null, 1101004, {
            vs: window.vsid || '',
            url: l.join(','),
            pos: h.posType,
            picid: m.join(','),
            adflags: u.join(','),
            picnum: d.length,
            curr: s - t,
            adtype: window.imgTempData && window.imgTempData.adType
          }),
          this._bdgNextSent = s
        } else if (p.length && r.offset().top > e) break
      }
    },
    sendCsLog: function (t) {
      for (var e = this, a = '', s = 0, n = '', o = '', r = t, d = !1, s = t[0] ? t[0].pageNum : 0, p = 0; p < r.length; p++) a += '' == t[p].cs ? '0,0$' + encodeURIComponent(t[p].objURL) + '$' + (t[p].personalized ? t[p].personalized : '') + '|' : t[p].cs + '$' + encodeURIComponent(t[p].objURL) + '$' + (t[p].personalized ? t[p].personalized : '') + '|',
      t[p].adPicId && t[p].decorationData && (n += t[p].adPicId + ',', 'string' == typeof t[p].decorationData && (t[p].decorationData = i.parseJSON(t[p].decorationData)), o += t[p].decorationData.strategy + ',');
      if (this.xgMidImgList && this.xgMidImgList.length && !d) {
        d = !0;
        var h = '',
        l = '';
        i(this.xgMidImgList).each(function (t, i) {
          t < e.xgMidImgList.length - 1 ? (h += i.picId + ',', l += i.fromURLHost + ',')  : (h += i.picId, l += i.fromURLHost)
        }),
        g && g(null, 1101002, {
          picnum: this.xgMidImgList.length,
          picid: h,
          url: l,
          vs: window.vsid || '',
          curr: 5
        })
      }
      var m = {
        format: '$contsign$objurl$personalized',
        cs: a,
        vs: window.vsid || '',
        pn: s,
        personalized: this.pageModel.get('personalized') > 0 ? 1 : 0
      };
      n && (m.adPicId = encodeURIComponent(n)),
      o && (m.strategy = encodeURIComponent(o)),
      g(null, 57, m)
    }
  }),
  e
});
; /*!searchresult:widget/ui/controls/hoverBox/hoverBox.js*/
define('searchresult:widget/ui/controls/hoverBox/hoverBox', function (t) {
  function e(t) {
    this.$container = a('#imgid'),
    this.loadTimer = null,
    this.leavetimer = null,
    this.pn = 0,
    this.cs = 0,
    this.currObjURL = 0,
    this.currFromURL = 0,
    this.adType = '0',
    this.imgid = '',
    this.model = t,
    this.templates = {
      normal: '<div class=\'hover\'>\n<div class=\'ct\'>\n<div style=\'padding-top: 7px;\'>\n<a class=\'title\' target=\'_blank\'></a>\n<br>\n<a class=\'size\'></a>\n<div>\n<a class=\'dutu\' target=\'_blank\' title=\'按图片搜索\'></a>\n<a target=\'_self\' class=\'down\' onclick=\'return p(null, 390, {newp: 42});\' title=\'下载原图\'></a>\n</div>\n</div>',
      origin: '<div class=\'hover decoration\'>\n<div class=\'ct\'>\n<a class=\'title\' target=\'_blank\'>\n</a>\n<p class=\'subTitle\'>\n</p>\n<a class=\'dutu\' target=\'_blank\' title=\'按图片搜索\'></a>\n<a target=\'_self\' class=\'down\' onclick=\'return p(null, 390, {newp: 42});\' title=\'下载原图\'></a>\n</div>\n</div>',
      designer: '<div class=\'hover decorationDesigner\'>\n<div class=\'ct\'>\n<p class="designer"></p>\n<a class=\'desTitle\' target=\'_blank\'>\n</a>\n<div class=\'headPic\'>\n</div>\n<a class=\'dutu\' target=\'_blank\' title=\'按图片搜索\'></a>\n<a target=\'_self\' class=\'down\' onclick=\'return p(null, 390, {newp: 42});\' title=\'下载原图\'></a>\n</div>\n</div>'
    },
    this.bindEvent()
  }
  var a = t('common:widget/ui/base/base'),
  i = t('searchresult:widget/ui/utils/utils'),
  n = t('common:widget/ui/base/events'),
  r = t('searchresult:widget/ui/statistic/statistic');
  return a.extend(e.prototype, n, {
    bindEvent: function () {
      var t = this;
      t.leavetimer = null,
      this.$container.on('mouseenter', '.imgpage .imgitem', function () {
        t.hover(a(this))
      }),
      this.$container.on('mouseleave', '.imgpage .imgitem', function () {
        t.leave(a(this))
      }),
      this.$container.on('mousedown', '.hover .title, .hover .desTitle', function (e) {
        var a = {
          ist: '',
          sr: 0,
          u: t.currObjURL,
          f: t.currFromURL,
          cs: t.cs,
          t: 1,
          personalized: t.personalized
        };
        t.decorationItems && (a.adPicId = encodeURIComponent(t.decorationItems.adPicId), a.strategy = encodeURIComponent(t.decorationItems.strategy)),
        r(e, 1, a)
      }),
      this.$container.on('mousedown', '.hover .down', function (e) {
        var a = {
          ist: '',
          sr: 0,
          adType: t.adType,
          u: t.currObjURL,
          f: t.currFromURL,
          cs: t.cs,
          pn: t.pn,
          t: 1,
          personalized: t.personalized
        };
        t.decorationItems && (a.adPicId = encodeURIComponent(t.decorationItems.adPicId), a.strategy = encodeURIComponent(t.decorationItems.strategy)),
        r(e, 7, a);
        var i = t.model.get('cg');
        if ('head' === i || 'wallpaper' === i || 'girl' === i) {
          var n = {
            imgid: t.pi,
            category: i,
            tag: t.model.data.queryWord,
            prfix: 'download'
          };
          t.rc(n)
        }
      }),
      this.$container.on('click', '.dutu', function () {
        a.cookie('uploadTime', (new Date).getTime(), {
          path: '/'
        })
      })
    },
    hover: function (t) {
      t.find('.img-time').hide(),
      this.loadTimer = (new Date).getTime(),
      clearTimeout(this.leavetimer),
      0 == a('.hover', t).length && t.append(this.buildTemplate(t)),
      this.populateTempData(t),
      this.play(t)
    },
    play: function (t) {
      var e = t.data('decoration'),
      i = e ? 2 === + e ? 104 : 58 : 50,
      n = 2 === + e ? 23 : 0;
      this.top = i;
      var r = a('.hover', t),
      s = a('.hactive', this.pullimages),
      o = 0,
      d = 9999;
      s.length > 0 && (s.removeClass('hactive'), o = s.offset().left, d = s.offset().top),
      t.addClass('hactive');
      var l = t.offset().left,
      c = t.offset().top,
      h = 0,
      u = 0,
      m = t.width();
      d === c && o === l ? u = i : d > c + i ? u = i : c - i > d ? u = - i : h = o > l ? m : - m,
      a('.ct', r).stop().css({
        left: h,
        top: u + n
      }).animate({
        left: 0,
        top: n,
        easing: 'linear'
      }, 250),
      s.length > 0 && (0 != u ? u = - u : h > 0 ? h = - 1 * s.width()  : 0 > h && (h = s.width()), a('.ct', s).stop().animate({
        left: h,
        top: u + n,
        easing: 'linear'
      }, 250, function () {
        a('.hover', s).remove()
      }))
    },
    buildTemplate: function (t) {
      var e = t.data('decoration') || 'normal';
      return 1 === + e && (e = 'origin'),
      2 === + e && (e = 'designer'),
      this.templates[e]
    },
    populateTempData: function (t) {
      var e = a('.hover', t),
      n = t.attr('pn'),
      r = t.attr('data-pi') || '',
      s = t.attr('data-specialType') || '',
      o = t.attr('data-title') || '',
      d = t.attr('data-width') || '',
      l = t.attr('data-height') || '',
      c = t.attr('data-fromURLHost') || '',
      h = (t.attr('data-fromURL') || '', t.attr('data-ext') || '', t.attr('data-objURL') || ''),
      u = t.attr('data-thumbURL') || '',
      m = t.attr('data-fromURL') || '',
      p = t.attr('data-cs') || '',
      g = t.data('decoration'),
      f = t.data('desc'),
      v = t.data('tags'),
      w = t.data('author'),
      b = t.data('authorUrl'),
      I = t.data('adPicId'),
      U = t.data('strategy'),
      y = t.find('img').attr('data-imgurl'),
      T = t.find('img').attr('src') || y;
      0 === T.indexOf('data:') && y && (T = y);
      var R = '/n/pc_search';
      R += '?queryImageUrl=' + encodeURIComponent(T),
      R += '&word=' + (this.model && this.model.get('queryWordEnc')),
      R += '&fm=searchresult&uptype=button',
      this.pn = n,
      this.cs = p,
      this.currObjURL = h,
      this.currFromURL = m,
      this.personalized = t.attr('data-personalized'),
      this.adType = s,
      this.pi = r,
      this.decorationItems = {
        adPicId: I,
        strategy: U,
        decoration: g,
        tags: v,
        desc: f,
        author: w,
        authorUrl: b
      };
      var x,
      L = t.width(),
      C = '',
      k = '',
      _ = '',
      P = Math.floor(L / 10 - 7),
      z = new RegExp('<strong>(.+)</strong>'),
      O = o.replace('<strong>', '').replace('</strong>', '');
      if (o && o.length > 0 && (_ = k = o), k.length > P && (k.indexOf('<strong>') >= 0 ? (x = z.exec(k) [1], k = O.substring(0, P) + '...', k = k.replace(x, '<strong>' + x + '</strong>'))  : k = k.substring(0, P) + '...'), d * l > 0 && (C = d + 'x' + l), e.attr('title', '图片来源： ' + c + '\n图片描述：' + i.trimTags(_ || this.model.get('queryWord'))), g) {
        if (1 === + g) {
          e.find('.title').text(f).attr('href', i.uncompile(m));
          for (var v = v.split('|'), D = '', j = 0; j < v.length; j++) D += '<span class="tag">' + a.trim(v[j]) + '</span>';
          e.find('.subTitle').html(D)
        }
        2 === + g && (e.find('.designer').text(w), e.find('.desTitle').text(f).attr('href', i.uncompile(m)), e.find('.headPic').css('backgroundImage', 'url(' + b + ')'))
      } else a('.title', e).html(k || this.model.get('queryWord')).attr('href', i.uncompile(m)),
      a('.size', e).html(C);
      a('.dutu', e).attr('href', R),
      a('.down', e).attr('href', '/search/down?tn=download&ipn=dwnl&word=download&ie=utf8&fr=result&url=' + encodeURIComponent(h) + '&thumburl=' + encodeURIComponent(u)),
      t.width() < 77 + a('.size', e).width() && a('.dutu', e).hide() && a('.down', e).css('right', '10px')
    },
    rc: function (t) {
      var e = t.imgid || '',
      i = t.category,
      n = t.tag,
      r = t.prfix || 'click';
      e && a.getJSON('/counter/picture' + r, {
        picture_id: e,
        category: i,
        tag: n,
        sortlog: 0,
        times: (new Date).getTime()
      }, function () {
      })
    },
    leave: function (t) {
      if (t.find('.img-time').show(), t.hasClass('hactive') && !t.hasClass('unhover')) {
        this.leavetimer = setTimeout(function () {
          a('.ct', t).stop().animate({
            top: this.top,
            easing: 'linear'
          }, 250, function () {
            t.removeClass('hactive')
          })
        }.bind(this), 80);
        var e = (new Date).getTime() - (this.loadTimer + 400),
        i = this;
        if (0 >= e || 0 == this.loadTimer);
         else {
          var n = {
            vtime: e,
            pn: i.pn,
            cs: i.cs,
            u: i.currObjURL,
            f: i.currFromURL
          };
          this.decorationItems && (n.adPicId = encodeURIComponent(this.decorationItems.adPicId), n.strategy = encodeURIComponent(this.decorationItems.strategy)),
          r(null, 29, n)
        }
      }
    }
  }),
  e
});
; /*!searchresult:widget/ui/controls/memoryBar/memoryBar.js*/
define('searchresult:widget/ui/controls/memoryBar/memoryBar', function (t) {
  function i(t) {
    this.id = 'memoryBar',
    this.model = t,
    this.$container = e('#memoryBar')
  }
  {
    var e = t('common:widget/ui/base/base');
    t('searchresult:widget/ui/statistic/statistic')
  }
  return e.extend(i.prototype, {
    init: function () {
      var t = e.cookie('BDqhfp') || '',
      i = this._splitInfo(t);
      i[0] === this.model.get('word') && i[1] === this.model.get('ic') + this.model.get('width') + this.model.get('height') + this.model.get('z') + this.model.get('st') + this.model.get('face') + this.model.get('lm') + this.model.get('s') && i[2] && i[3] && i[3] > 3 && (e('.memory-page').html(i[3]), this.hide(), this._bindEvent(i))
    },
    changeHeight: function (t) {
      var i = this;
      return e(window).scrollTop(e(window).scrollTop() + 10),
      t <= e(window).scrollTop() ? (i.hide(), this.model.set('isAutoScroll', 0), 1)  : setTimeout(function () {
        i.changeHeight(t)
      }, 0.1)
    },
    setLocaldata: function () {
    },
    _splitInfo: function (t) {
      var i = t.split('&&');
      return i
    },
    _bindEvent: function (t) {
      var i = this;
      e('.memory-close').bind('click', i.hide),
      e('.memory-link').bind('click', function () {
        i.changeHeight(t[2])
      })
    },
    show: function () {
      this.$container.show()
    },
    hide: function () {
      e('#memoryBar').hide()
    }
  }),
  i
});
; /*!searchresult:widget/ui/base/common/common.js*/
define('searchresult:widget/ui/base/common/common', function (e) {
  var t = e('common:widget/ui/base/base'),
  o = navigator.userAgent.toLowerCase();
  if (window.browser = {
    version: (o.match(/.+(?:rv|it|ra|ie)[\/: ]([\d.]+)/) || [
      0,
      '0'
    ]) [1],
    safari: /webkit/i.test(o) && !this.chrome,
    opera: /opera/i.test(o),
    firefox: /firefox/i.test(o),
    ie: /msie/i.test(o) && !/opera/.test(o),
    mozilla: /mozilla/i.test(o) && !/(compatible|webkit)/.test(o) && !this.chrome,
    chrome: /chrome/i.test(o) && /webkit/i.test(o) && /mozilla/i.test(o)
  }, window.browser.ie) {
    var r = 6;
    10 == document.documentMode ? r = '10' : 9 == document.documentMode ? r = '9' : window.postMessage ? r = '8' : window.XMLHttpRequest ? r = '7' : document.compatMode && (r = '6'),
    window.browser.version = r
  }
  window.browser.ie && 1 * window.browser.version <= 6 && (t.fx.off = !0),
  window.html_encode = function (e) {
    var t = '';
    return 0 == e.length ? '' : (t = e.replace(/&/g, '&gt;'), t = t.replace(/</g, '&lt;'), t = t.replace(/>/g, '&gt;'), t = t.replace(/\'/g, '&#39;'), t = t.replace(/\"/g, '&quot;'), t = t.replace(/\n/g, '<br>'))
  },
  window.html_decode = function (e) {
    var t = '';
    return 0 == e.length ? '' : (t = e.replace(/&gt;/g, '&'), t = t.replace(/&lt;/g, '<'), t = t.replace(/&gt;/g, '>'), t = t.replace(/&nbsp;/g, ' '), t = t.replace(/&#39;/g, '\''), t = t.replace(/&quot;/g, '"'), t = t.replace(/<br>/g, '\n'))
  },
  window.fiximg = function (e, o, r) {
    var i = t(e).width(),
    n = t(e).height();
    o && i > o && (n = o * n / i, i = o),
    r && n > r && (i = r * i / n, n = r),
    o && i > o && (n = o * n / i, i = o),
    t(e).css({
      width: i + 'px',
      height: n + 'px'
    })
  },
  window.fixword = function (e, t, o) {
    e = e.replace(/ /g, ''),
    o = o || 12;
    var r = Math.floor(t / o);
    return e.length < r && (e = e.substring(0, r)),
    e
  }
});
; /*!searchresult:widget/ui/base/windowHandle/windowHandle.js*/
define('searchresult:widget/ui/base/windowHandle/windowHandle', function (e, i, n) {
  var t = e('common:widget/ui/base/base'),
  o = e('common:widget/ui/EventEmitter/EventEmitter'),
  r = function () {
    {
      var e = (t('.header').outerHeight(), t('#lefter'));
      t('#floatHeader'),
      t('.header')
    }
    o.eventCenter.on('search-box-switch', function (i) {
      'fixed' != i.state || e.hasClass('fixedLefter') ? 'top' == i.state && e.hasClass('fixedLefter') && (window.browser.ie && 1 * window.browser.version == 6 || e.removeClass('fixedLefter'), e.trigger('RESIZE_LEFTER'))  : (window.browser.ie && 1 * window.browser.version == 6 || e.addClass('fixedLefter'), e.trigger('RESIZE_LEFTER'))
    })
  };
  t.extend(r.prototype, {
    clientHeight: function () {
      return document.documentElement.clientHeight || window.innerHeight
    },
    clientWidth: function () {
      return document.documentElement.clientWidth || window.innerWidth
    },
    doresize: function () {
      this.clientHeight()
    },
    scrollTop: function () {
      return document.body.scrollTop || document.documentElement.scrollTop
    },
    scrollLeft: function () {
      return document.body.scrollLeft || document.documentElement.scrollLeft
    },
    iniResize: function () {
    },
    doscroll: function () {
    },
    iniScroll: function () {
    },
    fixresize: function (e) {
      var i = this;
      return window.browser.ie ? (window.fixresizefn && window.fixresizefn.length > 0 ? window.fixresizefn.push(e)  : window.fixresizefn = [
        e
      ], window.fixresizetimer, window.fixwidth = i.clientWidth(), window.fixheight = i.clientHeight(), void t(window).resize(function () {
        (window.fixwidth != i.clientWidth() || window.fixheight != i.clientHeight()) && (Math.abs(window.fixwidth - i.clientWidth()) < 20 && Math.abs(window.fixheight - i.clientHeight()) <= 20 || (window.fixwidth = i.clientWidth(), window.fixheight = i.clientHeight(), clearTimeout(window.fixresizetimer), window.fixresizetimer = setTimeout(function () {
          if (window.fixresizefn && window.fixresizefn.length) for (var e in window.fixresizefn) window.fixresizefn[e].call(window);
          clearTimeout(window.fixresizetimer)
        }, 200)))
      }))  : void t(window).resize(e)
    }
  }),
  window.handle = n.exports = new r
});
; /*!searchresult:widget/ui/base/view/AvFilterView/AvFilterView.js*/
define('searchresult:widget/ui/base/view/AvFilterView/AvFilterView', function (i, t, a) {
  var e = i('common:widget/ui/base/base'),
  s = i('common:widget/ui/base/events'),
  n = i('searchresult:widget/ui/statistic/statistic'),
  c = a.exports = function () {
    this.lastid = null
  };
  e.extend(c.prototype, s, {
    ini: function () {
    },
    optcfg: [
    ],
    render: function () {
      var i = this,
      t = '<div id="' + i.id + '" class="avfilter" ><div class="icon"></div><div class="title">' + i.title + '</div><div class="options"></div>' + (i.blank ? '<div class="blank"></div>' : '') + '</div>',
      a = e(t);
      i.container.append(a),
      i.o = a.find('.options');
      for (var s in i.optcfg) {
        i.optcfg[s].active && (this.lastid = s);
        var n = e('<a class="item ' + (i.optcfg[s].style ? i.optcfg[s].style : '') + ' ' + (i.optcfg[s].active ? 'active' : '') + (i.optcfg[s].hidden ? ' hidden' : '') + '" >' + i.optcfg[s].title + '</a>');
        n[0].i = s,
        i.optcfg[s].param && e(n).click(function () {
          i.change(this),
          i.changeParam(this)
        }),
        i.optcfg[s].mouseenter && e(n).mouseenter(function () {
          i.optcfg[this.i].mouseenter(this)
        }),
        i.o.append(n)
      }
      e(window).bind('RESETAVFILTERS', function () {
        i.resetParam()
      })
    },
    change: function (i) {
      var t = this,
      a = i.i;
      if (this.lastid != a) {
        this.lastid = a;
        for (var s in t.optcfg) s !== a && t.optcfg[s].changeout && t.optcfg[s].changeout();
        t.o.find('.item.active').removeClass('active'),
        e(i).addClass('active')
      }
    },
    changeParam: function (i) {
      var t = this,
      a = {
      },
      e = i.i;
      if ('string' == typeof t.optcfg[e].param) a[t.optcfg[e].param] = t.optcfg[e].value;
       else for (var s in t.optcfg[e].param) a[t.optcfg[e].param[s]] = t.optcfg[e].value[s];
      a.cl = '',
      a.ct = '',
      this.dispatchEvent('sizeChanged', a),
      n(null, 390, {
        newp: 383,
        tp: t.id
      })
    },
    resetParam: function () {
      var i = this;
      i.o.find('.item.active').removeClass('active');
      for (var t in i.optcfg) {
        var a = i.optcfg[t];
        if (t !== this.lastid && a.changeout && a.changeout(), a.base && a.param) {
          var e = {
          };
          if ('string' == typeof a.param) e[a.param] = a.value;
           else for (var s in a.param) e[a.param[s]] = a.value[s];
          e.cl = '',
          e.ct = '',
          this.dispatchEvent('sizeChanged', e),
          n(null, 390, {
            newp: 383,
            tp: i.id
          }),
          i.lastid = t,
          i.o.find('.item:eq(' + t + ')').addClass('active')
        }
      }
    },
    hide: function () {
      e('#' + this.id).hide()
    },
    show: function () {
      e('#' + this.id).show()
    }
  })
});
; /*!searchresult:widget/ui/base/view/AvMuiltSizeFilterView/AvMuiltSizeFilterView.js*/
define('searchresult:widget/ui/base/view/AvMuiltSizeFilterView/AvMuiltSizeFilterView', function (i, e, t) {
  var h = i('common:widget/ui/base/base'),
  n = i('searchresult:widget/ui/base/view/AvFilterView/AvFilterView'),
  o = i('searchresult:widget/ui/statistic/statistic'),
  c = t.exports = function () {
    this.id = 'avfilter_msize',
    this.title = '',
    this.container = null,
    this.timerPc = null,
    this.timerPhone = null
  };
  h.extend(c.prototype, n.prototype, {
    ini: function (i) {
      var e = this;
      this.model = i.model,
      e.container = i.container,
      e.blank = i.blank === !1 ? !1 : !0,
      e.optcfg = [
        {
          title: '全部尺寸',
          base: !0,
          style: 'allsize',
          param: [
            'width',
            'height'
          ],
          value: [
            '',
            ''
          ]
        },
        {
          title: '您的屏幕尺寸：' + window.screen.width + 'x' + window.screen.height,
          style: 'mine',
          param: [
            'width',
            'height'
          ],
          value: [
            window.screen.width,
            window.screen.height
          ]
        },
        {
          title: '<div class="pcct">电脑壁纸</div>',
          style: 'pc',
          mouseenter: function () {
            e.showPc()
          },
          changeout: function () {
            e.outPc()
          }
        },
        {
          title: '<div class="phonect">手机壁纸</div>',
          style: 'phone',
          mouseenter: function () {
            e.showPhone()
          },
          changeout: function () {
            e.outPhone()
          }
        }
      ],
      e.pc = [
        {
          width: 1920,
          height: 1200
        },
        {
          width: 1920,
          height: 1080
        },
        {
          width: 1680,
          height: 1050
        },
        {
          width: 1600,
          height: 900
        },
        {
          width: 1440,
          height: 900
        },
        {
          width: 1366,
          height: 768
        },
        {
          width: 1360,
          height: 768
        },
        {
          width: 1280,
          height: 1024
        },
        {
          width: 1280,
          height: 960
        },
        {
          width: 1280,
          height: 800
        },
        {
          width: 1280,
          height: 768
        },
        {
          width: 1280,
          height: 720
        },
        {
          width: 1280,
          height: 960
        },
        {
          width: 1152,
          height: 864
        },
        {
          width: 1090,
          height: 1080
        },
        {
          width: 1080,
          height: 960
        },
        {
          width: 1024,
          height: 768
        }
      ],
      e.phone = [
        {
          height: 2560,
          width: 1440
        },
        {
          height: 1920,
          width: 1080
        },
        {
          height: 1334,
          width: 750
        },
        {
          height: 1280,
          width: 720
        },
        {
          height: 1136,
          width: 640
        },
        {
          height: 960,
          width: 640
        },
        {
          height: 960,
          width: 540
        },
        {
          height: 854,
          width: 480
        },
        {
          height: 800,
          width: 480
        },
        {
          height: 480,
          width: 320
        }
      ];
      var t = this.model.get('width') || 0,
      n = this.model.get('height') || 0;
      for (var o in e.optcfg) e.optcfg[o].value && 1 * e.optcfg[o].value[0] == t && 1 * e.optcfg[o].value[1] == n && (e.optcfg[o].active = !0);
      if (e.render(), e.renderPcFilter(), e.renderPhoneFilter(), t && n) if (t == window.screen.width && n == window.screen.height) h('.item.active', e.o).removeClass('active'),
      h('.item.mine', e.o).addClass('active');
       else {
        for (var o in e.pc) t == e.pc[o].width && n == e.pc[o].height && (e.lastid = 10 + o, e.o.find('.pcitem:eq(' + o + ')').click());
        for (var o in e.phone) t == e.phone[o].width && n == e.phone[o].height && (e.lastid = 50 + o, e.o.find('.phoneitem:eq(' + o + ')').click())
      }
    },
    renderPcFilter: function () {
      var i = this,
      e = i.o.find('.item.pc'),
      t = '';
      for (var n in i.pc) {
        var o = i.pc[n];
        t += '<div class="pcitem">' + o.width + 'x' + o.height + '</div>'
      }
      var c = '<div class="pc_arrow pccb"></div><div class="pc_container pccb" style="width: 148px;height:215px;">' + t + '<div></div></div><div class="pc_selected"></div>';
      e.append(c),
      e.bind('mouseleave', function () {
        i.hidePc()
      }),
      h('.pcitem', e).click(function () {
        i.changePc(this)
      })
    },
    showPc: function () {
      this.hidePhone(!0),
      clearTimeout(this.timerPc),
      this.timerPc = null,
      this.o.find('.pccb').show(),
      this.o.addClass('pcon')
    },
    hidePc: function (i) {
      var e = this;
      clearTimeout(this.timerPc),
      e.timerPc = null,
      e.timerPc = setTimeout(function () {
        e.o.find('.pccb').hide(),
        e.o.find('.item.pc').removeClass('pcon')
      }, i ? 0 : 500)
    },
    changePc: function (i) {
      var e = this,
      t = h(i).index();
      if (e.o.find('.pccb').hide(), e.o.removeClass('pcon'), h('.actcs', e.o).removeClass('actcs'), h('.item.active', e.o).removeClass('active'), h('.item.pc', e.o).addClass('active'), h(i).addClass('actcs'), e.lastid != 10 + t) {
        var n = {
        };
        n.width = e.pc[t].width,
        n.height = e.pc[t].height,
        h('.pcct', e.o).html(n.width + 'x' + n.height),
        o(null, 390, {
          newp: 383,
          tp: e.id,
          attr: 'pc'
        }),
        n.cl = '',
        n.ct = '',
        this.dispatchEvent('sizeChanged', n),
        e.lastid = 10 + t,
        e.outPhone()
      }
    },
    outPc: function () {
      h('.pcct', this.o).html('电脑壁纸'),
      h('.pc .actcs', this.o).removeClass('actcs')
    },
    renderPhoneFilter: function () {
      var i = this,
      e = i.o.find('.item.phone'),
      t = '';
      for (var n in i.phone) {
        var o = i.phone[n];
        t += '<div class="phoneitem">' + o.height + 'x' + o.width + '</div>'
      }
      var c = '<div class="phone_arrow phonecb"></div><div class="phone_container phonecb" style="width: 148px;height:215px;">' + t + '<div></div></div><div class="phone_selected"></div>';
      e.append(c),
      e.bind('mouseleave', function () {
        i.hidePhone()
      }),
      h('.phoneitem', e).click(function () {
        i.changePhone(this)
      })
    },
    showPhone: function () {
      this.hidePc(!0),
      clearTimeout(this.timerPhone),
      this.timerPhone = null,
      this.o.find('.phonecb').show(),
      this.o.addClass('phoneon')
    },
    hidePhone: function (i) {
      var e = this;
      clearTimeout(this.timerPhone),
      e.timerPhone = null,
      e.timerPhone = setTimeout(function () {
        e.o.find('.phonecb').hide(),
        e.o.find('.item.phone').removeClass('phoneon')
      }, i ? 0 : 500)
    },
    changePhone: function (i) {
      var e = this,
      t = h(i).index();
      if (e.o.find('.phonecb').hide(), e.o.removeClass('phoneon'), h('.actcs', e.o).removeClass('actcs'), h('.item.active', e.o).removeClass('active'), h('.item.phone', e.o).addClass('active'), h(i).addClass('actcs'), e.lastid != 50 + t) {
        var n = {
        };
        n.width = e.phone[t].width,
        n.height = e.phone[t].height,
        h('.phonect', e.o).html(n.height + 'x' + n.width),
        o(null, 390, {
          newp: 383,
          tp: e.id,
          attr: 'phone'
        }),
        n.cl = '',
        n.ct = '',
        this.dispatchEvent('sizeChanged', n),
        e.lastid = 50 + t,
        e.outPc()
      }
    },
    outPhone: function () {
      h('.phonect', this.o).html('手机壁纸'),
      h('.phone .actcs', this.o).removeClass('actcs')
    }
  })
});
; /*!searchresult:widget/ui/base/view/AvTypeFilterView/AvTypeFilterView.js*/
define('searchresult:widget/ui/base/view/AvTypeFilterView/AvTypeFilterView', function (e, t, i) {
  var a = e('common:widget/ui/base/base'),
  l = e('searchresult:widget/ui/base/view/AvFilterView/AvFilterView'),
  r = i.exports = function () {
    this.id = 'avfilter_type',
    this.title = '头像格式',
    this.container = null
  };
  a.extend(r.prototype, l.prototype, {
    ini: function (e) {
      var t = this;
      this.model = e.model,
      t.container = e.container,
      t.blank = e.blank === !1 ? !1 : !0,
      t.optcfg = [
        {
          title: '全部',
          base: !0,
          param: 'lm',
          value: ''
        },
        {
          title: '动态',
          param: 'lm',
          value: '6'
        },
        {
          title: '静态',
          param: 'lm',
          value: '7'
        }
      ],
      t.title = e.title || t.title;
      var i = + this.model.get('lm') || 0;
      6 == i ? t.optcfg[1].active = !0 : 7 == i ? t.optcfg[2].active = !0 : t.optcfg[0].active = !0,
      t.render()
    }
  })
});
; /*!searchresult:widget/ui/base/view/AvColorWallFilterView/AvColorWallFilterView.js*/
define('searchresult:widget/ui/base/view/AvColorWallFilterView/AvColorWallFilterView', function (o, l, e) {
  var s = o('common:widget/ui/base/base'),
  r = o('searchresult:widget/ui/base/view/AvFilterView/AvFilterView'),
  t = o('searchresult:widget/ui/statistic/statistic'),
  i = e.exports = function () {
    this.id = 'avfilter_wallcolor',
    this.title = '',
    this.container = null,
    this.timer = null
  };
  s.extend(i.prototype, r.prototype, {
    ini: function (o) {
      var l = this;
      this.model = o.model,
      l.container = o.container,
      l.blank = o.blank === !1 ? !1 : !0,
      l.optcfg = [
        {
          title: '全部颜色',
          base: !0,
          param: 'ic',
          value: '',
          hidden: !0
        },
        {
          title: '<div class="colorstitle">全部颜色</div>',
          style: 'colors',
          mouseenter: function () {
            l.showColors()
          },
          changeout: function () {
            l.outColors()
          }
        }
      ],
      l.colors = [
        {
          value: '1',
          text: '红色',
          color: '#DE2020',
          borderC: '#CB1C1C',
          'class': 'red'
        },
        {
          value: '256',
          text: '橙色',
          color: '#FE6C00',
          borderC: '#E96300',
          'class': 'orange'
        },
        {
          value: '2',
          text: '黄色',
          color: '#FEBF00',
          borderC: '#E9B000',
          'class': 'yellow'
        },
        {
          value: '4',
          text: '绿色',
          color: '#59A725',
          borderC: '#539B23',
          'class': 'green'
        },
        {
          value: '32',
          text: '紫色',
          color: '#892BCF',
          borderC: '#7A27B7',
          'class': 'purple'
        },
        {
          value: '64',
          text: '粉色',
          color: '#D744BA',
          borderC: '#C63FAB',
          'class': 'pink'
        },
        {
          value: '8',
          text: '青色',
          color: '#06B7C8',
          borderC: '#07A6B7',
          'class': 'cyan'
        },
        {
          value: '16',
          text: '蓝色',
          color: '#0065FE',
          borderC: '#005CEB',
          'class': 'blue'
        },
        {
          value: '128',
          text: '棕色',
          color: '#733413',
          borderC: '#6B3012',
          'class': 'gray'
        },
        {
          value: '1024',
          text: '白色',
          color: '#fff',
          borderC: '#C0BABC',
          'class': 'white',
          type: 3
        },
        {
          value: '512',
          text: '黑色',
          color: '#000',
          borderC: '#000',
          'class': 'black'
        },
        {
          value: '2048',
          text: '黑白',
          type: 2,
          tips: '黑白',
          borderC: '#fff',
          'class': 'bw',
          bg: '#fff url(//img0.bdstatic.com/img/image/newFilterBg.png) no-repeat -1px -319px'
        }
      ];
      var e = + this.model.get('ic') || 0;
      for (var r in l.optcfg) 1 * l.optcfg[r].value == e && (l.optcfg[r].active = !0);
      var t = null;
      for (var r in l.colors) {
        var i = 1 * l.colors[r].value;
        e == i && 1024 != e && 512 != e && (t = r, l.optcfg[1].active = !0)
      }
      if (l.render(), l.renderColors(), t) {
        var i = l.colors[t];
        s('.citem:eq(' + t + ')', l.o).addClass('actcs'),
        l.o.find('.colors_selected').css({
          borderColor: i.borderC,
          background: i.bg ? i.bg : i.color
        }).show(),
        l.o.find('.item.colors').removeClass('active').removeClass('colorsall'),
        l.o.find('.item.colors .colorstitle').html(i.text)
      } else l.o.find('.item.colors').addClass('colorsall')
    },
    renderColors: function () {
      var o = this,
      l = o.o.find('.item.colors'),
      e = '';
      for (var r in o.colors) {
        var t = o.colors[r];
        e += '<div class="citem ' + t['class'] + '" title="' + t.text + '"  style="background:' + (t.bg ? t.bg : t.color) + ';border-color:' + t.borderC + '" ></div>'
      }
      var i = '<div class="colors_arrow cb"></div><div class="colors_container cb" style="width: 128px;height:125px;"><div class="colors_allbtn">全部颜色</div><div class="colors_blink"></div>' + e + '<div></div></div><div class="colors_selected"></div>';
      l.append(i),
      l.bind('mouseleave', function () {
        o.hideColors()
      }),
      s('.citem', l).click(function () {
        o.changeColors(this)
      }),
      o.o.find('.colors_allbtn').click(function () {
        o.resetParam(),
        o.hideColors(!0)
      })
    },
    showColors: function () {
      clearTimeout(this.timer),
      this.timer = null,
      this.o.find('.cb').show(),
      this.o.addClass('colorson')
    },
    hideColors: function (o) {
      var l = this;
      l.timer = setTimeout(function () {
        l.o.find('.cb').hide(),
        l.o.find('.item.colors').removeClass('colorson')
      }, o ? 0 : 500)
    },
    colorsall: function () {
      this.o.find('.item.colors .colorstitle').html('全部颜色'),
      this.o.find('.item.colors').addClass('colorsall')
    },
    changeColors: function (o) {
      var l = this,
      e = s(o).index() - 2;
      if (l.lastid != 10 + e) {
        l.o.find('.cb').hide(),
        l.o.removeClass('colorson'),
        l.o.find('.item.colors').removeClass('colorsall'),
        l.o.find('.item.colors .colorstitle').html(l.colors[e].text),
        t(null, 390, {
          newp: 383,
          tp: l.id,
          attr: l.colors[e].value
        }),
        l.o.find('.colors_selected').css({
          borderColor: l.colors[e].borderC,
          background: l.colors[e].bg ? l.colors[e].bg : l.colors[e].color
        }).show(),
        s('.actcs', l.o).removeClass('actcs'),
        s(o).addClass('actcs');
        var r = {
        };
        r.ic = l.colors[e].value,
        r.cl = '',
        r.ct = '',
        this.dispatchEvent('sizeChanged', r),
        l.lastid = 10 + e
      }
    },
    outColors: function () {
      s('.actcs', this.o).removeClass('actcs'),
      this.o.find('.colors_selected').hide(),
      this.colorsall()
    }
  })
});
; /*!searchresult:widget/ui/base/view/AvColorFilterView/AvColorFilterView.js*/
define('searchresult:widget/ui/base/view/AvColorFilterView/AvColorFilterView', function (o, e, r) {
  var t = o('common:widget/ui/base/base'),
  l = o('searchresult:widget/ui/base/view/AvFilterView/AvFilterView'),
  s = o('searchresult:widget/ui/statistic/statistic'),
  c = r.exports = function () {
    this.id = 'avfilter_color',
    this.title = '头像色调',
    this.container = null,
    this.timer = null
  };
  t.extend(c.prototype, l.prototype, {
    ini: function (o) {
      var e = this;
      this.model = o.model,
      e.container = o.container,
      e.blank = o.blank === !1 ? !1 : !0,
      e.optcfg = [
        {
          title: '全部',
          base: !0,
          param: 'ic',
          value: ''
        },
        {
          title: '黑色',
          param: 'ic',
          value: '512'
        },
        {
          title: '白色',
          param: 'ic',
          value: '1024'
        },
        {
          title: '其他颜色',
          style: 'colors',
          mouseenter: function () {
            e.showColors()
          },
          changeout: function () {
            e.outColors()
          }
        }
      ],
      e.colors = [
        {
          value: '1',
          text: '红色',
          color: '#DE2020',
          borderC: '#CB1C1C',
          'class': 'red'
        },
        {
          value: '256',
          text: '橙色',
          color: '#FE6C00',
          borderC: '#E96300',
          'class': 'orange'
        },
        {
          value: '2',
          text: '黄色',
          color: '#FEBF00',
          borderC: '#E9B000',
          'class': 'yellow'
        },
        {
          value: '4',
          text: '绿色',
          color: '#59A725',
          borderC: '#539B23',
          'class': 'green'
        },
        {
          value: '32',
          text: '紫色',
          color: '#892BCF',
          borderC: '#7A27B7',
          'class': 'purple'
        },
        {
          value: '64',
          text: '粉色',
          color: '#D744BA',
          borderC: '#C63FAB',
          'class': 'pink'
        },
        {
          value: '8',
          text: '青色',
          color: '#06B7C8',
          borderC: '#07A6B7',
          'class': 'cyan'
        },
        {
          value: '16',
          text: '蓝色',
          color: '#0065FE',
          borderC: '#005CEB',
          'class': 'blue'
        },
        {
          value: '128',
          text: '棕色',
          color: '#733413',
          borderC: '#6B3012',
          'class': 'gray'
        },
        {
          value: '1024',
          text: '白色',
          color: '#fff',
          borderC: '#C0BABC',
          'class': 'white',
          type: 3
        },
        {
          value: '512',
          text: '黑色',
          color: '#000',
          borderC: '#000',
          'class': 'black'
        },
        {
          value: '2048',
          text: '黑白',
          type: 2,
          tips: '黑白',
          borderC: '#fff',
          'class': 'bw',
          bg: '#fff url(//img0.bdstatic.com/img/image/newFilterBg.png) no-repeat -1px -319px'
        }
      ];
      var r = + this.model.get('ic') || 0;
      for (var l in e.optcfg) 1 * e.optcfg[l].value == r && (e.optcfg[l].active = !0);
      var s = null;
      for (var l in e.colors) {
        var c = 1 * e.colors[l].value;
        r == c && 1024 != r && 512 != r && (s = l, e.optcfg[3].active = !0)
      }
      if (e.render(), e.renderColors(), s) {
        var c = e.colors[s];
        t('.citem:eq(' + s + ')', e.o).addClass('actcs'),
        e.o.find('.colors_selected').css({
          borderColor: c.borderC,
          background: c.bg ? c.bg : c.color
        }).show()
      }
    },
    renderColors: function () {
      var o = this,
      e = o.o.find('.item.colors'),
      r = '';
      for (var l in o.colors) {
        var s = o.colors[l];
        r += '<div class="citem ' + s['class'] + '" title="' + s.text + '"  style="background:' + (s.bg ? s.bg : s.color) + ';border-color:' + s.borderC + '" ></div>'
      }
      var c = '<div class="colors_arrow cb"></div><div class="colors_container cb" style="width:' + 28 * o.colors.length + 'px;">' + r + '<div></div></div><div class="colors_selected"></div>';
      e.append(c),
      e.bind('mouseleave', function () {
        o.hideColors()
      }),
      t('.citem', e).click(function () {
        o.changeColors(this)
      })
    },
    showColors: function () {
      clearTimeout(this.timer),
      this.timer = null,
      this.o.find('.cb').show()
    },
    hideColors: function () {
      var o = this;
      o.timer = setTimeout(function () {
        o.o.find('.cb').hide()
      }, 500)
    },
    changeColors: function (o) {
      var e = this,
      r = t(o).index();
      if (e.lastid != 10 + r) {
        e.o.find('.cb').hide(),
        e.o.find('.item.active').removeClass('active'),
        e.o.find('.item.colors').addClass('active'),
        e.o.find('.colors_selected').css({
          borderColor: e.colors[r].borderC,
          background: e.colors[r].bg ? e.colors[r].bg : e.colors[r].color
        }).show(),
        s(null, 390, {
          newp: 383,
          tp: e.id,
          attr: e.colors[r].value
        }),
        t('.actcs', e.o).removeClass('actcs'),
        t(o).addClass('actcs');
        var l = {
        };
        l.ic = e.colors[r].value,
        l.cl = '',
        l.ct = '',
        this.dispatchEvent('sizeChanged', l),
        e.lastid = 10 + r
      }
    },
    outColors: function () {
      t('.actcs', this.o).removeClass('actcs'),
      this.o.find('.colors_selected').hide()
    }
  })
});
; /*!searchresult:widget/pagelets/base/avfilter/init.js*/
define('searchresult:widget/pagelets/base/avfilter/init', function (require, exports, module) {
  var $ = require('common:widget/ui/base/base'),
  common = require('searchresult:widget/ui/base/common/common'),
  handle = require('searchresult:widget/ui/base/windowHandle/windowHandle'),
  AvMuiltSizeFilterView = require('searchresult:widget/ui/base/view/AvMuiltSizeFilterView/AvMuiltSizeFilterView'),
  AvTypeFilterView = require('searchresult:widget/ui/base/view/AvTypeFilterView/AvTypeFilterView'),
  AvColorWallFilterView = require('searchresult:widget/ui/base/view/AvColorWallFilterView/AvColorWallFilterView'),
  AvColorFilterView = require('searchresult:widget/ui/base/view/AvColorFilterView/AvColorFilterView'),
  Filter = module.exports = function (e) {
    this.f = null,
    this.options = e || {
    },
    this.options.conf = {
      filters: [
        {
          name: 'AvTypeFilterView',
          hidewidth: 450
        },
        {
          name: 'AvColorFilterView',
          blank: !1,
          hidewidth: 770
        }
      ]
    },
    this.options.avatarCategory && 'wallpaper' === this.options.avatarCategory && (this.options.conf.filters = [
      {
        name: 'AvMuiltSizeFilterView'
      },
      {
        name: 'AvColorWallFilterView',
        blank: !1,
        hidewidth: 760
      }
    ])
  };
  $.extend(Filter.prototype, {
    ini: function () {
      var t = this;
      if (this.options.avatarCategory) {
        t.f = $('<div id="avfilter_container"></div>'),
        $('#top-filter-hoder').hide(),
        $('#avfilter').show().append(t.f),
        handle.fixresize(function () {
          t.fix()
        });
        for (var i in this.options.conf.filters) {
          var name = this.options.conf.filters[i].name,
          ft = eval('new ' + name + '()');
          ft.ini($.extend({
            container: t.f,
            model: this.options.model
          }, this.options.conf.filters[i])),
          t[name.toLocaleLowerCase()] = ft
        }
        t.fix()
      }
    },
    getFilters: function () {
      return this.options.conf.filters
    },
    fix: function () {
      var e = $('#imgid').width();
      200 > e ? this.f.hide()  : this.f.show();
      for (var i in this.options.conf.filters) {
        var t = this.options.conf.filters[i].hidewidth;
        if (t) {
          var r = this.options.conf.filters[i].name,
          o = this[r.toLocaleLowerCase()];
          t > e ? o.hide()  : o.show()
        }
      }
    }
  })
});
; /*!searchresult:widget/ui/controls/tagbar/tagbar.js*/
define('searchresult:widget/ui/controls/tagbar/tagbar', function (t, e, i) {
  var a = t('common:widget/ui/base/base'),
  s = t('searchresult:widget/ui/statistic/statistic'),
  n = t('common:widget/ui/base/events'),
  l = t('searchresult:widget/ui/base/windowHandle/windowHandle'),
  r = t('common:widget/ui/EventEmitter/EventEmitter'),
  o = i.exports = function (t) {
    this.lefter = a('#lefter'),
    this.i = 0,
    s(null, 390, {
      newp: 438,
      tp: 0
    }),
    this.scrolllock = !1,
    this.showTag = !0,
    this.scrollLimitHeight = 0,
    this.scrollLeftHeight = 0,
    this.lastTop = 0,
    this.leftTop = 56,
    this.model = t.model || {
    }
  };
  a.extend(o.prototype, n, {
    ini: function () {
      var t = '',
      e = this,
      i = this.model.data;
      window.getGIcon = function (t) {
        return e.getGIcon(t)
      };
      var s,
      n = [
      ];
      for (var o in i.tags) '全部' != i.tags[o].name ? i.tag == i.tags[o].name ? n.unshift(i.tags[o])  : n.push(i.tags[o])  : s = i.tags[o];
      s && n.unshift(s),
      i.tags = n;
      for (var o in i.tags) {
        var g = i.tags[o].name,
        h = i.tags[o].show,
        c = [
        ],
        f = 0;
        g = i.tags[o].name = i.tags[o].name.replace(/&amp;/g, '&');
        for (var d in i.tags[o].subs) {
          i.tags[o].subs[d].name = i.tags[o].subs[d].name.replace(/&amp;/g, '&');
          var u = i.tags[o].subs[d];
          if ('全部' != u.show) {
            var m = 1,
            v = u.name.replace(/[《》]/g, '');
            6 > f + m ? (c.push('<a j="' + d + '" title="' + v + '"  class="itsub its' + m + ' ' + (h == i.tagFatherSelected && u.show == i.tagSelected ? 'activesub' : '') + '" >' + u.show + '</a>'), f += m)  : (c.push('<a j="' + d + '" class="itsub ithide its' + m + ' ' + (h == i.tagFatherSelected && u.show == i.tagSelected ? 'activesub' : '') + '" >' + u.show + '</a>'), f = 999)
          }
        }
        999 == f && c.push('<a class="itsmore" onclick="p(null,390,{newp:438,tp:0});" href="javascript:void(0);">更多</a><a class="itsless" onclick="p(null,390,{newp:438,tp:1});" href="javascript:void(0);">收起</a>');
        var p = '<div  class="tag item ' + (h == i.tagFatherSelected ? 'activeitem' : '') + '  ' + (0 == c.length ? 'nosub ' : '') + (o % 2 == 0 ? 'gray' : 'white') + ' " tag="' + i.tags[o].show + '" ><div class="itemtop"><span class="fl">' + i.tags[o].show + '</span></div><div class="itemsubs">' + c.join('') + '</div></div>';
        t += p
      }
      var w = '';
      this.lefter.prepend('<div id="lefter-wapper">' + w + '<div class="tagbox" ><div class="tagscroll" >' + t + '</div></div><a class="tagbtn">展开更多</a></div>'),
      a('.brand .ct', this.lefter).click(function (t) {
        e.onall(t)
      }),
      a('.nosub .fl', this.lefter).click(function (t) {
        e.ontop(t)
      }),
      a('.itsub', this.lefter).click(function (t) {
        e.onsub(t)
      }),
      e.tagStatus = 0,
      a('.tagbox', e.lefter).height(e.fixTagHeight(5)),
      a('.tagbtn', this.lefter).click(function () {
        if (0 == e.tagStatus) {
          var t = e.fixTagHeight();
          a('.tagbox', e.lefter).animate({
            height: t,
            easing: 'linear'
          }, 300, function () {
            a('.tagbox', e.lefter).height(e.fixTagHeight()),
            a('.tagbtn').html('收起').addClass('tagup'),
            e.showTag = !1,
            e.tagStatus = 1,
            e.fix(!0)
          })
        } else {
          var t = e.fixTagHeight(5);
          a('.tagbox', e.lefter).animate({
            height: t,
            easing: 'linear'
          }, 300, function () {
            a('.tagbox', e.lefter).height(e.fixTagHeight(5)),
            a('.tagbtn').html('展开更多').removeClass('tagup'),
            e.showTag = !0,
            e.tagStatus = 0,
            e.fix(!0)
          })
        }
      }),
      a('.itsmore', this.lefter).click(function (t) {
        e.onmore(t, this)
      }),
      a('.itsless', this.lefter).click(function (t) {
        e.onless(t, this)
      });
      i.tags.length <= 5 && (e.showTag = !1),
      1 == e.showTag ? a('.tagbtn', this.lefter).show()  : a('.tagbtn', this.lefter).hide(),
      l.fixresize(function () {
        e.fix()
      }),
      a(window).scroll(function (t) {
        e.scroll(t)
      }),
      this.lefter.on('RESIZE_LEFTER', function () {
        e.scroll()
      }),
      r.eventCenter.on('tagbar.addView', function () {
        e.addView()
      }),
      e.addView(),
      this.fix()
    },
    addView: function () {
      var t = this,
      e = this.model.data;
      e.tagView = e.tagView || [
      ];
      e.tagView;
      if (e.tagView.length > 0) {
        var i = e.tagView.shift(0);
        i.success(function () {
          t.addView()
        }),
        i.render()
      } else t.fix()
    },
    fixTagHeight: function (t) {
      t = t || 999;
      var e = 0;
      return a('.tagscroll .tag', this.lefter).each(function (i) {
        t > i && (e += a(this).outerHeight())
      }),
      e
    },
    fix: function (t) {
      var e = this,
      i = window.handle.clientHeight() - 56;
      t && a('.tagbox', e.lefter).height(e.fixTagHeight(e.tagStatus ? 0 : 5));
      var s = this.scrollLeftHeight;
      if (this.scrollLeftHeight = a('#lefter-wapper', this.lefter).outerHeight(), this.scrollLimitHeight = i, t && this.lefter.hasClass('fixedLefter')) {
        var n = s - this.scrollLeftHeight;
        this.leftTop += n,
        this.leftTop = Math.min(this.leftTop, 56),
        this.lefter.css({
          top: this.leftTop
        })
      }
      var l = Math.max(i + 56 - this.leftTop, this.scrollLeftHeight);
      this.lefter.height(l)
    },
    onsub: function (t) {
      var e = t.target,
      i = this.model.data,
      n = a(e).parents('.item:first').index(),
      l = a(e).attr('j') || 0;
      i.tab = 100 * n + l,
      a('#lefter .brand').addClass('brand-w'),
      a('#lefter .brand .icon').removeClass('rgicon').addClass('wgicon'),
      a('#lefter .activesub').removeClass('activesub'),
      a(e).addClass('activesub'),
      a('#lefter .activeitem').removeClass('activeitem'),
      a(e).parents('.item:first').addClass('activeitem');
      var r = {
        queryWord: i.tags[n].subs[l].name,
        queryWordEnc: i.tags[n].subs[l].name,
        word: i.tags[n].subs[l].name,
        itg: 1
      };
      this.dispatchEvent('sizeChanged', r),
      s(null, 390, {
        newp: 414,
        fm: i.tab
      })
    },
    onall: function () {
      var t = this.model.data;
      t.tab = null,
      a('#lefter .activesub').removeClass('activesub'),
      a('#lefter .brand').removeClass('brand-w'),
      a('#lefter .brand .icon').addClass('rgicon').removeClass('wgicon'),
      a('#lefter .activeitem').removeClass('activeitem'),
      a('#lefter .brand').addClass('activeitem'),
      s(null, 390, {
        newp: 414,
        fm: t.tab
      })
    },
    ontop: function (t) {
      var e = t.target,
      i = this.model.data,
      n = a(e).parents('.item:first').index();
      i.tab = 100 * n,
      a('#lefter .brand').addClass('brand-w'),
      a('#lefter .brand .icon').removeClass('rgicon').addClass('wgicon'),
      a('#lefter .activeitem').removeClass('activeitem'),
      a(e).parents('.item:first').addClass('activeitem');
      var l = {
        queryWord: i.tags[n].name,
        queryWordEnc: i.tags[n].name,
        word: i.tags[n].name,
        itg: 1
      };
      this.dispatchEvent('sizeChanged', l),
      s(null, 390, {
        newp: 414,
        fm: i.tab
      })
    },
    icons: {
      '全部': 'wg-all',
      '风格': 'wg-fengge',
      '户型': 'wg-huxing',
      '空间': 'wg-kongjian',
      '局部': 'wg-jubu',
      '物品': 'wg-wupin'
    },
    gicons: {
      '全部': 'lg-all',
      '风格': 'lg-fengge',
      '户型': 'lg-huxing',
      '空间': 'lg-kongjian',
      '局部': 'lg-jubu',
      '物品': 'lg-wupin'
    },
    getIcon: function (t) {
      var e;
      for (var i in this.icons) !e && t.indexOf(i) > - 1 && (e = this.icons[i]);
      return e || (e = 'wg-all'),
      e
    },
    getGIcon: function (t) {
      var e;
      for (var i in this.gicons) !e && t.indexOf(i) > - 1 && (e = this.gicons[i]);
      return e || (e = 'lg-all'),
      e
    },
    scroll: function () {
      var t = this,
      e = document.documentElement.scrollTop + document.body.scrollTop;
      if (!this.lefter.hasClass('fixedLefter') || 0 === e) return t.leftTop = 56,
      void this.lefter.css({
        top: 0
      });
      if (t.scrollLimitHeight > t.scrollLeftHeight) return void this.lefter.css({
        top: 56
      });
      var i = t.lastTop - e;
      t.leftTop += 0.5 * i,
      t.leftTop = Math.min(t.leftTop, 56),
      t.leftTop = Math.max(t.leftTop, 56 + t.scrollLimitHeight - t.scrollLeftHeight),
      t.lefter.css({
        top: t.leftTop
      }),
      t.lastTop = e
    },
    onmore: function (t, e) {
      var i = this,
      s = a(e).parents('.item:first'),
      n = s.attr('startH') || s.height();
      a(e).hide(),
      a('.itsless', s).show(),
      a('.ithide', s).removeClass('ithide');
      var l = s.attr('endH') || s.height();
      s.attr('startH', n),
      s.attr('endH', l),
      s.height(n).animate({
        height: l,
        easing: 'linear'
      }, 200, function () {
        i.fix(!0)
      })
    },
    onless: function (t, e) {
      var i = this,
      s = a(e).parents('.item:first'),
      n = s.attr('startH'),
      l = s.attr('endH');
      a(e).hide(),
      a('.itsmore', s).show(),
      s.height(l).animate({
        height: n,
        easing: 'linear'
      }, 200, function () {
        a('.itsub:gt(4)', s).addClass('ithide'),
        i.fix(!0)
      })
    }
  })
});
; /*!searchresult:widget/ui/controls/jzFilter/jzFilter.js*/
define('searchresult:widget/ui/controls/jzFilter/jzFilter', function (t, e, s) {
  var i = t('common:widget/ui/base/base'),
  a = (t('searchresult:widget/ui/statistic/statistic'), t('common:widget/ui/base/events')),
  o = t('searchresult:widget/ui/base/windowHandle/windowHandle'),
  l = s.exports = function (t) {
    this.lefter = i('#lefter'),
    this.i = 0,
    this.scrolllock = !1,
    this.showTag = !0,
    this.scrollLimitHeight = 0,
    this.scrollLeftHeight = 0,
    this.lastTop = 0,
    this.leftTop = 0,
    this.tagHeight = 0,
    this.clientHeight = window.handle.clientHeight(),
    this.model = t.model || {
    }
  };
  i.extend(l.prototype, a, {
    ini: function () {
      var t = '<div class="tag item"><div class="itemtop"><span class="fl">全部分类</span></div><div class="itemsubs"><ul id="selectedSubs">',
      e = '',
      s = this,
      a = s.model.data;
      a.colors = [
        {
          text: '黑色',
          color: '#000',
          borderC: '#000',
          'class': 'black'
        },
        {
          text: '白色',
          color: '#fff',
          borderC: '#999',
          'class': 'white'
        },
        {
          text: '灰色',
          color: '#969696',
          borderC: '#969696',
          'class': 'grey'
        },
        {
          text: '棕色',
          color: '#6e371d',
          borderC: '#6e371d',
          'class': 'gray'
        },
        {
          text: '绿色',
          color: '#548c46',
          borderC: '#548c46',
          'class': 'green'
        },
        {
          text: '黄色',
          color: '#c8ae61',
          borderC: '#c8ae61',
          'class': 'yellow'
        },
        {
          text: '蓝色',
          color: '#6493c8',
          borderC: '#6493c8',
          'class': 'blue'
        },
        {
          text: '红色',
          color: '#f02e19',
          borderC: '#f02e19',
          'class': 'red'
        },
        {
          text: '粉色',
          color: '#e58fc4',
          borderC: '#e58fc4',
          'class': 'pink'
        }
      ],
      s.tagsLength = a.tags.length + 2;
      for (var l in a.tags) {
        var r = a.tags[l].show,
        c = [
        ];
        s.tagStatus = 0,
        t += '<li findex="' + l + '" style="display:none"><span class="selectedSubName"></span><span class="subCloseBtn">x</span></li>';
        for (var d in a.tags[l].subs) {
          var n = a.tags[l].subs[d];
          c.push('<a j="' + d + '" materialId="' + n.materialId + '" class="itsub">' + n.show + '</a>')
        }
        e += '<div class="tag item ' + (0 === c.length ? 'nosub ' : '') + (l % 2 === 0 ? 'gray' : 'white') + '" tag="' + r + '"><div class="itemtop"><span class="fl">' + r + '</span></div><div class="itemsubs" tagType = "' + r + '">' + c.join('') + '</div></div>'
      }
      t += '<li findex="-1" style="display:none"><span class="selectedColor"></span><span class="subCloseBtn">x</span></li></ul></div></div>',
      t += e,
      t += '<div class="tag item"><div class="itemtop"><span class="fl">颜色</span></div><div class="itemsubs colorSubs">';
      for (var d in a.colors) {
        var u = a.colors[d];
        t += '<a j="' + d + '" color="' + u.text + '" style="background:' + u.color + ';border-color:' + u.borderC + '" class="itsub"></a>'
      }
      t += '</div></div>',
      s.lefter.prepend('<div id="lefter-wapper"><div class="tagbox" ><div class="tagscroll" >' + t + '</div></div><a class="tagbtn">展开更多</a></div>'),
      i('.tagbtn').hide(),
      i('.itsub', s.lefter).click(function (t) {
        s.onsub(t)
      }),
      i('.tagbox', s.lefter).height(s.fixTagHeight(s.tagsLength)),
      i('.subCloseBtn').click(function (t) {
        s.delSub(t)
      }),
      i(window).scroll(function (t) {
        s.scroll(t)
      }),
      s.lefter.on('RESIZE_LEFTER', function () {
        s.scroll()
      }),
      i('#lefter-wapper').css('padding-bottom', '0px'),
      s.lefter.css({
        'min-height': '0px'
      }),
      o.fixresize(function () {
        s.clientHeight = window.handle.clientHeight()
      })
    },
    addBlockSubs: function (t, e) {
      var s;
      for (var a in t) s = i('.itemsubs[tagType="' + e + '"]').find('.itsub[materialId="' + t[a] + '"]'),
      s.addClass('blockSub'),
      s.off('click')
    },
    delBlockSubs: function (t, e) {
      var s,
      a = this;
      for (var o in t) s = i('.itemsubs[tagType="' + e + '"]').find('.itsub[materialId="' + t[o] + '"]'),
      s.removeClass('blockSub'),
      s.on('click', function (t) {
        a.onsub(t)
      })
    },
    delSub: function (t) {
      var e,
      s,
      a = t.target,
      o = this,
      l = o.model.data,
      r = i('#selectedSubs'),
      c = i(a).parent('li'),
      d = parseInt(c.attr('findex'), 10) + 1 || 0,
      n = i('#kw').val(),
      u = [
      ];
      c.hide(),
      - 1 !== parseInt(c.attr('findex'), 10) && (e = JSON.parse(l.tags[d - 1].subs[c.attr('sindex')].adDesc), e && e.blockTagList && e.tagType && (u = e.blockTagList, s = e.tagType, o.delBlockSubs(u, s))),
      i('#lefter .item').eq(d).find('.activesub').removeClass('activesub'),
      r.find('li').each(function (t, e) {
        var e = i(this);
        e.is(':hidden') || (n += - 1 === parseInt(e.attr('findex'), 10) ? ' ' + i('.selectedColor').attr('color')  : ' ' + e.find('.selectedSubName').text().split('/') [0])
      });
      var g = {
        queryWord: n,
        queryWordEnc: n,
        word: n,
        itg: 1
      };
      this.dispatchEvent('sizeChanged', g)
    },
    fixTagHeight: function () {
      var t = this,
      e = 0;
      return i('.tagscroll .tag', t.lefter).each(function () {
        e += i(this).outerHeight()
      }),
      t.tagHeight = e,
      e
    },
    addSelectedSubs: function (t, e) {
      var s,
      a,
      o,
      l,
      r = i('#selectedSubs'),
      c = this,
      d = c.model.data,
      n = '',
      u = '',
      g = [
      ];
      return t !== c.tagsLength - 2 && (u = d.tags[t].subs[e].show),
      r.find('li').each(function (s, a) {
        if (a = i(this), t === s && t !== c.tagsLength - 2) {
          if (a.attr('sindex') >= 0 && + a.attr('sindex') !== + e) {
            var o = JSON.parse(d.tags[t].subs[a.attr('sindex')].adDesc);
            o && o.blockTagList && o.tagType && c.delBlockSubs(o.blockTagList, o.tagType)
          }
          a.attr('sindex', e),
          a.find('.selectedSubName').empty().text(u),
          a.is(':hidden') && a.show()
        }
      }),
      t === c.tagsLength - 2 ? (l = d.colors[e], o = i('.selectedColor').parent('li'), i('.selectedColor').attr('color', l.text).css({
        background: l.color,
        'border-color': l.borderC
      }), o.is(':hidden') && o.show(), t = - 1, o.attr('sindex', e))  : (u = d.tags[t].subs[e].show, s = JSON.parse(d.tags[t].subs[e].adDesc), s && s.blockTagList && s.tagType && (g = s.blockTagList, a = s.tagType, c.addBlockSubs(g, a))),
      r.find('li').each(function (t, e) {
        e = i(this),
        e.is(':hidden') || (n += - 1 === parseInt(e.attr('findex'), 10) ? ' ' + i('.selectedColor').attr('color')  : ' ' + e.find('.selectedSubName').text().split('/') [0])
      }),
      i('.tagbox', c.lefter).height(c.fixTagHeight(c.tagsLength)),
      n
    },
    onsub: function (t) {
      var e = this,
      s = t.target,
      a = (e.model.data, i(s).parents('.item:first').index() - 1),
      o = i(s).attr('j') || 0,
      l = i('#kw').val() + e.addSelectedSubs(a, o);
      i(s).parent('.itemsubs').find('.activesub').removeClass('activesub'),
      i(s).addClass('activesub');
      var r = {
        queryWord: l,
        queryWordEnc: l,
        word: l,
        itg: 1
      };
      e.dispatchEvent('sizeChanged', r)
    },
    scroll: function () {
      {
        var t = this,
        e = document.documentElement.scrollTop + document.body.scrollTop;
        i('#search').height()
      }
      return 0 === e ? (t.lefter.css({
        position: 'absolute',
        top: '0px',
        bottom: 'auto'
      }), !1)  : t.clientHeight - t.tagHeight > 90 ? (t.lefter.css({
        position: 'fixed',
        top: '85px',
        bottom: 'auto'
      }), !1)  : void t.lefter.css({
        position: 'fixed',
        bottom: '0px',
        top: 'auto'
      })
    }
  })
});
; /*!searchresult:widget/ui/app/page.js*/
define('searchresult:widget/ui/app/page', function (t) {
  var a = t('common:widget/ui/base/base'),
  e = t('common:widget/ui/base/events'),
  i = t('searchresult:widget/ui/app/history'),
  o = t('common:widget/ui/arch/behavior/pageresizer'),
  n = (t('searchresult:widget/ui/utils/lib'), t('searchresult:widget/ui/app/sizemanager')),
  r = t('searchresult:widget/ui/app/scrollmanager'),
  s = t('common:widget/ui/arch/handlers'),
  l = t('searchresult:widget/ui/models/filtermodel'),
  d = t('searchresult:widget/ui/collections/imgcollection'),
  g = t('searchresult:widget/ui/strategy/imglayoutstrategy'),
  c = t('searchresult:widget/ui/strategy/insertstrategy'),
  h = t('searchresult:widget/ui/controls/imgpagelist/imgpagelist'),
  m = t('searchresult:widget/ui/controls/hoverBox/hoverBox'),
  u = t('searchresult:widget/ui/controls/memoryBar/memoryBar'),
  p = t('searchresult:widget/pagelets/base/avfilter/init'),
  f = t('searchresult:widget/ui/controls/tagbar/tagbar'),
  w = t('searchresult:widget/ui/controls/jzFilter/jzFilter'),
  D = t('searchresult:widget/ui/statistic/statistic'),
  v = t('searchresult:widget/ui/statistic/bdgstat'),
  y = t('searchresult:widget/ui/utils/utils'),
  L = !0,
  C = a.extend({
    model: null,
    filterModel: null,
    imgCollection: new d,
    insertStrategy: new c,
    history: null,
    featureManager: null,
    imgLoadStratey: null,
    controls: {
      imgPageList: null
    },
    handlers: new s(this),
    _isFirstImgLoaded: !1,
    init: function (t) {
      return this.model = t,
      this.filterModel = new l(this.model),
      this.model.get('hasResult') ? (this.initData(), window.jsStartTime = new Date, this.history = new i(this.model), this.history.init(), this.resizer = o, this.resizer.init({
        tick: 20,
        resizeHeight: !1
      }), a(window).on('load', this.onPageLoaded.bind(C)).on('unload', this.handlers.get('onPageUnLoadedHandler')), this.resizer.addEventListener('resizeEnd', this.handlers.get('onPageResizeHandler')), this.history.addEventListener('popstate', this.handlers.get('onHistoryChangedHandler')), void this.createControls())  : void this.noPageload()
    },
    initData: function () {
      var t = this.model.tempData.get('imgInfo');
      t && this.imgLoadStratey.immediateLoad(this.imgCollection.mapField(t))
    },
    createControls: function () {
      var t = this,
      e = t.controls,
      i = t.model.tempData.get('imgData').data,
      o = t.model.tempData.get('fcadData').fcData,
      n = {
        asyImgNum: i.length + (o ? o.length : 0),
        asyAdNum: o.length
      };
      e.imgPageList = new h(a('#imgid'), this.model, n),
      e.memoryBox = new u(this.model),
      e.hoverBox = new m(this.model);
      var r = this.model.get('cg'),
      s = {
      };
      ('wallpaper' === r || 'head' === r) && (s.avatarCategory = this.model.data.cg, s.model = this.model, e.avatarFilter = new p(s), e.tagBar = new f(s)),
      'jiazhuang' === r && (s.avatarCategory = r, s.model = this.model, e.jzFilter = new w(s))
    },
    run: function () {
      var t = this;
      if (this.model.get('hasResult')) {
        var e = t.model.tempData.get('fcadData');
        if (window.rpPageNum = 1, window.fcBtData = e.fcBtData, window.fcMidData = e.fcMidData, window.imgTempData = {
          fcType: e.fcType,
          adType: e.adType,
          fcAdDatasLen: e.fcAdDatasLen,
          fcData: e.fcData
        }, e.fcData && e.fcData.length && (t.imgCollection.putFixData(e.fcData), e.fcAdDatasLen > 0)) {
          for (var i = '', o = '', n = '', r = '', s = '', l = '', d = e.fcAdDatasLen, c = [
          ], h = function () {
            var t = (new Date).getTime() + '-',
            a = 0;
            return function () {
              return t + a++
            }
          }(), m = function (t) {
            var a = window.tjAdLog || (window.tjAdLog = {
            }),
            e = h(),
            i = a[e] = new Image;
            i.onload = i.onerror = function () {
              i.onload = i.onerror = null,
              i = null,
              delete a[e]
            },
            i.src = t + '&_uid=' + e
          }; d > 0; ) {
            if (i += e.fcData[d - 1].picId, o += e.fcData[d - 1].fromPageTitle.replace(/&/g, '-'), n += e.fcData[d - 1].fromPageAbs, r += e.fcData[d - 1].fromURLHost, s += e.fcData[d - 1].thumbURL, l += e.fcData[d - 1].adTag, c.push(e.fcData[d - 1].adFlag), d > 1 && (i += ',', o += '||', n += '||', r += ',', l += ',', s += ','), 'TJAD' === e.fcData[d - 1].type || 'TJNAD' === e.fcData[d - 1].type) {
              var u = {
              },
              p = [
              ],
              f = 0;
              !!e.fcData[d - 1].tag_list && (p = e.fcData[d - 1].tag_list.split(',')),
              !!e.fcData[d - 1] && (u = {
                tags: p
              }),
              f = (window.samplekey.match('UI_PC_TJAD:1') || window.samplekey.match('UI_PC_TJAD:2')) && u.tags.length > 0 ? window.samplekey.match('UI_PC_TJAD:1') ? 1 : 2 : 0,
              m(e.fcData[0].tjUrl + '&actionid=4&attach=' + (d - 1) + '|src=result|render_type=' + f)
            }
            --d
          }
          D && D(null, 1101001, {
            vs: window.vsid || '',
            adtype: e.adType
          }),
          D && D(null, 1101002, {
            vs: window.vsid || '',
            adtype: e.adType,
            picnum: e.fcAdDatasLen,
            picid: i,
            url: r,
            pos: 70010
          });
          var w = {
            vs: window.vsid || '',
            url: r,
            pos: 70010,
            picid: i,
            adflags: c.join(','),
            picnum: e.fcAdDatasLen,
            adtype: e.adType
          };
          'FBAD' === e.fcData[0].type && (w.maincont = encodeURIComponent(o), w.landpage = encodeURIComponent(r), w.picurl = encodeURIComponent(s), w.as = encodeURIComponent(l)),
          D && D(null, 1101004, w)
        }
        if (window.fcBtData && window.fcBtData.length) {
          for (var y = '', L = '', C = window.fcBtData.length; C > 0; ) y += window.fcBtData[C - 1].picId,
          L += window.fcBtData[C - 1].fromURLHost,
          C > 1 && (y += ',', L += ','),
          --C;
          D && D(null, 1101002, {
            vs: window.vsid || '',
            adtype: window.imgTempData && window.imgTempData.adType,
            picnum: window.fcBtData.length,
            picid: y,
            url: L,
            pos: 70011
          })
        }
        var b = t.model.tempData.get('imgData');
        if (b.data && b.data.length) {
          for (var z = 0, B = 0, F = b.data.length; F - 1 > B; B++) t.imgCollection.put(t.imgCollection.mapField(b.data[B])),
          '3' === b.data[B].adType && z++;
          if (0 !== z) for (var P = 0, B = 0, F = b.data.length; F - 1 > B; B++) '3' === b.data[B].adType && v.sendLog({
            as: b.brandName,
            p: 1010100,
            pos: 'pc_result_before_insert',
            subpos: P++,
            shownum: z,
            matcont: b.data[B].imgUrl,
            materialNum: '1'
          })
        }
        var _ = t.model.tempData.get('xgMidData');
        if (_ && _.xgMidData && _.xgMidData.length) {
          var M = 0,
          T = _.xgMidData.length,
          j = [
          ];
          for (M; T > M; M++) j[M] = t.imgCollection.mapField(_.xgMidData[M]);
          for (var I = j; I.length < 20; ) a(j).each(function (t, e) {
            I[I.length] = a.extend({
            }, e),
            I[I.length - 1].piccopyid = I.length - 1
          });
          _.mapXgMidData = I,
          window.xgMidData = _
        }
        var x = t.model.tempData.get('rpData');
        if (x && x.data && x.data.length) {
          var A = 0,
          U = x.data.length,
          j = [
          ];
          for (A; U > A; A++) j[A] = t.imgCollection.mapField(x.data[A]);
          x.data = j,
          window.rpData = x
        }
        t.controls.imgPageList.reset(t.imgCollection, new g(this.model), this.insertStrategy, !0),
        alog && alog('speed.set', 'c_firstPageStartLoad', + new Date),
        alog.fire && alog.fire('mark'),
        t.initControls(),
        t.bindEvent(),
        t.bindModel()
      }
    },
    initControls: function () {
      var t = this.controls;
      this.sizeManager = n,
      this.scrollManager = r,
      n.init(),
      n.update(),
      t.memoryBox.init(),
      this.scrollManager.init('#imgid', t.imgPageList, this.model),
      this.scrollManager.update();
      var a = this.model.get('cg');
      ('wallpaper' === a || 'head' === a) && (t.avatarFilter && t.avatarFilter.ini(), t.tagBar && t.tagBar.ini()),
      'jiazhuang' === a && t.jzFilter && t.jzFilter.ini()
    },
    bindModel: function () {
      this.controls,
      this.filterModel
    },
    bindEvent: function () {
      var t = this.controls,
      e = this.handlers;
      this.scrollManager.bindScrollEvent('scrollEnd', function (a) {
        t.imgPageList.sendBdgLog(a)
      }),
      this.scrollManager.run(),
      t.imgPageList.on('firstload', this.lazyload),
      this.sizeManager.addObserver(r, 'updateWinHeight').addObserver(t.imgPageList, 'refresh').notify();
      var i = this.model.get('cg');
      if ('head' === i || 'wallpaper' === i) {
        var o = t.avatarFilter.getFilters();
        o && o.length && a(o).each(function (a, i) {
          t.avatarFilter[i.name.toLocaleLowerCase()].on('sizeChanged', e.get('onFilterSizeChanged'))
        }),
        t.tagBar.on('sizeChanged', e.get('onFilterSizeChanged'))
      }
      'jiazhuang' === i && t.jzFilter.on('sizeChanged', e.get('onFilterSizeChanged')),
      window.speed && window.speed.mark('app_ready')
    },
    onPageLoaded: function () {
      this.fire('loaded')
    },
    lazyload: function () {
      var e = C;
      alog && alog('speed.set', 'c_firstPageComplete', + new Date),
      alog.fire && alog.fire('mark'),
      alog && alog('speed.set', 'fs', + new Date),
      alog.fire && alog.fire('mark'),
      L && (L = !1, t.async(['searchresult:widget/ui/app/lazyPage'], function (t) {
        var a = new t;
        a.init(e)
      })),
      a('#footer').show();
      try {
        var i = + e.model.get('hs');
        !e._alaLog && window._alaEnter && window._alaEnter !== !0 && window._alaEnter('firstsc');
        var o = y.query2Json((location.search || '').replace('?', ''));
        if (!e._alaLog && 3 === i && 'http:' === location.protocol && 'baiduimage' === o.tn) {
          var n = {
            dsp: 'pc',
            hs: i,
            tn: 'result',
            type: 'link',
            t: + new Date
          },
          r = {
            type: 'submit'
          },
          s = new Image,
          l = new Image,
          d = function (t) {
            (new Image).src = 'http://image.baidu.com/pv/pv.gif?' + y.json2Query(a.extend({
              url: encodeURIComponent(location.href)
            }, n, t))
          },
          g = function (t, a, e) {
            var i = window.performance,
            o = 0;
            if (i && i.getEntriesByName) {
              var n = (i.getEntriesByName(a) || [
              ]) [0];
              o = n && n.duration
            }
            ~a.indexOf('https:') ? (t.https = e, t.httpsDiff = ~~o)  : (t.http = e, t.httpDiff = ~~o),
            t.http && t.https && d(t)
          };
          s.onload = l.onload = function () {
            g(r, this.src, 2)
          },
          s.onerror = l.onerror = function () {
            g(r, this.src, 1)
          },
          l.src = 'https://image.baidu.com/pv/pv.gif?proto=https&' + y.json2Query(n),
          s.src = 'http://image.baidu.com/pv/pv.gif?proto=http&' + y.json2Query(n);
          var c = {
            type: 'submit-ext'
          },
          h = new Image,
          m = new Image;
          h.onload = m.onload = function () {
            g(c, this.src, 2)
          },
          h.onerror = m.onerror = function () {
            g(c, this.src, 1)
          },
          m.src = 'https://www.baidu.com/nocache/imgdata/gs.gif?proto=https&' + y.json2Query(n),
          h.src = 'http://www.baidu.com/nocache/imgdata/gs.gif?proto=http&' + y.json2Query(n)
        }
        e._alaLog = !0
      } catch (u) {
      }
    },
    noPageload: function () {
      var e = C;
      L && (L = !1, t.async(['searchresult:widget/ui/app/noResultPage'], function (t) {
        t.init(e)
      })),
      a('#footer').show()
    },
    imgSwitched: function () {
    },
    initAds: function () {
    }
  }, e);
  return C
});
; /*!searchresult:widget/ui/app/app.js*/
define('searchresult:widget/ui/app/app', function (e) {
  var t = e('common:widget/ui/base/base'),
  i = e('common:widget/ui/utils/utils'),
  a = e('common:widget/ui/arch/app'),
  o = e('searchresult:widget/ui/app/pagemodel'),
  n = (e('searchresult:widget/ui/app/page'), new a(o));
  return t.extend(n, {
    logicBeginTime: (new Date).getTime(),
    setPageInfo: function (e) {
      e && (e.word && (e.word = e.word.replace(/\\'/g, '\'').replace(/\\"/g, '"'), e.word = i.tryDecodeURIComponent(e.word)), o.set(e))
    },
    init: function () {
      window.speed && window.speed.mark('app_init'),
      alog && alog('speed.set', 'c_jsStart', + new Date),
      alog.fire && alog.fire('mark');
      try {
        window._alaEnter && window._alaEnter !== !0 && window._alaEnter('init')
      } catch (e) {
      }
      a.prototype.init.call(this);
      var t = function () {
        return [{
          rule: {
            tpl: 'pullface'
          },
          action: 'searchresult:widget/ui/action/pullface/action.js'
        },
        {
          rule: {
            tpl: 'comic'
          },
          action: 'searchresult:widget/ui/action/comic/action.js'
        },
        {
          rule: {
            tpl: 'ald'
          },
          action: 'searchresult:widget/ui/action/ald/action.js'
        },
        {
          rule: {
            tpl: 'map'
          },
          action: 'searchresult:widget/ui/action/map/action.js'
        },
        {
          rule: {
            tpl: 'star'
          },
          action: 'searchresult:widget/ui/action/star/action.js'
        },
        {
          rule: {
            tpl: 'simgs'
          },
          action: 'searchresult:widget/ui/action/simgs/action.js'
        },
        {
          rule: {
            tpl: 'movie'
          },
          action: 'searchresult:widget/ui/action/movie/action.js'
        },
        {
          rule: {
          },
          action: 'searchresult:widget/ui/action/base/base.js'
        }
        ]
      }();
      this.router.addRules(t)
    },
    setData: function (e, t) {
      this.pageModel.tempData.set(e, t)
    },
    run: function () {
      a.prototype.run.apply(this, arguments)
    }
  }),
  n
});
; /*!searchresult:widget/ui/app/datacontroller.js*/
define('searchresult:widget/ui/app/datacontroller', function (i) {
  function t(i, t, e, o) {
    this.pageModel = i,
    this.imgModel = t,
    this.imgCollection = e,
    this.priorDataProc = o
  }
  {
    var e = i('common:widget/ui/base/base');
    i('searchresult:widget/ui/utils/lib')
  }
  return e.extend(t.prototype, {
    switchImage: function (i, t) {
      if (i) {
        var e = i.offset - this.imgCollection.getFixDataLength(),
        o = t && t.offset || 0,
        s = t || i,
        a = this.pageModel;
        a.set({
          pn: e,
          spn: o,
          di: i.di,
          cs: i.cs,
          os: i.os,
          adpicid: i.adPicId,
          fromurl: i.compiledFromURL || i.fromURL,
          objurl: s.objURL,
          'imgData.width': s.width,
          'imgData.height': s.height,
          'imgData.filesize': s.filesize,
          'imgData.type': s.type
        }),
        this.imgModel.set({
          word: a.get('word'),
          gbkword: a.get('gbkword'),
          bigImgUrl: s.bigImgUrl,
          imgData: s,
          rootImg: i,
          offset: i.offset,
          pn: e,
          spn: o
        })
      }
    }
  }),
  t
});
; /*!searchresult:widget/ui/component/component.js*/
define('searchresult:widget/ui/component/component', function (t, e, n) {
  function i() {
    this._initialized = !1,
    this._inDocument = !1,
    this._element = null,
    this._parent = null,
    this._children = [
    ],
    this._id = 'c_' + i._componentCounter++
  }
  var o = t('common:widget/ui/base/base');
  i._componentCounter = 0,
  o.extend(i.prototype, {
    enterDocument: function () {
      this._inDocument = !0,
      this._initialized || this.init(),
      o.each(this._children, function (t, e) {
        !e._inDocument && e._element && e.enterDocument()
      })
    },
    init: function () {
      this._initialized || (this._element || this.createDom(), this._initialized = !0)
    },
    exitDocument: function () {
      o.each(this._children, function (t, e) {
        e._inDocument && e.exitDocument()
      }),
      this._inDocument = !1
    },
    render: function (t) {
      this._inDocument || (this._element || this.createDom(), t && t.length && t.append(this._element), (!this._parent || this._parent._inDocument) && this.enterDocument())
    },
    addChild: function (t, e) {
      t._parent || (t._parent = this, this._children.push(t), this._element || this.createDom(), t.render(e ? e : this._element))
    },
    removeChild: function (t, e) {
      for (var n = 0, i = this._children.length; i > n; n++) if (this._children[n] === t) {
        this._children.splice(n, 1),
        e && t._inDocument && t.exitDocument(),
        t._parent = null;
        break
      }
    },
    remove: function () {
      this._parent && this._parent.removeChild(this, !0),
      this._inDocument && this.exitDocument(),
      this._element && this._element.remove()
    },
    createDom: function () {
      var t = this.buildDom();
      'string' == typeof t ? t = o(t)  : t || (t = o('<div></div>')),
      this._element = t
    },
    buildDom: function () {
      return '<div></div>'
    }
  });
  var c = function (t) {
    function e(t) {
      i.apply(this, arguments),
      this.opts = this.opts || {
      },
      o.extend(this.opts, t)
    }
    return e.prototype = o.extend({
    }, i.prototype, t, {
      constructor: e
    }),
    o.each(['init',
    'enterDocument'], function (n, o) {
      t[o] && (e.prototype[o] = function () {
        i.prototype[o].call(this),
        t[o].call(this)
      })
    }),
    o.each(['exitDocument'], function (n, o) {
      t[o] && (e.prototype[o] = function () {
        t[o].call(this),
        i.prototype[o].call(this)
      })
    }),
    o.each(['buildDom'], function (n, i) {
      t[i] && (e.prototype[i] = t[i])
    }),
    e
  };
  n.exports = c
});
; /*!searchresult:widget/ui/action/base/imgcollectioin_setting.js*/
define('searchresult:widget/ui/action/base/imgcollectioin_setting', function (e) {
  function t(e, t) {
    this.imgCollection = e,
    this.pageModel = t,
    this._fieldMapBinded = !1
  }
  var i = e('common:widget/ui/base/base'),
  s = e('searchresult:widget/ui/utils/utils'),
  r = e('searchresult:widget/ui/utils/lib');
  return i.extend(t.prototype, {
    fieldMap: {
      key: function (e) {
        return r.getUniqId('imgkey_') + '_' + (e.di || '')
      },
      objURL: function (e) {
        return r.uncompileURL(e.objURL)
      },
      imgUrl: function (e) {
        return e.thumbURL || e.hoverURL || e.largeTnImageUrl || e.objURL
      },
      detailUrl: function (e) {
        var t = this.pageModel,
        i = + t.get('rpstart') || 0,
        n = + t.get('rpnum') || 0,
        o = + e.personalized ? i : + e.pageNum >= i ? n : 0,
        g = + e.pageNum + o;
        return '/search/detail?ct=503316480&z=' + t.get('z') + '&tn=baiduimagedetail&ipn=d&word=' + t.get('queryWordEnc') + '&step_word=' + (t.get('step_word') || '') + '&ie=' + t.get('ie') + '&in=' + e.currentIndex + '&cl=' + t.get('cl') + '&lm=' + t.get('lm') + '&st=' + t.get('st') + '&cs=' + e.cs + '&os=' + e.os + '&simid=' + e.simid + '&pn=' + g + '&rn=1&di=' + e.di + '&ln=' + t.get('listNum') + '&fr=&fmq=' + s.fmqValueSet() + '&fm=' + (t.get('fm') || '') + '&ic=' + t.get('ic') + '&s=' + t.get('s') + '&se=' + t.get('se') + '&sme=' + t.get('sme') + '&tab=' + (e.tab || 0) + '&width=&height=&face=' + e.face + '&is=' + e.is + '&istype=' + (t.get('istype') || 0) + '&ist=' + e.source_type + '&jit=' + t.get('jit') + '&bdtype=' + (e.bdSrcType || 0) + '&spn=' + (e.spn || 0) + ('&pi=' + (e.pi || '')) + '&gsm=' + (t.get('tmpGsm') || 0) + ( + t.get('hs') ? '&hs=' + t.get('hs')  : '') + (t.get('oriquery') ? '&oriquery=' + t.get('oriquery')  : '') + '&objurl=' + encodeURIComponent(r.uncompileURL(e.objURL)) + '&rpstart=' + (t.get('rpstart') || 0) + '&rpnum=' + (t.get('rpnum') || 0) + '&adpicid=' + (e.adPicId || 0)
      }
    },
    getReqParams: function () {
      var e = this.pageModel,
      t = {
        tn: e.get('datatn') || 'resultjson_com',
        ipn: 'rj',
        ct: '201326592',
        is: e.get('statNum') ? e.get('is')  : null,
        fp: 'result'
      },
      s = [
        'queryWord',
        'cl',
        'lm',
        'ie',
        'oe',
        'adpicid',
        'st',
        'z',
        'ic',
        'word',
        's',
        'se',
        'tab',
        'width',
        'height',
        'face',
        'istype',
        'qc',
        'nc',
        'fr'
      ],
      r = e.get('queryWord'),
      n = e.get('step_word');
      return i(s).each(function (i, s) {
        t[s] = e.get(s) || ''
      }),
      t.fr = '',
      n && (t.word = r, t.step_word = n, t.ie = 'utf-8'),
      t.word = r,
      e.get('cg') && (t.cg = e.get('cg')),
      t
    },
    setImgSetCollection: function () {
    },
    getFieldMap: function () {
      if (!this._fieldMapBinded && this.fieldMap) {
        var e = this.fieldMap;
        for (var t in e) if (e.hasOwnProperty(t)) {
          var i = e[t];
          'function' == typeof i && (e[t] = i.bind(this))
        }
        this._fieldMapBinded = !0
      }
      return this.fieldMap
    },
    process: function () {
      this.imgCollection;
      this.imgCollection.setFieldMap(this.getFieldMap()),
      this.imgCollection.setReqParams(this.getReqParams()),
      this.setImgSetCollection()
    }
  }),
  t
});
; /*!searchresult:widget/ui/action/base/base.js*/
define('searchresult:widget/ui/action/base/base', function (t) {
  function e(t) {
    this._pdcFirstScrStep = 0,
    this.pageModel = t
  }
  var n = t('common:widget/ui/base/base'),
  i = t('searchresult:widget/ui/action/base/imgcollectioin_setting'),
  o = t('searchresult:widget/ui/collections/imgcollection'),
  s = t('searchresult:widget/ui/strategy/imglayoutstrategy'),
  a = t('searchresult:widget/ui/app/page');
  return n.extend(e.prototype, {
    initPage: function () {
      a.init(this.pageModel)
    },
    afterInit: function () {
    },
    initImgCollection: function () {
      new i(a.imgCollection, this.pageModel).process()
    },
    initFeature: function () {
    },
    initAds: function () {
    },
    process: function () {
      this.initPage(),
      this.initImgCollection(),
      this.initFeature(),
      this.initAds(),
      this.afterInit(),
      this.initHandlers(),
      this.bindEvent(),
      a.run(),
      this.attatchControls()
    },
    initHandlers: function () {
      a.handlers.extend({
        onPageResizeHandler: function () {
          a.sizeManager.update()
        },
        onHistoryChangedHandler: function (t) {
          null != t.state && (pn = t.state && t.state.pn || 0, spn = t.state && t.state.spn || 0, a.dataController.changePn(1 * pn, 1 * spn))
        },
        onPageUnLoadedHandler: function () {
        },
        onFilterSizeChanged: function (t) {
          window.scrollTo(0, 0);
          var e = new o;
          a.filterModel.set('word', a.model.get('queryWord')),
          a.model.set('word', a.model.get('queryWord')),
          a.filterModel.set(t),
          a.model.set(t),
          new i(e, a.filterModel).process(),
          a.controls.imgPageList.clear(),
          a.controls.imgPageList.reset(e, new s(a.model), a.insertStrategy, !1),
          a.controls.imgPageList.append()
        }
      })
    },
    bindEvent: function () {
    },
    attatchControls: function () {
    }
  }),
  e
});
; /*!searchresult:widget/ui/controls/IqiyiVideoBox/IqiyiVideoBox.js*/
define('searchresult:widget/ui/controls/IqiyiVideoBox/IqiyiVideoBox', function (e, a, i) {
  var s,
  o = e('common:widget/ui/base/base'),
  A = e('common:widget/ui/utils/utils'),
  l = window.ban_data && window.ban_data.flashimg,
  d = l && l.length > 0 ? !0 : !1;
  s = /Firefox/i.test(window.navigator.userAgent) && 'https:' == window.location.protocol ? 'https://www.iqiyi.com/common/flashplayer/20160704/18111a7ff0f5.swf?source=&purl=' : A.ihttpsAgent('http://dispatcher.video.qiyi.com') + '/disp/shareplayer.swf';
  var t = '<div class="body"><object class="albumVideo" id="starVideoPlayer" width="954" height="540" type="application/x-shockwave-flash" data="' + s + '"><param name="allowscriptaccess" value="always"><param name="wmode" value="Opaque"><param name="allowfullscreen" value="false"><param name="bgcolor" value="#000000"><param name="flashvars" value="{{=it.flashvars}}"></object></div><div class="video-box-brand"></div>',
  c = '<div class="body"><img class="video-bigimg" src="' + l + '"></div>',
  r = '<div class="videoMask"></div><div id="video-player"><span class="video-box-close-btn"></span>' + (d ? c : t) + '</div>',
  n = '<div class="body"><object id="starVideoPlayer" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="954" height="540" class="albumVideo"><PARAM NAME="_cx" VALUE="25241"><PARAM NAME="_cy" VALUE="14288"><PARAM NAME="FlashVars" VALUE="{{=it.flashvars}}"><PARAM NAME="Movie" VALUE="' + s + '"><PARAM NAME="Src" VALUE="' + s + '"><PARAM NAME="WMode" VALUE="Opaque"><PARAM NAME="Play" VALUE="0"><PARAM NAME="Loop" VALUE="1"><PARAM NAME="Quality" VALUE="High"><PARAM NAME="SAlign" VALUE="LT"><PARAM NAME="Menu" VALUE="-1"><PARAM NAME="Base" VALUE=""><PARAM NAME="AllowScriptAccess" VALUE="always"><PARAM NAME="Scale" VALUE="NoScale"><PARAM NAME="DeviceFont" VALUE="0"><PARAM NAME="EmbedMovie" VALUE="0"><PARAM NAME="BGColor" VALUE="000000"><PARAM NAME="SWRemote" VALUE=""><PARAM NAME="MovieData" VALUE=""><PARAM NAME="SeamlessTabbing" VALUE="1"><PARAM NAME="Profile" VALUE="0"><PARAM NAME="ProfileAddress" VALUE=""><PARAM NAME="ProfilePort" VALUE="0"><PARAM NAME="AllowNetworking" VALUE="all"><PARAM NAME="AllowFullScreen" VALUE="false"><PARAM NAME="AllowFullScreenInteractive" VALUE="false"><PARAM NAME="IsDependent" VALUE="0"></object></div><div class="video-box-brand"></div>',
  M = '<div class="body"><img class="video-bigimg" src="' + l + '"></div>',
  v = '<div class="videoMask"></div><div id="video-player"><span class="video-box-close-btn"></span><div class="body">' + (d ? M : n) + '</div>',
  E = i.exports = function () {
    o.browser.msie && (r = v)
  };
  o.extend(E.prototype, {
    render: function (e) {
      var a = this;
      a.cfg = e;
      var i = doT.template(r),
      s = i(e);
      window.notice = a.processCallback.bind(this),
      o('body').append(s),
      o('#video-player .video-box-close-btn').click(function () {
        a.closeHandler()
      }),
      o('html').css({
        overflow: 'hidden'
      }),
      d && o('#video-player').css({
        height: 'initial',
        'margin-left': '-440px'
      })
    },
    processCallback: function (e) {
      'string' == typeof e && (e = o.parseJSON(e));
      var a = e.type,
      i = e.data,
      s = i.state;
      if ('playStateChange' == a) switch (s) {
        case 'StartPlay':
          this.startPlayHandler();
          break;
        case 'EndPlay':
          this.closeHandler()
      }
    },
    startPlayHandler: function () {
      o('.video-box-brand').delay(1000).fadeOut(500)
    },
    updateModel: function () {
    },
    closeHandler: function () {
      o('.videoMask,#video-player').remove(),
      this.cfg.bghide !== !0 && o('html').css({
        overflow: 'auto'
      })
    }
  })
});
; /*!searchresult:widget/ui/controls/feedback/feedback.js*/
define('searchresult:widget/ui/controls/feedback/feedback', function (require, exports, module) {
  var utils = require('common:widget/ui/utils/utils'),
  bds = bds || {
  };
  bds.qa = bds.qa || {
  },
  bds.qa.ShortCut = {
    base_url_path: utils.ihttpsAgent('http://f3.baidu.com'),
    up_file: !1,
    is_feedbacking: !1,
    product_id: 0,
    entrance_id: 0,
    send_img: !1,
    img_data: '',
    onlyUpFile: !1,
    pro_data: '',
    plugintitle: '意见反馈&nbsp;<font style="font-size:13px;color:#2d9ef8;line-height:13px;">|&nbsp;<a style="font-size:14px;color:#2d9ef8;line-height:26px;text-decoration:underline;margin-left:20px;height:26px;" href="http://f3.baidu.com/index.php/feedback/f/index" target="_blank">我的反馈</a></font>',
    issueTips: '详细描述',
    issuePlaceholder: '欢迎提出您在使用过程中遇到的问题或宝贵建议（400字以内），感谢您对百度的支持。',
    emailPlaceholder: '请留下您的联系方式，以便我们及时回复您。',
    guide: '<span>申请删除百度快照内容，请在<a style="text-decoration:underline;" href="http://tousu.baidu.com/webmaster/add" target="_blank">网页搜索投诉中心</a>提交。</span><br><span>网站收录、流量等站长相关问题，请在<a style="text-decoration:underline;" href="http://zhanzhang.baidu.com/feedback/index" target="_blank">站长平台</a>反馈。</span>',
    cutFileTips: '&nbsp;点我，可以上传图片哦~',
    cutCanvasTips: '&nbsp;点我，可以在当前页面截图哦~&nbsp;<a style="text-decoration:underline;" href="http://f3.baidu.com/index.php/feedback/tiyan/steps" target="_blank">使用方法</a>',
    emailTips: '联系方式',
    showPosition: 'right',
    skinStyle: 'flat',
    needLevelType: !0,
    needIssueTips: !0,
    needIssue: !0,
    needCut: !0,
    needEmail: !0,
    needGuide: !1,
    defaultCut: !1,
    cutImg: 'jietu.png',
    upImg: 'upload.png',
    win_width: '',
    queryWord: '',
    dialogPosition: {
      left: '5px',
      right: '5px',
      bottom: '5px'
    },
    initRightBar: function (fb_styles, fb_data) {
      return bds.qa.ShortCut.is_feedbacking ? !0 : (bds.qa.ShortCut.is_feedbacking = !0, bds.qa.ShortCut._disposeHttps(), bds.qa.ShortCut._getMyJquery(), bds.qa.ShortCut.queryWord = fb_data, bds.qa.ShortCut.load_first(fb_styles), void 0 != fb_data ? bds.qa.ShortCut._getProData(fb_data)  : '', void (bds.qa.ShortCut._isIE() && ('object' != typeof JSON && (JSON = {
      }), function () {
        function f(t) {
          return 10 > t ? '0' + t : t
        }
        function quote(t) {
          return escapable.lastIndex = 0,
          escapable.test(t) ? '"' + t.replace(escapable, function (t) {
            var e = meta[t];
            return 'string' == typeof e ? e : '\\u' + ('0000' + t.charCodeAt(0).toString(16)).slice( - 4)
          }) + '"' : '"' + t + '"'
        }
        function str(t, e) {
          var n,
          i,
          o,
          r,
          a,
          s = gap,
          l = e[t];
          switch (l && 'object' == typeof l && 'function' == typeof l.toJSON && (l = l.toJSON(t)), 'function' == typeof rep && (l = rep.call(e, t, l)), typeof l) {
            case 'string':
              return quote(l);
            case 'number':
              return isFinite(l) ? String(l)  : 'null';
            case 'boolean':
            case 'null':
              return String(l);
            case 'object':
              if (!l) return 'null';
              if (gap += indent, a = [
              ], '[object Array]' === Object.prototype.toString.apply(l)) {
                for (r = l.length, n = 0; r > n; n += 1) a[n] = str(n, l) || 'null';
                return o = 0 === a.length ? '[]' : gap ? '[\n' + gap + a.join(',\n' + gap) + '\n' + s + ']' : '[' + a.join(',') + ']',
                gap = s,
                o
              }
              if (rep && 'object' == typeof rep) for (r = rep.length, n = 0; r > n; n += 1) 'string' == typeof rep[n] && (i = rep[n], o = str(i, l), o && a.push(quote(i) + (gap ? ': ' : ':') + o));
               else for (i in l) Object.prototype.hasOwnProperty.call(l, i) && (o = str(i, l), o && a.push(quote(i) + (gap ? ': ' : ':') + o));
              return o = 0 === a.length ? '{}' : gap ? '{\n' + gap + a.join(',\n' + gap) + '\n' + s + '}' : '{' + a.join(',') + '}',
              gap = s,
              o
          }
        }
        'function' != typeof Date.prototype.toJSON && (Date.prototype.toJSON = function () {
          return isFinite(this.valueOf()) ? this.getUTCFullYear() + '-' + f(this.getUTCMonth() + 1) + '-' + f(this.getUTCDate()) + 'T' + f(this.getUTCHours()) + ':' + f(this.getUTCMinutes()) + ':' + f(this.getUTCSeconds()) + 'Z' : null
        }, String.prototype.toJSON = Number.prototype.toJSON = Boolean.prototype.toJSON = function () {
          return this.valueOf()
        });
        var cx,
        escapable,
        gap,
        indent,
        meta,
        rep;
        'function' != typeof JSON.stringify && (escapable = /[\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g, meta = {
          '': '\\b',
          '   ': '\\t',
          '\n': '\\n',
          '\f': '\\f',
          '\r': '\\r',
          '"': '\\"',
          '\\': '\\\\'
        }, JSON.stringify = function (t, e, n) {
          var i;
          if (gap = '', indent = '', 'number' == typeof n) for (i = 0; n > i; i += 1) indent += ' ';
           else 'string' == typeof n && (indent = n);
          if (rep = e, e && 'function' != typeof e && ('object' != typeof e || 'number' != typeof e.length)) throw new Error('JSON.stringify');
          return str('', {
            '': t
          })
        }),
        'function' != typeof JSON.parse && (cx = /[\u0000\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g, JSON.parse = function (text, reviver) {
          function walk(t, e) {
            var n,
            i,
            o = t[e];
            if (o && 'object' == typeof o) for (n in o) Object.prototype.hasOwnProperty.call(o, n) && (i = walk(o, n), void 0 !== i ? o[n] = i : delete o[n]);
            return reviver.call(t, e, o)
          }
          var j;
          if (text = String(text), cx.lastIndex = 0, cx.test(text) && (text = text.replace(cx, function (t) {
            return '\\u' + ('0000' + t.charCodeAt(0).toString(16)).slice( - 4)
          })), /^[\],:{}\s]*$/.test(text.replace(/\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g, '@').replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g, ']').replace(/(?:^|:|,)(?:\s*\[)+/g, ''))) return j = eval('(' + text + ')'),
          'function' == typeof reviver ? walk({
            '': j
          }, '')  : j;
          throw new SyntaxError('JSON.parse')
        })
      }())))
    },
    load_first: function (t) {
      t || (t = bds.qa.ShortCut.default_options),
      bds.qa.ShortCut.initialize(t),
      bds.qa.ShortCut.getPrepare(),
      bds.qa.ShortCut.init(),
      bds.qa.ShortCut.imgLog(bds.qa.ShortCut.base_url_path + '/index.php/feedback/zx/clickcount/pro_id/' + bds.qa.ShortCut.product_id + '/entra_id/' + bds.qa.ShortCut.entrance_id)
    },
    _getMyJquery: function () {
      !function (t, e) {
        e(t)
      }('undefined' != typeof window ? window : this, function (t, e) {
        function n(t) {
          var e = t.length,
          n = oe.type(t);
          return 'function' === n || oe.isWindow(t) ? !1 : 1 === t.nodeType && e ? !0 : 'array' === n || 0 === e || 'number' == typeof e && e > 0 && e - 1 in t
        }
        function i(t, e, n) {
          if (oe.isFunction(e)) return oe.grep(t, function (t, i) {
            return !!e.call(t, i, t) !== n
          });
          if (e.nodeType) return oe.grep(t, function (t) {
            return t === e !== n
          });
          if ('string' == typeof e) {
            if (fe.test(e)) return oe.filter(e, t, n);
            e = oe.filter(e, t)
          }
          return oe.grep(t, function (t) {
            return oe.inArray(t, e) >= 0 !== n
          })
        }
        function o(t, e) {
          do t = t[e];
          while (t && 1 !== t.nodeType);
          return t
        }
        function r(t) {
          var e = xe[t] = {
          };
          return oe.each(t.match(ye) || [
          ], function (t, n) {
            e[n] = !0
          }),
          e
        }
        function a() {
          pe.addEventListener ? (pe.removeEventListener('DOMContentLoaded', s, !1), t.removeEventListener('load', s, !1))  : (pe.detachEvent('onreadystatechange', s), t.detachEvent('onload', s))
        }
        function s() {
          (pe.addEventListener || 'load' === event.type || 'complete' === pe.readyState) && (a(), oe.ready())
        }
        function l(t, e, n) {
          if (void 0 === n && 1 === t.nodeType) {
            var i = 'data-' + e.replace(qe, '-$1').toLowerCase();
            if (n = t.getAttribute(i), 'string' == typeof n) {
              try {
                n = 'true' === n ? !0 : 'false' === n ? !1 : 'null' === n ? null : + n + '' === n ? + n : _e.test(n) ? oe.parseJSON(n)  : n
              } catch (o) {
              }
              oe.data(t, e, n)
            } else n = void 0
          }
          return n
        }
        function u(t) {
          var e;
          for (e in t) if (('data' !== e || !oe.isEmptyObject(t[e])) && 'toJSON' !== e) return !1;
          return !0
        }
        function d(t, e, n, i) {
          if (oe.acceptData(t)) {
            var o,
            r,
            a = oe.expando,
            s = t.nodeType,
            l = s ? oe.cache : t,
            u = s ? t[a] : t[a] && a;
            if (u && l[u] && (i || l[u].data) || void 0 !== n || 'string' != typeof e) return u || (u = s ? t[a] = X.pop() || oe.guid++ : a),
            l[u] || (l[u] = s ? {
            }
             : {
              toJSON: oe.noop
            }),
            ('object' == typeof e || 'function' == typeof e) && (i ? l[u] = oe.extend(l[u], e)  : l[u].data = oe.extend(l[u].data, e)),
            r = l[u],
            i || (r.data || (r.data = {
            }), r = r.data),
            void 0 !== n && (r[oe.camelCase(e)] = n),
            'string' == typeof e ? (o = r[e], null == o && (o = r[oe.camelCase(e)]))  : o = r,
            o
          }
        }
        function c(t, e, n) {
          if (oe.acceptData(t)) {
            var i,
            o,
            r = t.nodeType,
            a = r ? oe.cache : t,
            s = r ? t[oe.expando] : oe.expando;
            if (a[s]) {
              if (e && (i = n ? a[s] : a[s].data)) {
                oe.isArray(e) ? e = e.concat(oe.map(e, oe.camelCase))  : e in i ? e = [
                  e
                ] : (e = oe.camelCase(e), e = e in i ? [
                  e
                ] : e.split(' ')),
                o = e.length;
                for (; o--; ) delete i[e[o]];
                if (n ? !u(i)  : !oe.isEmptyObject(i)) return
              }(n || (delete a[s].data, u(a[s]))) && (r ? oe.cleanData([t], !0)  : ne.deleteExpando || a != a.window ? delete a[s] : a[s] = null)
            }
          }
        }
        function f() {
          return !0
        }
        function h() {
          return !1
        }
        function p() {
          try {
            return pe.activeElement
          } catch (t) {
          }
        }
        function g(t) {
          var e = Pe.split('|'),
          n = t.createDocumentFragment();
          if (n.createElement) for (; e.length; ) n.createElement(e.pop());
          return n
        }
        function m(t, e) {
          var n,
          i,
          o = 0,
          r = typeof t.getElementsByTagName !== Se ? t.getElementsByTagName(e || '*')  : typeof t.querySelectorAll !== Se ? t.querySelectorAll(e || '*')  : void 0;
          if (!r) for (r = [
          ], n = t.childNodes || t; null != (i = n[o]); o++) !e || oe.nodeName(i, e) ? r.push(i)  : oe.merge(r, m(i, e));
          return void 0 === e || e && oe.nodeName(t, e) ? oe.merge([t], r)  : r
        }
        function b(t) {
          De.test(t.type) && (t.defaultChecked = t.checked)
        }
        function v(t, e) {
          return oe.nodeName(t, 'table') && oe.nodeName(11 !== e.nodeType ? e : e.firstChild, 'tr') ? t.getElementsByTagName('tbody') [0] || t.appendChild(t.ownerDocument.createElement('tbody'))  : t
        }
        function y(t) {
          return t.type = (null !== oe.find.attr(t, 'type')) + '/' + t.type,
          t
        }
        function x(t) {
          var e = $e.exec(t.type);
          return e ? t.type = e[1] : t.removeAttribute('type'),
          t
        }
        function C(t, e) {
          for (var n, i = 0; null != (n = t[i]); i++) oe._data(n, 'globalEval', !e || oe._data(e[i], 'globalEval'))
        }
        function w(t, e) {
          if (1 === e.nodeType && oe.hasData(t)) {
            var n,
            i,
            o,
            r = oe._data(t),
            a = oe._data(e, r),
            s = r.events;
            if (s) {
              delete a.handle,
              a.events = {
              };
              for (n in s) for (i = 0, o = s[n].length; o > i; i++) oe.event.add(e, n, s[n][i])
            }
            a.data && (a.data = oe.extend({
            }, a.data))
          }
        }
        function S(t, e) {
          var n,
          i,
          o;
          if (1 === e.nodeType) {
            if (n = e.nodeName.toLowerCase(), !ne.noCloneEvent && e[oe.expando]) {
              o = oe._data(e);
              for (i in o.events) oe.removeEvent(e, i, o.handle);
              e.removeAttribute(oe.expando)
            }
            'script' === n && e.text !== t.text ? (y(e).text = t.text, x(e))  : 'object' === n ? (e.parentNode && (e.outerHTML = t.outerHTML), ne.html5Clone && t.innerHTML && !oe.trim(e.innerHTML) && (e.innerHTML = t.innerHTML))  : 'input' === n && De.test(t.type) ? (e.defaultChecked = e.checked = t.checked, e.value !== t.value && (e.value = t.value))  : 'option' === n ? e.defaultSelected = e.selected = t.defaultSelected : ('input' === n || 'textarea' === n) && (e.defaultValue = t.defaultValue)
          }
        }
        function _(e, n) {
          var i,
          o = oe(n.createElement(e)).appendTo(n.body),
          r = t.getDefaultComputedStyle && (i = t.getDefaultComputedStyle(o[0])) ? i.display : oe.css(o[0], 'display');
          return o.detach(),
          r
        }
        function q(t) {
          var e = pe,
          n = Ze[t];
          return n || (n = _(t, e), 'none' !== n && n || (Ke = (Ke || oe('<iframe frameborder=\'0\' width=\'0\' height=\'0\'/>')).appendTo(e.documentElement), e = (Ke[0].contentWindow || Ke[0].contentDocument).document, e.write(), e.close(), n = _(t, e), Ke.detach()), Ze[t] = n),
          n
        }
        function T(t, e) {
          return {
            get: function () {
              var n = t();
              if (null != n) return n ? void delete this.get : (this.get = e).apply(this, arguments)
            }
          }
        }
        function k(t, e) {
          if (e in t) return e;
          for (var n = e.charAt(0).toUpperCase() + e.slice(1), i = e, o = hn.length; o--; ) if (e = hn[o] + n, e in t) return e;
          return i
        }
        function E(t, e) {
          for (var n, i, o, r = [
          ], a = 0, s = t.length; s > a; a++) i = t[a],
          i.style && (r[a] = oe._data(i, 'olddisplay'), n = i.style.display, e ? (r[a] || 'none' !== n || (i.style.display = ''), '' === i.style.display && Ee(i) && (r[a] = oe._data(i, 'olddisplay', q(i.nodeName))))  : (o = Ee(i), (n && 'none' !== n || !o) && oe._data(i, 'olddisplay', o ? n : oe.css(i, 'display'))));
          for (a = 0; s > a; a++) i = t[a],
          i.style && (e && 'none' !== i.style.display && '' !== i.style.display || (i.style.display = e ? r[a] || '' : 'none'));
          return t
        }
        function N(t, e, n) {
          var i = un.exec(e);
          return i ? Math.max(0, i[1] - (n || 0)) + (i[2] || 'px')  : e
        }
        function D(t, e, n, i, o) {
          for (var r = n === (i ? 'border' : 'content') ? 4 : 'width' === e ? 1 : 0, a = 0; 4 > r; r += 2) 'margin' === n && (a += oe.css(t, n + ke[r], !0, o)),
          i ? ('content' === n && (a -= oe.css(t, 'padding' + ke[r], !0, o)), 'margin' !== n && (a -= oe.css(t, 'border' + ke[r] + 'Width', !0, o)))  : (a += oe.css(t, 'padding' + ke[r], !0, o), 'padding' !== n && (a += oe.css(t, 'border' + ke[r] + 'Width', !0, o)));
          return a
        }
        function L(t, e, n) {
          var i = !0,
          o = 'width' === e ? t.offsetWidth : t.offsetHeight,
          r = tn(t),
          a = ne.boxSizing && 'border-box' === oe.css(t, 'boxSizing', !1, r);
          if (0 >= o || null == o) {
            if (o = en(t, e, r), (0 > o || null == o) && (o = t.style[e]), on.test(o)) return o;
            i = a && (ne.boxSizingReliable() || o === t.style[e]),
            o = parseFloat(o) || 0
          }
          return o + D(t, e, n || (a ? 'border' : 'content'), i, r) + 'px'
        }
        function A(t, e, n, i, o) {
          return new A.prototype.init(t, e, n, i, o)
        }
        function J() {
          return setTimeout(function () {
            pn = void 0
          }),
          pn = oe.now()
        }
        function I(t, e) {
          var n,
          i = {
            height: t
          },
          o = 0;
          for (e = e ? 1 : 0; 4 > o; o += 2 - e) n = ke[o],
          i['margin' + n] = i['padding' + n] = t;
          return e && (i.opacity = i.width = t),
          i
        }
        function M(t, e, n) {
          for (var i, o = (xn[e] || [
          ]).concat(xn['*']), r = 0, a = o.length; a > r; r++) if (i = o[r].call(n, e, t)) return i
        }
        function P(t, e, n) {
          var i,
          o,
          r,
          a,
          s,
          l,
          u,
          d,
          c = this,
          f = {
          },
          h = t.style,
          p = t.nodeType && Ee(t),
          g = oe._data(t, 'fxshow');
          n.queue || (s = oe._queueHooks(t, 'fx'), null == s.unqueued && (s.unqueued = 0, l = s.empty.fire, s.empty.fire = function () {
            s.unqueued || l()
          }), s.unqueued++, c.always(function () {
            c.always(function () {
              s.unqueued--,
              oe.queue(t, 'fx').length || s.empty.fire()
            })
          })),
          1 === t.nodeType && ('height' in e || 'width' in e) && (n.overflow = [
            h.overflow,
            h.overflowX,
            h.overflowY
          ], u = oe.css(t, 'display'), d = 'none' === u ? oe._data(t, 'olddisplay') || q(t.nodeName)  : u, 'inline' === d && 'none' === oe.css(t, 'float') && (ne.inlineBlockNeedsLayout && 'inline' !== q(t.nodeName) ? h.zoom = 1 : h.display = 'inline-block')),
          n.overflow && (h.overflow = 'hidden', ne.shrinkWrapBlocks() || c.always(function () {
            h.overflow = n.overflow[0],
            h.overflowX = n.overflow[1],
            h.overflowY = n.overflow[2]
          }));
          for (i in e) if (o = e[i], mn.exec(o)) {
            if (delete e[i], r = r || 'toggle' === o, o === (p ? 'hide' : 'show')) {
              if ('show' !== o || !g || void 0 === g[i]) continue;
              p = !0
            }
            f[i] = g && g[i] || oe.style(t, i)
          } else u = void 0;
          if (oe.isEmptyObject(f)) 'inline' === ('none' === u ? q(t.nodeName)  : u) && (h.display = u);
           else {
            g ? 'hidden' in g && (p = g.hidden)  : g = oe._data(t, 'fxshow', {
            }),
            r && (g.hidden = !p),
            p ? oe(t).show()  : c.done(function () {
              oe(t).hide()
            }),
            c.done(function () {
              var e;
              oe._removeData(t, 'fxshow');
              for (e in f) oe.style(t, e, f[e])
            });
            for (i in f) a = M(p ? g[i] : 0, i, c),
            i in g || (g[i] = a.start, p && (a.end = a.start, a.start = 'width' === i || 'height' === i ? 1 : 0))
          }
        }
        function O(t, e) {
          var n,
          i,
          o,
          r,
          a;
          for (n in t) if (i = oe.camelCase(n), o = e[i], r = t[n], oe.isArray(r) && (o = r[1], r = t[n] = r[0]), n !== i && (t[i] = r, delete t[n]), a = oe.cssHooks[i], a && 'expand' in a) {
            r = a.expand(r),
            delete t[i];
            for (n in r) n in t || (t[n] = r[n], e[n] = o)
          } else e[i] = o
        }
        function R(t, e, n) {
          var i,
          o,
          r = 0,
          a = yn.length,
          s = oe.Deferred().always(function () {
            delete l.elem
          }),
          l = function () {
            if (o) return !1;
            for (var e = pn || J(), n = Math.max(0, u.startTime + u.duration - e), i = n / u.duration || 0, r = 1 - i, a = 0, l = u.tweens.length; l > a; a++) u.tweens[a].run(r);
            return s.notifyWith(t, [
              u,
              r,
              n
            ]),
            1 > r && l ? n : (s.resolveWith(t, [
              u
            ]), !1)
          },
          u = s.promise({
            elem: t,
            props: oe.extend({
            }, e),
            opts: oe.extend(!0, {
              specialEasing: {
              }
            }, n),
            originalProperties: e,
            originalOptions: n,
            startTime: pn || J(),
            duration: n.duration,
            tweens: [
            ],
            createTween: function (e, n) {
              var i = oe.Tween(t, u.opts, e, n, u.opts.specialEasing[e] || u.opts.easing);
              return u.tweens.push(i),
              i
            },
            stop: function (e) {
              var n = 0,
              i = e ? u.tweens.length : 0;
              if (o) return this;
              for (o = !0; i > n; n++) u.tweens[n].run(1);
              return e ? s.resolveWith(t, [
                u,
                e
              ])  : s.rejectWith(t, [
                u,
                e
              ]),
              this
            }
          }),
          d = u.props;
          for (O(d, u.opts.specialEasing); a > r; r++) if (i = yn[r].call(u, t, d, u.opts)) return i;
          return oe.map(d, M, u),
          oe.isFunction(u.opts.start) && u.opts.start.call(t, u),
          oe.fx.timer(oe.extend(l, {
            elem: t,
            anim: u,
            queue: u.opts.queue
          })),
          u.progress(u.opts.progress).done(u.opts.done, u.opts.complete).fail(u.opts.fail).always(u.opts.always)
        }
        function Q(t) {
          return function (e, n) {
            'string' != typeof e && (n = e, e = '*');
            var i,
            o = 0,
            r = e.toLowerCase().match(ye) || [
            ];
            if (oe.isFunction(n)) for (; i = r[o++]; ) '+' === i.charAt(0) ? (i = i.slice(1) || '*', (t[i] = t[i] || [
            ]).unshift(n))  : (t[i] = t[i] || [
            ]).push(n)
          }
        }
        function j(t, e, n, i) {
          function o(s) {
            var l;
            return r[s] = !0,
            oe.each(t[s] || [
            ], function (t, s) {
              var u = s(e, n, i);
              return 'string' != typeof u || a || r[u] ? a ? !(l = u)  : void 0 : (e.dataTypes.unshift(u), o(u), !1)
            }),
            l
          }
          var r = {
          },
          a = t === Bn;
          return o(e.dataTypes[0]) || !r['*'] && o('*')
        }
        function H(t, e) {
          var n,
          i,
          o = oe.ajaxSettings.flatOptions || {
          };
          for (i in e) void 0 !== e[i] && ((o[i] ? t : n || (n = {
          })) [i] = e[i]);
          return n && oe.extend(!0, t, n),
          t
        }
        function F(t, e, n) {
          for (var i, o, r, a, s = t.contents, l = t.dataTypes; '*' === l[0]; ) l.shift(),
          void 0 === o && (o = t.mimeType || e.getResponseHeader('Content-Type'));
          if (o) for (a in s) if (s[a] && s[a].test(o)) {
            l.unshift(a);
            break
          }
          if (l[0] in n) r = l[0];
           else {
            for (a in n) {
              if (!l[0] || t.converters[a + ' ' + l[0]]) {
                r = a;
                break
              }
              i || (i = a)
            }
            r = r || i
          }
          return r ? (r !== l[0] && l.unshift(r), n[r])  : void 0
        }
        function z(t, e, n, i) {
          var o,
          r,
          a,
          s,
          l,
          u = {
          },
          d = t.dataTypes.slice();
          if (d[1]) for (a in t.converters) u[a.toLowerCase()] = t.converters[a];
          for (r = d.shift(); r; ) if (t.responseFields[r] && (n[t.responseFields[r]] = e), !l && i && t.dataFilter && (e = t.dataFilter(e, t.dataType)), l = r, r = d.shift()) if ('*' === r) r = l;
           else if ('*' !== l && l !== r) {
            if (a = u[l + ' ' + r] || u['* ' + r], !a) for (o in u) if (s = o.split(' '), s[1] === r && (a = u[l + ' ' + s[0]] || u['* ' + s[0]])) {
              a === !0 ? a = u[o] : u[o] !== !0 && (r = s[0], d.unshift(s[1]));
              break
            }
            if (a !== !0) if (a && t['throws']) e = a(e);
             else try {
              e = a(e)
            } catch (c) {
              return {
                state: 'parsererror',
                error: a ? c : 'No conversion from ' + l + ' to ' + r
              }
            }
          }
          return {
            state: 'success',
            data: e
          }
        }
        function B(t, e, n, i) {
          var o;
          if (oe.isArray(e)) oe.each(e, function (e, o) {
            n || Xn.test(t) ? i(t, o)  : B(t + '[' + ('object' == typeof o ? e : '') + ']', o, n, i)
          });
           else if (n || 'object' !== oe.type(e)) i(t, e);
           else for (o in e) B(t + '[' + o + ']', e[o], n, i)
        }
        function W() {
          try {
            return new t.XMLHttpRequest
          } catch (e) {
          }
        }
        function U() {
          try {
            return new t.ActiveXObject('Microsoft.XMLHTTP')
          } catch (e) {
          }
        }
        function $(t) {
          return oe.isWindow(t) ? t : 9 === t.nodeType ? t.defaultView || t.parentWindow : !1
        }
        var X = [
        ],
        G = X.slice,
        V = X.concat,
        Y = X.push,
        K = X.indexOf,
        Z = {
        },
        te = Z.toString,
        ee = Z.hasOwnProperty,
        ne = {
        },
        ie = '1.11.2',
        oe = function (t, e) {
          return new oe.fn.init(t, e)
        },
        re = /^[\s\uFEFF\xA0]+|[\s\uFEFF\xA0]+$/g,
        ae = /^-ms-/,
        se = /-([\da-z])/gi,
        le = function (t, e) {
          return e.toUpperCase()
        };
        oe.fn = oe.prototype = {
          jquery: ie,
          constructor: oe,
          selector: '',
          length: 0,
          toArray: function () {
            return G.call(this)
          },
          get: function (t) {
            return null != t ? 0 > t ? this[t + this.length] : this[t] : G.call(this)
          },
          pushStack: function (t) {
            var e = oe.merge(this.constructor(), t);
            return e.prevObject = this,
            e.context = this.context,
            e
          },
          each: function (t, e) {
            return oe.each(this, t, e)
          },
          map: function (t) {
            return this.pushStack(oe.map(this, function (e, n) {
              return t.call(e, n, e)
            }))
          },
          slice: function () {
            return this.pushStack(G.apply(this, arguments))
          },
          first: function () {
            return this.eq(0)
          },
          last: function () {
            return this.eq( - 1)
          },
          eq: function (t) {
            var e = this.length,
            n = + t + (0 > t ? e : 0);
            return this.pushStack(n >= 0 && e > n ? [
              this[n]
            ] : [
            ])
          },
          end: function () {
            return this.prevObject || this.constructor(null)
          },
          push: Y,
          sort: X.sort,
          splice: X.splice
        },
        oe.extend = oe.fn.extend = function () {
          var t,
          e,
          n,
          i,
          o,
          r,
          a = arguments[0] || {
          },
          s = 1,
          l = arguments.length,
          u = !1;
          for ('boolean' == typeof a && (u = a, a = arguments[s] || {
          }, s++), 'object' == typeof a || oe.isFunction(a) || (a = {
          }), s === l && (a = this, s--); l > s; s++) if (null != (o = arguments[s])) for (i in o) t = a[i],
          n = o[i],
          a !== n && (u && n && (oe.isPlainObject(n) || (e = oe.isArray(n))) ? (e ? (e = !1, r = t && oe.isArray(t) ? t : [
          ])  : r = t && oe.isPlainObject(t) ? t : {
          }, a[i] = oe.extend(u, r, n))  : void 0 !== n && (a[i] = n));
          return a
        },
        oe.extend({
          expando: 'jQuery' + (ie + Math.random()).replace(/\D/g, ''),
          isReady: !0,
          error: function (t) {
            throw new Error(t)
          },
          noop: function () {
          },
          isFunction: function (t) {
            return 'function' === oe.type(t)
          },
          isArray: Array.isArray || function (t) {
            return 'array' === oe.type(t)
          },
          isWindow: function (t) {
            return null != t && t == t.window
          },
          isNumeric: function (t) {
            return !oe.isArray(t) && t - parseFloat(t) + 1 >= 0
          },
          isEmptyObject: function (t) {
            var e;
            for (e in t) return !1;
            return !0
          },
          isPlainObject: function (t) {
            var e;
            if (!t || 'object' !== oe.type(t) || t.nodeType || oe.isWindow(t)) return !1;
            try {
              if (t.constructor && !ee.call(t, 'constructor') && !ee.call(t.constructor.prototype, 'isPrototypeOf')) return !1
            } catch (n) {
              return !1
            }
            if (ne.ownLast) for (e in t) return ee.call(t, e);
            for (e in t);
            return void 0 === e || ee.call(t, e)
          },
          type: function (t) {
            return null == t ? t + '' : 'object' == typeof t || 'function' == typeof t ? Z[te.call(t)] || 'object' : typeof t
          },
          globalEval: function (e) {
            e && oe.trim(e) && (t.execScript || function (e) {
              t.eval.call(t, e)
            }) (e)
          },
          camelCase: function (t) {
            return t.replace(ae, 'ms-').replace(se, le)
          },
          nodeName: function (t, e) {
            return t.nodeName && t.nodeName.toLowerCase() === e.toLowerCase()
          },
          each: function (t, e, i) {
            var o,
            r = 0,
            a = t.length,
            s = n(t);
            if (i) {
              if (s) for (; a > r && (o = e.apply(t[r], i), o !== !1); r++);
               else for (r in t) if (o = e.apply(t[r], i), o === !1) break
            } else if (s) for (; a > r && (o = e.call(t[r], r, t[r]), o !== !1); r++);
             else for (r in t) if (o = e.call(t[r], r, t[r]), o === !1) break;
            return t
          },
          trim: function (t) {
            return null == t ? '' : (t + '').replace(re, '')
          },
          makeArray: function (t, e) {
            var i = e || [
            ];
            return null != t && (n(Object(t)) ? oe.merge(i, 'string' == typeof t ? [
              t
            ] : t)  : Y.call(i, t)),
            i
          },
          inArray: function (t, e, n) {
            var i;
            if (e) {
              if (K) return K.call(e, t, n);
              for (i = e.length, n = n ? 0 > n ? Math.max(0, i + n)  : n : 0; i > n; n++) if (n in e && e[n] === t) return n
            }
            return - 1
          },
          merge: function (t, e) {
            for (var n = + e.length, i = 0, o = t.length; n > i; ) t[o++] = e[i++];
            if (n !== n) for (; void 0 !== e[i]; ) t[o++] = e[i++];
            return t.length = o,
            t
          },
          grep: function (t, e, n) {
            for (var i, o = [
            ], r = 0, a = t.length, s = !n; a > r; r++) i = !e(t[r], r),
            i !== s && o.push(t[r]);
            return o
          },
          map: function (t, e, i) {
            var o,
            r = 0,
            a = t.length,
            s = n(t),
            l = [
            ];
            if (s) for (; a > r; r++) o = e(t[r], r, i),
            null != o && l.push(o);
             else for (r in t) o = e(t[r], r, i),
            null != o && l.push(o);
            return V.apply([], l)
          },
          guid: 1,
          proxy: function (t, e) {
            var n,
            i,
            o;
            return 'string' == typeof e && (o = t[e], e = t, t = o),
            oe.isFunction(t) ? (n = G.call(arguments, 2), i = function () {
              return t.apply(e || this, n.concat(G.call(arguments)))
            }, i.guid = t.guid = t.guid || oe.guid++, i)  : void 0
          },
          now: function () {
            return + new Date
          },
          support: ne
        }),
        oe.each('Boolean Number String Function Array Date RegExp Object Error'.split(' '), function (t, e) {
          Z['[object ' + e + ']'] = e.toLowerCase()
        });
        var ue = function (t) {
          function e(t, e, n, i) {
            var o,
            r,
            a,
            s,
            l,
            u,
            c,
            h,
            p,
            g;
            if ((e ? e.ownerDocument || e : j) !== A && L(e), e = e || A, n = n || [
            ], s = e.nodeType, 'string' != typeof t || !t || 1 !== s && 9 !== s && 11 !== s) return n;
            if (!i && I) {
              if (11 !== s && (o = ve.exec(t))) if (a = o[1]) {
                if (9 === s) {
                  if (r = e.getElementById(a), !r || !r.parentNode) return n;
                  if (r.id === a) return n.push(r),
                  n
                } else if (e.ownerDocument && (r = e.ownerDocument.getElementById(a)) && R(e, r) && r.id === a) return n.push(r),
                n
              } else {
                if (o[2]) return K.apply(n, e.getElementsByTagName(t)),
                n;
                if ((a = o[3]) && C.getElementsByClassName) return K.apply(n, e.getElementsByClassName(a)),
                n
              }
              if (C.qsa && (!M || !M.test(t))) {
                if (h = c = Q, p = e, g = 1 !== s && t, 1 === s && 'object' !== e.nodeName.toLowerCase()) {
                  for (u = q(t), (c = e.getAttribute('id')) ? h = c.replace(xe, '\\$&')  : e.setAttribute('id', h), h = '[id=\'' + h + '\'] ', l = u.length; l--; ) u[l] = h + f(u[l]);
                  p = ye.test(t) && d(e.parentNode) || e,
                  g = u.join(',')
                }
                if (g) try {
                  return K.apply(n, p.querySelectorAll(g)),
                  n
                } catch (m) {
                } finally {
                  c || e.removeAttribute('id')
                }
              }
            }
            return k(t.replace(le, '$1'), e, n, i)
          }
          function n() {
            function t(n, i) {
              return e.push(n + ' ') > w.cacheLength && delete t[e.shift()],
              t[n + ' '] = i
            }
            var e = [
            ];
            return t
          }
          function i(t) {
            return t[Q] = !0,
            t
          }
          function o(t) {
            var e = A.createElement('div');
            try {
              return !!t(e)
            } catch (n) {
              return !1
            } finally {
              e.parentNode && e.parentNode.removeChild(e),
              e = null
            }
          }
          function r(t, e) {
            for (var n = t.split('|'), i = t.length; i--; ) w.attrHandle[n[i]] = e
          }
          function a(t, e) {
            var n = e && t,
            i = n && 1 === t.nodeType && 1 === e.nodeType && (~e.sourceIndex || $) - (~t.sourceIndex || $);
            if (i) return i;
            if (n) for (; n = n.nextSibling; ) if (n === e) return - 1;
            return t ? 1 : - 1
          }
          function s(t) {
            return function (e) {
              var n = e.nodeName.toLowerCase();
              return 'input' === n && e.type === t
            }
          }
          function l(t) {
            return function (e) {
              var n = e.nodeName.toLowerCase();
              return ('input' === n || 'button' === n) && e.type === t
            }
          }
          function u(t) {
            return i(function (e) {
              return e = + e,
              i(function (n, i) {
                for (var o, r = t([], n.length, e), a = r.length; a--; ) n[o = r[a]] && (n[o] = !(i[o] = n[o]))
              })
            })
          }
          function d(t) {
            return t && 'undefined' != typeof t.getElementsByTagName && t
          }
          function c() {
          }
          function f(t) {
            for (var e = 0, n = t.length, i = ''; n > e; e++) i += t[e].value;
            return i
          }
          function h(t, e, n) {
            var i = e.dir,
            o = n && 'parentNode' === i,
            r = F++;
            return e.first ? function (e, n, r) {
              for (; e = e[i]; ) if (1 === e.nodeType || o) return t(e, n, r)
            }
             : function (e, n, a) {
              var s,
              l,
              u = [
                H,
                r
              ];
              if (a) {
                for (; e = e[i]; ) if ((1 === e.nodeType || o) && t(e, n, a)) return !0
              } else for (; e = e[i]; ) if (1 === e.nodeType || o) {
                if (l = e[Q] || (e[Q] = {
                }), (s = l[i]) && s[0] === H && s[1] === r) return u[2] = s[2];
                if (l[i] = u, u[2] = t(e, n, a)) return !0
              }
            }
          }
          function p(t) {
            return t.length > 1 ? function (e, n, i) {
              for (var o = t.length; o--; ) if (!t[o](e, n, i)) return !1;
              return !0
            }
             : t[0]
          }
          function g(t, n, i) {
            for (var o = 0, r = n.length; r > o; o++) e(t, n[o], i);
            return i
          }
          function m(t, e, n, i, o) {
            for (var r, a = [
            ], s = 0, l = t.length, u = null != e; l > s; s++) (r = t[s]) && (!n || n(r, i, o)) && (a.push(r), u && e.push(s));
            return a
          }
          function b(t, e, n, o, r, a) {
            return o && !o[Q] && (o = b(o)),
            r && !r[Q] && (r = b(r, a)),
            i(function (i, a, s, l) {
              var u,
              d,
              c,
              f = [
              ],
              h = [
              ],
              p = a.length,
              b = i || g(e || '*', s.nodeType ? [
                s
              ] : s, [
              ]),
              v = !t || !i && e ? b : m(b, f, t, s, l),
              y = n ? r || (i ? t : p || o) ? [
              ] : a : v;
              if (n && n(v, y, s, l), o) for (u = m(y, h), o(u, [
              ], s, l), d = u.length; d--; ) (c = u[d]) && (y[h[d]] = !(v[h[d]] = c));
              if (i) {
                if (r || t) {
                  if (r) {
                    for (u = [
                    ], d = y.length; d--; ) (c = y[d]) && u.push(v[d] = c);
                    r(null, y = [
                    ], u, l)
                  }
                  for (d = y.length; d--; ) (c = y[d]) && (u = r ? te(i, c)  : f[d]) > - 1 && (i[u] = !(a[u] = c))
                }
              } else y = m(y === a ? y.splice(p, y.length)  : y),
              r ? r(null, a, y, l)  : K.apply(a, y)
            })
          }
          function v(t) {
            for (var e, n, i, o = t.length, r = w.relative[t[0].type], a = r || w.relative[' '], s = r ? 1 : 0, l = h(function (t) {
              return t === e
            }, a, !0), u = h(function (t) {
              return te(e, t) > - 1
            }, a, !0), d = [
              function (t, n, i) {
                var o = !r && (i || n !== E) || ((e = n).nodeType ? l(t, n, i)  : u(t, n, i));
                return e = null,
                o
              }
            ]; o > s; s++) if (n = w.relative[t[s].type]) d = [
              h(p(d), n)
            ];
             else {
              if (n = w.filter[t[s].type].apply(null, t[s].matches), n[Q]) {
                for (i = ++s; o > i && !w.relative[t[i].type]; i++);
                return b(s > 1 && p(d), s > 1 && f(t.slice(0, s - 1).concat({
                  value: ' ' === t[s - 2].type ? '*' : ''
                })).replace(le, '$1'), n, i > s && v(t.slice(s, i)), o > i && v(t = t.slice(i)), o > i && f(t))
              }
              d.push(n)
            }
            return p(d)
          }
          function y(t, n) {
            var o = n.length > 0,
            r = t.length > 0,
            a = function (i, a, s, l, u) {
              var d,
              c,
              f,
              h = 0,
              p = '0',
              g = i && [
              ],
              b = [
              ],
              v = E,
              y = i || r && w.find.TAG('*', u),
              x = H += null == v ? 1 : Math.random() || 0.1,
              C = y.length;
              for (u && (E = a !== A && a); p !== C && null != (d = y[p]); p++) {
                if (r && d) {
                  for (c = 0; f = t[c++]; ) if (f(d, a, s)) {
                    l.push(d);
                    break
                  }
                  u && (H = x)
                }
                o && ((d = !f && d) && h--, i && g.push(d))
              }
              if (h += p, o && p !== h) {
                for (c = 0; f = n[c++]; ) f(g, b, a, s);
                if (i) {
                  if (h > 0) for (; p--; ) g[p] || b[p] || (b[p] = V.call(l));
                  b = m(b)
                }
                K.apply(l, b),
                u && !i && b.length > 0 && h + n.length > 1 && e.uniqueSort(l)
              }
              return u && (H = x, E = v),
              g
            };
            return o ? i(a)  : a
          }
          var x,
          C,
          w,
          S,
          _,
          q,
          T,
          k,
          E,
          N,
          D,
          L,
          A,
          J,
          I,
          M,
          P,
          O,
          R,
          Q = 'sizzle' + 1 * new Date,
          j = t.document,
          H = 0,
          F = 0,
          z = n(),
          B = n(),
          W = n(),
          U = function (t, e) {
            return t === e && (D = !0),
            0
          },
          $ = 1 << 31,
          X = {
          }.hasOwnProperty,
          G = [
          ],
          V = G.pop,
          Y = G.push,
          K = G.push,
          Z = G.slice,
          te = function (t, e) {
            for (var n = 0, i = t.length; i > n; n++) if (t[n] === e) return n;
            return - 1
          },
          ee = 'checked|selected|async|autofocus|autoplay|controls|defer|disabled|hidden|ismap|loop|multiple|open|readonly|required|scoped',
          ne = '[\\x20\\t\\r\\n\\f]',
          ie = '(?:\\\\.|[\\w-]|[^\\x00-\\xa0])+',
          oe = ie.replace('w', 'w#'),
          re = '\\[' + ne + '*(' + ie + ')(?:' + ne + '*([*^$|!~]?=)' + ne + '*(?:\'((?:\\\\.|[^\\\\\'])*)\'|"((?:\\\\.|[^\\\\"])*)"|(' + oe + '))|)' + ne + '*\\]',
          ae = ':(' + ie + ')(?:\\(((\'((?:\\\\.|[^\\\\\'])*)\'|"((?:\\\\.|[^\\\\"])*)")|((?:\\\\.|[^\\\\()[\\]]|' + re + ')*)|.*)\\)|)',
          se = new RegExp(ne + '+', 'g'),
          le = new RegExp('^' + ne + '+|((?:^|[^\\\\])(?:\\\\.)*)' + ne + '+$', 'g'),
          ue = new RegExp('^' + ne + '*,' + ne + '*'),
          de = new RegExp('^' + ne + '*([>+~]|' + ne + ')' + ne + '*'),
          ce = new RegExp('=' + ne + '*([^\\]\'"]*?)' + ne + '*\\]', 'g'),
          fe = new RegExp(ae),
          he = new RegExp('^' + oe + '$'),
          pe = {
            ID: new RegExp('^#(' + ie + ')'),
            CLASS: new RegExp('^\\.(' + ie + ')'),
            TAG: new RegExp('^(' + ie.replace('w', 'w*') + ')'),
            ATTR: new RegExp('^' + re),
            PSEUDO: new RegExp('^' + ae),
            CHILD: new RegExp('^:(only|first|last|nth|nth-last)-(child|of-type)(?:\\(' + ne + '*(even|odd|(([+-]|)(\\d*)n|)' + ne + '*(?:([+-]|)' + ne + '*(\\d+)|))' + ne + '*\\)|)', 'i'),
            bool: new RegExp('^(?:' + ee + ')$', 'i'),
            needsContext: new RegExp('^' + ne + '*[>+~]|:(even|odd|eq|gt|lt|nth|first|last)(?:\\(' + ne + '*((?:-\\d)?\\d*)' + ne + '*\\)|)(?=[^-]|$)', 'i')
          },
          ge = /^(?:input|select|textarea|button)$/i,
          me = /^h\d$/i,
          be = /^[^{]+\{\s*\[native \w/,
          ve = /^(?:#([\w-]+)|(\w+)|\.([\w-]+))$/,
          ye = /[+~]/,
          xe = /'|\\/g,
          Ce = new RegExp('\\\\([\\da-f]{1,6}' + ne + '?|(' + ne + ')|.)', 'ig'),
          we = function (t, e, n) {
            var i = '0x' + e - 65536;
            return i !== i || n ? e : 0 > i ? String.fromCharCode(i + 65536)  : String.fromCharCode(i >> 10 | 55296, 1023 & i | 56320)
          },
          Se = function () {
            L()
          };
          try {
            K.apply(G = Z.call(j.childNodes), j.childNodes),
            G[j.childNodes.length].nodeType
          } catch (_e) {
            K = {
              apply: G.length ? function (t, e) {
                Y.apply(t, Z.call(e))
              }
               : function (t, e) {
                for (var n = t.length, i = 0; t[n++] = e[i++]; );
                t.length = n - 1
              }
            }
          }
          C = e.support = {
          },
          _ = e.isXML = function (t) {
            var e = t && (t.ownerDocument || t).documentElement;
            return e ? 'HTML' !== e.nodeName : !1
          },
          L = e.setDocument = function (t) {
            var e,
            n,
            i = t ? t.ownerDocument || t : j;
            return i !== A && 9 === i.nodeType && i.documentElement ? (A = i, J = i.documentElement, n = i.defaultView, n && n !== n.top && (n.addEventListener ? n.addEventListener('unload', Se, !1)  : n.attachEvent && n.attachEvent('onunload', Se)), I = !_(i), C.attributes = o(function (t) {
              return t.className = 'i',
              !t.getAttribute('className')
            }), C.getElementsByTagName = o(function (t) {
              return t.appendChild(i.createComment('')),
              !t.getElementsByTagName('*').length
            }), C.getElementsByClassName = be.test(i.getElementsByClassName), C.getById = o(function (t) {
              return J.appendChild(t).id = Q,
              !i.getElementsByName || !i.getElementsByName(Q).length
            }), C.getById ? (w.find.ID = function (t, e) {
              if ('undefined' != typeof e.getElementById && I) {
                var n = e.getElementById(t);
                return n && n.parentNode ? [
                  n
                ] : [
                ]
              }
            }, w.filter.ID = function (t) {
              var e = t.replace(Ce, we);
              return function (t) {
                return t.getAttribute('id') === e
              }
            })  : (delete w.find.ID, w.filter.ID = function (t) {
              var e = t.replace(Ce, we);
              return function (t) {
                var n = 'undefined' != typeof t.getAttributeNode && t.getAttributeNode('id');
                return n && n.value === e
              }
            }), w.find.TAG = C.getElementsByTagName ? function (t, e) {
              return 'undefined' != typeof e.getElementsByTagName ? e.getElementsByTagName(t)  : C.qsa ? e.querySelectorAll(t)  : void 0
            }
             : function (t, e) {
              var n,
              i = [
              ],
              o = 0,
              r = e.getElementsByTagName(t);
              if ('*' === t) {
                for (; n = r[o++]; ) 1 === n.nodeType && i.push(n);
                return i
              }
              return r
            }, w.find.CLASS = C.getElementsByClassName && function (t, e) {
              return I ? e.getElementsByClassName(t)  : void 0
            }, P = [
            ], M = [
            ], (C.qsa = be.test(i.querySelectorAll)) && (o(function (t) {
              J.appendChild(t).innerHTML = '<a id=\'' + Q + '\'></a><select id=\'' + Q + '-\f]\' msallowcapture=\'\'><option selected=\'\'></option></select>',
              t.querySelectorAll('[msallowcapture^=\'\']').length && M.push('[*^$]=' + ne + '*(?:\'\'|"")'),
              t.querySelectorAll('[selected]').length || M.push('\\[' + ne + '*(?:value|' + ee + ')'),
              t.querySelectorAll('[id~=' + Q + '-]').length || M.push('~='),
              t.querySelectorAll(':checked').length || M.push(':checked'),
              t.querySelectorAll('a#' + Q + '+*').length || M.push('.#.+[+~]')
            }), o(function (t) {
              var e = i.createElement('input');
              e.setAttribute('type', 'hidden'),
              t.appendChild(e).setAttribute('name', 'D'),
              t.querySelectorAll('[name=d]').length && M.push('name' + ne + '*[*^$|!~]?='),
              t.querySelectorAll(':enabled').length || M.push(':enabled', ':disabled'),
              t.querySelectorAll('*,:x'),
              M.push(',.*:')
            })), (C.matchesSelector = be.test(O = J.matches || J.webkitMatchesSelector || J.mozMatchesSelector || J.oMatchesSelector || J.msMatchesSelector)) && o(function (t) {
              C.disconnectedMatch = O.call(t, 'div'),
              O.call(t, '[s!=\'\']:x'),
              P.push('!=', ae)
            }), M = M.length && new RegExp(M.join('|')), P = P.length && new RegExp(P.join('|')), e = be.test(J.compareDocumentPosition), R = e || be.test(J.contains) ? function (t, e) {
              var n = 9 === t.nodeType ? t.documentElement : t,
              i = e && e.parentNode;
              return t === i || !(!i || 1 !== i.nodeType || !(n.contains ? n.contains(i)  : t.compareDocumentPosition && 16 & t.compareDocumentPosition(i)))
            }
             : function (t, e) {
              if (e) for (; e = e.parentNode; ) if (e === t) return !0;
              return !1
            }, U = e ? function (t, e) {
              if (t === e) return D = !0,
              0;
              var n = !t.compareDocumentPosition - !e.compareDocumentPosition;
              return n ? n : (n = (t.ownerDocument || t) === (e.ownerDocument || e) ? t.compareDocumentPosition(e)  : 1, 1 & n || !C.sortDetached && e.compareDocumentPosition(t) === n ? t === i || t.ownerDocument === j && R(j, t) ? - 1 : e === i || e.ownerDocument === j && R(j, e) ? 1 : N ? te(N, t) - te(N, e)  : 0 : 4 & n ? - 1 : 1)
            }
             : function (t, e) {
              if (t === e) return D = !0,
              0;
              var n,
              o = 0,
              r = t.parentNode,
              s = e.parentNode,
              l = [
                t
              ],
              u = [
                e
              ];
              if (!r || !s) return t === i ? - 1 : e === i ? 1 : r ? - 1 : s ? 1 : N ? te(N, t) - te(N, e)  : 0;
              if (r === s) return a(t, e);
              for (n = t; n = n.parentNode; ) l.unshift(n);
              for (n = e; n = n.parentNode; ) u.unshift(n);
              for (; l[o] === u[o]; ) o++;
              return o ? a(l[o], u[o])  : l[o] === j ? - 1 : u[o] === j ? 1 : 0
            }, i)  : A
          },
          e.matches = function (t, n) {
            return e(t, null, null, n)
          },
          e.matchesSelector = function (t, n) {
            if ((t.ownerDocument || t) !== A && L(t), n = n.replace(ce, '=\'$1\']'), !(!C.matchesSelector || !I || P && P.test(n) || M && M.test(n))) try {
              var i = O.call(t, n);
              if (i || C.disconnectedMatch || t.document && 11 !== t.document.nodeType) return i
            } catch (o) {
            }
            return e(n, A, null, [
              t
            ]).length > 0
          },
          e.contains = function (t, e) {
            return (t.ownerDocument || t) !== A && L(t),
            R(t, e)
          },
          e.attr = function (t, e) {
            (t.ownerDocument || t) !== A && L(t);
            var n = w.attrHandle[e.toLowerCase()],
            i = n && X.call(w.attrHandle, e.toLowerCase()) ? n(t, e, !I)  : void 0;
            return void 0 !== i ? i : C.attributes || !I ? t.getAttribute(e)  : (i = t.getAttributeNode(e)) && i.specified ? i.value : null
          },
          e.error = function (t) {
            throw new Error('Syntax error, unrecognized expression: ' + t)
          },
          e.uniqueSort = function (t) {
            var e,
            n = [
            ],
            i = 0,
            o = 0;
            if (D = !C.detectDuplicates, N = !C.sortStable && t.slice(0), t.sort(U), D) {
              for (; e = t[o++]; ) e === t[o] && (i = n.push(o));
              for (; i--; ) t.splice(n[i], 1)
            }
            return N = null,
            t
          },
          S = e.getText = function (t) {
            var e,
            n = '',
            i = 0,
            o = t.nodeType;
            if (o) {
              if (1 === o || 9 === o || 11 === o) {
                if ('string' == typeof t.textContent) return t.textContent;
                for (t = t.firstChild; t; t = t.nextSibling) n += S(t)
              } else if (3 === o || 4 === o) return t.nodeValue
            } else for (; e = t[i++]; ) n += S(e);
            return n
          },
          w = e.selectors = {
            cacheLength: 50,
            createPseudo: i,
            match: pe,
            attrHandle: {
            },
            find: {
            },
            relative: {
              '>': {
                dir: 'parentNode',
                first: !0
              },
              ' ': {
                dir: 'parentNode'
              },
              '+': {
                dir: 'previousSibling',
                first: !0
              },
              '~': {
                dir: 'previousSibling'
              }
            },
            preFilter: {
              ATTR: function (t) {
                return t[1] = t[1].replace(Ce, we),
                t[3] = (t[3] || t[4] || t[5] || '').replace(Ce, we),
                '~=' === t[2] && (t[3] = ' ' + t[3] + ' '),
                t.slice(0, 4)
              },
              CHILD: function (t) {
                return t[1] = t[1].toLowerCase(),
                'nth' === t[1].slice(0, 3) ? (t[3] || e.error(t[0]), t[4] = + (t[4] ? t[5] + (t[6] || 1)  : 2 * ('even' === t[3] || 'odd' === t[3])), t[5] = + (t[7] + t[8] || 'odd' === t[3]))  : t[3] && e.error(t[0]),
                t
              },
              PSEUDO: function (t) {
                var e,
                n = !t[6] && t[2];
                return pe.CHILD.test(t[0]) ? null : (t[3] ? t[2] = t[4] || t[5] || '' : n && fe.test(n) && (e = q(n, !0)) && (e = n.indexOf(')', n.length - e) - n.length) && (t[0] = t[0].slice(0, e), t[2] = n.slice(0, e)), t.slice(0, 3))
              }
            },
            filter: {
              TAG: function (t) {
                var e = t.replace(Ce, we).toLowerCase();
                return '*' === t ? function () {
                  return !0
                }
                 : function (t) {
                  return t.nodeName && t.nodeName.toLowerCase() === e
                }
              },
              CLASS: function (t) {
                var e = z[t + ' '];
                return e || (e = new RegExp('(^|' + ne + ')' + t + '(' + ne + '|$)')) && z(t, function (t) {
                  return e.test('string' == typeof t.className && t.className || 'undefined' != typeof t.getAttribute && t.getAttribute('class') || '')
                })
              },
              ATTR: function (t, n, i) {
                return function (o) {
                  var r = e.attr(o, t);
                  return null == r ? '!=' === n : n ? (r += '', '=' === n ? r === i : '!=' === n ? r !== i : '^=' === n ? i && 0 === r.indexOf(i)  : '*=' === n ? i && r.indexOf(i) > - 1 : '$=' === n ? i && r.slice( - i.length) === i : '~=' === n ? (' ' + r.replace(se, ' ') + ' ').indexOf(i) > - 1 : '|=' === n ? r === i || r.slice(0, i.length + 1) === i + '-' : !1)  : !0
                }
              },
              CHILD: function (t, e, n, i, o) {
                var r = 'nth' !== t.slice(0, 3),
                a = 'last' !== t.slice( - 4),
                s = 'of-type' === e;
                return 1 === i && 0 === o ? function (t) {
                  return !!t.parentNode
                }
                 : function (e, n, l) {
                  var u,
                  d,
                  c,
                  f,
                  h,
                  p,
                  g = r !== a ? 'nextSibling' : 'previousSibling',
                  m = e.parentNode,
                  b = s && e.nodeName.toLowerCase(),
                  v = !l && !s;
                  if (m) {
                    if (r) {
                      for (; g; ) {
                        for (c = e; c = c[g]; ) if (s ? c.nodeName.toLowerCase() === b : 1 === c.nodeType) return !1;
                        p = g = 'only' === t && !p && 'nextSibling'
                      }
                      return !0
                    }
                    if (p = [
                      a ? m.firstChild : m.lastChild
                    ], a && v) {
                      for (d = m[Q] || (m[Q] = {
                      }), u = d[t] || [
                      ], h = u[0] === H && u[1], f = u[0] === H && u[2], c = h && m.childNodes[h]; c = ++h && c && c[g] || (f = h = 0) || p.pop(); ) if (1 === c.nodeType && ++f && c === e) {
                        d[t] = [
                          H,
                          h,
                          f
                        ];
                        break
                      }
                    } else if (v && (u = (e[Q] || (e[Q] = {
                    })) [t]) && u[0] === H) f = u[1];
                     else for (; (c = ++h && c && c[g] || (f = h = 0) || p.pop()) && ((s ? c.nodeName.toLowerCase() !== b : 1 !== c.nodeType) || !++f || (v && ((c[Q] || (c[Q] = {
                    })) [t] = [
                      H,
                      f
                    ]), c !== e)); );
                    return f -= o,
                    f === i || f % i === 0 && f / i >= 0
                  }
                }
              },
              PSEUDO: function (t, n) {
                var o,
                r = w.pseudos[t] || w.setFilters[t.toLowerCase()] || e.error('unsupported pseudo: ' + t);
                return r[Q] ? r(n)  : r.length > 1 ? (o = [
                  t,
                  t,
                  '',
                  n
                ], w.setFilters.hasOwnProperty(t.toLowerCase()) ? i(function (t, e) {
                  for (var i, o = r(t, n), a = o.length; a--; ) i = te(t, o[a]),
                  t[i] = !(e[i] = o[a])
                })  : function (t) {
                  return r(t, 0, o)
                })  : r
              }
            },
            pseudos: {
              not: i(function (t) {
                var e = [
                ],
                n = [
                ],
                o = T(t.replace(le, '$1'));
                return o[Q] ? i(function (t, e, n, i) {
                  for (var r, a = o(t, null, i, [
                  ]), s = t.length; s--; ) (r = a[s]) && (t[s] = !(e[s] = r))
                })  : function (t, i, r) {
                  return e[0] = t,
                  o(e, null, r, n),
                  e[0] = null,
                  !n.pop()
                }
              }),
              has: i(function (t) {
                return function (n) {
                  return e(t, n).length > 0
                }
              }),
              contains: i(function (t) {
                return t = t.replace(Ce, we),
                function (e) {
                  return (e.textContent || e.innerText || S(e)).indexOf(t) > - 1
                }
              }),
              lang: i(function (t) {
                return he.test(t || '') || e.error('unsupported lang: ' + t),
                t = t.replace(Ce, we).toLowerCase(),
                function (e) {
                  var n;
                  do if (n = I ? e.lang : e.getAttribute('xml:lang') || e.getAttribute('lang')) return n = n.toLowerCase(),
                  n === t || 0 === n.indexOf(t + '-');
                  while ((e = e.parentNode) && 1 === e.nodeType);
                  return !1
                }
              }),
              target: function (e) {
                var n = t.location && t.location.hash;
                return n && n.slice(1) === e.id
              },
              root: function (t) {
                return t === J
              },
              focus: function (t) {
                return t === A.activeElement && (!A.hasFocus || A.hasFocus()) && !!(t.type || t.href || ~t.tabIndex)
              },
              enabled: function (t) {
                return t.disabled === !1
              },
              disabled: function (t) {
                return t.disabled === !0
              },
              checked: function (t) {
                var e = t.nodeName.toLowerCase();
                return 'input' === e && !!t.checked || 'option' === e && !!t.selected
              },
              selected: function (t) {
                return t.parentNode && t.parentNode.selectedIndex,
                t.selected === !0
              },
              empty: function (t) {
                for (t = t.firstChild; t; t = t.nextSibling) if (t.nodeType < 6) return !1;
                return !0
              },
              parent: function (t) {
                return !w.pseudos.empty(t)
              },
              header: function (t) {
                return me.test(t.nodeName)
              },
              input: function (t) {
                return ge.test(t.nodeName)
              },
              button: function (t) {
                var e = t.nodeName.toLowerCase();
                return 'input' === e && 'button' === t.type || 'button' === e
              },
              text: function (t) {
                var e;
                return 'input' === t.nodeName.toLowerCase() && 'text' === t.type && (null == (e = t.getAttribute('type')) || 'text' === e.toLowerCase())
              },
              first: u(function () {
                return [0]
              }),
              last: u(function (t, e) {
                return [e - 1]
              }),
              eq: u(function (t, e, n) {
                return [0 > n ? n + e : n]
              }),
              even: u(function (t, e) {
                for (var n = 0; e > n; n += 2) t.push(n);
                return t
              }),
              odd: u(function (t, e) {
                for (var n = 1; e > n; n += 2) t.push(n);
                return t
              }),
              lt: u(function (t, e, n) {
                for (var i = 0 > n ? n + e : n; --i >= 0; ) t.push(i);
                return t
              }),
              gt: u(function (t, e, n) {
                for (var i = 0 > n ? n + e : n; ++i < e; ) t.push(i);
                return t
              })
            }
          },
          w.pseudos.nth = w.pseudos.eq;
          for (x in {
            radio: !0,
            checkbox: !0,
            file: !0,
            password: !0,
            image: !0
          }) w.pseudos[x] = s(x);
          for (x in {
            submit: !0,
            reset: !0
          }) w.pseudos[x] = l(x);
          return c.prototype = w.filters = w.pseudos,
          w.setFilters = new c,
          q = e.tokenize = function (t, n) {
            var i,
            o,
            r,
            a,
            s,
            l,
            u,
            d = B[t + ' '];
            if (d) return n ? 0 : d.slice(0);
            for (s = t, l = [
            ], u = w.preFilter; s; ) {
              (!i || (o = ue.exec(s))) && (o && (s = s.slice(o[0].length) || s), l.push(r = [
              ])),
              i = !1,
              (o = de.exec(s)) && (i = o.shift(), r.push({
                value: i,
                type: o[0].replace(le, ' ')
              }), s = s.slice(i.length));
              for (a in w.filter) !(o = pe[a].exec(s)) || u[a] && !(o = u[a](o)) || (i = o.shift(), r.push({
                value: i,
                type: a,
                matches: o
              }), s = s.slice(i.length));
              if (!i) break
            }
            return n ? s.length : s ? e.error(t)  : B(t, l).slice(0)
          },
          T = e.compile = function (t, e) {
            var n,
            i = [
            ],
            o = [
            ],
            r = W[t + ' '];
            if (!r) {
              for (e || (e = q(t)), n = e.length; n--; ) r = v(e[n]),
              r[Q] ? i.push(r)  : o.push(r);
              r = W(t, y(o, i)),
              r.selector = t
            }
            return r
          },
          k = e.select = function (t, e, n, i) {
            var o,
            r,
            a,
            s,
            l,
            u = 'function' == typeof t && t,
            c = !i && q(t = u.selector || t);
            if (n = n || [
            ], 1 === c.length) {
              if (r = c[0] = c[0].slice(0), r.length > 2 && 'ID' === (a = r[0]).type && C.getById && 9 === e.nodeType && I && w.relative[r[1].type]) {
                if (e = (w.find.ID(a.matches[0].replace(Ce, we), e) || [
                ]) [0], !e) return n;
                u && (e = e.parentNode),
                t = t.slice(r.shift().value.length)
              }
              for (o = pe.needsContext.test(t) ? 0 : r.length; o-- && (a = r[o], !w.relative[s = a.type]); ) if ((l = w.find[s]) && (i = l(a.matches[0].replace(Ce, we), ye.test(r[0].type) && d(e.parentNode) || e))) {
                if (r.splice(o, 1), t = i.length && f(r), !t) return K.apply(n, i),
                n;
                break
              }
            }
            return (u || T(t, c)) (i, e, !I, n, ye.test(t) && d(e.parentNode) || e),
            n
          },
          C.sortStable = Q.split('').sort(U).join('') === Q,
          C.detectDuplicates = !!D,
          L(),
          C.sortDetached = o(function (t) {
            return 1 & t.compareDocumentPosition(A.createElement('div'))
          }),
          o(function (t) {
            return t.innerHTML = '<a href=\'#\'></a>',
            '#' === t.firstChild.getAttribute('href')
          }) || r('type|href|height|width', function (t, e, n) {
            return n ? void 0 : t.getAttribute(e, 'type' === e.toLowerCase() ? 1 : 2)
          }),
          C.attributes && o(function (t) {
            return t.innerHTML = '<input/>',
            t.firstChild.setAttribute('value', ''),
            '' === t.firstChild.getAttribute('value')
          }) || r('value', function (t, e, n) {
            return n || 'input' !== t.nodeName.toLowerCase() ? void 0 : t.defaultValue
          }),
          o(function (t) {
            return null == t.getAttribute('disabled')
          }) || r(ee, function (t, e, n) {
            var i;
            return n ? void 0 : t[e] === !0 ? e.toLowerCase()  : (i = t.getAttributeNode(e)) && i.specified ? i.value : null
          }),
          e
        }(t);
        oe.find = ue,
        oe.expr = ue.selectors,
        oe.expr[':'] = oe.expr.pseudos,
        oe.unique = ue.uniqueSort,
        oe.text = ue.getText,
        oe.isXMLDoc = ue.isXML,
        oe.contains = ue.contains;
        var de = oe.expr.match.needsContext,
        ce = /^<(\w+)\s*\/?>(?:<\/\1>|)$/,
        fe = /^.[^:#\[\.,]*$/;
        oe.filter = function (t, e, n) {
          var i = e[0];
          return n && (t = ':not(' + t + ')'),
          1 === e.length && 1 === i.nodeType ? oe.find.matchesSelector(i, t) ? [
            i
          ] : [
          ] : oe.find.matches(t, oe.grep(e, function (t) {
            return 1 === t.nodeType
          }))
        },
        oe.fn.extend({
          find: function (t) {
            var e,
            n = [
            ],
            i = this,
            o = i.length;
            if ('string' != typeof t) return this.pushStack(oe(t).filter(function () {
              for (e = 0; o > e; e++) if (oe.contains(i[e], this)) return !0
            }));
            for (e = 0; o > e; e++) oe.find(t, i[e], n);
            return n = this.pushStack(o > 1 ? oe.unique(n)  : n),
            n.selector = this.selector ? this.selector + ' ' + t : t,
            n
          },
          filter: function (t) {
            return this.pushStack(i(this, t || [
            ], !1))
          },
          not: function (t) {
            return this.pushStack(i(this, t || [
            ], !0))
          },
          is: function (t) {
            return !!i(this, 'string' == typeof t && de.test(t) ? oe(t)  : t || [
            ], !1).length
          }
        });
        var he,
        pe = t.document,
        ge = /^(?:\s*(<[\w\W]+>)[^>]*|#([\w-]*))$/,
        me = oe.fn.init = function (t, e) {
          var n,
          i;
          if (!t) return this;
          if ('string' == typeof t) {
            if (n = '<' === t.charAt(0) && '>' === t.charAt(t.length - 1) && t.length >= 3 ? [
              null,
              t,
              null
            ] : ge.exec(t), !n || !n[1] && e) return !e || e.jquery ? (e || he).find(t)  : this.constructor(e).find(t);
            if (n[1]) {
              if (e = e instanceof oe ? e[0] : e, oe.merge(this, oe.parseHTML(n[1], e && e.nodeType ? e.ownerDocument || e : pe, !0)), ce.test(n[1]) && oe.isPlainObject(e)) for (n in e) oe.isFunction(this[n]) ? this[n](e[n])  : this.attr(n, e[n]);
              return this
            }
            if (i = pe.getElementById(n[2]), i && i.parentNode) {
              if (i.id !== n[2]) return he.find(t);
              this.length = 1,
              this[0] = i
            }
            return this.context = pe,
            this.selector = t,
            this
          }
          return t.nodeType ? (this.context = this[0] = t, this.length = 1, this)  : oe.isFunction(t) ? 'undefined' != typeof he.ready ? he.ready(t)  : t(oe)  : (void 0 !== t.selector && (this.selector = t.selector, this.context = t.context), oe.makeArray(t, this))
        };
        me.prototype = oe.fn,
        he = oe(pe);
        var be = /^(?:parents|prev(?:Until|All))/,
        ve = {
          children: !0,
          contents: !0,
          next: !0,
          prev: !0
        };
        oe.extend({
          dir: function (t, e, n) {
            for (var i = [
            ], o = t[e]; o && 9 !== o.nodeType && (void 0 === n || 1 !== o.nodeType || !oe(o).is(n)); ) 1 === o.nodeType && i.push(o),
            o = o[e];
            return i
          },
          sibling: function (t, e) {
            for (var n = [
            ]; t; t = t.nextSibling) 1 === t.nodeType && t !== e && n.push(t);
            return n
          }
        }),
        oe.fn.extend({
          has: function (t) {
            var e,
            n = oe(t, this),
            i = n.length;
            return this.filter(function () {
              for (e = 0; i > e; e++) if (oe.contains(this, n[e])) return !0
            })
          },
          closest: function (t, e) {
            for (var n, i = 0, o = this.length, r = [
            ], a = de.test(t) || 'string' != typeof t ? oe(t, e || this.context)  : 0; o > i; i++) for (n = this[i]; n && n !== e; n = n.parentNode) if (n.nodeType < 11 && (a ? a.index(n) > - 1 : 1 === n.nodeType && oe.find.matchesSelector(n, t))) {
              r.push(n);
              break
            }
            return this.pushStack(r.length > 1 ? oe.unique(r)  : r)
          },
          index: function (t) {
            return t ? 'string' == typeof t ? oe.inArray(this[0], oe(t))  : oe.inArray(t.jquery ? t[0] : t, this)  : this[0] && this[0].parentNode ? this.first().prevAll().length : - 1
          },
          add: function (t, e) {
            return this.pushStack(oe.unique(oe.merge(this.get(), oe(t, e))))
          },
          addBack: function (t) {
            return this.add(null == t ? this.prevObject : this.prevObject.filter(t))
          }
        }),
        oe.each({
          parent: function (t) {
            var e = t.parentNode;
            return e && 11 !== e.nodeType ? e : null
          },
          parents: function (t) {
            return oe.dir(t, 'parentNode')
          },
          parentsUntil: function (t, e, n) {
            return oe.dir(t, 'parentNode', n)
          },
          next: function (t) {
            return o(t, 'nextSibling')
          },
          prev: function (t) {
            return o(t, 'previousSibling')
          },
          nextAll: function (t) {
            return oe.dir(t, 'nextSibling')
          },
          prevAll: function (t) {
            return oe.dir(t, 'previousSibling')
          },
          nextUntil: function (t, e, n) {
            return oe.dir(t, 'nextSibling', n)
          },
          prevUntil: function (t, e, n) {
            return oe.dir(t, 'previousSibling', n)
          },
          siblings: function (t) {
            return oe.sibling((t.parentNode || {
            }).firstChild, t)
          },
          children: function (t) {
            return oe.sibling(t.firstChild)
          },
          contents: function (t) {
            return oe.nodeName(t, 'iframe') ? t.contentDocument || t.contentWindow.document : oe.merge([], t.childNodes)
          }
        }, function (t, e) {
          oe.fn[t] = function (n, i) {
            var o = oe.map(this, e, n);
            return 'Until' !== t.slice( - 5) && (i = n),
            i && 'string' == typeof i && (o = oe.filter(i, o)),
            this.length > 1 && (ve[t] || (o = oe.unique(o)), be.test(t) && (o = o.reverse())),
            this.pushStack(o)
          }
        });
        var ye = /\S+/g,
        xe = {
        };
        oe.Callbacks = function (t) {
          t = 'string' == typeof t ? xe[t] || r(t)  : oe.extend({
          }, t);
          var e,
          n,
          i,
          o,
          a,
          s,
          l = [
          ],
          u = !t.once && [
          ],
          d = function (r) {
            for (n = t.memory && r, i = !0, a = s || 0, s = 0, o = l.length, e = !0; l && o > a; a++) if (l[a].apply(r[0], r[1]) === !1 && t.stopOnFalse) {
              n = !1;
              break
            }
            e = !1,
            l && (u ? u.length && d(u.shift())  : n ? l = [
            ] : c.disable())
          },
          c = {
            add: function () {
              if (l) {
                var i = l.length;
                !function r(e) {
                  oe.each(e, function (e, n) {
                    var i = oe.type(n);
                    'function' === i ? t.unique && c.has(n) || l.push(n)  : n && n.length && 'string' !== i && r(n)
                  })
                }(arguments),
                e ? o = l.length : n && (s = i, d(n))
              }
              return this
            },
            remove: function () {
              return l && oe.each(arguments, function (t, n) {
                for (var i; (i = oe.inArray(n, l, i)) > - 1; ) l.splice(i, 1),
                e && (o >= i && o--, a >= i && a--)
              }),
              this
            },
            has: function (t) {
              return t ? oe.inArray(t, l) > - 1 : !(!l || !l.length)
            },
            empty: function () {
              return l = [
              ],
              o = 0,
              this
            },
            disable: function () {
              return l = u = n = void 0,
              this
            },
            disabled: function () {
              return !l
            },
            lock: function () {
              return u = void 0,
              n || c.disable(),
              this
            },
            locked: function () {
              return !u
            },
            fireWith: function (t, n) {
              return !l || i && !u || (n = n || [
              ], n = [
                t,
                n.slice ? n.slice()  : n
              ], e ? u.push(n)  : d(n)),
              this
            },
            fire: function () {
              return c.fireWith(this, arguments),
              this
            },
            fired: function () {
              return !!i
            }
          };
          return c
        },
        oe.extend({
          Deferred: function (t) {
            var e = [
              ['resolve',
              'done',
              oe.Callbacks('once memory'),
              'resolved'],
              [
                'reject',
                'fail',
                oe.Callbacks('once memory'),
                'rejected'
              ],
              [
                'notify',
                'progress',
                oe.Callbacks('memory')
              ]
            ],
            n = 'pending',
            i = {
              state: function () {
                return n
              },
              always: function () {
                return o.done(arguments).fail(arguments),
                this
              },
              then: function () {
                var t = arguments;
                return oe.Deferred(function (n) {
                  oe.each(e, function (e, r) {
                    var a = oe.isFunction(t[e]) && t[e];
                    o[r[1]](function () {
                      var t = a && a.apply(this, arguments);
                      t && oe.isFunction(t.promise) ? t.promise().done(n.resolve).fail(n.reject).progress(n.notify)  : n[r[0] + 'With'](this === i ? n.promise()  : this, a ? [
                        t
                      ] : arguments)
                    })
                  }),
                  t = null
                }).promise()
              },
              promise: function (t) {
                return null != t ? oe.extend(t, i)  : i
              }
            },
            o = {
            };
            return i.pipe = i.then,
            oe.each(e, function (t, r) {
              var a = r[2],
              s = r[3];
              i[r[1]] = a.add,
              s && a.add(function () {
                n = s
              }, e[1 ^ t][2].disable, e[2][2].lock),
              o[r[0]] = function () {
                return o[r[0] + 'With'](this === o ? i : this, arguments),
                this
              },
              o[r[0] + 'With'] = a.fireWith
            }),
            i.promise(o),
            t && t.call(o, o),
            o
          },
          when: function (t) {
            var e,
            n,
            i,
            o = 0,
            r = G.call(arguments),
            a = r.length,
            s = 1 !== a || t && oe.isFunction(t.promise) ? a : 0,
            l = 1 === s ? t : oe.Deferred(),
            u = function (t, n, i) {
              return function (o) {
                n[t] = this,
                i[t] = arguments.length > 1 ? G.call(arguments)  : o,
                i === e ? l.notifyWith(n, i)  : --s || l.resolveWith(n, i)
              }
            };
            if (a > 1) for (e = new Array(a), n = new Array(a), i = new Array(a); a > o; o++) r[o] && oe.isFunction(r[o].promise) ? r[o].promise().done(u(o, i, r)).fail(l.reject).progress(u(o, n, e))  : --s;
            return s || l.resolveWith(i, r),
            l.promise()
          }
        });
        var Ce;
        oe.fn.ready = function (t) {
          return oe.ready.promise().done(t),
          this
        },
        oe.extend({
          isReady: !1,
          readyWait: 1,
          holdReady: function (t) {
            t ? oe.readyWait++ : oe.ready(!0)
          },
          ready: function (t) {
            if (t === !0 ? !--oe.readyWait : !oe.isReady) {
              if (!pe.body) return setTimeout(oe.ready);
              oe.isReady = !0,
              t !== !0 && --oe.readyWait > 0 || (Ce.resolveWith(pe, [
                oe
              ]), oe.fn.triggerHandler && (oe(pe).triggerHandler('ready'), oe(pe).off('ready')))
            }
          }
        }),
        oe.ready.promise = function (e) {
          if (!Ce) if (Ce = oe.Deferred(), 'complete' === pe.readyState) setTimeout(oe.ready);
           else if (pe.addEventListener) pe.addEventListener('DOMContentLoaded', s, !1),
          t.addEventListener('load', s, !1);
           else {
            pe.attachEvent('onreadystatechange', s),
            t.attachEvent('onload', s);
            var n = !1;
            try {
              n = null == t.frameElement && pe.documentElement
            } catch (i) {
            }
            n && n.doScroll && !function o() {
              if (!oe.isReady) {
                try {
                  n.doScroll('left')
                } catch (t) {
                  return setTimeout(o, 50)
                }
                a(),
                oe.ready()
              }
            }()
          }
          return Ce.promise(e)
        };
        var we,
        Se = 'undefined';
        for (we in oe(ne)) break;
        ne.ownLast = '0' !== we,
        ne.inlineBlockNeedsLayout = !1,
        oe(function () {
          var t,
          e,
          n,
          i;
          n = pe.getElementsByTagName('body') [0],
          n && n.style && (e = pe.createElement('div'), i = pe.createElement('div'), i.style.cssText = 'position:absolute;border:0;width:0;height:0;top:0;left:-9999px', n.appendChild(i).appendChild(e), typeof e.style.zoom !== Se && (e.style.cssText = 'display:inline;margin:0;border:0;padding:1px;width:1px;zoom:1', ne.inlineBlockNeedsLayout = t = 3 === e.offsetWidth, t && (n.style.zoom = 1)), n.removeChild(i))
        }),
        function () {
          var t = pe.createElement('div');
          if (null == ne.deleteExpando) {
            ne.deleteExpando = !0;
            try {
              delete t.test
            } catch (e) {
              ne.deleteExpando = !1
            }
          }
          t = null
        }(),
        oe.acceptData = function (t) {
          var e = oe.noData[(t.nodeName + ' ').toLowerCase()],
          n = + t.nodeType || 1;
          return 1 !== n && 9 !== n ? !1 : !e || e !== !0 && t.getAttribute('classid') === e
        };
        var _e = /^(?:\{[\w\W]*\}|\[[\w\W]*\])$/,
        qe = /([A-Z])/g;
        oe.extend({
          cache: {
          },
          noData: {
            'applet ': !0,
            'embed ': !0,
            'object ': 'clsid:D27CDB6E-AE6D-11cf-96B8-444553540000'
          },
          hasData: function (t) {
            return t = t.nodeType ? oe.cache[t[oe.expando]] : t[oe.expando],
            !!t && !u(t)
          },
          data: function (t, e, n) {
            return d(t, e, n)
          },
          removeData: function (t, e) {
            return c(t, e)
          },
          _data: function (t, e, n) {
            return d(t, e, n, !0)
          },
          _removeData: function (t, e) {
            return c(t, e, !0)
          }
        }),
        oe.fn.extend({
          data: function (t, e) {
            var n,
            i,
            o,
            r = this[0],
            a = r && r.attributes;
            if (void 0 === t) {
              if (this.length && (o = oe.data(r), 1 === r.nodeType && !oe._data(r, 'parsedAttrs'))) {
                for (n = a.length; n--; ) a[n] && (i = a[n].name, 0 === i.indexOf('data-') && (i = oe.camelCase(i.slice(5)), l(r, i, o[i])));
                oe._data(r, 'parsedAttrs', !0)
              }
              return o
            }
            return 'object' == typeof t ? this.each(function () {
              oe.data(this, t)
            })  : arguments.length > 1 ? this.each(function () {
              oe.data(this, t, e)
            })  : r ? l(r, t, oe.data(r, t))  : void 0
          },
          removeData: function (t) {
            return this.each(function () {
              oe.removeData(this, t)
            })
          }
        }),
        oe.extend({
          queue: function (t, e, n) {
            var i;
            return t ? (e = (e || 'fx') + 'queue', i = oe._data(t, e), n && (!i || oe.isArray(n) ? i = oe._data(t, e, oe.makeArray(n))  : i.push(n)), i || [
            ])  : void 0
          },
          dequeue: function (t, e) {
            e = e || 'fx';
            var n = oe.queue(t, e),
            i = n.length,
            o = n.shift(),
            r = oe._queueHooks(t, e),
            a = function () {
              oe.dequeue(t, e)
            };
            'inprogress' === o && (o = n.shift(), i--),
            o && ('fx' === e && n.unshift('inprogress'), delete r.stop, o.call(t, a, r)),
            !i && r && r.empty.fire()
          },
          _queueHooks: function (t, e) {
            var n = e + 'queueHooks';
            return oe._data(t, n) || oe._data(t, n, {
              empty: oe.Callbacks('once memory').add(function () {
                oe._removeData(t, e + 'queue'),
                oe._removeData(t, n)
              })
            })
          }
        }),
        oe.fn.extend({
          queue: function (t, e) {
            var n = 2;
            return 'string' != typeof t && (e = t, t = 'fx', n--),
            arguments.length < n ? oe.queue(this[0], t)  : void 0 === e ? this : this.each(function () {
              var n = oe.queue(this, t, e);
              oe._queueHooks(this, t),
              'fx' === t && 'inprogress' !== n[0] && oe.dequeue(this, t)
            })
          },
          dequeue: function (t) {
            return this.each(function () {
              oe.dequeue(this, t)
            })
          },
          clearQueue: function (t) {
            return this.queue(t || 'fx', [
            ])
          },
          promise: function (t, e) {
            var n,
            i = 1,
            o = oe.Deferred(),
            r = this,
            a = this.length,
            s = function () {
              --i || o.resolveWith(r, [
                r
              ])
            };
            for ('string' != typeof t && (e = t, t = void 0), t = t || 'fx'; a--; ) n = oe._data(r[a], t + 'queueHooks'),
            n && n.empty && (i++, n.empty.add(s));
            return s(),
            o.promise(e)
          }
        });
        var Te = /[+-]?(?:\d*\.|)\d+(?:[eE][+-]?\d+|)/.source,
        ke = [
          'Top',
          'Right',
          'Bottom',
          'Left'
        ],
        Ee = function (t, e) {
          return t = e || t,
          'none' === oe.css(t, 'display') || !oe.contains(t.ownerDocument, t)
        },
        Ne = oe.access = function (t, e, n, i, o, r, a) {
          var s = 0,
          l = t.length,
          u = null == n;
          if ('object' === oe.type(n)) {
            o = !0;
            for (s in n) oe.access(t, e, s, n[s], !0, r, a)
          } else if (void 0 !== i && (o = !0, oe.isFunction(i) || (a = !0), u && (a ? (e.call(t, i), e = null)  : (u = e, e = function (t, e, n) {
            return u.call(oe(t), n)
          })), e)) for (; l > s; s++) e(t[s], n, a ? i : i.call(t[s], s, e(t[s], n)));
          return o ? t : u ? e.call(t)  : l ? e(t[0], n)  : r
        },
        De = /^(?:checkbox|radio)$/i;
        !function () {
          var t = pe.createElement('input'),
          e = pe.createElement('div'),
          n = pe.createDocumentFragment();
          if (e.innerHTML = '  <link/><table></table><a href=\'/a\'>a</a><input type=\'checkbox\'/>', ne.leadingWhitespace = 3 === e.firstChild.nodeType, ne.tbody = !e.getElementsByTagName('tbody').length, ne.htmlSerialize = !!e.getElementsByTagName('link').length, ne.html5Clone = '<:nav></:nav>' !== pe.createElement('nav').cloneNode(!0).outerHTML, t.type = 'checkbox', t.checked = !0, n.appendChild(t), ne.appendChecked = t.checked, e.innerHTML = '<textarea>x</textarea>', ne.noCloneChecked = !!e.cloneNode(!0).lastChild.defaultValue, n.appendChild(e), e.innerHTML = '<input type=\'radio\' checked=\'checked\' name=\'t\'/>', ne.checkClone = e.cloneNode(!0).cloneNode(!0).lastChild.checked, ne.noCloneEvent = !0, e.attachEvent && (e.attachEvent('onclick', function () {
            ne.noCloneEvent = !1
          }), e.cloneNode(!0).click()), null == ne.deleteExpando) {
            ne.deleteExpando = !0;
            try {
              delete e.test
            } catch (i) {
              ne.deleteExpando = !1
            }
          }
        }(),
        function () {
          var e,
          n,
          i = pe.createElement('div');
          for (e in {
            submit: !0,
            change: !0,
            focusin: !0
          }) n = 'on' + e,
          (ne[e + 'Bubbles'] = n in t) || (i.setAttribute(n, 't'), ne[e + 'Bubbles'] = i.attributes[n].expando === !1);
          i = null
        }();
        var Le = /^(?:input|select|textarea)$/i,
        Ae = /^key/,
        Je = /^(?:mouse|pointer|contextmenu)|click/,
        Ie = /^(?:focusinfocus|focusoutblur)$/,
        Me = /^([^.]*)(?:\.(.+)|)$/;
        oe.event = {
          global: {
          },
          add: function (t, e, n, i, o) {
            var r,
            a,
            s,
            l,
            u,
            d,
            c,
            f,
            h,
            p,
            g,
            m = oe._data(t);
            if (m) {
              for (n.handler && (l = n, n = l.handler, o = l.selector), n.guid || (n.guid = oe.guid++), (a = m.events) || (a = m.events = {
              }), (d = m.handle) || (d = m.handle = function (t) {
                return typeof oe === Se || t && oe.event.triggered === t.type ? void 0 : oe.event.dispatch.apply(d.elem, arguments)
              }, d.elem = t), e = (e || '').match(ye) || [
                ''
              ], s = e.length; s--; ) r = Me.exec(e[s]) || [
              ],
              h = g = r[1],
              p = (r[2] || '').split('.').sort(),
              h && (u = oe.event.special[h] || {
              }, h = (o ? u.delegateType : u.bindType) || h, u = oe.event.special[h] || {
              }, c = oe.extend({
                type: h,
                origType: g,
                data: i,
                handler: n,
                guid: n.guid,
                selector: o,
                needsContext: o && oe.expr.match.needsContext.test(o),
                namespace: p.join('.')
              }, l), (f = a[h]) || (f = a[h] = [
              ], f.delegateCount = 0, u.setup && u.setup.call(t, i, p, d) !== !1 || (t.addEventListener ? t.addEventListener(h, d, !1)  : t.attachEvent && t.attachEvent('on' + h, d))), u.add && (u.add.call(t, c), c.handler.guid || (c.handler.guid = n.guid)), o ? f.splice(f.delegateCount++, 0, c)  : f.push(c), oe.event.global[h] = !0);
              t = null
            }
          },
          remove: function (t, e, n, i, o) {
            var r,
            a,
            s,
            l,
            u,
            d,
            c,
            f,
            h,
            p,
            g,
            m = oe.hasData(t) && oe._data(t);
            if (m && (d = m.events)) {
              for (e = (e || '').match(ye) || [
                ''
              ], u = e.length; u--; ) if (s = Me.exec(e[u]) || [
              ], h = g = s[1], p = (s[2] || '').split('.').sort(), h) {
                for (c = oe.event.special[h] || {
                }, h = (i ? c.delegateType : c.bindType) || h, f = d[h] || [
                ], s = s[2] && new RegExp('(^|\\.)' + p.join('\\.(?:.*\\.|)') + '(\\.|$)'), l = r = f.length; r--; ) a = f[r],
                !o && g !== a.origType || n && n.guid !== a.guid || s && !s.test(a.namespace) || i && i !== a.selector && ('**' !== i || !a.selector) || (f.splice(r, 1), a.selector && f.delegateCount--, c.remove && c.remove.call(t, a));
                l && !f.length && (c.teardown && c.teardown.call(t, p, m.handle) !== !1 || oe.removeEvent(t, h, m.handle), delete d[h])
              } else for (h in d) oe.event.remove(t, h + e[u], n, i, !0);
              oe.isEmptyObject(d) && (delete m.handle, oe._removeData(t, 'events'))
            }
          },
          trigger: function (e, n, i, o) {
            var r,
            a,
            s,
            l,
            u,
            d,
            c,
            f = [
              i || pe
            ],
            h = ee.call(e, 'type') ? e.type : e,
            p = ee.call(e, 'namespace') ? e.namespace.split('.')  : [
            ];
            if (s = d = i = i || pe, 3 !== i.nodeType && 8 !== i.nodeType && !Ie.test(h + oe.event.triggered) && (h.indexOf('.') >= 0 && (p = h.split('.'), h = p.shift(), p.sort()), a = h.indexOf(':') < 0 && 'on' + h, e = e[oe.expando] ? e : new oe.Event(h, 'object' == typeof e && e), e.isTrigger = o ? 2 : 3, e.namespace = p.join('.'), e.namespace_re = e.namespace ? new RegExp('(^|\\.)' + p.join('\\.(?:.*\\.|)') + '(\\.|$)')  : null, e.result = void 0, e.target || (e.target = i), n = null == n ? [
              e
            ] : oe.makeArray(n, [
              e
            ]), u = oe.event.special[h] || {
            }, o || !u.trigger || u.trigger.apply(i, n) !== !1)) {
              if (!o && !u.noBubble && !oe.isWindow(i)) {
                for (l = u.delegateType || h, Ie.test(l + h) || (s = s.parentNode); s; s = s.parentNode) f.push(s),
                d = s;
                d === (i.ownerDocument || pe) && f.push(d.defaultView || d.parentWindow || t)
              }
              for (c = 0; (s = f[c++]) && !e.isPropagationStopped(); ) e.type = c > 1 ? l : u.bindType || h,
              r = (oe._data(s, 'events') || {
              }) [e.type] && oe._data(s, 'handle'),
              r && r.apply(s, n),
              r = a && s[a],
              r && r.apply && oe.acceptData(s) && (e.result = r.apply(s, n), e.result === !1 && e.preventDefault());
              if (e.type = h, !o && !e.isDefaultPrevented() && (!u._default || u._default.apply(f.pop(), n) === !1) && oe.acceptData(i) && a && i[h] && !oe.isWindow(i)) {
                d = i[a],
                d && (i[a] = null),
                oe.event.triggered = h;
                try {
                  i[h]()
                } catch (g) {
                }
                oe.event.triggered = void 0,
                d && (i[a] = d)
              }
              return e.result
            }
          },
          dispatch: function (t) {
            t = oe.event.fix(t);
            var e,
            n,
            i,
            o,
            r,
            a = [
            ],
            s = G.call(arguments),
            l = (oe._data(this, 'events') || {
            }) [t.type] || [
            ],
            u = oe.event.special[t.type] || {
            };
            if (s[0] = t, t.delegateTarget = this, !u.preDispatch || u.preDispatch.call(this, t) !== !1) {
              for (a = oe.event.handlers.call(this, t, l), e = 0; (o = a[e++]) && !t.isPropagationStopped(); ) for (t.currentTarget = o.elem, r = 0; (i = o.handlers[r++]) && !t.isImmediatePropagationStopped(); ) (!t.namespace_re || t.namespace_re.test(i.namespace)) && (t.handleObj = i, t.data = i.data, n = ((oe.event.special[i.origType] || {
              }).handle || i.handler).apply(o.elem, s), void 0 !== n && (t.result = n) === !1 && (t.preventDefault(), t.stopPropagation()));
              return u.postDispatch && u.postDispatch.call(this, t),
              t.result
            }
          },
          handlers: function (t, e) {
            var n,
            i,
            o,
            r,
            a = [
            ],
            s = e.delegateCount,
            l = t.target;
            if (s && l.nodeType && (!t.button || 'click' !== t.type)) for (; l != this; l = l.parentNode || this) if (1 === l.nodeType && (l.disabled !== !0 || 'click' !== t.type)) {
              for (o = [
              ], r = 0; s > r; r++) i = e[r],
              n = i.selector + ' ',
              void 0 === o[n] && (o[n] = i.needsContext ? oe(n, this).index(l) >= 0 : oe.find(n, this, null, [
                l
              ]).length),
              o[n] && o.push(i);
              o.length && a.push({
                elem: l,
                handlers: o
              })
            }
            return s < e.length && a.push({
              elem: this,
              handlers: e.slice(s)
            }),
            a
          },
          fix: function (t) {
            if (t[oe.expando]) return t;
            var e,
            n,
            i,
            o = t.type,
            r = t,
            a = this.fixHooks[o];
            for (a || (this.fixHooks[o] = a = Je.test(o) ? this.mouseHooks : Ae.test(o) ? this.keyHooks : {
            }), i = a.props ? this.props.concat(a.props)  : this.props, t = new oe.Event(r), e = i.length; e--; ) n = i[e],
            t[n] = r[n];
            return t.target || (t.target = r.srcElement || pe),
            3 === t.target.nodeType && (t.target = t.target.parentNode),
            t.metaKey = !!t.metaKey,
            a.filter ? a.filter(t, r)  : t
          },
          props: 'altKey bubbles cancelable ctrlKey currentTarget eventPhase metaKey relatedTarget shiftKey target timeStamp view which'.split(' '),
          fixHooks: {
          },
          keyHooks: {
            props: 'char charCode key keyCode'.split(' '),
            filter: function (t, e) {
              return null == t.which && (t.which = null != e.charCode ? e.charCode : e.keyCode),
              t
            }
          },
          mouseHooks: {
            props: 'button buttons clientX clientY fromElement offsetX offsetY pageX pageY screenX screenY toElement'.split(' '),
            filter: function (t, e) {
              var n,
              i,
              o,
              r = e.button,
              a = e.fromElement;
              return null == t.pageX && null != e.clientX && (i = t.target.ownerDocument || pe, o = i.documentElement, n = i.body, t.pageX = e.clientX + (o && o.scrollLeft || n && n.scrollLeft || 0) - (o && o.clientLeft || n && n.clientLeft || 0), t.pageY = e.clientY + (o && o.scrollTop || n && n.scrollTop || 0) - (o && o.clientTop || n && n.clientTop || 0)),
              !t.relatedTarget && a && (t.relatedTarget = a === t.target ? e.toElement : a),
              t.which || void 0 === r || (t.which = 1 & r ? 1 : 2 & r ? 3 : 4 & r ? 2 : 0),
              t
            }
          },
          special: {
            load: {
              noBubble: !0
            },
            focus: {
              trigger: function () {
                if (this !== p() && this.focus) try {
                  return this.focus(),
                  !1
                } catch (t) {
                }
              },
              delegateType: 'focusin'
            },
            blur: {
              trigger: function () {
                return this === p() && this.blur ? (this.blur(), !1)  : void 0
              },
              delegateType: 'focusout'
            },
            click: {
              trigger: function () {
                return oe.nodeName(this, 'input') && 'checkbox' === this.type && this.click ? (this.click(), !1)  : void 0
              },
              _default: function (t) {
                return oe.nodeName(t.target, 'a')
              }
            },
            beforeunload: {
              postDispatch: function (t) {
                void 0 !== t.result && t.originalEvent && (t.originalEvent.returnValue = t.result)
              }
            }
          },
          simulate: function (t, e, n, i) {
            var o = oe.extend(new oe.Event, n, {
              type: t,
              isSimulated: !0,
              originalEvent: {
              }
            });
            i ? oe.event.trigger(o, null, e)  : oe.event.dispatch.call(e, o),
            o.isDefaultPrevented() && n.preventDefault()
          }
        },
        oe.removeEvent = pe.removeEventListener ? function (t, e, n) {
          t.removeEventListener && t.removeEventListener(e, n, !1)
        }
         : function (t, e, n) {
          var i = 'on' + e;
          t.detachEvent && (typeof t[i] === Se && (t[i] = null), t.detachEvent(i, n))
        },
        oe.Event = function (t, e) {
          return this instanceof oe.Event ? (t && t.type ? (this.originalEvent = t, this.type = t.type, this.isDefaultPrevented = t.defaultPrevented || void 0 === t.defaultPrevented && t.returnValue === !1 ? f : h)  : this.type = t, e && oe.extend(this, e), this.timeStamp = t && t.timeStamp || oe.now(), void (this[oe.expando] = !0))  : new oe.Event(t, e)
        },
        oe.Event.prototype = {
          isDefaultPrevented: h,
          isPropagationStopped: h,
          isImmediatePropagationStopped: h,
          preventDefault: function () {
            var t = this.originalEvent;
            this.isDefaultPrevented = f,
            t && (t.preventDefault ? t.preventDefault()  : t.returnValue = !1)
          },
          stopPropagation: function () {
            var t = this.originalEvent;
            this.isPropagationStopped = f,
            t && (t.stopPropagation && t.stopPropagation(), t.cancelBubble = !0)
          },
          stopImmediatePropagation: function () {
            var t = this.originalEvent;
            this.isImmediatePropagationStopped = f,
            t && t.stopImmediatePropagation && t.stopImmediatePropagation(),
            this.stopPropagation()
          }
        },
        oe.each({
          mouseenter: 'mouseover',
          mouseleave: 'mouseout',
          pointerenter: 'pointerover',
          pointerleave: 'pointerout'
        }, function (t, e) {
          oe.event.special[t] = {
            delegateType: e,
            bindType: e,
            handle: function (t) {
              var n,
              i = this,
              o = t.relatedTarget,
              r = t.handleObj;
              return (!o || o !== i && !oe.contains(i, o)) && (t.type = r.origType, n = r.handler.apply(this, arguments), t.type = e),
              n
            }
          }
        }),
        ne.submitBubbles || (oe.event.special.submit = {
          setup: function () {
            return oe.nodeName(this, 'form') ? !1 : void oe.event.add(this, 'click._submit keypress._submit', function (t) {
              var e = t.target,
              n = oe.nodeName(e, 'input') || oe.nodeName(e, 'button') ? e.form : void 0;
              n && !oe._data(n, 'submitBubbles') && (oe.event.add(n, 'submit._submit', function (t) {
                t._submit_bubble = !0
              }), oe._data(n, 'submitBubbles', !0))
            })
          },
          postDispatch: function (t) {
            t._submit_bubble && (delete t._submit_bubble, this.parentNode && !t.isTrigger && oe.event.simulate('submit', this.parentNode, t, !0))
          },
          teardown: function () {
            return oe.nodeName(this, 'form') ? !1 : void oe.event.remove(this, '._submit')
          }
        }),
        ne.changeBubbles || (oe.event.special.change = {
          setup: function () {
            return Le.test(this.nodeName) ? (('checkbox' === this.type || 'radio' === this.type) && (oe.event.add(this, 'propertychange._change', function (t) {
              'checked' === t.originalEvent.propertyName && (this._just_changed = !0)
            }), oe.event.add(this, 'click._change', function (t) {
              this._just_changed && !t.isTrigger && (this._just_changed = !1),
              oe.event.simulate('change', this, t, !0)
            })), !1)  : void oe.event.add(this, 'beforeactivate._change', function (t) {
              var e = t.target;
              Le.test(e.nodeName) && !oe._data(e, 'changeBubbles') && (oe.event.add(e, 'change._change', function (t) {
                !this.parentNode || t.isSimulated || t.isTrigger || oe.event.simulate('change', this.parentNode, t, !0)
              }), oe._data(e, 'changeBubbles', !0))
            })
          },
          handle: function (t) {
            var e = t.target;
            return this !== e || t.isSimulated || t.isTrigger || 'radio' !== e.type && 'checkbox' !== e.type ? t.handleObj.handler.apply(this, arguments)  : void 0
          },
          teardown: function () {
            return oe.event.remove(this, '._change'),
            !Le.test(this.nodeName)
          }
        }),
        ne.focusinBubbles || oe.each({
          focus: 'focusin',
          blur: 'focusout'
        }, function (t, e) {
          var n = function (t) {
            oe.event.simulate(e, t.target, oe.event.fix(t), !0)
          };
          oe.event.special[e] = {
            setup: function () {
              var i = this.ownerDocument || this,
              o = oe._data(i, e);
              o || i.addEventListener(t, n, !0),
              oe._data(i, e, (o || 0) + 1)
            },
            teardown: function () {
              var i = this.ownerDocument || this,
              o = oe._data(i, e) - 1;
              o ? oe._data(i, e, o)  : (i.removeEventListener(t, n, !0), oe._removeData(i, e))
            }
          }
        }),
        oe.fn.extend({
          on: function (t, e, n, i, o) {
            var r,
            a;
            if ('object' == typeof t) {
              'string' != typeof e && (n = n || e, e = void 0);
              for (r in t) this.on(r, e, n, t[r], o);
              return this
            }
            if (null == n && null == i ? (i = e, n = e = void 0)  : null == i && ('string' == typeof e ? (i = n, n = void 0)  : (i = n, n = e, e = void 0)), i === !1) i = h;
             else if (!i) return this;
            return 1 === o && (a = i, i = function (t) {
              return oe().off(t),
              a.apply(this, arguments)
            }, i.guid = a.guid || (a.guid = oe.guid++)),
            this.each(function () {
              oe.event.add(this, t, i, n, e)
            })
          },
          one: function (t, e, n, i) {
            return this.on(t, e, n, i, 1)
          },
          off: function (t, e, n) {
            var i,
            o;
            if (t && t.preventDefault && t.handleObj) return i = t.handleObj,
            oe(t.delegateTarget).off(i.namespace ? i.origType + '.' + i.namespace : i.origType, i.selector, i.handler),
            this;
            if ('object' == typeof t) {
              for (o in t) this.off(o, e, t[o]);
              return this
            }
            return (e === !1 || 'function' == typeof e) && (n = e, e = void 0),
            n === !1 && (n = h),
            this.each(function () {
              oe.event.remove(this, t, n, e)
            })
          },
          trigger: function (t, e) {
            return this.each(function () {
              oe.event.trigger(t, e, this)
            })
          },
          triggerHandler: function (t, e) {
            var n = this[0];
            return n ? oe.event.trigger(t, e, n, !0)  : void 0
          }
        });
        var Pe = 'abbr|article|aside|audio|bdi|canvas|data|datalist|details|figcaption|figure|footer|header|hgroup|mark|meter|nav|output|progress|section|summary|time|video',
        Oe = / jQuery\d+="(?:null|\d+)"/g,
        Re = new RegExp('<(?:' + Pe + ')[\\s/>]', 'i'),
        Qe = /^\s+/,
        je = /<(?!area|br|col|embed|hr|img|input|link|meta|param)(([\w:]+)[^>]*)\/>/gi,
        He = /<([\w:]+)/,
        Fe = /<tbody/i,
        ze = /<|&#?\w+;/,
        Be = /<(?:script|style|link)/i,
        We = /checked\s*(?:[^=]|=\s*.checked.)/i,
        Ue = /^$|\/(?:java|ecma)script/i,
        $e = /^true\/(.*)/,
        Xe = /^\s*<!(?:\[CDATA\[|--)|(?:\]\]|--)>\s*$/g,
        Ge = {
          option: [
            1,
            '<select multiple=\'multiple\'>',
            '</select>'
          ],
          legend: [
            1,
            '<fieldset>',
            '</fieldset>'
          ],
          area: [
            1,
            '<map>',
            '</map>'
          ],
          param: [
            1,
            '<object>',
            '</object>'
          ],
          thead: [
            1,
            '<table>',
            '</table>'
          ],
          tr: [
            2,
            '<table><tbody>',
            '</tbody></table>'
          ],
          col: [
            2,
            '<table><tbody></tbody><colgroup>',
            '</colgroup></table>'
          ],
          td: [
            3,
            '<table><tbody><tr>',
            '</tr></tbody></table>'
          ],
          _default: ne.htmlSerialize ? [
            0,
            '',
            ''
          ] : [
            1,
            'X<div>',
            '</div>'
          ]
        },
        Ve = g(pe),
        Ye = Ve.appendChild(pe.createElement('div'));
        Ge.optgroup = Ge.option,
        Ge.tbody = Ge.tfoot = Ge.colgroup = Ge.caption = Ge.thead,
        Ge.th = Ge.td,
        oe.extend({
          clone: function (t, e, n) {
            var i,
            o,
            r,
            a,
            s,
            l = oe.contains(t.ownerDocument, t);
            if (ne.html5Clone || oe.isXMLDoc(t) || !Re.test('<' + t.nodeName + '>') ? r = t.cloneNode(!0)  : (Ye.innerHTML = t.outerHTML, Ye.removeChild(r = Ye.firstChild)), !(ne.noCloneEvent && ne.noCloneChecked || 1 !== t.nodeType && 11 !== t.nodeType || oe.isXMLDoc(t))) for (i = m(r), s = m(t), a = 0; null != (o = s[a]); ++a) i[a] && S(o, i[a]);
            if (e) if (n) for (s = s || m(t), i = i || m(r), a = 0; null != (o = s[a]); a++) w(o, i[a]);
             else w(t, r);
            return i = m(r, 'script'),
            i.length > 0 && C(i, !l && m(t, 'script')),
            i = s = o = null,
            r
          },
          buildFragment: function (t, e, n, i) {
            for (var o, r, a, s, l, u, d, c = t.length, f = g(e), h = [
            ], p = 0; c > p; p++) if (r = t[p], r || 0 === r) if ('object' === oe.type(r)) oe.merge(h, r.nodeType ? [
              r
            ] : r);
             else if (ze.test(r)) {
              for (s = s || f.appendChild(e.createElement('div')), l = (He.exec(r) || [
                '',
                ''
              ]) [1].toLowerCase(), d = Ge[l] || Ge._default, s.innerHTML = d[1] + r.replace(je, '<$1></$2>') + d[2], o = d[0]; o--; ) s = s.lastChild;
              if (!ne.leadingWhitespace && Qe.test(r) && h.push(e.createTextNode(Qe.exec(r) [0])), !ne.tbody) for (r = 'table' !== l || Fe.test(r) ? '<table>' !== d[1] || Fe.test(r) ? 0 : s : s.firstChild, o = r && r.childNodes.length; o--; ) oe.nodeName(u = r.childNodes[o], 'tbody') && !u.childNodes.length && r.removeChild(u);
              for (oe.merge(h, s.childNodes), s.textContent = ''; s.firstChild; ) s.removeChild(s.firstChild);
              s = f.lastChild
            } else h.push(e.createTextNode(r));
            for (s && f.removeChild(s), ne.appendChecked || oe.grep(m(h, 'input'), b), p = 0; r = h[p++]; ) if ((!i || - 1 === oe.inArray(r, i)) && (a = oe.contains(r.ownerDocument, r), s = m(f.appendChild(r), 'script'), a && C(s), n)) for (o = 0; r = s[o++]; ) Ue.test(r.type || '') && n.push(r);
            return s = null,
            f
          },
          cleanData: function (t, e) {
            for (var n, i, o, r, a = 0, s = oe.expando, l = oe.cache, u = ne.deleteExpando, d = oe.event.special; null != (n = t[a]); a++) if ((e || oe.acceptData(n)) && (o = n[s], r = o && l[o])) {
              if (r.events) for (i in r.events) d[i] ? oe.event.remove(n, i)  : oe.removeEvent(n, i, r.handle);
              l[o] && (delete l[o], u ? delete n[s] : typeof n.removeAttribute !== Se ? n.removeAttribute(s)  : n[s] = null, X.push(o))
            }
          }
        }),
        oe.fn.extend({
          text: function (t) {
            return Ne(this, function (t) {
              return void 0 === t ? oe.text(this)  : this.empty().append((this[0] && this[0].ownerDocument || pe).createTextNode(t))
            }, null, t, arguments.length)
          },
          append: function () {
            return this.domManip(arguments, function (t) {
              if (1 === this.nodeType || 11 === this.nodeType || 9 === this.nodeType) {
                var e = v(this, t);
                e.appendChild(t)
              }
            })
          },
          prepend: function () {
            return this.domManip(arguments, function (t) {
              if (1 === this.nodeType || 11 === this.nodeType || 9 === this.nodeType) {
                var e = v(this, t);
                e.insertBefore(t, e.firstChild)
              }
            })
          },
          before: function () {
            return this.domManip(arguments, function (t) {
              this.parentNode && this.parentNode.insertBefore(t, this)
            })
          },
          after: function () {
            return this.domManip(arguments, function (t) {
              this.parentNode && this.parentNode.insertBefore(t, this.nextSibling)
            })
          },
          remove: function (t, e) {
            for (var n, i = t ? oe.filter(t, this)  : this, o = 0; null != (n = i[o]); o++) e || 1 !== n.nodeType || oe.cleanData(m(n)),
            n.parentNode && (e && oe.contains(n.ownerDocument, n) && C(m(n, 'script')), n.parentNode.removeChild(n));
            return this
          },
          empty: function () {
            for (var t, e = 0; null != (t = this[e]); e++) {
              for (1 === t.nodeType && oe.cleanData(m(t, !1)); t.firstChild; ) t.removeChild(t.firstChild);
              t.options && oe.nodeName(t, 'select') && (t.options.length = 0)
            }
            return this
          },
          clone: function (t, e) {
            return t = null == t ? !1 : t,
            e = null == e ? t : e,
            this.map(function () {
              return oe.clone(this, t, e)
            })
          },
          html: function (t) {
            return Ne(this, function (t) {
              var e = this[0] || {
              },
              n = 0,
              i = this.length;
              if (void 0 === t) return 1 === e.nodeType ? e.innerHTML.replace(Oe, '')  : void 0;
              if (!('string' != typeof t || Be.test(t) || !ne.htmlSerialize && Re.test(t) || !ne.leadingWhitespace && Qe.test(t) || Ge[(He.exec(t) || [
                '',
                ''
              ]) [1].toLowerCase()])) {
                t = t.replace(je, '<$1></$2>');
                try {
                  for (; i > n; n++) e = this[n] || {
                  },
                  1 === e.nodeType && (oe.cleanData(m(e, !1)), e.innerHTML = t);
                  e = 0
                } catch (o) {
                }
              }
              e && this.empty().append(t)
            }, null, t, arguments.length)
          },
          replaceWith: function () {
            var t = arguments[0];
            return this.domManip(arguments, function (e) {
              t = this.parentNode,
              oe.cleanData(m(this)),
              t && t.replaceChild(e, this)
            }),
            t && (t.length || t.nodeType) ? this : this.remove()
          },
          detach: function (t) {
            return this.remove(t, !0)
          },
          domManip: function (t, e) {
            t = V.apply([], t);
            var n,
            i,
            o,
            r,
            a,
            s,
            l = 0,
            u = this.length,
            d = this,
            c = u - 1,
            f = t[0],
            h = oe.isFunction(f);
            if (h || u > 1 && 'string' == typeof f && !ne.checkClone && We.test(f)) return this.each(function (n) {
              var i = d.eq(n);
              h && (t[0] = f.call(this, n, i.html())),
              i.domManip(t, e)
            });
            if (u && (s = oe.buildFragment(t, this[0].ownerDocument, !1, this), n = s.firstChild, 1 === s.childNodes.length && (s = n), n)) {
              for (r = oe.map(m(s, 'script'), y), o = r.length; u > l; l++) i = s,
              l !== c && (i = oe.clone(i, !0, !0), o && oe.merge(r, m(i, 'script'))),
              e.call(this[l], i, l);
              if (o) for (a = r[r.length - 1].ownerDocument, oe.map(r, x), l = 0; o > l; l++) i = r[l],
              Ue.test(i.type || '') && !oe._data(i, 'globalEval') && oe.contains(a, i) && (i.src ? oe._evalUrl && oe._evalUrl(i.src)  : oe.globalEval((i.text || i.textContent || i.innerHTML || '').replace(Xe, '')));
              s = n = null
            }
            return this
          }
        }),
        oe.each({
          appendTo: 'append',
          prependTo: 'prepend',
          insertBefore: 'before',
          insertAfter: 'after',
          replaceAll: 'replaceWith'
        }, function (t, e) {
          oe.fn[t] = function (t) {
            for (var n, i = 0, o = [
            ], r = oe(t), a = r.length - 1; a >= i; i++) n = i === a ? this : this.clone(!0),
            oe(r[i]) [e](n),
            Y.apply(o, n.get());
            return this.pushStack(o)
          }
        });
        var Ke,
        Ze = {
        };
        !function () {
          var t;
          ne.shrinkWrapBlocks = function () {
            if (null != t) return t;
            t = !1;
            var e,
            n,
            i;
            return n = pe.getElementsByTagName('body') [0],
            n && n.style ? (e = pe.createElement('div'), i = pe.createElement('div'), i.style.cssText = 'position:absolute;border:0;width:0;height:0;top:0;left:-9999px', n.appendChild(i).appendChild(e), typeof e.style.zoom !== Se && (e.style.cssText = '-webkit-box-sizing:content-box;-moz-box-sizing:content-box;box-sizing:content-box;display:block;margin:0;border:0;padding:1px;width:1px;zoom:1', e.appendChild(pe.createElement('div')).style.width = '5px', t = 3 !== e.offsetWidth), n.removeChild(i), t)  : void 0
          }
        }();
        var tn,
        en,
        nn = /^margin/,
        on = new RegExp('^(' + Te + ')(?!px)[a-z%]+$', 'i'),
        rn = /^(top|right|bottom|left)$/;
        t.getComputedStyle ? (tn = function (e) {
          return e.ownerDocument.defaultView.opener ? e.ownerDocument.defaultView.getComputedStyle(e, null)  : t.getComputedStyle(e, null)
        }, en = function (t, e, n) {
          var i,
          o,
          r,
          a,
          s = t.style;
          return n = n || tn(t),
          a = n ? n.getPropertyValue(e) || n[e] : void 0,
          n && ('' !== a || oe.contains(t.ownerDocument, t) || (a = oe.style(t, e)), on.test(a) && nn.test(e) && (i = s.width, o = s.minWidth, r = s.maxWidth, s.minWidth = s.maxWidth = s.width = a, a = n.width, s.width = i, s.minWidth = o, s.maxWidth = r)),
          void 0 === a ? a : a + ''
        })  : pe.documentElement.currentStyle && (tn = function (t) {
          return t.currentStyle
        }, en = function (t, e, n) {
          var i,
          o,
          r,
          a,
          s = t.style;
          return n = n || tn(t),
          a = n ? n[e] : void 0,
          null == a && s && s[e] && (a = s[e]),
          on.test(a) && !rn.test(e) && (i = s.left, o = t.runtimeStyle, r = o && o.left, r && (o.left = t.currentStyle.left), s.left = 'fontSize' === e ? '1em' : a, a = s.pixelLeft + 'px', s.left = i, r && (o.left = r)),
          void 0 === a ? a : a + '' || 'auto'
        }),
        function () {
          function e() {
            var e,
            n,
            i,
            o;
            n = pe.getElementsByTagName('body') [0],
            n && n.style && (e = pe.createElement('div'), i = pe.createElement('div'), i.style.cssText = 'position:absolute;border:0;width:0;height:0;top:0;left:-9999px', n.appendChild(i).appendChild(e), e.style.cssText = '-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box;display:block;margin-top:1%;top:1%;border:1px;padding:1px;width:4px;position:absolute', r = a = !1, l = !0, t.getComputedStyle && (r = '1%' !== (t.getComputedStyle(e, null) || {
            }).top, a = '4px' === (t.getComputedStyle(e, null) || {
              width: '4px'
            }).width, o = e.appendChild(pe.createElement('div')), o.style.cssText = e.style.cssText = '-webkit-box-sizing:content-box;-moz-box-sizing:content-box;box-sizing:content-box;display:block;margin:0;border:0;padding:0', o.style.marginRight = o.style.width = '0', e.style.width = '1px', l = !parseFloat((t.getComputedStyle(o, null) || {
            }).marginRight), e.removeChild(o)), e.innerHTML = '<table><tr><td></td><td>t</td></tr></table>', o = e.getElementsByTagName('td'), o[0].style.cssText = 'margin:0;border:0;padding:0;display:none', s = 0 === o[0].offsetHeight, s && (o[0].style.display = '', o[1].style.display = 'none', s = 0 === o[0].offsetHeight), n.removeChild(i))
          }
          var n,
          i,
          o,
          r,
          a,
          s,
          l;
          n = pe.createElement('div'),
          n.innerHTML = '  <link/><table></table><a href=\'/a\'>a</a><input type=\'checkbox\'/>',
          o = n.getElementsByTagName('a') [0],
          i = o && o.style,
          i && (i.cssText = 'float:left;opacity:.5', ne.opacity = '0.5' === i.opacity, ne.cssFloat = !!i.cssFloat, n.style.backgroundClip = 'content-box', n.cloneNode(!0).style.backgroundClip = '', ne.clearCloneStyle = 'content-box' === n.style.backgroundClip, ne.boxSizing = '' === i.boxSizing || '' === i.MozBoxSizing || '' === i.WebkitBoxSizing, oe.extend(ne, {
            reliableHiddenOffsets: function () {
              return null == s && e(),
              s
            },
            boxSizingReliable: function () {
              return null == a && e(),
              a
            },
            pixelPosition: function () {
              return null == r && e(),
              r
            },
            reliableMarginRight: function () {
              return null == l && e(),
              l
            }
          }))
        }(),
        oe.swap = function (t, e, n, i) {
          var o,
          r,
          a = {
          };
          for (r in e) a[r] = t.style[r],
          t.style[r] = e[r];
          o = n.apply(t, i || [
          ]);
          for (r in e) t.style[r] = a[r];
          return o
        };
        var an = /alpha\([^)]*\)/i,
        sn = /opacity\s*=\s*([^)]*)/,
        ln = /^(none|table(?!-c[ea]).+)/,
        un = new RegExp('^(' + Te + ')(.*)$', 'i'),
        dn = new RegExp('^([+-])=(' + Te + ')', 'i'),
        cn = {
          position: 'absolute',
          visibility: 'hidden',
          display: 'block'
        },
        fn = {
          letterSpacing: '0',
          fontWeight: '400'
        },
        hn = [
          'Webkit',
          'O',
          'Moz',
          'ms'
        ];
        oe.extend({
          cssHooks: {
            opacity: {
              get: function (t, e) {
                if (e) {
                  var n = en(t, 'opacity');
                  return '' === n ? '1' : n
                }
              }
            }
          },
          cssNumber: {
            columnCount: !0,
            fillOpacity: !0,
            flexGrow: !0,
            flexShrink: !0,
            fontWeight: !0,
            lineHeight: !0,
            opacity: !0,
            order: !0,
            orphans: !0,
            widows: !0,
            zIndex: !0,
            zoom: !0
          },
          cssProps: {
            'float': ne.cssFloat ? 'cssFloat' : 'styleFloat'
          },
          style: function (t, e, n, i) {
            if (t && 3 !== t.nodeType && 8 !== t.nodeType && t.style) {
              var o,
              r,
              a,
              s = oe.camelCase(e),
              l = t.style;
              if (e = oe.cssProps[s] || (oe.cssProps[s] = k(l, s)), a = oe.cssHooks[e] || oe.cssHooks[s], void 0 === n) return a && 'get' in a && void 0 !== (o = a.get(t, !1, i)) ? o : l[e];
              if (r = typeof n, 'string' === r && (o = dn.exec(n)) && (n = (o[1] + 1) * o[2] + parseFloat(oe.css(t, e)), r = 'number'), null != n && n === n && ('number' !== r || oe.cssNumber[s] || (n += 'px'), ne.clearCloneStyle || '' !== n || 0 !== e.indexOf('background') || (l[e] = 'inherit'), !(a && 'set' in a && void 0 === (n = a.set(t, n, i))))) try {
                l[e] = n
              } catch (u) {
              }
            }
          },
          css: function (t, e, n, i) {
            var o,
            r,
            a,
            s = oe.camelCase(e);
            return e = oe.cssProps[s] || (oe.cssProps[s] = k(t.style, s)),
            a = oe.cssHooks[e] || oe.cssHooks[s],
            a && 'get' in a && (r = a.get(t, !0, n)),
            void 0 === r && (r = en(t, e, i)),
            'normal' === r && e in fn && (r = fn[e]),
            '' === n || n ? (o = parseFloat(r), n === !0 || oe.isNumeric(o) ? o || 0 : r)  : r
          }
        }),
        oe.each(['height',
        'width'], function (t, e) {
          oe.cssHooks[e] = {
            get: function (t, n, i) {
              return n ? ln.test(oe.css(t, 'display')) && 0 === t.offsetWidth ? oe.swap(t, cn, function () {
                return L(t, e, i)
              })  : L(t, e, i)  : void 0
            },
            set: function (t, n, i) {
              var o = i && tn(t);
              return N(t, n, i ? D(t, e, i, ne.boxSizing && 'border-box' === oe.css(t, 'boxSizing', !1, o), o)  : 0)
            }
          }
        }),
        ne.opacity || (oe.cssHooks.opacity = {
          get: function (t, e) {
            return sn.test((e && t.currentStyle ? t.currentStyle.filter : t.style.filter) || '') ? 0.01 * parseFloat(RegExp.$1) + '' : e ? '1' : ''
          },
          set: function (t, e) {
            var n = t.style,
            i = t.currentStyle,
            o = oe.isNumeric(e) ? 'alpha(opacity=' + 100 * e + ')' : '',
            r = i && i.filter || n.filter || '';
            n.zoom = 1,
            (e >= 1 || '' === e) && '' === oe.trim(r.replace(an, '')) && n.removeAttribute && (n.removeAttribute('filter'), '' === e || i && !i.filter) || (n.filter = an.test(r) ? r.replace(an, o)  : r + ' ' + o)
          }
        }),
        oe.cssHooks.marginRight = T(ne.reliableMarginRight, function (t, e) {
          return e ? oe.swap(t, {
            display: 'inline-block'
          }, en, [
            t,
            'marginRight'
          ])  : void 0
        }),
        oe.each({
          margin: '',
          padding: '',
          border: 'Width'
        }, function (t, e) {
          oe.cssHooks[t + e] = {
            expand: function (n) {
              for (var i = 0, o = {
              }, r = 'string' == typeof n ? n.split(' ')  : [
                n
              ]; 4 > i; i++) o[t + ke[i] + e] = r[i] || r[i - 2] || r[0];
              return o
            }
          },
          nn.test(t) || (oe.cssHooks[t + e].set = N)
        }),
        oe.fn.extend({
          css: function (t, e) {
            return Ne(this, function (t, e, n) {
              var i,
              o,
              r = {
              },
              a = 0;
              if (oe.isArray(e)) {
                for (i = tn(t), o = e.length; o > a; a++) r[e[a]] = oe.css(t, e[a], !1, i);
                return r
              }
              return void 0 !== n ? oe.style(t, e, n)  : oe.css(t, e)
            }, t, e, arguments.length > 1)
          },
          show: function () {
            return E(this, !0)
          },
          hide: function () {
            return E(this)
          },
          toggle: function (t) {
            return 'boolean' == typeof t ? t ? this.show()  : this.hide()  : this.each(function () {
              Ee(this) ? oe(this).show()  : oe(this).hide()
            })
          }
        }),
        oe.Tween = A,
        A.prototype = {
          constructor: A,
          init: function (t, e, n, i, o, r) {
            this.elem = t,
            this.prop = n,
            this.easing = o || 'swing',
            this.options = e,
            this.start = this.now = this.cur(),
            this.end = i,
            this.unit = r || (oe.cssNumber[n] ? '' : 'px')
          },
          cur: function () {
            var t = A.propHooks[this.prop];
            return t && t.get ? t.get(this)  : A.propHooks._default.get(this)
          },
          run: function (t) {
            var e,
            n = A.propHooks[this.prop];
            return this.pos = e = this.options.duration ? oe.easing[this.easing](t, this.options.duration * t, 0, 1, this.options.duration)  : t,
            this.now = (this.end - this.start) * e + this.start,
            this.options.step && this.options.step.call(this.elem, this.now, this),
            n && n.set ? n.set(this)  : A.propHooks._default.set(this),
            this
          }
        },
        A.prototype.init.prototype = A.prototype,
        A.propHooks = {
          _default: {
            get: function (t) {
              var e;
              return null == t.elem[t.prop] || t.elem.style && null != t.elem.style[t.prop] ? (e = oe.css(t.elem, t.prop, ''), e && 'auto' !== e ? e : 0)  : t.elem[t.prop]
            },
            set: function (t) {
              oe.fx.step[t.prop] ? oe.fx.step[t.prop](t)  : t.elem.style && (null != t.elem.style[oe.cssProps[t.prop]] || oe.cssHooks[t.prop]) ? oe.style(t.elem, t.prop, t.now + t.unit)  : t.elem[t.prop] = t.now
            }
          }
        },
        A.propHooks.scrollTop = A.propHooks.scrollLeft = {
          set: function (t) {
            t.elem.nodeType && t.elem.parentNode && (t.elem[t.prop] = t.now)
          }
        },
        oe.easing = {
          linear: function (t) {
            return t
          },
          swing: function (t) {
            return 0.5 - Math.cos(t * Math.PI) / 2
          }
        },
        oe.fx = A.prototype.init,
        oe.fx.step = {
        };
        var pn,
        gn,
        mn = /^(?:toggle|show|hide)$/,
        bn = new RegExp('^(?:([+-])=|)(' + Te + ')([a-z%]*)$', 'i'),
        vn = /queueHooks$/,
        yn = [
          P
        ],
        xn = {
          '*': [
            function (t, e) {
              var n = this.createTween(t, e),
              i = n.cur(),
              o = bn.exec(e),
              r = o && o[3] || (oe.cssNumber[t] ? '' : 'px'),
              a = (oe.cssNumber[t] || 'px' !== r && + i) && bn.exec(oe.css(n.elem, t)),
              s = 1,
              l = 20;
              if (a && a[3] !== r) {
                r = r || a[3],
                o = o || [
                ],
                a = + i || 1;
                do s = s || '.5',
                a /= s,
                oe.style(n.elem, t, a + r);
                while (s !== (s = n.cur() / i) && 1 !== s && --l)
              }
              return o && (a = n.start = + a || + i || 0, n.unit = r, n.end = o[1] ? a + (o[1] + 1) * o[2] : + o[2]),
              n
            }
          ]
        };
        oe.Animation = oe.extend(R, {
          tweener: function (t, e) {
            oe.isFunction(t) ? (e = t, t = [
              '*'
            ])  : t = t.split(' ');
            for (var n, i = 0, o = t.length; o > i; i++) n = t[i],
            xn[n] = xn[n] || [
            ],
            xn[n].unshift(e)
          },
          prefilter: function (t, e) {
            e ? yn.unshift(t)  : yn.push(t)
          }
        }),
        oe.speed = function (t, e, n) {
          var i = t && 'object' == typeof t ? oe.extend({
          }, t)  : {
            complete: n || !n && e || oe.isFunction(t) && t,
            duration: t,
            easing: n && e || e && !oe.isFunction(e) && e
          };
          return i.duration = oe.fx.off ? 0 : 'number' == typeof i.duration ? i.duration : i.duration in oe.fx.speeds ? oe.fx.speeds[i.duration] : oe.fx.speeds._default,
          (null == i.queue || i.queue === !0) && (i.queue = 'fx'),
          i.old = i.complete,
          i.complete = function () {
            oe.isFunction(i.old) && i.old.call(this),
            i.queue && oe.dequeue(this, i.queue)
          },
          i
        },
        oe.fn.extend({
          fadeTo: function (t, e, n, i) {
            return this.filter(Ee).css('opacity', 0).show().end().animate({
              opacity: e
            }, t, n, i)
          },
          animate: function (t, e, n, i) {
            var o = oe.isEmptyObject(t),
            r = oe.speed(e, n, i),
            a = function () {
              var e = R(this, oe.extend({
              }, t), r);
              (o || oe._data(this, 'finish')) && e.stop(!0)
            };
            return a.finish = a,
            o || r.queue === !1 ? this.each(a)  : this.queue(r.queue, a)
          },
          stop: function (t, e, n) {
            var i = function (t) {
              var e = t.stop;
              delete t.stop,
              e(n)
            };
            return 'string' != typeof t && (n = e, e = t, t = void 0),
            e && t !== !1 && this.queue(t || 'fx', [
            ]),
            this.each(function () {
              var e = !0,
              o = null != t && t + 'queueHooks',
              r = oe.timers,
              a = oe._data(this);
              if (o) a[o] && a[o].stop && i(a[o]);
               else for (o in a) a[o] && a[o].stop && vn.test(o) && i(a[o]);
              for (o = r.length; o--; ) r[o].elem !== this || null != t && r[o].queue !== t || (r[o].anim.stop(n), e = !1, r.splice(o, 1));
              (e || !n) && oe.dequeue(this, t)
            })
          },
          finish: function (t) {
            return t !== !1 && (t = t || 'fx'),
            this.each(function () {
              var e,
              n = oe._data(this),
              i = n[t + 'queue'],
              o = n[t + 'queueHooks'],
              r = oe.timers,
              a = i ? i.length : 0;
              for (n.finish = !0, oe.queue(this, t, [
              ]), o && o.stop && o.stop.call(this, !0), e = r.length; e--; ) r[e].elem === this && r[e].queue === t && (r[e].anim.stop(!0), r.splice(e, 1));
              for (e = 0; a > e; e++) i[e] && i[e].finish && i[e].finish.call(this);
              delete n.finish
            })
          }
        }),
        oe.each(['toggle',
        'show',
        'hide'], function (t, e) {
          var n = oe.fn[e];
          oe.fn[e] = function (t, i, o) {
            return null == t || 'boolean' == typeof t ? n.apply(this, arguments)  : this.animate(I(e, !0), t, i, o)
          }
        }),
        oe.each({
          slideDown: I('show'),
          slideUp: I('hide'),
          slideToggle: I('toggle'),
          fadeIn: {
            opacity: 'show'
          },
          fadeOut: {
            opacity: 'hide'
          },
          fadeToggle: {
            opacity: 'toggle'
          }
        }, function (t, e) {
          oe.fn[t] = function (t, n, i) {
            return this.animate(e, t, n, i)
          }
        }),
        oe.timers = [
        ],
        oe.fx.tick = function () {
          var t,
          e = oe.timers,
          n = 0;
          for (pn = oe.now(); n < e.length; n++) t = e[n],
          t() || e[n] !== t || e.splice(n--, 1);
          e.length || oe.fx.stop(),
          pn = void 0
        },
        oe.fx.timer = function (t) {
          oe.timers.push(t),
          t() ? oe.fx.start()  : oe.timers.pop()
        },
        oe.fx.interval = 13,
        oe.fx.start = function () {
          gn || (gn = setInterval(oe.fx.tick, oe.fx.interval))
        },
        oe.fx.stop = function () {
          clearInterval(gn),
          gn = null
        },
        oe.fx.speeds = {
          slow: 600,
          fast: 200,
          _default: 400
        },
        oe.fn.delay = function (t, e) {
          return t = oe.fx ? oe.fx.speeds[t] || t : t,
          e = e || 'fx',
          this.queue(e, function (e, n) {
            var i = setTimeout(e, t);
            n.stop = function () {
              clearTimeout(i)
            }
          })
        },
        function () {
          var t,
          e,
          n,
          i,
          o;
          e = pe.createElement('div'),
          e.setAttribute('className', 't'),
          e.innerHTML = '  <link/><table></table><a href=\'/a\'>a</a><input type=\'checkbox\'/>',
          i = e.getElementsByTagName('a') [0],
          n = pe.createElement('select'),
          o = n.appendChild(pe.createElement('option')),
          t = e.getElementsByTagName('input') [0],
          i.style.cssText = 'top:1px',
          ne.getSetAttribute = 't' !== e.className,
          ne.style = /top/.test(i.getAttribute('style')),
          ne.hrefNormalized = '/a' === i.getAttribute('href'),
          ne.checkOn = !!t.value,
          ne.optSelected = o.selected,
          ne.enctype = !!pe.createElement('form').enctype,
          n.disabled = !0,
          ne.optDisabled = !o.disabled,
          t = pe.createElement('input'),
          t.setAttribute('value', ''),
          ne.input = '' === t.getAttribute('value'),
          t.value = 't',
          t.setAttribute('type', 'radio'),
          ne.radioValue = 't' === t.value
        }();
        var Cn = /\r/g;
        oe.fn.extend({
          val: function (t) {
            var e,
            n,
            i,
            o = this[0];
            {
              if (arguments.length) return i = oe.isFunction(t),
              this.each(function (n) {
                var o;
                1 === this.nodeType && (o = i ? t.call(this, n, oe(this).val())  : t, null == o ? o = '' : 'number' == typeof o ? o += '' : oe.isArray(o) && (o = oe.map(o, function (t) {
                  return null == t ? '' : t + ''
                })), e = oe.valHooks[this.type] || oe.valHooks[this.nodeName.toLowerCase()], e && 'set' in e && void 0 !== e.set(this, o, 'value') || (this.value = o))
              });
              if (o) return e = oe.valHooks[o.type] || oe.valHooks[o.nodeName.toLowerCase()],
              e && 'get' in e && void 0 !== (n = e.get(o, 'value')) ? n : (n = o.value, 'string' == typeof n ? n.replace(Cn, '')  : null == n ? '' : n)
            }
          }
        }),
        oe.extend({
          valHooks: {
            option: {
              get: function (t) {
                var e = oe.find.attr(t, 'value');
                return null != e ? e : oe.trim(oe.text(t))
              }
            },
            select: {
              get: function (t) {
                for (var e, n, i = t.options, o = t.selectedIndex, r = 'select-one' === t.type || 0 > o, a = r ? null : [
                ], s = r ? o + 1 : i.length, l = 0 > o ? s : r ? o : 0; s > l; l++) if (n = i[l], !(!n.selected && l !== o || (ne.optDisabled ? n.disabled : null !== n.getAttribute('disabled')) || n.parentNode.disabled && oe.nodeName(n.parentNode, 'optgroup'))) {
                  if (e = oe(n).val(), r) return e;
                  a.push(e)
                }
                return a
              },
              set: function (t, e) {
                for (var n, i, o = t.options, r = oe.makeArray(e), a = o.length; a--; ) if (i = o[a], oe.inArray(oe.valHooks.option.get(i), r) >= 0) try {
                  i.selected = n = !0
                } catch (s) {
                  i.scrollHeight
                } else i.selected = !1;
                return n || (t.selectedIndex = - 1),
                o
              }
            }
          }
        }),
        oe.each(['radio',
        'checkbox'], function () {
          oe.valHooks[this] = {
            set: function (t, e) {
              return oe.isArray(e) ? t.checked = oe.inArray(oe(t).val(), e) >= 0 : void 0
            }
          },
          ne.checkOn || (oe.valHooks[this].get = function (t) {
            return null === t.getAttribute('value') ? 'on' : t.value
          })
        });
        var wn,
        Sn,
        _n = oe.expr.attrHandle,
        qn = /^(?:checked|selected)$/i,
        Tn = ne.getSetAttribute,
        kn = ne.input;
        oe.fn.extend({
          attr: function (t, e) {
            return Ne(this, oe.attr, t, e, arguments.length > 1)
          },
          removeAttr: function (t) {
            return this.each(function () {
              oe.removeAttr(this, t)
            })
          }
        }),
        oe.extend({
          attr: function (t, e, n) {
            var i,
            o,
            r = t.nodeType;
            if (t && 3 !== r && 8 !== r && 2 !== r) return typeof t.getAttribute === Se ? oe.prop(t, e, n)  : (1 === r && oe.isXMLDoc(t) || (e = e.toLowerCase(), i = oe.attrHooks[e] || (oe.expr.match.bool.test(e) ? Sn : wn)), void 0 === n ? i && 'get' in i && null !== (o = i.get(t, e)) ? o : (o = oe.find.attr(t, e), null == o ? void 0 : o)  : null !== n ? i && 'set' in i && void 0 !== (o = i.set(t, n, e)) ? o : (t.setAttribute(e, n + ''), n)  : void oe.removeAttr(t, e))
          },
          removeAttr: function (t, e) {
            var n,
            i,
            o = 0,
            r = e && e.match(ye);
            if (r && 1 === t.nodeType) for (; n = r[o++]; ) i = oe.propFix[n] || n,
            oe.expr.match.bool.test(n) ? kn && Tn || !qn.test(n) ? t[i] = !1 : t[oe.camelCase('default-' + n)] = t[i] = !1 : oe.attr(t, n, ''),
            t.removeAttribute(Tn ? n : i)
          },
          attrHooks: {
            type: {
              set: function (t, e) {
                if (!ne.radioValue && 'radio' === e && oe.nodeName(t, 'input')) {
                  var n = t.value;
                  return t.setAttribute('type', e),
                  n && (t.value = n),
                  e
                }
              }
            }
          }
        }),
        Sn = {
          set: function (t, e, n) {
            return e === !1 ? oe.removeAttr(t, n)  : kn && Tn || !qn.test(n) ? t.setAttribute(!Tn && oe.propFix[n] || n, n)  : t[oe.camelCase('default-' + n)] = t[n] = !0,
            n
          }
        },
        oe.each(oe.expr.match.bool.source.match(/\w+/g), function (t, e) {
          var n = _n[e] || oe.find.attr;
          _n[e] = kn && Tn || !qn.test(e) ? function (t, e, i) {
            var o,
            r;
            return i || (r = _n[e], _n[e] = o, o = null != n(t, e, i) ? e.toLowerCase()  : null, _n[e] = r),
            o
          }
           : function (t, e, n) {
            return n ? void 0 : t[oe.camelCase('default-' + e)] ? e.toLowerCase()  : null
          }
        }),
        kn && Tn || (oe.attrHooks.value = {
          set: function (t, e, n) {
            return oe.nodeName(t, 'input') ? void (t.defaultValue = e)  : wn && wn.set(t, e, n)
          }
        }),
        Tn || (wn = {
          set: function (t, e, n) {
            var i = t.getAttributeNode(n);
            return i || t.setAttributeNode(i = t.ownerDocument.createAttribute(n)),
            i.value = e += '',
            'value' === n || e === t.getAttribute(n) ? e : void 0
          }
        }, _n.id = _n.name = _n.coords = function (t, e, n) {
          var i;
          return n ? void 0 : (i = t.getAttributeNode(e)) && '' !== i.value ? i.value : null
        }, oe.valHooks.button = {
          get: function (t, e) {
            var n = t.getAttributeNode(e);
            return n && n.specified ? n.value : void 0
          },
          set: wn.set
        }, oe.attrHooks.contenteditable = {
          set: function (t, e, n) {
            wn.set(t, '' === e ? !1 : e, n)
          }
        }, oe.each(['width',
        'height'], function (t, e) {
          oe.attrHooks[e] = {
            set: function (t, n) {
              return '' === n ? (t.setAttribute(e, 'auto'), n)  : void 0
            }
          }
        })),
        ne.style || (oe.attrHooks.style = {
          get: function (t) {
            return t.style.cssText || void 0
          },
          set: function (t, e) {
            return t.style.cssText = e + ''
          }
        });
        var En = /^(?:input|select|textarea|button|object)$/i,
        Nn = /^(?:a|area)$/i;
        oe.fn.extend({
          prop: function (t, e) {
            return Ne(this, oe.prop, t, e, arguments.length > 1)
          },
          removeProp: function (t) {
            return t = oe.propFix[t] || t,
            this.each(function () {
              try {
                this[t] = void 0,
                delete this[t]
              } catch (e) {
              }
            })
          }
        }),
        oe.extend({
          propFix: {
            'for': 'htmlFor',
            'class': 'className'
          },
          prop: function (t, e, n) {
            var i,
            o,
            r,
            a = t.nodeType;
            if (t && 3 !== a && 8 !== a && 2 !== a) return r = 1 !== a || !oe.isXMLDoc(t),
            r && (e = oe.propFix[e] || e, o = oe.propHooks[e]),
            void 0 !== n ? o && 'set' in o && void 0 !== (i = o.set(t, n, e)) ? i : t[e] = n : o && 'get' in o && null !== (i = o.get(t, e)) ? i : t[e]
          },
          propHooks: {
            tabIndex: {
              get: function (t) {
                var e = oe.find.attr(t, 'tabindex');
                return e ? parseInt(e, 10)  : En.test(t.nodeName) || Nn.test(t.nodeName) && t.href ? 0 : - 1
              }
            }
          }
        }),
        ne.hrefNormalized || oe.each(['href',
        'src'], function (t, e) {
          oe.propHooks[e] = {
            get: function (t) {
              return t.getAttribute(e, 4)
            }
          }
        }),
        ne.optSelected || (oe.propHooks.selected = {
          get: function (t) {
            var e = t.parentNode;
            return e && (e.selectedIndex, e.parentNode && e.parentNode.selectedIndex),
            null
          }
        }),
        oe.each(['tabIndex',
        'readOnly',
        'maxLength',
        'cellSpacing',
        'cellPadding',
        'rowSpan',
        'colSpan',
        'useMap',
        'frameBorder',
        'contentEditable'], function () {
          oe.propFix[this.toLowerCase()] = this
        }),
        ne.enctype || (oe.propFix.enctype = 'encoding');
        var Dn = /[\t\r\n\f]/g;
        oe.fn.extend({
          addClass: function (t) {
            var e,
            n,
            i,
            o,
            r,
            a,
            s = 0,
            l = this.length,
            u = 'string' == typeof t && t;
            if (oe.isFunction(t)) return this.each(function (e) {
              oe(this).addClass(t.call(this, e, this.className))
            });
            if (u) for (e = (t || '').match(ye) || [
            ]; l > s; s++) if (n = this[s], i = 1 === n.nodeType && (n.className ? (' ' + n.className + ' ').replace(Dn, ' ')  : ' ')) {
              for (r = 0; o = e[r++]; ) i.indexOf(' ' + o + ' ') < 0 && (i += o + ' ');
              a = oe.trim(i),
              n.className !== a && (n.className = a)
            }
            return this
          },
          removeClass: function (t) {
            var e,
            n,
            i,
            o,
            r,
            a,
            s = 0,
            l = this.length,
            u = 0 === arguments.length || 'string' == typeof t && t;
            if (oe.isFunction(t)) return this.each(function (e) {
              oe(this).removeClass(t.call(this, e, this.className))
            });
            if (u) for (e = (t || '').match(ye) || [
            ]; l > s; s++) if (n = this[s], i = 1 === n.nodeType && (n.className ? (' ' + n.className + ' ').replace(Dn, ' ')  : '')) {
              for (r = 0; o = e[r++]; ) for (; i.indexOf(' ' + o + ' ') >= 0; ) i = i.replace(' ' + o + ' ', ' ');
              a = t ? oe.trim(i)  : '',
              n.className !== a && (n.className = a)
            }
            return this
          },
          toggleClass: function (t, e) {
            var n = typeof t;
            return 'boolean' == typeof e && 'string' === n ? e ? this.addClass(t)  : this.removeClass(t)  : this.each(oe.isFunction(t) ? function (n) {
              oe(this).toggleClass(t.call(this, n, this.className, e), e)
            }
             : function () {
              if ('string' === n) for (var e, i = 0, o = oe(this), r = t.match(ye) || [
              ]; e = r[i++]; ) o.hasClass(e) ? o.removeClass(e)  : o.addClass(e);
               else (n === Se || 'boolean' === n) && (this.className && oe._data(this, '__className__', this.className), this.className = this.className || t === !1 ? '' : oe._data(this, '__className__') || '')
            })
          },
          hasClass: function (t) {
            for (var e = ' ' + t + ' ', n = 0, i = this.length; i > n; n++) if (1 === this[n].nodeType && (' ' + this[n].className + ' ').replace(Dn, ' ').indexOf(e) >= 0) return !0;
            return !1
          }
        }),
        oe.each('blur focus focusin focusout load resize scroll unload click dblclick mousedown mouseup mousemove mouseover mouseout mouseenter mouseleave change select submit keydown keypress keyup error contextmenu'.split(' '), function (t, e) {
          oe.fn[e] = function (t, n) {
            return arguments.length > 0 ? this.on(e, null, t, n)  : this.trigger(e)
          }
        }),
        oe.fn.extend({
          hover: function (t, e) {
            return this.mouseenter(t).mouseleave(e || t)
          },
          bind: function (t, e, n) {
            return this.on(t, null, e, n)
          },
          unbind: function (t, e) {
            return this.off(t, null, e)
          },
          delegate: function (t, e, n, i) {
            return this.on(e, t, n, i)
          },
          undelegate: function (t, e, n) {
            return 1 === arguments.length ? this.off(t, '**')  : this.off(e, t || '**', n)
          }
        });
        var Ln = oe.now(),
        An = /\?/,
        Jn = /(,)|(\[|{)|(}|])|"(?:[^"\\\r\n]|\\["\\\/bfnrt]|\\u[\da-fA-F]{4})*"\s*:?|true|false|null|-?(?!0\d)\d+(?:\.\d+|)(?:[eE][+-]?\d+|)/g;
        oe.parseJSON = function (e) {
          if (t.JSON && t.JSON.parse) return t.JSON.parse(e + '');
          var n,
          i = null,
          o = oe.trim(e + '');
          return o && !oe.trim(o.replace(Jn, function (t, e, o, r) {
            return n && e && (i = 0),
            0 === i ? t : (n = o || e, i += !r - !o, '')
          })) ? Function('return ' + o) ()  : oe.error('Invalid JSON: ' + e)
        },
        oe.parseXML = function (e) {
          var n,
          i;
          if (!e || 'string' != typeof e) return null;
          try {
            t.DOMParser ? (i = new DOMParser, n = i.parseFromString(e, 'text/xml'))  : (n = new ActiveXObject('Microsoft.XMLDOM'), n.async = 'false', n.loadXML(e))
          } catch (o) {
            n = void 0
          }
          return n && n.documentElement && !n.getElementsByTagName('parsererror').length || oe.error('Invalid XML: ' + e),
          n
        };
        var In,
        Mn,
        Pn = /#.*$/,
        On = /([?&])_=[^&]*/,
        Rn = /^(.*?):[ \t]*([^\r\n]*)\r?$/gm,
        Qn = /^(?:about|app|app-storage|.+-extension|file|res|widget):$/,
        jn = /^(?:GET|HEAD)$/,
        Hn = /^\/\//,
        Fn = /^([\w.+-]+:)(?:\/\/(?:[^\/?#]*@|)([^\/?#:]*)(?::(\d+)|)|)/,
        zn = {
        },
        Bn = {
        },
        Wn = '*/'.concat('*');
        try {
          Mn = location.href
        } catch (Un) {
          Mn = pe.createElement('a'),
          Mn.href = '',
          Mn = Mn.href
        }
        In = Fn.exec(Mn.toLowerCase()) || [
        ],
        oe.extend({
          active: 0,
          lastModified: {
          },
          etag: {
          },
          ajaxSettings: {
            url: Mn,
            type: 'GET',
            isLocal: Qn.test(In[1]),
            global: !0,
            processData: !0,
            async: !0,
            contentType: 'application/x-www-form-urlencoded; charset=UTF-8',
            accepts: {
              '*': Wn,
              text: 'text/plain',
              html: 'text/html',
              xml: 'application/xml, text/xml',
              json: 'application/json, text/javascript'
            },
            contents: {
              xml: /xml/,
              html: /html/,
              json: /json/
            },
            responseFields: {
              xml: 'responseXML',
              text: 'responseText',
              json: 'responseJSON'
            },
            converters: {
              '* text': String,
              'text html': !0,
              'text json': oe.parseJSON,
              'text xml': oe.parseXML
            },
            flatOptions: {
              url: !0,
              context: !0
            }
          },
          ajaxSetup: function (t, e) {
            return e ? H(H(t, oe.ajaxSettings), e)  : H(oe.ajaxSettings, t)
          },
          ajaxPrefilter: Q(zn),
          ajaxTransport: Q(Bn),
          ajax: function (t, e) {
            function n(t, e, n, i) {
              var o,
              d,
              b,
              v,
              x,
              w = e;
              2 !== y && (y = 2, s && clearTimeout(s), u = void 0, a = i || '', C.readyState = t > 0 ? 4 : 0, o = t >= 200 && 300 > t || 304 === t, n && (v = F(c, C, n)), v = z(c, v, C, o), o ? (c.ifModified && (x = C.getResponseHeader('Last-Modified'), x && (oe.lastModified[r] = x), x = C.getResponseHeader('etag'), x && (oe.etag[r] = x)), 204 === t || 'HEAD' === c.type ? w = 'nocontent' : 304 === t ? w = 'notmodified' : (w = v.state, d = v.data, b = v.error, o = !b))  : (b = w, (t || !w) && (w = 'error', 0 > t && (t = 0))), C.status = t, C.statusText = (e || w) + '', o ? p.resolveWith(f, [
                d,
                w,
                C
              ])  : p.rejectWith(f, [
                C,
                w,
                b
              ]), C.statusCode(m), m = void 0, l && h.trigger(o ? 'ajaxSuccess' : 'ajaxError', [
                C,
                c,
                o ? d : b
              ]), g.fireWith(f, [
                C,
                w
              ]), l && (h.trigger('ajaxComplete', [
                C,
                c
              ]), --oe.active || oe.event.trigger('ajaxStop')))
            }
            'object' == typeof t && (e = t, t = void 0),
            e = e || {
            };
            var i,
            o,
            r,
            a,
            s,
            l,
            u,
            d,
            c = oe.ajaxSetup({
            }, e),
            f = c.context || c,
            h = c.context && (f.nodeType || f.jquery) ? oe(f)  : oe.event,
            p = oe.Deferred(),
            g = oe.Callbacks('once memory'),
            m = c.statusCode || {
            },
            b = {
            },
            v = {
            },
            y = 0,
            x = 'canceled',
            C = {
              readyState: 0,
              getResponseHeader: function (t) {
                var e;
                if (2 === y) {
                  if (!d) for (d = {
                  }; e = Rn.exec(a); ) d[e[1].toLowerCase()] = e[2];
                  e = d[t.toLowerCase()]
                }
                return null == e ? null : e
              },
              getAllResponseHeaders: function () {
                return 2 === y ? a : null
              },
              setRequestHeader: function (t, e) {
                var n = t.toLowerCase();
                return y || (t = v[n] = v[n] || t, b[t] = e),
                this
              },
              overrideMimeType: function (t) {
                return y || (c.mimeType = t),
                this
              },
              statusCode: function (t) {
                var e;
                if (t) if (2 > y) for (e in t) m[e] = [
                  m[e],
                  t[e]
                ];
                 else C.always(t[C.status]);
                return this
              },
              abort: function (t) {
                var e = t || x;
                return u && u.abort(e),
                n(0, e),
                this
              }
            };
            if (p.promise(C).complete = g.add, C.success = C.done, C.error = C.fail, c.url = ((t || c.url || Mn) + '').replace(Pn, '').replace(Hn, In[1] + '//'), c.type = e.method || e.type || c.method || c.type, c.dataTypes = oe.trim(c.dataType || '*').toLowerCase().match(ye) || [
              ''
            ], null == c.crossDomain && (i = Fn.exec(c.url.toLowerCase()), c.crossDomain = !(!i || i[1] === In[1] && i[2] === In[2] && (i[3] || ('http:' === i[1] ? '80' : '443')) === (In[3] || ('http:' === In[1] ? '80' : '443')))), c.data && c.processData && 'string' != typeof c.data && (c.data = oe.param(c.data, c.traditional)), j(zn, c, e, C), 2 === y) return C;
            l = oe.event && c.global,
            l && 0 === oe.active++ && oe.event.trigger('ajaxStart'),
            c.type = c.type.toUpperCase(),
            c.hasContent = !jn.test(c.type),
            r = c.url,
            c.hasContent || (c.data && (r = c.url += (An.test(r) ? '&' : '?') + c.data, delete c.data), c.cache === !1 && (c.url = On.test(r) ? r.replace(On, '$1_=' + Ln++)  : r + (An.test(r) ? '&' : '?') + '_=' + Ln++)),
            c.ifModified && (oe.lastModified[r] && C.setRequestHeader('If-Modified-Since', oe.lastModified[r]), oe.etag[r] && C.setRequestHeader('If-None-Match', oe.etag[r])),
            (c.data && c.hasContent && c.contentType !== !1 || e.contentType) && C.setRequestHeader('Content-Type', c.contentType),
            C.setRequestHeader('Accept', c.dataTypes[0] && c.accepts[c.dataTypes[0]] ? c.accepts[c.dataTypes[0]] + ('*' !== c.dataTypes[0] ? ', ' + Wn + '; q=0.01' : '')  : c.accepts['*']);
            for (o in c.headers) C.setRequestHeader(o, c.headers[o]);
            if (c.beforeSend && (c.beforeSend.call(f, C, c) === !1 || 2 === y)) return C.abort();
            x = 'abort';
            for (o in {
              success: 1,
              error: 1,
              complete: 1
            }) C[o](c[o]);
            if (u = j(Bn, c, e, C)) {
              C.readyState = 1,
              l && h.trigger('ajaxSend', [
                C,
                c
              ]),
              c.async && c.timeout > 0 && (s = setTimeout(function () {
                C.abort('timeout')
              }, c.timeout));
              try {
                y = 1,
                u.send(b, n)
              } catch (w) {
                if (!(2 > y)) throw w;
                n( - 1, w)
              }
            } else n( - 1, 'No Transport');
            return C
          },
          getJSON: function (t, e, n) {
            return oe.get(t, e, n, 'json')
          },
          getScript: function (t, e) {
            return oe.get(t, void 0, e, 'script')
          }
        }),
        oe.each(['get',
        'post'], function (t, e) {
          oe[e] = function (t, n, i, o) {
            return oe.isFunction(n) && (o = o || i, i = n, n = void 0),
            oe.ajax({
              url: t,
              type: e,
              dataType: o,
              data: n,
              success: i
            })
          }
        }),
        oe._evalUrl = function (t) {
          return oe.ajax({
            url: t,
            type: 'GET',
            dataType: 'script',
            async: !1,
            global: !1,
            'throws': !0
          })
        },
        oe.fn.extend({
          wrapAll: function (t) {
            if (oe.isFunction(t)) return this.each(function (e) {
              oe(this).wrapAll(t.call(this, e))
            });
            if (this[0]) {
              var e = oe(t, this[0].ownerDocument).eq(0).clone(!0);
              this[0].parentNode && e.insertBefore(this[0]),
              e.map(function () {
                for (var t = this; t.firstChild && 1 === t.firstChild.nodeType; ) t = t.firstChild;
                return t
              }).append(this)
            }
            return this
          },
          wrapInner: function (t) {
            return this.each(oe.isFunction(t) ? function (e) {
              oe(this).wrapInner(t.call(this, e))
            }
             : function () {
              var e = oe(this),
              n = e.contents();
              n.length ? n.wrapAll(t)  : e.append(t)
            })
          },
          wrap: function (t) {
            var e = oe.isFunction(t);
            return this.each(function (n) {
              oe(this).wrapAll(e ? t.call(this, n)  : t)
            })
          },
          unwrap: function () {
            return this.parent().each(function () {
              oe.nodeName(this, 'body') || oe(this).replaceWith(this.childNodes)
            }).end()
          }
        }),
        oe.expr.filters.hidden = function (t) {
          return t.offsetWidth <= 0 && t.offsetHeight <= 0 || !ne.reliableHiddenOffsets() && 'none' === (t.style && t.style.display || oe.css(t, 'display'))
        },
        oe.expr.filters.visible = function (t) {
          return !oe.expr.filters.hidden(t)
        };
        var $n = /%20/g,
        Xn = /\[\]$/,
        Gn = /\r?\n/g,
        Vn = /^(?:submit|button|image|reset|file)$/i,
        Yn = /^(?:input|select|textarea|keygen)/i;
        oe.param = function (t, e) {
          var n,
          i = [
          ],
          o = function (t, e) {
            e = oe.isFunction(e) ? e()  : null == e ? '' : e,
            i[i.length] = encodeURIComponent(t) + '=' + encodeURIComponent(e)
          };
          if (void 0 === e && (e = oe.ajaxSettings && oe.ajaxSettings.traditional), oe.isArray(t) || t.jquery && !oe.isPlainObject(t)) oe.each(t, function () {
            o(this.name, this.value)
          });
           else for (n in t) B(n, t[n], e, o);
          return i.join('&').replace($n, '+')
        },
        oe.fn.extend({
          serialize: function () {
            return oe.param(this.serializeArray())
          },
          serializeArray: function () {
            return this.map(function () {
              var t = oe.prop(this, 'elements');
              return t ? oe.makeArray(t)  : this
            }).filter(function () {
              var t = this.type;
              return this.name && !oe(this).is(':disabled') && Yn.test(this.nodeName) && !Vn.test(t) && (this.checked || !De.test(t))
            }).map(function (t, e) {
              var n = oe(this).val();
              return null == n ? null : oe.isArray(n) ? oe.map(n, function (t) {
                return {
                  name: e.name,
                  value: t.replace(Gn, '\r\n')
                }
              })  : {
                name: e.name,
                value: n.replace(Gn, '\r\n')
              }
            }).get()
          }
        }),
        oe.ajaxSettings.xhr = void 0 !== t.ActiveXObject ? function () {
          return !this.isLocal && /^(get|post|head|put|delete|options)$/i.test(this.type) && W() || U()
        }
         : W;
        var Kn = 0,
        Zn = {
        },
        ti = oe.ajaxSettings.xhr();
        t.attachEvent && t.attachEvent('onunload', function () {
          for (var t in Zn) Zn[t](void 0, !0)
        }),
        ne.cors = !!ti && 'withCredentials' in ti,
        ti = ne.ajax = !!ti,
        ti && oe.ajaxTransport(function (t) {
          if (!t.crossDomain || ne.cors) {
            var e;
            return {
              send: function (n, i) {
                var o,
                r = t.xhr(),
                a = ++Kn;
                if (r.open(t.type, t.url, t.async, t.username, t.password), t.xhrFields) for (o in t.xhrFields) r[o] = t.xhrFields[o];
                t.mimeType && r.overrideMimeType && r.overrideMimeType(t.mimeType),
                t.crossDomain || n['X-Requested-With'] || (n['X-Requested-With'] = 'XMLHttpRequest');
                for (o in n) void 0 !== n[o] && r.setRequestHeader(o, n[o] + '');
                r.send(t.hasContent && t.data || null),
                e = function (n, o) {
                  var s,
                  l,
                  u;
                  if (e && (o || 4 === r.readyState)) if (delete Zn[a], e = void 0, r.onreadystatechange = oe.noop, o) 4 !== r.readyState && r.abort();
                   else {
                    u = {
                    },
                    s = r.status,
                    'string' == typeof r.responseText && (u.text = r.responseText);
                    try {
                      l = r.statusText
                    } catch (d) {
                      l = ''
                    }
                    s || !t.isLocal || t.crossDomain ? 1223 === s && (s = 204)  : s = u.text ? 200 : 404
                  }
                  u && i(s, l, u, r.getAllResponseHeaders())
                },
                t.async ? 4 === r.readyState ? setTimeout(e)  : r.onreadystatechange = Zn[a] = e : e()
              },
              abort: function () {
                e && e(void 0, !0)
              }
            }
          }
        }),
        oe.ajaxSetup({
          accepts: {
            script: 'text/javascript, application/javascript, application/ecmascript, application/x-ecmascript'
          },
          contents: {
            script: /(?:java|ecma)script/
          },
          converters: {
            'text script': function (t) {
              return oe.globalEval(t),
              t
            }
          }
        }),
        oe.ajaxPrefilter('script', function (t) {
          void 0 === t.cache && (t.cache = !1),
          t.crossDomain && (t.type = 'GET', t.global = !1)
        }),
        oe.ajaxTransport('script', function (t) {
          if (t.crossDomain) {
            var e,
            n = pe.head || oe('head') [0] || pe.documentElement;
            return {
              send: function (i, o) {
                e = pe.createElement('script'),
                e.async = !0,
                t.scriptCharset && (e.charset = t.scriptCharset),
                e.src = t.url,
                e.onload = e.onreadystatechange = function (t, n) {
                  (n || !e.readyState || /loaded|complete/.test(e.readyState)) && (e.onload = e.onreadystatechange = null, e.parentNode && e.parentNode.removeChild(e), e = null, n || o(200, 'success'))
                },
                n.insertBefore(e, n.firstChild)
              },
              abort: function () {
                e && e.onload(void 0, !0)
              }
            }
          }
        });
        var ei = [
        ],
        ni = /(=)\?(?=&|$)|\?\?/;
        oe.ajaxSetup({
          jsonp: 'callback',
          jsonpCallback: function () {
            var t = ei.pop() || oe.expando + '_' + Ln++;
            return this[t] = !0,
            t
          }
        }),
        oe.ajaxPrefilter('json jsonp', function (e, n, i) {
          var o,
          r,
          a,
          s = e.jsonp !== !1 && (ni.test(e.url) ? 'url' : 'string' == typeof e.data && !(e.contentType || '').indexOf('application/x-www-form-urlencoded') && ni.test(e.data) && 'data');
          return s || 'jsonp' === e.dataTypes[0] ? (o = e.jsonpCallback = oe.isFunction(e.jsonpCallback) ? e.jsonpCallback()  : e.jsonpCallback, s ? e[s] = e[s].replace(ni, '$1' + o)  : e.jsonp !== !1 && (e.url += (An.test(e.url) ? '&' : '?') + e.jsonp + '=' + o), e.converters['script json'] = function () {
            return a || oe.error(o + ' was not called'),
            a[0]
          }, e.dataTypes[0] = 'json', r = t[o], t[o] = function () {
            a = arguments
          }, i.always(function () {
            t[o] = r,
            e[o] && (e.jsonpCallback = n.jsonpCallback, ei.push(o)),
            a && oe.isFunction(r) && r(a[0]),
            a = r = void 0
          }), 'script')  : void 0
        }),
        oe.parseHTML = function (t, e, n) {
          if (!t || 'string' != typeof t) return null;
          'boolean' == typeof e && (n = e, e = !1),
          e = e || pe;
          var i = ce.exec(t),
          o = !n && [
          ];
          return i ? [
            e.createElement(i[1])
          ] : (i = oe.buildFragment([t], e, o), o && o.length && oe(o).remove(), oe.merge([], i.childNodes))
        };
        var ii = oe.fn.load;
        oe.fn.load = function (t, e, n) {
          if ('string' != typeof t && ii) return ii.apply(this, arguments);
          var i,
          o,
          r,
          a = this,
          s = t.indexOf(' ');
          return s >= 0 && (i = oe.trim(t.slice(s, t.length)), t = t.slice(0, s)),
          oe.isFunction(e) ? (n = e, e = void 0)  : e && 'object' == typeof e && (r = 'POST'),
          a.length > 0 && oe.ajax({
            url: t,
            type: r,
            dataType: 'html',
            data: e
          }).done(function (t) {
            o = arguments,
            a.html(i ? oe('<div>').append(oe.parseHTML(t)).find(i)  : t)
          }).complete(n && function (t, e) {
            a.each(n, o || [
              t.responseText,
              e,
              t
            ])
          }),
          this
        },
        oe.each(['ajaxStart',
        'ajaxStop',
        'ajaxComplete',
        'ajaxError',
        'ajaxSuccess',
        'ajaxSend'], function (t, e) {
          oe.fn[e] = function (t) {
            return this.on(e, t)
          }
        }),
        oe.expr.filters.animated = function (t) {
          return oe.grep(oe.timers, function (e) {
            return t === e.elem
          }).length
        };
        var oi = t.document.documentElement;
        oe.offset = {
          setOffset: function (t, e, n) {
            var i,
            o,
            r,
            a,
            s,
            l,
            u,
            d = oe.css(t, 'position'),
            c = oe(t),
            f = {
            };
            'static' === d && (t.style.position = 'relative'),
            s = c.offset(),
            r = oe.css(t, 'top'),
            l = oe.css(t, 'left'),
            u = ('absolute' === d || 'fixed' === d) && oe.inArray('auto', [
              r,
              l
            ]) > - 1,
            u ? (i = c.position(), a = i.top, o = i.left)  : (a = parseFloat(r) || 0, o = parseFloat(l) || 0),
            oe.isFunction(e) && (e = e.call(t, n, s)),
            null != e.top && (f.top = e.top - s.top + a),
            null != e.left && (f.left = e.left - s.left + o),
            'using' in e ? e.using.call(t, f)  : c.css(f)
          }
        },
        oe.fn.extend({
          offset: function (t) {
            if (arguments.length) return void 0 === t ? this : this.each(function (e) {
              oe.offset.setOffset(this, t, e)
            });
            var e,
            n,
            i = {
              top: 0,
              left: 0
            },
            o = this[0],
            r = o && o.ownerDocument;
            if (r) return e = r.documentElement,
            oe.contains(e, o) ? (typeof o.getBoundingClientRect !== Se && (i = o.getBoundingClientRect()), n = $(r), {
              top: i.top + (n.pageYOffset || e.scrollTop) - (e.clientTop || 0),
              left: i.left + (n.pageXOffset || e.scrollLeft) - (e.clientLeft || 0)
            })  : i
          },
          position: function () {
            if (this[0]) {
              var t,
              e,
              n = {
                top: 0,
                left: 0
              },
              i = this[0];
              return 'fixed' === oe.css(i, 'position') ? e = i.getBoundingClientRect()  : (t = this.offsetParent(), e = this.offset(), oe.nodeName(t[0], 'html') || (n = t.offset()), n.top += oe.css(t[0], 'borderTopWidth', !0), n.left += oe.css(t[0], 'borderLeftWidth', !0)),
              {
                top: e.top - n.top - oe.css(i, 'marginTop', !0),
                left: e.left - n.left - oe.css(i, 'marginLeft', !0)
              }
            }
          },
          offsetParent: function () {
            return this.map(function () {
              for (var t = this.offsetParent || oi; t && !oe.nodeName(t, 'html') && 'static' === oe.css(t, 'position'); ) t = t.offsetParent;
              return t || oi
            })
          }
        }),
        oe.each({
          scrollLeft: 'pageXOffset',
          scrollTop: 'pageYOffset'
        }, function (t, e) {
          var n = /Y/.test(e);
          oe.fn[t] = function (i) {
            return Ne(this, function (t, i, o) {
              var r = $(t);
              return void 0 === o ? r ? e in r ? r[e] : r.document.documentElement[i] : t[i] : void (r ? r.scrollTo(n ? oe(r).scrollLeft()  : o, n ? o : oe(r).scrollTop())  : t[i] = o)
            }, t, i, arguments.length, null)
          }
        }),
        oe.each(['top',
        'left'], function (t, e) {
          oe.cssHooks[e] = T(ne.pixelPosition, function (t, n) {
            return n ? (n = en(t, e), on.test(n) ? oe(t).position() [e] + 'px' : n)  : void 0
          })
        }),
        oe.each({
          Height: 'height',
          Width: 'width'
        }, function (t, e) {
          oe.each({
            padding: 'inner' + t,
            content: e,
            '': 'outer' + t
          }, function (n, i) {
            oe.fn[i] = function (i, o) {
              var r = arguments.length && (n || 'boolean' != typeof i),
              a = n || (i === !0 || o === !0 ? 'margin' : 'border');
              return Ne(this, function (e, n, i) {
                var o;
                return oe.isWindow(e) ? e.document.documentElement['client' + t] : 9 === e.nodeType ? (o = e.documentElement, Math.max(e.body['scroll' + t], o['scroll' + t], e.body['offset' + t], o['offset' + t], o['client' + t]))  : void 0 === i ? oe.css(e, n, a)  : oe.style(e, n, i, a)
              }, e, r ? i : void 0, r, null)
            }
          })
        }),
        oe.fn.size = function () {
          return this.length
        },
        oe.fn.andSelf = oe.fn.addBack,
        'function' == typeof define && define.amd && define('jquery', [
        ], function () {
          return oe
        });
        var ri = t.jQuery,
        ai = t.$;
        return oe.noConflict = function (e) {
          return t.$ === oe && (t.$ = ai),
          e && t.jQuery === oe && (t.jQuery = ri),
          oe
        },
        typeof e === Se && (t.jQuery2 = t.$2 = oe),
        oe
      }),
      bds.qa.ShortCut.fbJQ = $2.noConflict()
    },
    initialize: function (t) {
      this.product_id = t.product_id ? t.product_id : bds.qa.ShortCut.default_options.product_id,
      this.entrance_id = void 0 != t.entrance_id ? t.entrance_id : bds.qa.ShortCut.default_options.entrance_id,
      this.needIssueTips = void 0 != t.needIssueTips ? t.needIssueTips : bds.qa.ShortCut.default_options.needIssueTips,
      this.needLevelType = void 0 != t.needLevelType ? t.needLevelType : bds.qa.ShortCut.default_options.needLevelType,
      this.needIssue = void 0 != t.needIssue ? t.needIssue : bds.qa.ShortCut.default_options.needIssue,
      this.needCut = void 0 != t.needCut ? t.needCut : bds.qa.ShortCut.default_options.needCut,
      this.needEmail = void 0 != t.needEmail ? t.needEmail : bds.qa.ShortCut.default_options.needEmail,
      this.needGuide = void 0 != t.needGuide ? t.needGuide : bds.qa.ShortCut.default_options.needGuide,
      this.defaultCut = void 0 != t.defaultCut ? t.defaultCut : bds.qa.ShortCut.default_options.defaultCut,
      this.plugintitle = void 0 != t.plugintitle ? t.plugintitle : bds.qa.ShortCut.default_options.plugintitle,
      this.issueTips = void 0 != t.issueTips ? t.issueTips : bds.qa.ShortCut.default_options.issueTips,
      this.issuePlaceholder = void 0 != t.issuePlaceholder ? t.issuePlaceholder : bds.qa.ShortCut.default_options.issuePlaceholder,
      this.emailPlaceholder = void 0 != t.emailPlaceholder ? t.emailPlaceholder : bds.qa.ShortCut.default_options.emailPlaceholder,
      this.guide = void 0 != t.guide ? t.guide : bds.qa.ShortCut.default_options.guide,
      this.cutFileTips = void 0 != t.cutFileTips ? t.cutFileTips : bds.qa.ShortCut.default_options.cutFileTips,
      this.cutCanvasTips = void 0 != t.cutCanvasTips ? t.cutCanvasTips : bds.qa.ShortCut.default_options.cutCanvasTips,
      this.emailTips = void 0 != t.emailTips ? t.emailTips : bds.qa.ShortCut.default_options.emailTips,
      this.onlyUpFile = void 0 != t.onlyUpFile ? t.onlyUpFile : bds.qa.ShortCut.default_options.onlyUpFile,
      this.showPosition = void 0 != t.showPosition ? t.showPosition : bds.qa.ShortCut.default_options.showPosition,
      this.skinStyle = void 0 != t.skinStyle ? t.skinStyle : bds.qa.ShortCut.default_options.skinStyle,
      this.cutImg = void 0 != t.cutImg ? t.cutImg : bds.qa.ShortCut.default_options.cutImg,
      this.upImg = void 0 != t.upImg ? t.upImg : bds.qa.ShortCut.default_options.upImg,
      this.win_width = parseInt(Math.max(document.body.scrollWidth, document.documentElement.clientWidth, document.body.clientWidth)),
      this.dialogPosition = t.dialogPosition ? t.dialogPosition : bds.qa.ShortCut.default_options.dialogPosition,
      bds.qa.ShortCut._getImg(),
      'pad' == bds.qa.ShortCut.skinStyle && (this.needCut = bds.qa.ShortCut._isUpperIos6())
    },
    getPrepare: function () {
      bds.qa.ShortCut.up_file = !bds.qa.ShortCut._identifyBrowser(),
      bds.qa.ShortCut.onlyUpFile > 0 && (bds.qa.ShortCut.up_file = !0),
      'pad' == bds.qa.ShortCut.skinStyle && (bds.qa.ShortCut.up_file = !0, bds.qa.ShortCut.upImg = 'padUp.png')
    },
    init: function () {
      bds.qa.ShortCut.init_action_dialog(),
      bds.qa.ShortCut.init_bind_action(),
      bds.qa.ShortCut._isIE6() || bds.qa.ShortCut.init_drag(),
      bds.qa.ShortCut.init_post_data()
    },
    init_action_dialog: function () {
      var t = document.getElementById('fb_baidu_right_dialog');
      if (!t) {
        var e = '',
        n = bds.qa.ShortCut.needIssueTips ? '<div  class ="fb-tips-block"><span class="fb-content-tips">' + bds.qa.ShortCut.issueTips + '</span><span class = "fb-danger-tips"></span></div>' : '',
        i = bds.qa.ShortCut.needLevelType ? '<div class="fb-level-type-block"><div class="fb-level-title"><span>您遇到的问题类型</span><span class="fb-danger-tips">(*必选)</span></div><ul><li data-value="1482"><div class="fb-radio"></div><span>图片无法显示</span></li><li data-value="1665"><div class="fb-radio"></div><span>个人隐私图片</span></li><li data-value="1483"><div class="fb-radio"></div><span>加载速度慢</span></li><li data-value="1487"><div class="fb-radio"></div><span>图片品质太差</span></li><li data-value="1484"><div class="fb-radio"></div><span>下载不了图片</span></li><li data-value="1248"><div class="fb-radio"></div><span>找不到想要的图片</span></li><li data-value="1485"><div class="fb-radio"></div><span>色情、暴力图片</span></li><li data-value="1249"><div class="fb-radio"></div><span>其它</span></li></ul></div>' : '',
        o = bds.qa.ShortCut.needIssue ? '<div class="fb-textarea fb-content-block"><textarea maxlength="400" class ="fb-des-content" name="issuedesc" id="fb_des_content" data-exclude="true">' + bds.qa.ShortCut.issuePlaceholder + '</textarea></div>' : '',
        r = bds.qa.ShortCut.needEmail ? '<div class="fb-block fb-email-block"><div class="fb-phone-txt">' + bds.qa.ShortCut.emailTips + '</div><div><input type="text" class="fb-email" maxlength="100" value="' + bds.qa.ShortCut.emailPlaceholder + '" id="feedback_email"></div></div>' : '',
        a = bds.qa.ShortCut.needGuide ? '<div class="fb-guide fb-guide-block">' + bds.qa.ShortCut.guide + '</div>' : '';
        if (bds.qa.ShortCut.up_file) s = bds.qa.ShortCut.needCut ? '<div class="fb-block fb-cut-block" ><div class="fb-cut-block-ie" style="background: url(' + bds.qa.ShortCut.base_url_path + '/feedback/images/' + bds.qa.ShortCut.upImg + ')"><input class="fb-cut-input" type="file" id="fb_shangchuan" name="issueimage" onchange="bds.qa.ShortCut._checkFileType(this)"></div><span id="fb_shangchuan_txt" class="fb-shangchuan">' + bds.qa.ShortCut.cutFileTips + '</span></div>' : '',
        e = '<div class="fb-modal " data-html2canvas-ignore="true"><div class="fb-header" id="fb_dialog_header" unselectable="on" onselectstart="return false;"><a class="fb-close" id="fb_close_x">×</a><h3  class="fb-header-tips">' + bds.qa.ShortCut.plugintitle + '</h3></div><div class="fb-body" id="fb_qa_feedback_body"><div class="fb-action"><form id="fb_right_post_form" enctype="multipart/form-data" action="" method="post" onsubmit = "return false;">' + i + n + o + s + r + '</form></div><div class="fb-footer"><div class="fb-btn fb-btn-primary" id="fb_right_post_save">提交反馈</div><a style="font-size:14px;color:#2d9ef8;line-height:26px;text-decoration:underline; margin-left:20px;height:26px;" href="http://f3.baidu.com/index.php/feedback/f/index" target="_blank">我的反馈</a></div>' + a + '</div></div>';
         else {
          bds.qa.ShortCut.up_file = !1;
          var s = bds.qa.ShortCut.needCut ? '<div class="fb-block fb-cut-block"><div><input type="button" class="fb-btn fb-cut-btn" style="background: url(' + bds.qa.ShortCut.cutImg + ') no-repeat center" id="fb_jietu" value=""/><span id = "fb_tips_span" >' + bds.qa.ShortCut.cutCanvasTips + '</span></div></div> ' : '';
          e = '<div class="fb-modal " data-html2canvas-ignore="true"><div class="fb-header" id="fb_dialog_header" unselectable="on" onselectstart="return false;"><a class="fb-close" id="fb_close_x">×</a><h3  class = "fb-header-tips">' + bds.qa.ShortCut.plugintitle + '</h3></div><div class="fb-body" id="fb_qa_feedback_body"><div class="fb-action">' + i + n + o + s + r + '</div><div class="fb-footer"><div class="fb-btn fb-btn-primary" id="fb_right_canvas_save">提交反馈</div><a style="font-size:14px;color:#2d9ef8;line-height:26px;text-decoration:underline; margin-left:20px;height:26px;" href="http://f3.baidu.com/index.php/feedback/f/index" target="_blank">我的反馈</a></div>' + a + '</div></div>'
        }
        var l = document.createElement('div');
        l.id = 'fb_baidu_right_dialog',
        l.className = 'fb-feedback-right-dialog',
        bds.qa.ShortCut._isIE6() || (l.style.display = 'none', l.style.position = 'fixed'),
        l.style.zIndex = 999999,
        l.innerHTML = e;
        var u = document.createElement('div');
        u.id = 'fb_baidu_wizard',
        u.className = 'fb-baidu-wizard',
        bds.qa.ShortCut.fbJQ('body').append(u),
        bds.qa.ShortCut._getWizardPosition(),
        bds.qa.ShortCut.fbJQ('body').append(l),
        bds.qa.ShortCut._fixedPage()
      }
    },
    init_bind_action: function () {
      bds.qa.ShortCut.fbJQ('.fb-level-type-block li').click(function () {
        bds.qa.ShortCut.fbJQ(this).hasClass('fb-check') ? bds.qa.ShortCut.fbJQ(this).removeClass('fb-check')  : bds.qa.ShortCut.fbJQ(this).addClass('fb-check').siblings().removeClass('fb-check')
      }),
      bds.qa.ShortCut.fbJQ('.fb-modal textarea').focus(function () {
        bds.qa.ShortCut.fbJQ(this).val() == bds.qa.ShortCut.issuePlaceholder && (bds.qa.ShortCut.fbJQ(this).val(''), bds.qa.ShortCut.fbJQ('#fb_pop_tips') && bds.qa.ShortCut.fbJQ('#fb_pop_tips').remove())
      }),
      bds.qa.ShortCut.fbJQ('.fb-modal textarea').blur(function () {
        '' == bds.qa.ShortCut.fbJQ(this).val() && (bds.qa.ShortCut.fbJQ(this).css('color', '#9a9a9a'), bds.qa.ShortCut.fbJQ(this).val(bds.qa.ShortCut.issuePlaceholder))
      }),
      bds.qa.ShortCut.fbJQ('.fb-modal textarea').keydown(function () {
        bds.qa.ShortCut.fbJQ(this).val() != bds.qa.ShortCut.issuePlaceholder && (bds.qa.ShortCut.fbJQ(this).css('color', 'black'), bds.qa.ShortCut.fbJQ('#fb_pop_tips') && bds.qa.ShortCut.fbJQ('#fb_pop_tips').remove())
      }),
      bds.qa.ShortCut.fbJQ('.fb-modal .fb-email').focus(function () {
        bds.qa.ShortCut.fbJQ(this).val() == bds.qa.ShortCut.emailPlaceholder && bds.qa.ShortCut.fbJQ(this).val('')
      }),
      bds.qa.ShortCut.fbJQ('.fb-modal .fb-email').blur(function () {
        '' == bds.qa.ShortCut.fbJQ(this).val() && (bds.qa.ShortCut.fbJQ(this).css('color', '#9a9a9a'), bds.qa.ShortCut.fbJQ(this).val(bds.qa.ShortCut.emailPlaceholder))
      }),
      bds.qa.ShortCut.fbJQ('.fb-modal textarea').keyup(function () {
        if (bds.qa.ShortCut.fbJQ(this).val().length >= 400) {
          var t = bds.qa.ShortCut.fbJQ(this).val().substr(0, 400);
          bds.qa.ShortCut.fbJQ(this).val(t)
        }
      }),
      bds.qa.ShortCut.fbJQ('.fb-modal .fb-email').keydown(function () {
        bds.qa.ShortCut.fbJQ(this).val() != bds.qa.ShortCut.emailPlaceholder && bds.qa.ShortCut.fbJQ(this).css('color', 'black')
      }),
      bds.qa.ShortCut.fbJQ('#fb_close_x').click(function () {
        var t = function () {
          bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').remove(),
          bds.qa.ShortCut.fbJQ('#ShortCut_wizard').remove(),
          bds.qa.ShortCut.fbJQ('#fb_base_wizard_canvas').remove(),
          bds.qa.ShortCut.fbJQ('#fb_baidu_wizard').remove(),
          bds.qa.ShortCut.fbJQ('#fb_right_dialog_canvas').remove(),
          bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas').remove(),
          bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas2').remove(),
          bds.qa.ShortCut.fbJQ('.fb_cancel_flag').remove(),
          bds.qa.ShortCut.fbJQ('#fb_popwindow').remove(),
          bds.qa.ShortCut.is_feedbacking = !1
        };
        'pad' == bds.qa.ShortCut.skinStyle ? t()  : (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').hide(), t()),
        bds.qa.ShortCut.send_img = !1
      }),
      bds.qa.ShortCut.fbJQ('#fb_jietu').click(function () {
        0 == bds.qa.ShortCut.send_img && (bds.qa.ShortCut.defaultCut = !0, bds.qa.ShortCut.fbJQ('#fb_right_dialog_canvas').css('cursor', 'crosshair'), bds.qa.ShortCut.fbJQ('#fb_jietu').css('cursor', 'crosshair'), bds.qa.ShortCut.init_img_render())
      }),
      'pad' == bds.qa.ShortCut.skinStyle && (bds.qa.ShortCut.fbJQ(window).on('orientationchange', function () {
        bds.qa.ShortCut._repaint()
      }), bds.qa.ShortCut.fbJQ('.fb-des-content').on('focus', function () {
        bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('position', 'absolute')
      }), bds.qa.ShortCut.fbJQ('.fb-email').on('focus', function () {
        bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('position', 'absolute')
      })),
      bds.qa.ShortCut.bindclick = 0,
      bds.qa.ShortCut._isIE6() && (('right' == bds.qa.ShortCut.showPosition || 'bottom_left' == bds.qa.ShortCut.showPosition || 'bottom_right' == bds.qa.ShortCut.showPosition) && bds.qa.ShortCut.fbJQ(window).scroll(function () {
        bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('top', parseInt(document.documentElement.clientHeight + document.documentElement.scrollTop - bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').height() - 5) + 'px')
      }), 'center' == bds.qa.ShortCut.showPosition && bds.qa.ShortCut.fbJQ(window).scroll(function () {
        bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('top', parseInt((bds.qa.ShortCut._getClientWidth() - bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').width()) / 2) + 'px')
      })),
      bds.qa.ShortCut.fbJQ(window).on('index_off', function () {
        bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').remove(),
        bds.qa.ShortCut.fbJQ('#ShortCut_wizard').remove(),
        bds.qa.ShortCut.fbJQ('#fb_base_wizard_canvas').remove(),
        bds.qa.ShortCut.fbJQ('#fb_baidu_wizard').remove(),
        bds.qa.ShortCut.fbJQ('#fb_right_dialog_canvas').remove(),
        bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas').remove(),
        bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas2').remove(),
        bds.qa.ShortCut.fbJQ('.fb_cancel_flag').remove(),
        bds.qa.ShortCut.fbJQ('#fb_popwindow').remove(),
        bds.qa.ShortCut.is_feedbacking = !1,
        bds.qa.ShortCut.send_img = !1
      })
    },
    init_drag: function () {
      function t(t, e, n) {
        t.addEventListener ? t.addEventListener(e, n, !1)  : t.attachEvent ? t.attachEvent('on' + e, n)  : t['on' + e] = n
      }
      function e(t, e, n) {
        t.removeEventListener ? t.removeEventListener(e, n, !1)  : t.detachEvent ? t.detachEvent('on' + e, n)  : t['on' + e] = null
      }
      var n = (document.all ? !0 : !1, function (t) {
        return 'string' == typeof t ? document.getElementById(t)  : t
      }),
      i = {
        create: function () {
          return function () {
            this.initialize.apply(this, arguments)
          }
        }
      },
      o = function (t, e) {
        return function () {
          return e.apply(t, arguments)
        }
      },
      r = function (t, e) {
        return function (n) {
          return e.call(t, n || window.event)
        }
      };
      bds.qa.ShortCut.SimpleDrag = i.create(),
      bds.qa.ShortCut.SimpleDrag.prototype = {
        initialize: function (e, i) {
          this.Drag = n(e),
          this.beDrag = n(i),
          this._x = this._y = 0,
          this._fM = r(this, this.Move),
          this._fS = o(this, this.Stop),
          t(this.Drag, 'mousedown', r(this, this.Start))
        },
        Start: function (e) {
          e.preventDefault ? e.preventDefault()  : e.returnValue = !1,
          this._x = e.clientX - this.beDrag.offsetLeft,
          this._y = e.clientY - this.beDrag.offsetTop,
          t(document, 'mousemove', this._fM),
          t(document, 'mouseup', this._fS)
        },
        Move: function (t) {
          if (bds.qa.ShortCut._isIE6()) this.beDrag.style.left = t.clientX - this._x + 'px',
          this.beDrag.style.top = t.clientY - this._y + 'px',
          this.Drag.style.left = t.clientX - this._x + 1 + 'px',
          this.Drag.style.top = t.clientY - this._y + 2 + 'px';
           else {
            var e = bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').height(),
            n = bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').width(),
            i = 0;
            document.documentElement && document.documentElement.clientWidth ? i = document.documentElement.clientWidth : document.body && (i = document.body.clientWidth);
            var o = 0;
            document.documentElement && document.documentElement.clientHeight ? o = document.documentElement.clientHeight : document.body && (o = document.body.clientHeight);
            var r = t.clientX - this._x,
            a = t.clientY - this._y,
            s = e,
            l = n;
            bds.qa.ShortCut._isIE() && (s = e, l = n),
            0 > r && (r = 0),
            r > i - l && (r = i - l),
            0 > a && (a = 0),
            a > o - s && (a = o - s),
            this.beDrag.style.left = r + 'px',
            this.beDrag.style.top = a + 'px',
            this.Drag.style.left = r + 1 + 'px',
            this.Drag.style.top = bds.qa.ShortCut._isIE() ? a + 1 + 'px' : a + 2 + 'px'
          }
          this.beDrag.style.bottom = '',
          this.beDrag.style.right = ''
        },
        Stop: function () {
          e(document, 'mousemove', this._fM),
          e(document, 'mouseup', this._fS)
        }
      },
      new bds.qa.ShortCut.SimpleDrag('fb_dialog_header', 'fb_baidu_right_dialog')
    },
    init_post_data: function () {
      bds.qa.ShortCut.fbJQ('#fb_right_canvas_save').click(function () {
        if (0 == bds.qa.ShortCut.send_img) {
          var t = bds.qa.ShortCut.fbJQ('.fb-level-type-block .fb-check').length;
          if ('' == t || 1 > t) return bds.qa.ShortCut.popwindow('请选择问题类型', 200),
          !1;
          bds.qa.ShortCut.sendCanvasData()
        }
      }),
      bds.qa.ShortCut.fbJQ('#fb_right_post_save').click(function () {
        var t = bds.qa.ShortCut.fbJQ('.fb-level-type-block .fb-check').length;
        if ('' == t || 1 > t) return bds.qa.ShortCut.popwindow('请选择问题类型', 200),
        !1;
        var e = bds.qa.ShortCut.fbJQ('#fb_shangchuan').val() || '',
        n = bds.qa.ShortCut.checkImage(e);
        return e && !n ? (bds.qa.ShortCut.popwindow('请上传PNG,JPEG,GIF等图片文件', 200), bds.qa.ShortCut.fbJQ('#fb_shangchuan').val(''), bds.qa.ShortCut.fbJQ('.fb_shangchuan_txt').html(''), !1)  : void bds.qa.ShortCut.postCrossDomainDataForm(bds.qa.ShortCut.sendDataResult)
      })
    },
    get_Snapshot: function () {
      !function (t, e, n) {
        function i(e) {
          u.logging && t.console && t.console.log && t.console.log(e)
        }
        function o(t, e, n, i, o, r) {
          var a,
          s,
          l,
          d,
          c = u.Util.getCSS(e, t, o);
          if (1 === c.length && (d = c[0], c = [
          ], c[0] = d, c[1] = d), - 1 !== c[0].toString().indexOf('%')) l = parseFloat(c[0]) / 100,
          s = n.width * l,
          'backgroundSize' !== t && (s -= (r || i).width * l);
           else if ('backgroundSize' === t) if ('auto' === c[0]) s = i.width;
           else if (c[0].match(/contain|cover/)) {
            var f = u.Util.resizeBounds(i.width, i.height, n.width, n.height, c[0]);
            s = f.width,
            a = f.height
          } else s = parseInt(c[0], 10);
           else s = parseInt(c[0], 10);
          return 'auto' === c[1] ? a = s / i.width * i.height : - 1 !== c[1].toString().indexOf('%') ? (l = parseFloat(c[1]) / 100, a = n.height * l, 'backgroundSize' !== t && (a -= (r || i).height * l))  : a = parseInt(c[1], 10),
          [
            s,
            a
          ]
        }
        function r(t, e) {
          var n = [
          ];
          return {
            storage: n,
            width: t,
            height: e,
            clip: function () {
              n.push({
                type: 'function',
                name: 'clip',
                arguments: arguments
              })
            },
            translate: function () {
              n.push({
                type: 'function',
                name: 'translate',
                arguments: arguments
              })
            },
            fill: function () {
              n.push({
                type: 'function',
                name: 'fill',
                arguments: arguments
              })
            },
            save: function () {
              n.push({
                type: 'function',
                name: 'save',
                arguments: arguments
              })
            },
            restore: function () {
              n.push({
                type: 'function',
                name: 'restore',
                arguments: arguments
              })
            },
            fillRect: function () {
              n.push({
                type: 'function',
                name: 'fillRect',
                arguments: arguments
              })
            },
            createPattern: function () {
              n.push({
                type: 'function',
                name: 'createPattern',
                arguments: arguments
              })
            },
            drawShape: function () {
              var t = [
              ];
              return n.push({
                type: 'function',
                name: 'drawShape',
                arguments: t
              }),
              {
                moveTo: function () {
                  t.push({
                    name: 'moveTo',
                    arguments: arguments
                  })
                },
                lineTo: function () {
                  t.push({
                    name: 'lineTo',
                    arguments: arguments
                  })
                },
                arcTo: function () {
                  t.push({
                    name: 'arcTo',
                    arguments: arguments
                  })
                },
                bezierCurveTo: function () {
                  t.push({
                    name: 'bezierCurveTo',
                    arguments: arguments
                  })
                },
                quadraticCurveTo: function () {
                  t.push({
                    name: 'quadraticCurveTo',
                    arguments: arguments
                  })
                }
              }
            },
            drawImage: function () {
              n.push({
                type: 'function',
                name: 'drawImage',
                arguments: arguments
              })
            },
            fillText: function () {
              n.push({
                type: 'function',
                name: 'fillText',
                arguments: arguments
              })
            },
            setVariable: function (t, e) {
              n.push({
                type: 'variable',
                name: t,
                arguments: e
              })
            }
          }
        }
        function a(t) {
          return {
            zindex: t,
            children: [
            ]
          }
        }
        var s,
        l,
        u = {
        };
        u.Util = {
        },
        u.Util.trimText = function (t) {
          return function (e) {
            return t ? t.apply(e)  : ((e || '') + '').replace(/^\s+|\s+$/g, '')
          }
        }(String.prototype.trim),
        u.Util.parseBackgroundImage = function (t) {
          var e,
          n,
          i,
          o,
          r,
          a,
          s,
          l,
          u = ' \r\n\t',
          d = [
          ],
          c = 0,
          f = 0,
          h = function () {
            e && ('"' === n.substr(0, 1) && (n = n.substr(1, n.length - 2)), n && l.push(n), '-' === e.substr(0, 1) && (o = e.indexOf('-', 1) + 1) > 0 && (i = e.substr(0, o), e = e.substr(o)), d.push({
              prefix: i,
              method: e.toLowerCase(),
              value: r,
              args: l
            })),
            l = [
            ],
            e = i = n = r = ''
          };
          h();
          for (var p = 0, g = t.length; g > p; p++) if (a = t[p], !(0 === c && u.indexOf(a) > - 1)) {
            switch (a) {
              case '"':
                s ? s === a && (s = null)  : s = a;
                break;
              case '(':
                if (s) break;
                if (0 === c) {
                  c = 1,
                  r += a;
                  continue
                }
                f++;
                break;
              case ')':
                if (s) break;
                if (1 === c) {
                  if (0 === f) {
                    c = 0,
                    r += a,
                    h();
                    continue
                  }
                  f--
                }
                break;
              case ',':
                if (s) break;
                if (0 === c) {
                  h();
                  continue
                }
                if (1 === c && 0 === f && !e.match(/^url$/i)) {
                  l.push(n),
                  n = '',
                  r += a;
                  continue
                }
            }
            r += a,
            0 === c ? e += a : n += a
          }
          return h(),
          d
        },
        u.Util.Bounds = function (t) {
          var e,
          n = {
          };
          return t.getBoundingClientRect ? (e = t.getBoundingClientRect(), n.top = e.top, n.bottom = e.bottom || e.top + e.height, n.left = e.left, n.width = e.width || e.right - e.left, n.height = e.height || e.bottom - e.top, n)  : void 0
        },
        u.Util.getCSS = function (t, i, o) {
          function r(e, n) {
            var i,
            o = t.runtimeStyle && t.runtimeStyle[e],
            r = t.style;
            return !/^-?[0-9]+\.?[0-9]*(?:px)?$/i.test(n) && /^-?\d/.test(n) && (i = r.left, o && (t.runtimeStyle.left = t.currentStyle.left), r.left = 'fontSize' === e ? '1em' : n || 0, n = r.pixelLeft + 'px', r.left = i, o && (t.runtimeStyle.left = o)),
            /^(thin|medium|thick)$/i.test(n) ? n : Math.round(parseFloat(n)) + 'px'
          }
          var a,
          d = i.match(/^background(Size|Position)$/);
          if (s !== t && (l = e.defaultView.getComputedStyle(t, null)), a = l[i], d) if (a = (a || '').split(','), a = a[o || 0] || a[0] || 'auto', a = u.Util.trimText(a).split(' '), 'backgroundSize' !== i || a[0] && !a[0].match(/cover|contain|auto/)) {
            if (a[0] = - 1 === a[0].indexOf('%') ? r(i + 'X', a[0])  : a[0], a[1] === n) {
              if ('backgroundSize' === i) return a[1] = 'auto',
              a;
              a[1] = a[0]
            }
            a[1] = - 1 === a[1].indexOf('%') ? r(i + 'Y', a[1])  : a[1]
          } else ;
           else if (/border(Top|Bottom)(Left|Right)Radius/.test(i)) {
            var c = a.split(' ');
            c.length <= 1 && (c[1] = c[0]),
            c[0] = parseInt(c[0], 10),
            c[1] = parseInt(c[1], 10),
            a = c
          }
          return a
        },
        u.Util.resizeBounds = function (t, e, n, i, o) {
          var r,
          a,
          s = n / i,
          l = t / e;
          return o && 'auto' !== o ? l > s ^ 'contain' === o ? (a = i, r = i * l)  : (r = n, a = n / l)  : (r = n, a = i),
          {
            width: r,
            height: a
          }
        },
        u.Util.BackgroundPosition = function (t, e, n, i, r) {
          var a = o('backgroundPosition', t, e, n, i, r);
          return {
            left: a[0],
            top: a[1]
          }
        },
        u.Util.BackgroundSize = function (t, e, n, i) {
          var r = o('backgroundSize', t, e, n, i);
          return {
            width: r[0],
            height: r[1]
          }
        },
        u.Util.Extend = function (t, e) {
          for (var n in t) t.hasOwnProperty(n) && (e[n] = t[n]);
          return e
        },
        u.Util.Children = function (t) {
          var e;
          try {
            e = t.nodeName && 'IFRAME' === t.nodeName.toUpperCase() ? t.contentDocument || t.contentWindow.document : function (t) {
              var e = [
              ];
              return null !== t && !function (t, e) {
                var i = t.length,
                o = 0;
                if ('number' == typeof e.length) for (var r = e.length; r > o; o++) t[i++] = e[o];
                 else for (; e[o] !== n; ) t[i++] = e[o++];
                return t.length = i,
                t
              }(e, t),
              e
            }(t.childNodes)
          } catch (o) {
            i('html2canvas.Util.Children failed with exception: ' + o.message),
            e = [
            ]
          }
          return e
        },
        u.Util.Font = function () {
          var t = {
          };
          return function (e, i, o) {
            if (t[e + '-' + i] !== n) return t[e + '-' + i];
            var r,
            a,
            s,
            l = o.createElement('div'),
            u = o.createElement('img'),
            d = o.createElement('span'),
            c = 'Hidden Text';
            return l.style.visibility = 'hidden',
            l.style.fontFamily = e,
            l.style.fontSize = i,
            l.style.margin = 0,
            l.style.padding = 0,
            o.body.appendChild(l),
            u.src = 'data:image/gif;base64,R0lGODlhAQABAIABAP///wAAACwAAAAAAQABAAACAkQBADs=',
            u.width = 1,
            u.height = 1,
            u.style.margin = 0,
            u.style.padding = 0,
            u.style.verticalAlign = 'baseline',
            d.style.fontFamily = e,
            d.style.fontSize = i,
            d.style.margin = 0,
            d.style.padding = 0,
            d.appendChild(o.createTextNode(c)),
            l.appendChild(d),
            l.appendChild(u),
            r = u.offsetTop - d.offsetTop + 1,
            l.removeChild(d),
            l.appendChild(o.createTextNode(c)),
            l.style.lineHeight = 'normal',
            u.style.verticalAlign = 'super',
            a = u.offsetTop - l.offsetTop + 1,
            s = {
              baseline: r,
              lineWidth: 1,
              middle: a
            },
            t[e + '-' + i] = s,
            o.body.removeChild(l),
            s
          }
        }(),
        function () {
          u.Generate = {
          };
          var t = [
            /^(-webkit-linear-gradient)\(([a-z\s]+)([\w\d\.\s,%\(\)]+)\)$/,
            /^(-o-linear-gradient)\(([a-z\s]+)([\w\d\.\s,%\(\)]+)\)$/,
            /^(-webkit-gradient)\((linear|radial),\s((?:\d{1,3}%?)\s(?:\d{1,3}%?),\s(?:\d{1,3}%?)\s(?:\d{1,3}%?))([\w\d\.\s,%\(\)\-]+)\)$/,
            /^(-moz-linear-gradient)\(((?:\d{1,3}%?)\s(?:\d{1,3}%?))([\w\d\.\s,%\(\)]+)\)$/,
            /^(-webkit-radial-gradient)\(((?:\d{1,3}%?)\s(?:\d{1,3}%?)),\s(\w+)\s([a-z\-]+)([\w\d\.\s,%\(\)]+)\)$/,
            /^(-moz-radial-gradient)\(((?:\d{1,3}%?)\s(?:\d{1,3}%?)),\s(\w+)\s?([a-z\-]*)([\w\d\.\s,%\(\)]+)\)$/,
            /^(-o-radial-gradient)\(((?:\d{1,3}%?)\s(?:\d{1,3}%?)),\s(\w+)\s([a-z\-]+)([\w\d\.\s,%\(\)]+)\)$/
          ];
          u.Generate.parseGradient = function (e, n) {
            var i,
            o,
            r,
            a,
            s,
            l,
            u,
            d,
            c,
            f,
            h,
            p,
            g = t.length;
            for (o = 0; g > o && !(r = e.match(t[o])); o += 1);
            if (r) switch (r[1]) {
              case '-webkit-linear-gradient':
              case '-o-linear-gradient':
                if (i = {
                  type: 'linear',
                  x0: null,
                  y0: null,
                  x1: null,
                  y1: null,
                  colorStops: [
                  ]
                }, s = r[2].match(/\w+/g)) for (l = s.length, o = 0; l > o; o += 1) switch (s[o]) {
                  case 'top':
                    i.y0 = 0,
                    i.y1 = n.height;
                    break;
                  case 'right':
                    i.x0 = n.width,
                    i.x1 = 0;
                    break;
                  case 'bottom':
                    i.y0 = n.height,
                    i.y1 = 0;
                    break;
                  case 'left':
                    i.x0 = 0,
                    i.x1 = n.width
                }
                if (null === i.x0 && null === i.x1 && (i.x0 = i.x1 = n.width / 2), null === i.y0 && null === i.y1 && (i.y0 = i.y1 = n.height / 2), s = r[3].match(/((?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\)(?:\s\d{1,3}(?:%|px))?)+/g)) for (l = s.length, u = 1 / Math.max(l - 1, 1), o = 0; l > o; o += 1) d = s[o].match(/((?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\))\s*(\d{1,3})?(%|px)?/),
                d[2] ? (a = parseFloat(d[2]), a /= '%' === d[3] ? 100 : n.width)  : a = o * u,
                i.colorStops.push({
                  color: d[1],
                  stop: a
                });
                break;
              case '-webkit-gradient':
                if (i = {
                  type: 'radial' === r[2] ? 'circle' : r[2],
                  x0: 0,
                  y0: 0,
                  x1: 0,
                  y1: 0,
                  colorStops: [
                  ]
                }, s = r[3].match(/(\d{1,3})%?\s(\d{1,3})%?,\s(\d{1,3})%?\s(\d{1,3})%?/), s && (i.x0 = s[1] * n.width / 100, i.y0 = s[2] * n.height / 100, i.x1 = s[3] * n.width / 100, i.y1 = s[4] * n.height / 100), s = r[4].match(/((?:from|to|color-stop)\((?:[0-9\.]+,\s)?(?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\)\))+/g)) for (l = s.length, o = 0; l > o; o += 1) d = s[o].match(/(from|to|color-stop)\(([0-9\.]+)?(?:,\s)?((?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\))\)/),
                a = parseFloat(d[2]),
                'from' === d[1] && (a = 0),
                'to' === d[1] && (a = 1),
                i.colorStops.push({
                  color: d[3],
                  stop: a
                });
                break;
              case '-moz-linear-gradient':
                if (i = {
                  type: 'linear',
                  x0: 0,
                  y0: 0,
                  x1: 0,
                  y1: 0,
                  colorStops: [
                  ]
                }, s = r[2].match(/(\d{1,3})%?\s(\d{1,3})%?/), s && (i.x0 = s[1] * n.width / 100, i.y0 = s[2] * n.height / 100, i.x1 = n.width - i.x0, i.y1 = n.height - i.y0), s = r[3].match(/((?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\)(?:\s\d{1,3}%)?)+/g)) for (l = s.length, u = 1 / Math.max(l - 1, 1), o = 0; l > o; o += 1) d = s[o].match(/((?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\))\s*(\d{1,3})?(%)?/),
                d[2] ? (a = parseFloat(d[2]), d[3] && (a /= 100))  : a = o * u,
                i.colorStops.push({
                  color: d[1],
                  stop: a
                });
                break;
              case '-webkit-radial-gradient':
              case '-moz-radial-gradient':
              case '-o-radial-gradient':
                if (i = {
                  type: 'circle',
                  x0: 0,
                  y0: 0,
                  x1: n.width,
                  y1: n.height,
                  cx: 0,
                  cy: 0,
                  rx: 0,
                  ry: 0,
                  colorStops: [
                  ]
                }, s = r[2].match(/(\d{1,3})%?\s(\d{1,3})%?/), s && (i.cx = s[1] * n.width / 100, i.cy = s[2] * n.height / 100), s = r[3].match(/\w+/), d = r[4].match(/[a-z\-]*/), s && d) switch (d[0]) {
                  case 'farthest-corner':
                  case 'cover':
                  case '':
                    c = Math.sqrt(Math.pow(i.cx, 2) + Math.pow(i.cy, 2)),
                    f = Math.sqrt(Math.pow(i.cx, 2) + Math.pow(i.y1 - i.cy, 2)),
                    h = Math.sqrt(Math.pow(i.x1 - i.cx, 2) + Math.pow(i.y1 - i.cy, 2)),
                    p = Math.sqrt(Math.pow(i.x1 - i.cx, 2) + Math.pow(i.cy, 2)),
                    i.rx = i.ry = Math.max(c, f, h, p);
                    break;
                  case 'closest-corner':
                    c = Math.sqrt(Math.pow(i.cx, 2) + Math.pow(i.cy, 2)),
                    f = Math.sqrt(Math.pow(i.cx, 2) + Math.pow(i.y1 - i.cy, 2)),
                    h = Math.sqrt(Math.pow(i.x1 - i.cx, 2) + Math.pow(i.y1 - i.cy, 2)),
                    p = Math.sqrt(Math.pow(i.x1 - i.cx, 2) + Math.pow(i.cy, 2)),
                    i.rx = i.ry = Math.min(c, f, h, p);
                    break;
                  case 'farthest-side':
                    'circle' === s[0] ? i.rx = i.ry = Math.max(i.cx, i.cy, i.x1 - i.cx, i.y1 - i.cy)  : (i.type = s[0], i.rx = Math.max(i.cx, i.x1 - i.cx), i.ry = Math.max(i.cy, i.y1 - i.cy));
                    break;
                  case 'closest-side':
                  case 'contain':
                    'circle' === s[0] ? i.rx = i.ry = Math.min(i.cx, i.cy, i.x1 - i.cx, i.y1 - i.cy)  : (i.type = s[0], i.rx = Math.min(i.cx, i.x1 - i.cx), i.ry = Math.min(i.cy, i.y1 - i.cy))
                }
                if (s = r[5].match(/((?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\)(?:\s\d{1,3}(?:%|px))?)+/g)) for (l = s.length, u = 1 / Math.max(l - 1, 1), o = 0; l > o; o += 1) d = s[o].match(/((?:rgb|rgba)\(\d{1,3},\s\d{1,3},\s\d{1,3}(?:,\s[0-9\.]+)?\))\s*(\d{1,3})?(%|px)?/),
                d[2] ? (a = parseFloat(d[2]), a /= '%' === d[3] ? 100 : n.width)  : a = o * u,
                i.colorStops.push({
                  color: d[1],
                  stop: a
                })
            }
            return i
          },
          u.Generate.Gradient = function (t, n) {
            if (0 !== n.width && 0 !== n.height) {
              var o,
              r,
              a,
              s,
              l = e.createElement('canvas'),
              d = l.getContext('2d');
              if (l.width = n.width, l.height = n.height, o = u.Generate.parseGradient(t, n)) if ('linear' === o.type) {
                for (r = d.createLinearGradient(o.x0, o.y0, o.x1, o.y1), a = 0, s = o.colorStops.length; s > a; a += 1) try {
                  r.addColorStop(o.colorStops[a].stop, o.colorStops[a].color)
                } catch (c) {
                  i(['failed to add color stop: ',
                  c,
                  '; tried to add: ',
                  o.colorStops[a],
                  '; stop: ',
                  a,
                  '; in: ',
                  t])
                }
                d.fillStyle = r,
                d.fillRect(0, 0, n.width, n.height)
              } else if ('circle' === o.type) {
                for (r = d.createRadialGradient(o.cx, o.cy, 0, o.cx, o.cy, o.rx), a = 0, s = o.colorStops.length; s > a; a += 1) try {
                  r.addColorStop(o.colorStops[a].stop, o.colorStops[a].color)
                } catch (c) {
                  i(['failed to add color stop: ',
                  c,
                  '; tried to add: ',
                  o.colorStops[a],
                  '; stop: ',
                  a,
                  '; in: ',
                  t])
                }
                d.fillStyle = r,
                d.fillRect(0, 0, n.width, n.height)
              } else if ('ellipse' === o.type) {
                var f = e.createElement('canvas'),
                h = f.getContext('2d'),
                p = Math.max(o.rx, o.ry),
                g = 2 * p;
                for (f.width = f.height = g, r = h.createRadialGradient(o.rx, o.ry, 0, o.rx, o.ry, p), a = 0, s = o.colorStops.length; s > a; a += 1) try {
                  r.addColorStop(o.colorStops[a].stop, o.colorStops[a].color)
                } catch (c) {
                  i(['failed to add color stop: ',
                  c,
                  '; tried to add: ',
                  o.colorStops[a],
                  '; stop: ',
                  a,
                  '; in: ',
                  t])
                }
                h.fillStyle = r,
                h.fillRect(0, 0, g, g),
                d.fillStyle = o.colorStops[a - 1].color,
                d.fillRect(0, 0, l.width, l.height),
                d.drawImage(f, o.cx - o.rx, o.cy - o.ry, 2 * o.rx, 2 * o.ry)
              }
              return l
            }
          },
          u.Generate.ListAlpha = function (t) {
            var e,
            n = '';
            do e = t % 26,
            n = String.fromCharCode(e + 64) + n,
            t /= 26;
            while (26 * t > 26);
            return n
          },
          u.Generate.ListRoman = function (t) {
            var e,
            n = [
              'M',
              'CM',
              'D',
              'CD',
              'C',
              'XC',
              'L',
              'XL',
              'X',
              'IX',
              'V',
              'IV',
              'I'
            ],
            i = [
              1000,
              900,
              500,
              400,
              100,
              90,
              50,
              40,
              10,
              9,
              5,
              4,
              1
            ],
            o = '',
            r = n.length;
            if (0 >= t || t >= 4000) return t;
            for (e = 0; r > e; e += 1) for (; t >= i[e]; ) t -= i[e],
            o += n[e];
            return o
          }
      }(),
      u.Parse = function (o, s) {
        function l() {
          return Math.max(Math.max(se.body.scrollWidth, se.documentElement.scrollWidth), Math.max(se.body.offsetWidth, se.documentElement.offsetWidth), Math.max(se.body.clientWidth, se.documentElement.clientWidth))
        }
        function d() {
          return Math.max(Math.max(se.body.scrollHeight, se.documentElement.scrollHeight), Math.max(se.body.offsetHeight, se.documentElement.offsetHeight), Math.max(se.body.clientHeight, se.documentElement.clientHeight))
        }
        function c(t, e) {
          var n = parseInt(ce(t, e), 10);
          return isNaN(n) ? 0 : n
        }
        function f(t, e, n, i, o, r) {
          'transparent' !== r && (t.setVariable('fillStyle', r), t.fillRect(e, n, i, o), ae += 1)
        }
        function h(t, e) {
          switch (e) {
            case 'lowercase':
              return t.toLowerCase();
            case 'capitalize':
              return t.replace(/(^|\s|:|-|\(|\))([a-z])/g, function (t, e, n) {
                return t.length > 0 ? e + n.toUpperCase()  : void 0
              });
            case 'uppercase':
              return t.toUpperCase();
            default:
              return t
          }
        }
        function p(t) {
          return /^(normal|none|0px)$/.test(t)
        }
        function g(t, e, n, i) {
          null !== t && u.Util.trimText(t).length > 0 && (i.fillText(t, e, n), ae += 1)
        }
        function m(t, e, n, i) {
          var o = !1,
          r = ce(e, 'fontWeight'),
          a = ce(e, 'fontFamily'),
          s = ce(e, 'fontSize');
          switch (parseInt(r, 10)) {
            case 401:
              r = 'bold';
              break;
            case 400:
              r = 'normal'
          }
          return t.setVariable('fillStyle', i),
          t.setVariable('font', [
            ce(e, 'fontStyle'),
            ce(e, 'fontVariant'),
            r,
            s,
            a
          ].join(' ')),
          t.setVariable('textAlign', o ? 'right' : 'left'),
          'none' !== n ? u.Util.Font(a, s, se)  : void 0
        }
        function b(t, e, n, i, o) {
          switch (e) {
            case 'underline':
              f(t, n.left, Math.round(n.top + i.baseline + i.lineWidth), n.width, 1, o);
              break;
            case 'overline':
              f(t, n.left, Math.round(n.top), n.width, 1, o);
              break;
            case 'line-through':
              f(t, n.left, Math.ceil(n.top + i.middle + i.lineWidth), n.width, 1, o)
          }
        }
        function v(t, e, n, i) {
          var o;
          if (le.rangeBounds) ('none' !== n || 0 !== u.Util.trimText(e).length) && (o = y(e, t.node, t.textOffset)),
          t.textOffset += e.length;
           else if (t.node && 'string' == typeof t.node.nodeValue) {
            var r = i ? t.node.splitText(e.length)  : null;
            o = x(t.node),
            t.node = r
          }
          return o
        }
        function y(t, e, n) {
          var i = se.createRange();
          return i.setStart(e, n),
          i.setEnd(e, n + t.length),
          i.getBoundingClientRect()
        }
        function x(t) {
          var e = t.parentNode,
          n = se.createElement('wrapper'),
          i = t.cloneNode(!0);
          n.appendChild(t.cloneNode(!0)),
          e.replaceChild(n, t);
          var o = u.Util.Bounds(n);
          return e.replaceChild(i, n),
          o
        }
        function C(t, e, n) {
          var i,
          o,
          r = n.ctx,
          a = ce(t, 'color'),
          l = ce(t, 'textDecoration'),
          d = ce(t, 'textAlign'),
          c = {
            node: e,
            textOffset: 0
          };
          u.Util.trimText(e.nodeValue).length > 0 && (e.nodeValue = h(e.nodeValue, ce(t, 'textTransform')), d = d.replace(['-webkit-auto'], [
            'auto'
          ]), o = e.nodeValue.split(!s.letterRendering && /^(left|right|justify|auto)$/.test(d) && p(ce(t, 'letterSpacing')) ? /(\b| )/ : ''), i = m(r, t, l, a), s.chinese && o.forEach(function (t, e) {
            /.*[\u4E00-\u9FA5].*$/.test(t) && (t = t.split(''), t.unshift(e, 1), o.splice.apply(o, t))
          }), o.forEach(function (t, e) {
            var n = v(c, t, l, e < o.length - 1);
            n && (g(t, n.left, n.bottom, r), b(r, l, n, i, a))
          }))
        }
        function w(t, e) {
          var n,
          i,
          o = se.createElement('boundelement');
          return o.style.display = 'inline',
          n = t.style.listStyleType,
          t.style.listStyleType = 'none',
          o.appendChild(se.createTextNode(e)),
          t.insertBefore(o, t.firstChild),
          i = u.Util.Bounds(o),
          t.removeChild(o),
          t.style.listStyleType = n,
          i
        }
        function S(t) {
          var e = - 1,
          n = 1,
          i = t.parentNode.childNodes;
          if (t.parentNode) {
            for (; i[++e] !== t; ) 1 === i[e].nodeType && n++;
            return n
          }
          return - 1
        }
        function _(t, e) {
          var n,
          i = S(t);
          switch (e) {
            case 'decimal':
              n = i;
              break;
            case 'decimal-leading-zero':
              n = 1 === i.toString().length ? i = '0' + i.toString()  : i.toString();
              break;
            case 'upper-roman':
              n = u.Generate.ListRoman(i);
              break;
            case 'lower-roman':
              n = u.Generate.ListRoman(i).toLowerCase();
              break;
            case 'lower-alpha':
              n = u.Generate.ListAlpha(i).toLowerCase();
              break;
            case 'upper-alpha':
              n = u.Generate.ListAlpha(i)
          }
          return n += '. '
        }
        function q(t, e, n) {
          var i,
          o,
          r,
          a = e.ctx,
          s = ce(t, 'listStyleType');
          if (/^(decimal|decimal-leading-zero|upper-alpha|upper-latin|upper-roman|lower-alpha|lower-greek|lower-latin|lower-roman)$/i.test(s)) {
            if (o = _(t, s), r = w(t, o), m(a, t, 'none', ce(t, 'color')), 'inside' !== ce(t, 'listStylePosition')) return;
            a.setVariable('textAlign', 'left'),
            i = n.left,
            g(o, i, r.bottom, a)
          }
        }
        function T(t) {
          var e = o[t];
          return e && e.succeeded === !0 ? e.img : !1
        }
        function k(t, e) {
          var n = Math.max(t.left, e.left),
          i = Math.max(t.top, e.top),
          o = Math.min(t.left + t.width, e.left + e.width),
          r = Math.min(t.top + t.height, e.top + e.height);
          return {
            left: n,
            top: i,
            width: o - n,
            height: r - i
          }
        }
        function E(t, e) {
          var n;
          return e ? 'auto' !== t ? (n = a(t), e.children.push(n), n)  : e : n = a(0)
        }
        function N(t, e, n, i, o) {
          var r = c(e, 'paddingLeft'),
          a = c(e, 'paddingTop'),
          s = c(e, 'paddingRight'),
          l = c(e, 'paddingBottom');
          H(t, n, 0, 0, n.width, n.height, i.left + r + o[3].width, i.top + a + o[0].width, i.width - (o[1].width + o[3].width + r + s), i.height - (o[0].width + o[2].width + a + l))
        }
        function D(t) {
          return ['Top',
          'Right',
          'Bottom',
          'Left'].map(function (e) {
            return {
              width: c(t, 'border' + e + 'Width'),
              color: ce(t, 'border' + e + 'Color')
            }
          })
        }
        function L(t) {
          return ['TopLeft',
          'TopRight',
          'BottomRight',
          'BottomLeft'].map(function (e) {
            return ce(t, 'border' + e + 'Radius')
          })
        }
        function A(t, e, n, i) {
          var o = function (t, e, n) {
            return {
              x: t.x + (e.x - t.x) * n,
              y: t.y + (e.y - t.y) * n
            }
          };
          return {
            start: t,
            startControl: e,
            endControl: n,
            end: i,
            subdivide: function (r) {
              var a = o(t, e, r),
              s = o(e, n, r),
              l = o(n, i, r),
              u = o(a, s, r),
              d = o(s, l, r),
              c = o(u, d, r);
              return [A(t, a, u, c),
              A(c, d, l, i)]
            },
            curveTo: function (t) {
              t.push(['bezierCurve',
              e.x,
              e.y,
              n.x,
              n.y,
              i.x,
              i.y])
            },
            curveToReversed: function (i) {
              i.push(['bezierCurve',
              n.x,
              n.y,
              e.x,
              e.y,
              t.x,
              t.y])
            }
          }
        }
        function J(t, e, n, i, o, r, a) {
          e[0] > 0 || e[1] > 0 ? (t.push(['line',
          i[0].start.x,
          i[0].start.y]), i[0].curveTo(t), i[1].curveTo(t))  : t.push(['line',
          r,
          a]),
          (n[0] > 0 || n[1] > 0) && t.push(['line',
          o[0].start.x,
          o[0].start.y])
        }
        function I(t, e, n, i, o, r, a) {
          var s = [
          ];
          return e[0] > 0 || e[1] > 0 ? (s.push(['line',
          i[1].start.x,
          i[1].start.y]), i[1].curveTo(s))  : s.push(['line',
          t.c1[0],
          t.c1[1]]),
          n[0] > 0 || n[1] > 0 ? (s.push(['line',
          r[0].start.x,
          r[0].start.y]), r[0].curveTo(s), s.push(['line',
          a[0].end.x,
          a[0].end.y]), a[0].curveToReversed(s))  : (s.push(['line',
          t.c2[0],
          t.c2[1]]), s.push(['line',
          t.c3[0],
          t.c3[1]])),
          e[0] > 0 || e[1] > 0 ? (s.push(['line',
          o[1].end.x,
          o[1].end.y]), o[1].curveToReversed(s))  : s.push(['line',
          t.c4[0],
          t.c4[1]]),
          s
        }
        function M(t, e, n) {
          var i = t.left,
          o = t.top,
          r = t.width,
          a = t.height,
          s = e[0][0],
          l = e[0][1],
          u = e[1][0],
          d = e[1][1],
          c = e[2][0],
          f = e[2][1],
          h = e[3][0],
          p = e[3][1],
          g = r - u,
          m = a - c,
          b = r - f,
          v = a - p;
          return {
            topLeftOuter: pe(i, o, s, l).topLeft.subdivide(0.5),
            topLeftInner: pe(i + n[3].width, o + n[0].width, Math.max(0, s - n[3].width), Math.max(0, l - n[0].width)).topLeft.subdivide(0.5),
            topRightOuter: pe(i + g, o, u, d).topRight.subdivide(0.5),
            topRightInner: pe(i + Math.min(g, r + n[3].width), o + n[0].width, g > r + n[3].width ? 0 : u - n[3].width, d - n[0].width).topRight.subdivide(0.5),
            bottomRightOuter: pe(i + b, o + m, f, c).bottomRight.subdivide(0.5),
            bottomRightInner: pe(i + Math.min(b, r + n[3].width), o + Math.min(m, a + n[0].width), Math.max(0, f - n[1].width), Math.max(0, c - n[2].width)).bottomRight.subdivide(0.5),
            bottomLeftOuter: pe(i, o + v, h, p).bottomLeft.subdivide(0.5),
            bottomLeftInner: pe(i + n[3].width, o + v, Math.max(0, h - n[3].width), Math.max(0, p - n[2].width)).bottomLeft.subdivide(0.5)
          }
        }
        function P(t, e, n, i, o) {
          var r = ce(t, 'backgroundClip'),
          a = [
          ];
          switch (r) {
            case 'content-box':
            case 'padding-box':
              J(a, i[0], i[1], e.topLeftInner, e.topRightInner, o.left + n[3].width, o.top + n[0].width),
              J(a, i[1], i[2], e.topRightInner, e.bottomRightInner, o.left + o.width - n[1].width, o.top + n[0].width),
              J(a, i[2], i[3], e.bottomRightInner, e.bottomLeftInner, o.left + o.width - n[1].width, o.top + o.height - n[2].width),
              J(a, i[3], i[0], e.bottomLeftInner, e.topLeftInner, o.left + n[3].width, o.top + o.height - n[2].width);
              break;
            default:
              J(a, i[0], i[1], e.topLeftOuter, e.topRightOuter, o.left, o.top),
              J(a, i[1], i[2], e.topRightOuter, e.bottomRightOuter, o.left + o.width, o.top),
              J(a, i[2], i[3], e.bottomRightOuter, e.bottomLeftOuter, o.left + o.width, o.top + o.height),
              J(a, i[3], i[0], e.bottomLeftOuter, e.topLeftOuter, o.left, o.top + o.height)
          }
          return a
        }
        function O(t, e, n) {
          var i,
          o,
          r,
          a,
          s,
          l,
          u = e.left,
          d = e.top,
          c = e.width,
          f = e.height,
          h = L(t),
          p = M(e, h, n),
          g = {
            clip: P(t, p, n, h, e),
            borders: [
            ]
          };
          for (i = 0; 4 > i; i++) if (n[i].width > 0) {
            switch (o = u, r = d, a = c, s = f - n[2].width, i) {
              case 0:
                s = n[0].width,
                l = I({
                  c1: [
                    o,
                    r
                  ],
                  c2: [
                    o + a,
                    r
                  ],
                  c3: [
                    o + a - n[1].width,
                    r + s
                  ],
                  c4: [
                    o + n[3].width,
                    r + s
                  ]
                }, h[0], h[1], p.topLeftOuter, p.topLeftInner, p.topRightOuter, p.topRightInner);
                break;
              case 1:
                o = u + c - n[1].width,
                a = n[1].width,
                l = I({
                  c1: [
                    o + a,
                    r
                  ],
                  c2: [
                    o + a,
                    r + s + n[2].width
                  ],
                  c3: [
                    o,
                    r + s
                  ],
                  c4: [
                    o,
                    r + n[0].width
                  ]
                }, h[1], h[2], p.topRightOuter, p.topRightInner, p.bottomRightOuter, p.bottomRightInner);
                break;
              case 2:
                r = r + f - n[2].width,
                s = n[2].width,
                l = I({
                  c1: [
                    o + a,
                    r + s
                  ],
                  c2: [
                    o,
                    r + s
                  ],
                  c3: [
                    o + n[3].width,
                    r
                  ],
                  c4: [
                    o + a - n[2].width,
                    r
                  ]
                }, h[2], h[3], p.bottomRightOuter, p.bottomRightInner, p.bottomLeftOuter, p.bottomLeftInner);
                break;
              case 3:
                a = n[3].width,
                l = I({
                  c1: [
                    o,
                    r + s + n[2].width
                  ],
                  c2: [
                    o,
                    r
                  ],
                  c3: [
                    o + a,
                    r + n[0].width
                  ],
                  c4: [
                    o + a,
                    r + s
                  ]
                }, h[3], h[0], p.bottomLeftOuter, p.bottomLeftInner, p.topLeftOuter, p.topLeftInner)
            }
            g.borders.push({
              args: l,
              color: n[i].color
            })
          }
          return g
        }
        function R(t, e) {
          var n = t.drawShape();
          return e.forEach(function (t, e) {
            n[0 === e ? 'moveTo' : t[0] + 'To'].apply(null, t.slice(1))
          }),
          n
        }
        function Q(t, e, n) {
          'transparent' !== n && (t.setVariable('fillStyle', n), R(t, e), t.fill(), ae += 1)
        }
        function j(t, e, n) {
          var o,
          r,
          a = se.createElement('valuewrap'),
          s = [
            'lineHeight',
            'textAlign',
            'fontFamily',
            'color',
            'fontSize',
            'paddingLeft',
            'paddingTop',
            'width',
            'height',
            'border',
            'borderLeftWidth',
            'borderTopWidth'
          ];
          s.forEach(function (e) {
            try {
              a.style[e] = ce(t, e)
            } catch (n) {
              i('html2canvas: Parse: Exception caught in renderFormValue: ' + n.message)
            }
          }),
          a.style.borderColor = 'black',
          a.style.borderStyle = 'solid',
          a.style.display = 'block',
          a.style.position = 'absolute',
          (/^(submit|reset|button|text|password)$/.test(t.type) || 'SELECT' === t.nodeName) && (a.style.lineHeight = ce(t, 'height')),
          a.style.top = e.top + 'px',
          a.style.left = e.left + 'px',
          o = 'SELECT' === t.nodeName ? (t.options[t.selectedIndex] || 0).text : t.value,
          o || (o = t.placeholder),
          r = se.createTextNode(o),
          a.appendChild(r),
          de.appendChild(a),
          C(t, r, n),
          de.removeChild(a)
        }
        function H(t) {
          t.drawImage.apply(t, Array.prototype.slice.call(arguments, 1)),
          ae += 1
        }
        function F(n, o) {
          var r = t.getComputedStyle(n, o);
          if (r && r.content && 'none' !== r.content && '-moz-alt-content' !== r.content) {
            var a = r.content + '',
            s = a.substr(0, 1);
            s === a.substr(a.length - 1) && s.match(/'|"/) && (a = a.substr(1, a.length - 2));
            var l = 'url' === a.substr(0, 3),
            d = e.createElement(l ? 'img' : 'span');
            return d.className = fe + '-before ' + fe + '-after',
            Object.keys(r).filter(z).forEach(function (t) {
              try {
                d.style[t] = r[t]
              } catch (e) {
                i(['Tried to assign readonly property ',
                t,
                'Error:',
                e])
              }
            }),
            l ? d.src = u.Util.parseBackgroundImage(a) [0].args[0] : d.innerHTML = a,
            d
          }
        }
        function z(e) {
          return isNaN(t.parseInt(e, 10))
        }
        function B(t, e) {
          var n = F(t, ':before'),
          i = F(t, ':after');
          (n || i) && (n && (t.className += ' ' + fe + '-before', t.parentNode.insertBefore(n, t), ne(n, e, !0), t.parentNode.removeChild(n), t.className = t.className.replace(fe + '-before', '').trim()), i && (t.className += ' ' + fe + '-after', t.appendChild(i), ne(i, e, !0), t.removeChild(i), t.className = t.className.replace(fe + '-after', '').trim()))
        }
        function W(t, e, n, i) {
          var o = Math.round(i.left + n.left),
          r = Math.round(i.top + n.top);
          t.createPattern(e),
          t.translate(o, r),
          t.fill(),
          t.translate( - o, - r)
        }
        function U(t, e, n, i, o, r, a, s) {
          var l = [
          ];
          l.push(['line',
          Math.round(o),
          Math.round(r)]),
          l.push(['line',
          Math.round(o + a),
          Math.round(r)]),
          l.push(['line',
          Math.round(o + a),
          Math.round(s + r)]),
          l.push(['line',
          Math.round(o),
          Math.round(s + r)]),
          R(t, l),
          t.save(),
          t.clip(),
          W(t, e, n, i),
          t.restore()
        }
        function $(t, e, n) {
          f(t, e.left, e.top, e.width, e.height, n)
        }
        function X(t, e, n, i, o) {
          var r = u.Util.BackgroundSize(t, e, i, o),
          a = u.Util.BackgroundPosition(t, e, i, o, r),
          s = ce(t, 'backgroundRepeat').split(',').map(function (t) {
            return t.trim()
          });
          switch (i = V(i, r), s = s[o] || s[0]) {
            case 'repeat-x':
              U(n, i, a, e, e.left, e.top + a.top, 99999, i.height);
              break;
            case 'repeat-y':
              U(n, i, a, e, e.left + a.left, e.top, i.width, 99999);
              break;
            case 'no-repeat':
              U(n, i, a, e, e.left + a.left, e.top + a.top, i.width, i.height);
              break;
            default:
              W(n, i, a, {
                top: e.top,
                left: e.left,
                width: i.width,
                height: i.height
              })
          }
        }
        function G(t, e, n) {
          for (var o, r = ce(t, 'backgroundImage'), a = u.Util.parseBackgroundImage(r), s = a.length; s--; ) if (r = a[s], r.args && 0 !== r.args.length) {
            var l = 'url' === r.method ? r.args[0] : r.value;
            o = T(l),
            o ? X(t, e, n, o, s)  : i('html2canvas: Error loading background:', r)
          }
        }
        function V(t, e) {
          if (t.width === e.width && t.height === e.height) return t;
          var n,
          i = se.createElement('canvas');
          return i.width = e.width,
          i.height = e.height,
          n = i.getContext('2d'),
          H(n, t, 0, 0, t.width, t.height, 0, 0, e.width, e.height),
          i
        }
        function Y(t, e, n) {
          var i = ce(e, 'opacity') * (n ? n.opacity : 1);
          return t.setVariable('globalAlpha', i),
          i
        }
        function K(t, e, n) {
          var i = r(e ? n.width : l(), e ? n.height : d()),
          o = {
            ctx: i,
            zIndex: E(ce(t, 'zIndex'), e ? e.zIndex : null),
            opacity: Y(i, t, e),
            cssPosition: ce(t, 'position'),
            borders: D(t),
            clip: e && e.clip ? u.Util.Extend({
            }, e.clip)  : null
          };
          return s.useOverflow === !0 && /(hidden|scroll|auto)/.test(ce(t, 'overflow')) === !0 && /(BODY)/i.test(t.nodeName) === !1 && (o.clip = o.clip ? k(o.clip, n)  : n),
          o.zIndex.children.push(o),
          o
        }
        function Z(t, e, n) {
          var i = {
            left: e.left + t[3].width,
            top: e.top + t[0].width,
            width: e.width - (t[1].width + t[3].width),
            height: e.height - (t[0].width + t[2].width)
          };
          return n && (i = k(i, n)),
          i
        }
        function te(t, e, n) {
          var o,
          r = u.Util.Bounds(t),
          a = ue.test(t.nodeName) ? '#efefef' : ce(t, 'backgroundColor'),
          s = K(t, e, r),
          l = s.borders,
          d = s.ctx,
          c = Z(l, r, s.clip),
          f = O(t, r, l);
          switch (R(d, f.clip), d.save(), d.clip(), c.height > 0 && c.width > 0 && ($(d, r, a), G(t, c, d)), d.restore(), f.borders.forEach(function (t) {
              Q(d, t.args, t.color)
            }), n || B(t, s), t.nodeName) {
            case 'IMG':
              (o = T(t.getAttribute('src'))) ? N(d, t, o, r, l)  : i('html2canvas: Error loading <img>:' + t.getAttribute('src'));
              break;
            case 'INPUT':
              /^(text|url|email|submit|button|reset)$/.test(t.type) && (t.value || t.placeholder).length > 0 && j(t, r, s);
              break;
            case 'TEXTAREA':
              (t.value || t.placeholder || '').length > 0 && j(t, r, s);
              break;
            case 'SELECT':
              (t.options || t.placeholder || '').length > 0 && j(t, r, s);
              break;
            case 'LI':
              q(t, s, c);
              break;
            case 'CANVAS':
              N(d, t, t, r, l)
          }
          return s
        }
        function ee(t) {
          return 'none' !== ce(t, 'display') && 'hidden' !== ce(t, 'visibility') && !t.hasAttribute('data-html2canvas-ignore')
        }
        function ne(t, e, n) {
          ee(t) && (e = te(t, e, n) || e, ue.test(t.nodeName) || u.Util.Children(t).forEach(function (i) {
            1 === i.nodeType ? ne(i, e, n)  : 3 === i.nodeType && C(t, i, e)
          }))
        }
        function ie(t, e) {
          function n(t) {
            var e,
            i,
            o,
            r,
            s,
            l = u.Util.Children(t),
            d = l.length;
            for (s = 0; d > s; s += 1) if (r = l[s], 3 === r.nodeType) a += r.nodeValue.replace(/</g, '&lt;').replace(/>/g, '&gt;');
             else if (1 === r.nodeType && !/^(script|meta|title)$/.test(r.nodeName.toLowerCase())) {
              if (a += '<' + r.nodeName.toLowerCase(), r.hasAttributes()) for (e = r.attributes, o = e.length, i = 0; o > i; i += 1) a += ' ' + e[i].name + '="' + e[i].value + '"';
              a += '>',
              n(r),
              a += '</' + r.nodeName.toLowerCase() + '>'
            }
          }
          var i = new Image,
          o = l(),
          r = d(),
          a = '';
          n(t),
          i.src = [
            'data:image/svg+xml,',
            '<svg xmlns=\'http://www.w3.org/2000/svg\' version=\'1.1\' width=\'' + o + '\' height=\'' + r + '\'>',
            '<foreignObject width=\'' + o + '\' height=\'' + r + '\'>',
            '<html xmlns=\'http://www.w3.org/1999/xhtml\' style=\'margin:0;\'>',
            a.replace(/\#/g, '%23'),
            '</html>',
            '</foreignObject>',
            '</svg>'
          ].join(''),
          i.onload = function () {
            e.svgRender = i
          }
        }
        function oe() {
          var t = te(re, null);
          return le.svgRendering && ie(e.documentElement, t),
          Array.prototype.slice.call(re.children, 0).forEach(function (e) {
            ne(e, t)
          }),
          t.backgroundColor = ce(e.documentElement, 'backgroundColor'),
          de.removeChild(he),
          t
        }
        bds.qa.ShortCut.scrollTop = t.pageYOffset || e.documentElement.scrollTop || e.body.scrollTop,
        t.scroll(0, 0);
        var re = s.elements === n ? e.body : s.elements[0],
        ae = 0,
        se = re.ownerDocument,
        le = u.Util.Support(s, se),
        ue = new RegExp('(' + s.ignoreElements + ')'),
        de = se.body,
        ce = u.Util.getCSS,
        fe = '___html2canvas___pseudoelement',
        he = se.createElement('style');
        he.innerHTML = '.' + fe + '-before:before { content: "" !important; display: none !important; }.' + fe + '-after:after { content: "" !important; display: none !important; }',
        de.appendChild(he),
        o = o || {
        };
        var pe = function (t) {
          return function (e, n, i, o) {
            var r = i * t,
            a = o * t,
            s = e + i,
            l = n + o;
            return {
              topLeft: A({
                x: e,
                y: l
              }, {
                x: e,
                y: l - a
              }, {
                x: s - r,
                y: n
              }, {
                x: s,
                y: n
              }),
              topRight: A({
                x: e,
                y: n
              }, {
                x: e + r,
                y: n
              }, {
                x: s,
                y: l - a
              }, {
                x: s,
                y: l
              }),
              bottomRight: A({
                x: s,
                y: n
              }, {
                x: s,
                y: n + a
              }, {
                x: e + r,
                y: l
              }, {
                x: e,
                y: l
              }),
              bottomLeft: A({
                x: s,
                y: l
              }, {
                x: s - r,
                y: l
              }, {
                x: e,
                y: n + a
              }, {
                x: e,
                y: n
              })
            }
          }
        }(4 * ((Math.sqrt(2) - 1) / 3));
        return oe()
      },
      u.Preload = function (o) {
        function r(t) {
          T.href = t,
          T.href = T.href;
          var e = T.protocol + T.host;
          return e === m
        }
        function a() {
          i('html2canvas: start: images: ' + x.numLoaded + ' / ' + x.numTotal + ' (failed: ' + x.numFailed + ')'),
          !x.firstRun && x.numLoaded >= x.numTotal && (i('Finished loading images: # ' + x.numTotal + ' (failed: ' + x.numFailed + ')'), 'function' == typeof o.complete && o.complete(x))
        }
        function s(e, i, r) {
          var s,
          l,
          u = o.proxy;
          T.href = e,
          e = T.href,
          s = 'html2canvas_' + C++,
          r.callbackname = s,
          u += u.indexOf('?') > - 1 ? '&' : '?',
          u += 'url=' + encodeURIComponent(e) + '&callback=' + s,
          l = S.createElement('script'),
          t[s] = function (e) {
            'error:' === e.substring(0, 6) ? (r.succeeded = !1, x.numLoaded++, x.numFailed++, a())  : (g(i, r), i.src = e),
            t[s] = n;
            try {
              delete t[s]
            } catch (o) {
            }
            l.parentNode.removeChild(l),
            l = null,
            delete r.script,
            delete r.callbackname
          },
          l.setAttribute('type', 'text/javascript'),
          l.setAttribute('src', u),
          r.script = l,
          t.document.body.appendChild(l)
        }
        function l(e, n) {
          var i = t.getComputedStyle(e, n),
          o = i.content;
          'url' === o.substr(0, 3) && b.loadImage(u.Util.parseBackgroundImage(o) [0].args[0]),
          h(i.backgroundImage, e)
        }
        function d(t) {
          l(t, ':before'),
          l(t, ':after')
        }
        function c(t, e) {
          var i = u.Generate.Gradient(t, e);
          i !== n && (x[t] = {
            img: i,
            succeeded: !0
          }, x.numTotal++, x.numLoaded++, a())
        }
        function f(t) {
          return t && t.method && t.args && t.args.length > 0
        }
        function h(t, e) {
          var i;
          u.Util.parseBackgroundImage(t).filter(f).forEach(function (t) {
            'url' === t.method ? b.loadImage(t.args[0])  : t.method.match(/\-?gradient$/) && (i === n && (i = u.Util.Bounds(e)), c(t.value, i))
          })
        }
        function p(t) {
          var e = !1;
          try {
            u.Util.Children(t).forEach(function (t) {
              p(t)
            })
          } catch (o) {
          }
          try {
            e = t.nodeType
          } catch (r) {
            e = !1,
            i('html2canvas: failed to access some element\'s nodeType - Exception: ' + r.message)
          }
          if (1 === e || e === n) {
            d(t);
            try {
              h(u.Util.getCSS(t, 'backgroundImage'), t)
            } catch (o) {
              i('html2canvas: failed to get background-image - Exception: ' + o.message)
            }
            h(t)
          }
        }
        function g(e, i) {
          e.onload = function () {
            i.timer !== n && t.clearTimeout(i.timer),
            x.numLoaded++,
            i.succeeded = !0,
            e.onerror = e.onload = null,
            a()
          },
          e.onerror = function () {
            if ('anonymous' === e.crossOrigin && (t.clearTimeout(i.timer), o.proxy)) {
              var n = e.src;
              return e = new Image,
              i.img = e,
              e.src = n,
              void s(e.src, e, i)
            }
            x.numLoaded++,
            x.numFailed++,
            i.succeeded = !1,
            e.onerror = e.onload = null,
            a()
          }
        }
        var m,
        b,
        v,
        y,
        x = {
          numLoaded: 0,
          numFailed: 0,
          numTotal: 0,
          cleanupDone: !1
        },
        C = 0,
        w = o.elements[0] || e.body,
        S = w.ownerDocument,
        _ = S.images,
        q = _.length,
        T = S.createElement('a'),
        k = function (t) {
          return t.crossOrigin !== n
        }(new Image);
        for (T.href = t.location.href, m = T.protocol + T.host, b = {
          loadImage: function (e) {
            var i,
            a;
            e && x[e] === n && (i = new Image, e.match(/data:image\/.*;base64,/i) ? (i.src = e.replace(/url\(['"]{0,}|['"]{0,}\)$/gi, ''), a = x[e] = {
              img: i
            }, x.numTotal++, g(i, a))  : r(e) || o.allowTaint === !0 ? (a = x[e] = {
              img: i
            }, x.numTotal++, g(i, a), i.src = e)  : k && !o.allowTaint && o.useCORS ? (i.crossOrigin = 'anonymous', a = x[e] = {
              img: i
            }, x.numTotal++, g(i, a), i.src = e, i.customComplete = function () {
              this.img.complete ? this.img.onerror()  : this.timer = t.setTimeout(this.img.customComplete, 100)
            }.bind(a), i.customComplete())  : o.proxy && (a = x[e] = {
              img: i
            }, x.numTotal++, s(e, i, a)))
          },
          cleanupDOM: function (r) {
            var s,
            l;
            if (!x.cleanupDone) {
              i(r && 'string' == typeof r ? 'html2canvas: Cleanup because: ' + r : 'html2canvas: Cleanup after timeout: ' + o.timeout + ' ms.');
              for (l in x) if (x.hasOwnProperty(l) && (s = x[l], 'object' == typeof s && s.callbackname && s.succeeded === n)) {
                t[s.callbackname] = n;
                try {
                  delete t[s.callbackname]
                } catch (u) {
                }
                s.script && s.script.parentNode && (s.script.setAttribute('src', 'about:blank'), s.script.parentNode.removeChild(s.script)),
                x.numLoaded++,
                x.numFailed++,
                i('html2canvas: Cleaned up failed img: \'' + l + '\' Steps: ' + x.numLoaded + ' / ' + x.numTotal)
              }
              t.stop !== n ? t.stop()  : e.execCommand !== n && e.execCommand('Stop', !1),
              e.close !== n && e.close(),
              x.cleanupDone = !0,
              r && 'string' == typeof r || a()
            }
          },
          renderingDone: function () {
            y && t.clearTimeout(y)
          }
        }, o.timeout > 0 && (y = t.setTimeout(b.cleanupDOM, o.timeout)), i('html2canvas: Preload starts: finding background-images'), x.firstRun = !0, p(w), i('html2canvas: Preload: Finding images'), v = 0; q > v; v += 1) b.loadImage(_[v].getAttribute('src'));
        return x.firstRun = !1,
        i('html2canvas: Preload: Done.'),
        x.numTotal === x.numLoaded && a(),
        b
      },
      u.Renderer = function (t, i) {
        function o(t) {
          var e = [
          ],
          n = function (t) {
            var i = [
            ],
            o = [
            ];
            t.children.forEach(function (t) {
              t.children && t.children.length > 0 ? (i.push(t), o.push(t.zindex))  : e.push(t)
            }),
            o.sort(function (t, e) {
              return t - e
            }),
            o.forEach(function (t) {
              var e;
              i.some(function (n, i) {
                return e = i,
                n.zindex === t
              }),
              n(i.splice(e, 1) [0])
            })
          };
          return t && t.zIndex && n(t.zIndex),
          e
        }
        function r(t) {
          var e;
          if ('string' == typeof i.renderer && u.Renderer[t] !== n) e = u.Renderer[t](i);
           else {
            if ('function' != typeof t) throw new Error('Unknown renderer');
            e = t(i)
          }
          if ('function' != typeof e) throw new Error('Invalid renderer defined');
          return e
        }
        return r(i.renderer) (t, i, e, o(t), u)
      },
      u.Util.Support = function (t, e) {
        function o() {
          var t = new Image,
          o = e.createElement('canvas'),
          r = o.getContext === n ? !1 : o.getContext('2d');
          if (r === !1) return !1;
          o.width = o.height = 10,
          t.src = [
            'data:image/svg+xml,',
            '<svg xmlns=\'http://www.w3.org/2000/svg\' width=\'10\' height=\'10\'>',
            '<foreignObject width=\'10\' height=\'10\'>',
            '<div xmlns=\'http://www.w3.org/1999/xhtml\' style=\'width:10;height:10;\'>',
            'sup',
            '</div>',
            '</foreignObject>',
            '</svg>'
          ].join('');
          try {
            r.drawImage(t, 0, 0),
            o.toDataURL()
          } catch (a) {
            return !1
          }
          return i('html2canvas: Parse: SVG powered rendering available'),
          !0
        }
        function r() {
          var t,
          n,
          i,
          o,
          r = !1;
          return e.createRange && (t = e.createRange(), t.getBoundingClientRect && (n = e.createElement('boundtest'), n.style.height = '123px', n.style.display = 'block', e.body.appendChild(n), t.selectNode(n), i = t.getBoundingClientRect(), o = i.height, 123 === o && (r = !0), e.body.removeChild(n))),
          r
        }
        return {
          rangeBounds: r(),
          svgRendering: t.svgRendering && o()
        }
      },
      t.html2canvas = function (e, n) {
        e = e.length ? e : [
          e
        ];
        var o,
        r,
        a = {
          logging: !1,
          elements: e,
          background: '#fff',
          proxy: null,
          timeout: 0,
          useCORS: !1,
          allowTaint: !1,
          svgRendering: !1,
          ignoreElements: 'IFRAME|OBJECT|PARAM',
          useOverflow: !0,
          letterRendering: !1,
          chinese: !1,
          width: null,
          height: null,
          taintTest: !0,
          renderer: 'Canvas'
        };
        return a = u.Util.Extend(n, a),
        u.logging = a.logging,
        a.complete = function (t) {
          ('function' != typeof a.onpreloaded || a.onpreloaded(t) !== !1) && (o = u.Parse(t, a), ('function' != typeof a.onparsed || a.onparsed(o) !== !1) && (r = u.Renderer(o, a), 'function' == typeof a.onrendered && a.onrendered(r)))
        },
        t.setTimeout(function () {
          u.Preload(a)
        }, 0),
        {
          render: function (t, e) {
            return u.Renderer(t, u.Util.Extend(e, a))
          },
          parse: function (t, e) {
            return u.Parse(t, u.Util.Extend(e, a))
          },
          preload: function (t) {
            return u.Preload(u.Util.Extend(t, a))
          },
          log: i
        }
      },
      t.html2canvas.log = i,
      t.html2canvas.Renderer = {
        Canvas: n
      },
      u.Renderer.Canvas = function (t) {
        function o(t, e) {
          t.beginPath(),
          e.forEach(function (e) {
            t[e.name].apply(t, e.arguments)
          }),
          t.closePath()
        }
        function r(t) {
          if ( - 1 === u.indexOf(t.arguments[0].src)) {
            c.drawImage(t.arguments[0], 0, 0);
            try {
              c.getImageData(0, 0, 1, 1)
            } catch (e) {
              return d = l.createElement('canvas'),
              c = d.getContext('2d'),
              !1
            }
            u.push(t.arguments[0].src)
          }
          return !0
        }
        function a(t) {
          return 'transparent' === t || 'rgba(0, 0, 0, 0)' === t
        }
        function s(e, n) {
          switch (n.type) {
            case 'variable':
              e[n.name] = n.arguments;
              break;
            case 'function':
              if ('createPattern' === n.name) {
                if (n.arguments[0].width > 0 && n.arguments[0].height > 0) try {
                  e.fillStyle = e.createPattern(n.arguments[0], 'repeat')
                } catch (a) {
                  i('html2canvas: Renderer: Error creating pattern', a.message)
                }
              } else 'drawShape' === n.name ? o(e, n.arguments)  : 'drawImage' === n.name ? n.arguments[8] > 0 && n.arguments[7] > 0 && (!t.taintTest || t.taintTest && r(n)) && e.drawImage.apply(e, n.arguments)  : e[n.name].apply(e, n.arguments)
          }
        }
        t = t || {
        };
        var l = e,
        u = [
        ],
        d = e.createElement('canvas'),
        c = d.getContext('2d'),
        f = t.canvas || l.createElement('canvas');
        return function (t, e, o, r, l) {
          var u,
          d,
          c,
          h,
          p,
          g,
          m = f.getContext('2d');
          if (f.width = f.style.width = e.width || t.ctx.width, f.height = f.style.height = e.height || t.ctx.height, g = m.fillStyle, m.fillStyle = a(t.backgroundColor) && e.background !== n ? e.background : t.backgroundColor, m.fillRect(0, 0, f.width, f.height), m.fillStyle = g, e.svgRendering && t.svgRender !== n) m.drawImage(t.svgRender, 0, 0);
           else for (d = 0, c = r.length; c > d; d += 1) u = r.splice(0, 1) [0],
          u.canvasPosition = u.canvasPosition || {
          },
          m.textBaseline = 'bottom',
          u.clip && (m.save(), m.beginPath(), m.rect(u.clip.left, u.clip.top, u.clip.width, u.clip.height), m.clip()),
          u.ctx.storage && u.ctx.storage.forEach(s.bind(null, m)),
          u.clip && m.restore();
          return i('html2canvas: Renderer: Canvas renderer done - returning canvas obj'),
          c = e.elements.length,
          1 === c && 'object' == typeof e.elements[0] && 'BODY' !== e.elements[0].nodeName ? (p = l.Util.Bounds(e.elements[0]), h = o.createElement('canvas'), h.width = p.width, h.height = p.height, m = h.getContext('2d'), m.drawImage(f, p.left, p.top, p.width, p.height, 0, 0, p.width, p.height), f = null, h)  : f
        }
      }
    }(window, document);
    var t = function () {
      html2canvas(document.body, {
        proxy: bds.qa.ShortCut.base_url_path + '/getProxyImage.php',
        onrendered: function (t) {
          t.id = 'fb_right_dialog_pagecanvas2',
          t.style.top = 0,
          t.style.left = 0,
          t.style.position = 'absolute',
          document.body.appendChild(t),
          bds.qa.ShortCut.img_data = t.toDataURL('image/png')
        }
      })
    };
    t()
  },
  init_img_render: function () {
    bds.qa.ShortCut.send_img = !0;
    var t = function () {
      var t = {
        init: function () {
          var e = function () {
            var e = document.getElementById('fb_right_dialog_canvas');
            e && bds.qa.ShortCut.fbJQ(e).remove(),
            bds.qa.ShortCut.fbJQ('#fb_baidu_wizard').remove();
            var n = document.createElement('canvas'),
            i = Math.max(Math.max(document.body.scrollHeight, document.documentElement.scrollHeight), Math.max(document.body.offsetHeight, document.documentElement.offsetHeight), Math.max(document.body.clientHeight, document.documentElement.clientHeight)),
            o = Math.max(Math.max(document.body.scrollWidth, document.documentElement.scrollWidth), Math.max(document.body.offsetWidth, document.documentElement.offsetWidth), Math.max(document.body.clientWidth, document.documentElement.clientWidth));
            n.width = o,
            n.height = i,
            n.style.top = 0,
            n.style.left = 0,
            n.style.position = 'absolute',
            n.style.zIndex = '999989',
            n.id = 'fb_right_dialog_canvas',
            document.body.appendChild(n),
            t.load(),
            t.bind(),
            bds.qa.ShortCut.fbJQ('#fb_right_dialog_canvas').css('cursor', 'crosshair')
          };
          e()
        },
        load: function () {
          this.x = [
          ],
          this.y = [
          ],
          this.clickDrag = [
          ],
          this.Rectangles = [
          ],
          this.rectangleNo = '',
          this.lock = !1,
          this.hasCover = !1,
          this.canvas = document.getElementById('fb_right_dialog_canvas'),
          this.cxt = this.canvas.getContext('2d'),
          this.cxt.fillStyle = 'rgba(85,85,85,0.5)',
          this.cxt.fillRect(0, 0, document.body.clientWidth, document.body.scrollHeight > window.screen.availHeight ? document.body.scrollHeight : window.screen.availHeight),
          this.cxt.globalCompositeOperation = 'destination-out',
          this.StartEvent = 'mousedown',
          this.MoveEvent = 'mousemove',
          this.EndEvent = 'mouseup'
        },
        bind: function () {
          var t = this;
          bds.qa.ShortCut.fbJQ('#fb_right_canvas_save').click(function () {
            if (1 == bds.qa.ShortCut.send_img) {
              var t = bds.qa.ShortCut.fbJQ('.fb-level-type-block .fb-check').length;
              if ('' == t || 1 > t) return bds.qa.ShortCut.popwindow('请选择问题类型', 200),
              !1;
              bds.qa.ShortCut.sendCanvasData()
            }
          }),
          this.canvas['on' + t.StartEvent] = function (e) {
            var n = t.touch ? e.touches[0] : e,
            i = window.pageYOffset || document.documentElement.scrollTop || document.body.scrollTop;
            if (t.movePoint(n.clientX - n.target.offsetLeft, n.clientY - n.target.offsetTop + i), t.hasCover) {
              var o = '#fb_cancel_' + t.rectangleNo;
              bds.qa.ShortCut.fbJQ(o).remove()
            }
            t.lock = !0
          },
          this.canvas['on' + t.MoveEvent] = function (e) {
            e = e ? e : window.event;
            var n = t.touch ? e.touches[0] : e,
            i = n.clientX - n.target.offsetLeft,
            o = window.pageYOffset || document.documentElement.scrollTop || document.body.scrollTop,
            r = n.clientY - n.target.offsetTop + o;
            t.lock ? (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').hide(), t.movePoint(i, r, !0), t.drawRectangle())  : t.showRectangle(i, r, t)
          },
          this.canvas['on' + t.EndEvent] = function () {
            bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').show(),
            t.lock = !1,
            t.Rectangles.push([t.x[0],
            t.y[0],
            t.x[t.x.length - 1] - t.x[0],
            t.y[t.y.length - 1] - t.y[0]]),
            t.x = [
            ],
            t.y = [
            ],
            t.clickDrag = [
            ],
            t.drawRectangle()
          }
        },
        createCancel: function (t, e, n) {
          var i = document.createElement('div');
          i.id = 'fb_cancel_' + n.rectangleNo,
          i.className = 'fb_cancel_flag',
          i.style.background = 'url(' + bds.qa.ShortCut.base_url_path + '/feedback/images/cancel.png)',
          i.style.top = parseInt(t - 8) + 'px',
          i.style.left = parseInt(e - 8) + 'px',
          i.style.width = '16px',
          i.style.height = '16px',
          i.style.position = 'absolute',
          i.style.zIndex = '999989',
          i.style.cursor = 'pointer',
          bds.qa.ShortCut.fbJQ('body').append(i),
          bds.qa.ShortCut.fbJQ('#fb_cancel_' + n.rectangleNo).click(function () {
            n.Rectangles[n.rectangleNo] = 0,
            bds.qa.ShortCut.fbJQ('#fb_cancel_' + n.rectangleNo).remove(),
            n.hasCover = !1,
            n.drawRectangle()
          })
        },
        movePoint: function (t, e) {
          this.x.push(t),
          this.y.push(e),
          this.clickDrag.push(e)
        },
        showRectangle: function (t, e, n) {
          for (i = 0; i < this.Rectangles.length; i++) {
            var o = n.hasCover ? this.Rectangles[n.rectangleNo] : this.Rectangles[i],
            r = o[3] > 0 ? o[1] : o[1] + o[3],
            a = o[3] > 0 ? o[1] + o[3] : o[1],
            s = o[2] > 0 ? o[0] : o[0] + o[2],
            l = o[2] > 0 ? o[0] + o[2] : o[0];
            if (n.hasCover) {
              var u = s > t || t > l || r > e || e > a;
              if (u) {
                this.cxt.globalAlpha = 1,
                this.cxt.globalCompositeOperation = 'source-over',
                this.cxt.strokeStyle = '#FF7F7D',
                this.cxt.lineWidth = '5',
                this.cxt.strokeRect(o[0], o[1], o[2], o[3]),
                this.cxt.globalCompositeOperation = 'destination-out',
                this.cxt.fillStyle = 'rgba(255,255,255,1)',
                this.cxt.fillRect(o[0], o[1], o[2], o[3]),
                n.hasCover = !1;
                var d = '#fb_cancel_' + n.rectangleNo;
                bds.qa.ShortCut.fbJQ(d).remove()
              }
            } else {
              var c = t > s && l > t && e > r && a > e;
              if (c) {
                this.cxt.globalCompositeOperation = 'source-over',
                this.cxt.strokeStyle = '#FF7F7D',
                this.cxt.lineWidth = '5',
                this.cxt.strokeRect(o[0], o[1], o[2], o[3]),
                this.cxt.globalCompositeOperation = 'destination-out',
                this.cxt.fillStyle = 'rgba(255,255,255,1)',
                this.cxt.fillRect(o[0], o[1], o[2], o[3]),
                n.hasCover = !0,
                n.rectangleNo = i,
                n.createCancel(r, l, n);
                break
              }
            }
          }
        },
        drawRectangle: function () {
          var t = this.x[this.x.length - 1] - this.x[0],
          e = this.y[this.y.length - 1] - this.y[0];
          this.clear(),
          this.drawBackground();
          var n = this.Rectangles.length;
          if (this.cxt.globalAlpha = 1, n) for (n -= 1; n >= 0; n--) {
            var i = this.Rectangles[n],
            o = i[0],
            r = i[1],
            a = i[2],
            s = i[3];
            this.cxt.globalCompositeOperation = 'source-over',
            this.cxt.strokeStyle = '#FF7F7D',
            this.cxt.lineWidth = '5',
            this.cxt.strokeRect(o, r, a, s),
            this.cxt.globalCompositeOperation = 'destination-out',
            this.cxt.fillStyle = 'rgba(255,255,255,1)',
            this.cxt.fillRect(o, r, a, s)
          }
          this.cxt.globalCompositeOperation = 'source-over',
          this.cxt.strokeStyle = '#FF7F7D',
          this.cxt.lineWidth = '5',
          this.cxt.strokeRect(this.x[0], this.y[0], t, e),
          this.cxt.globalCompositeOperation = 'destination-out',
          this.cxt.fillStyle = 'rgba(255,255,255,1)',
          this.cxt.fillRect(this.x[0], this.y[0], t, e)
        },
        clear: function () {
          this.cxt.clearRect(0, 0, this.w, this.h)
        },
        removeNode: function (t) {
          t && t.parentNode && t.parentNode.removeChild(t)
        },
        drawBackground: function () {
          this.cxt.globalCompositeOperation = 'copy',
          this.cxt.fillStyle = 'rgba(85,85,85,0.5)',
          this.cxt.fillRect(0, 0, document.body.clientWidth, document.body.scrollHeight > window.screen.availHeight ? document.body.scrollHeight : window.screen.availHeight),
          this.cxt.globalCompositeOperation = 'destination-out'
        }
      };
      t.init()
    };
    t()
  },
  _getNecData: function () {
    var t = bds.qa.ShortCut.fbJQ('#feedback_email').val();
    t == bds.qa.ShortCut.emailPlaceholder && (t = '');
    var e = bds.qa.ShortCut.fbJQ('#fb_des_content').val();
    e == bds.qa.ShortCut.issuePlaceholder && (e = '');
    var n = {
      product_id: bds.qa.ShortCut.product_id,
      userAgent: navigator.userAgent,
      issuedesc: encodeURIComponent(e),
      issueimage: bds.qa.ShortCut.img_data,
      issuehtml: encodeURIComponent(bds.qa.ShortCut.fbJQ('html').html()),
      email: t,
      documentcookie: document.cookie,
      url: document.location.href
    };
    return n
  },
  _getProData: function (t) {
    bds.qa.ShortCut.pro_data = {
      level1_type_id: bds.qa.ShortCut.fbJQ('.fb-level-type-block .fb-check').attr('data-value'),
      query: t,
      fb_from: 'pc'
    }
  },
  sendCanvasData: function () {
    var t = bds.qa.ShortCut._getNecData();
    bds.qa.ShortCut._getProData(bds.qa.ShortCut.queryWord),
    bds.qa.ShortCut.sendDataResult(!0),
    bds.qa.ShortCut.defaultCut ? bds.qa.ShortCut.get_Snapshot()  : '';
    var e = '',
    n = function () {
      var o = document.getElementById('fb_right_dialog_pagecanvas2');
      o ? (t.issueimage = bds.qa.ShortCut.img_data, i(), window.clearTimeout(e))  : e = setTimeout(n, 1000)
    },
    i = function () {
      var e = bds.qa.ShortCut.pro_data,
      n = bds.qa.ShortCut.fbJQ('#shujufasongzhong');
      n || bds.qa.ShortCut.fbJQ('.fb-action').append('<div id="shujufasongzhong" style="color:grey;text-align:left;">数据发送中...</div>');
      var i = document.createElement('iframe'),
      o = 'fb_qa_feedback_frame_id';
      bds.qa.ShortCut.fbJQ('#fb_qa_feedback_frame_id').remove(),
      document.body.appendChild(i),
      i.style.display = 'none',
      i.contentWindow.name = o;
      var r = document.createElement('form');
      r.enctype = 'multipart/form-data',
      r.target = o,
      r.action = bds.qa.ShortCut.base_url_path + '/index.php/feedback/zx/getData',
      r.method = 'POST';
      var a = document.createElement('input');
      a.type = 'hidden',
      a.name = 'necData',
      a.value = JSON.stringify(t),
      r.appendChild(a);
      var a = document.createElement('input');
      a.type = 'hidden',
      a.name = 'proData',
      a.value = JSON.stringify(e),
      r.appendChild(a),
      document.body.appendChild(r),
      r.submit(),
      i.onload = function () {
        bds.qa.ShortCut.fbJQ(i).remove(),
        bds.qa.ShortCut.fbJQ(r).remove(),
        bds.qa.ShortCut._removeAllElement()
      }
    };
    bds.qa.ShortCut.defaultCut ? n()  : i()
  },
  postCrossDomainDataForm: function () {
    bds.qa.ShortCut._getProData(bds.qa.ShortCut.queryWord);
    var t = bds.qa.ShortCut._getNecData(),
    e = bds.qa.ShortCut.pro_data,
    n = document.createElement('iframe'),
    i = 'fb_qa_feedback_frame_id';
    bds.qa.ShortCut.fbJQ('#fb_qa_feedback_frame_id').remove(),
    document.body.appendChild(n),
    n.style.display = 'none',
    n.contentWindow.name = i;
    var o = document.getElementById('fb_right_post_form');
    if (o) {
      o.enctype = 'multipart/form-data',
      o.target = i,
      o.method = 'POST',
      o.action = bds.qa.ShortCut.base_url_path + '/index.php/feedback/zx/getData';
      var r = document.createElement('input');
      r.type = 'hidden',
      r.name = 'necData',
      r.value = JSON.stringify(t),
      o.appendChild(r);
      var r = document.createElement('input');
      r.type = 'hidden',
      r.name = 'proData',
      r.value = JSON.stringify(e),
      o.appendChild(r),
      o.submit(),
      bds.qa.ShortCut.sendDataResult(!0),
      n.onload = function () {
        bds.qa.ShortCut.fbJQ(n).remove(),
        bds.qa.ShortCut.fbJQ(o).remove(),
        bds.qa.ShortCut._removeAllElement()
      }
    }
  },
  sendDataResult: function () {
    return bds.qa.ShortCut.popwindowEnd(),
    !0
  },
  _disposeHttps: function () {
    var t = bds && bds.util && bds.util.domain && bds.util.domain.get;
    t && (bds.qa.ShortCut.base_url_path = bds.util.domain.get('http://f3.baidu.com'))
  },
  imgLog: function (t) {
    var e = 'imglog__' + (new Date).getTime(),
    n = window[e] = new Image;
    n.onload = n.onerror = function () {
      window[e] = null
    },
    n.src = t,
    n = null
  },
  checkImage: function (t) {
    var e = t.lastIndexOf('.'),
    n = t.substring(e + 1).toUpperCase();
    return !('JPG' != n && 'GIF' != n && 'PNG' != n && 'JPEG' != n)
  },
  _isIE: function () {
    var t = document.all ? !0 : !1;
    return t
  },
  _isIE6: function () {
    var t = document.all ? !0 : !1,
    e = t && !window.XMLHttpRequest;
    return e
  },
  _isIE7: function () {
    var t = navigator.appName,
    e = navigator.appVersion,
    n = e.split(';');
    if (n.length <= 1) return !1;
    var i = n[1].replace(/[ ]/g, '');
    return 'Microsoft Internet Explorer' == t && 'MSIE7.0' == i
  },
  _identifyBrowser: function () {
    if (window.ActiveXObject) return !1;
    try {
      var t = document.createElement('canvas').getContext('2d');
      return t = null,
      !0
    } catch (e) {
      return !1
    }
  },
  _checkFileType: function (t) {
    var e = t.value,
    n = bds.qa.ShortCut.checkImage(e);
    if (!n) return bds.qa.ShortCut.popwindow('请上传PNG,JPEG,JPG,GIF等图片文件', 100),
    bds.qa.ShortCut.fbJQ('#fb_shangchuan').val(''),
    bds.qa.ShortCut.fbJQ('.fb_shangchuan_txt').html(''),
    !1;
    var i = t.value.lastIndexOf('\\');
    document.getElementById('fb_shangchuan_txt').innerHTML = t.value.substring(i + 1)
  },
  hidwindow: function () {
    bds.qa.ShortCut.fbJQ('#fb_popwindow').slideUp(500);
    var t = function () {
      bds.qa.ShortCut.fbJQ('#fb_popwindow').remove()
    };
    setTimeout(t, 1000)
  },
  _removeAllElement: function () {
    bds.qa.ShortCut.fbJQ('#ShortCut_wizard').remove(),
    bds.qa.ShortCut.fbJQ('#fb_base_wizard_canvas').remove(),
    bds.qa.ShortCut.fbJQ('#fb_baidu_wizard').remove(),
    bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').remove(),
    bds.qa.ShortCut.fbJQ('#fb_right_post_form').remove(),
    bds.qa.ShortCut.fbJQ('#fb_popwindow').remove(),
    bds.qa.ShortCut.fbJQ('#fb_right_dialog_canvas').remove(),
    bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas').remove(),
    bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas2').remove(),
    bds.qa.ShortCut.fbJQ('.fb_cancel_flag').remove(),
    bds.qa.ShortCut.is_feedbacking = !1
  },
  hidwindowEnd: function () {
    'pad' == bds.qa.ShortCut.skinStyle ? (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('display', 'none'), bds.qa.ShortCut.fbJQ('#ShortCut_wizard').css('display', 'none'), bds.qa.ShortCut.fbJQ('#fb_base_wizard_canvas').css('display', 'none'), bds.qa.ShortCut.fbJQ('#fb_baidu_wizard').css('display', 'none'), bds.qa.ShortCut.fbJQ('#fb_right_post_form').css('display', 'none'), bds.qa.ShortCut.fbJQ('#fb_popwindow').css('display', 'none'), bds.qa.ShortCut.fbJQ('#fb_right_dialog_canvas').css('display', 'none'), bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas').css('display', 'none'), bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas2').css('display', 'none'), bds.qa.ShortCut.fbJQ('.fb_cancel_flag').css('display', 'none'))  : (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').fadeOut(500), bds.qa.ShortCut.fbJQ('#ShortCut_wizard').fadeOut(500), bds.qa.ShortCut.fbJQ('#fb_base_wizard_canvas').fadeOut(500), bds.qa.ShortCut.fbJQ('#fb_baidu_wizard').fadeOut(500), bds.qa.ShortCut.fbJQ('#fb_right_post_form').fadeOut(500), bds.qa.ShortCut.fbJQ('#fb_popwindow').fadeOut(500), bds.qa.ShortCut.fbJQ('#fb_right_dialog_canvas').fadeOut(500), bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas').fadeOut(500), bds.qa.ShortCut.fbJQ('#fb_right_dialog_pagecanvas2').fadeOut(500), bds.qa.ShortCut.fbJQ('.fb_cancel_flag').fadeOut(500))
  },
  popwindow: function (t) {
    var e = document.getElementById('fb_pop_tips');
    e || bds.qa.ShortCut.fbJQ('.fb-action').append('<div id=\'fb_pop_tips\' style=\'height:25px;line-height:20px; padding-top: 3px;\'><span style=\'color:red;\'>' + t + '</span></div>'),
    ('center' == bds.qa.ShortCut.showPosition || 'top' == bds.qa.ShortCut.showPosition) && bds.qa.ShortCut.fbJQ('#fb_pop_tips').css('text-align', 'center'),
    bds.qa.ShortCut.fbJQ('#fb_pop_tips').fadeOut(3500);
    var n = function () {
      bds.qa.ShortCut.fbJQ('#fb_pop_tips').remove()
    };
    setTimeout(n, 4000)
  },
  popwindowEnd: function () {
    document.getElementById('fb_qa_feedback_body').style.height = 'auto',
    bds.qa.ShortCut.fbJQ('.fb-modal').css('margin-top', '150px'),
    bds.qa.ShortCut.fbJQ('.fb-action').css('height', 'auto'),
    bds.qa.ShortCut.fbJQ('.fb-action').css('width', bds.qa.ShortCut.fbJQ('#fb_qa_feedback_body').width() + 20 + 'px'),
    bds.qa.ShortCut.fbJQ('#fb_dialog_header').css('margin-top', '0px'),
    bds.qa.ShortCut.fbJQ('#fb_dialog_header').css('bottom', 'inherit'),
    bds.qa.ShortCut.fbJQ('.fb-footer').remove(),
    bds.qa.ShortCut.fbJQ('.fb-guide').remove(),
    bds.qa.ShortCut.fbJQ('.fb-action').css({
      'margin-left': '0px',
      'text-align': 'center'
    }),
    bds.qa.ShortCut.fbJQ('.fb-action').html('<div class="fb-finished" ><img src="' + bds.qa.ShortCut.base_url_path + '/feedback/images/fb_ok.png" style="float: left;margin-left: 30px;margin-top: 25px;"><p style="line-height: 80px;font-size: 16px;">您的意见我们已经收到，谢谢！</p><div>'),
    setTimeout(bds.qa.ShortCut.hidwindowEnd, 2500)
  },
  _getWizardPosition: function () {
    bds.qa.ShortCut.fbJQ('.fb-baidu-wizard').css('height', parseInt(Math.max(document.body.scrollHeight, document.documentElement.clientHeight, document.body.clientHeight)) + 'px'),
    bds.qa.ShortCut.fbJQ('.fb-baidu-wizard').css('width', this.win_width + 'px')
  },
  _getDialogPosition: function () {
    var t = bds.qa.ShortCut._getClientHeight() - bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').height();
    0 > t && (t = 0);
    var e = bds.qa.ShortCut._getClientWidth() - bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').width();
    0 > e && (e = 0),
    'right' == bds.qa.ShortCut.showPosition ? (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('right', '5px'), bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('bottom', '5px'))  : 'center' == bds.qa.ShortCut.showPosition ? (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('top', parseInt(t / 2) + 'px'), bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('left', parseInt(e / 2) + 'px'))  : 'top' == bds.qa.ShortCut.showPosition ? (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('top', '15px'), bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('left', parseInt(e / 2) + 'px'))  : 'custom' == bds.qa.ShortCut.showPosition ? (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('top', this.dialogPosition.top ? this.dialogPosition.top : '5px'), bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('left', this.dialogPosition.left ? this.dialogPosition.left : '5px'))  : 'bottom_right' == bds.qa.ShortCut.showPosition ? (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('right', this.dialogPosition.right ? this.dialogPosition.right : '5px'), bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('bottom', this.dialogPosition.bottom ? this.dialogPosition.bottom : '5px'))  : 'bottom_left' == bds.qa.ShortCut.showPosition && (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('left', this.dialogPosition.left ? this.dialogPosition.left : '5px'), bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('bottom', this.dialogPosition.bottom ? this.dialogPosition.bottom : '5px')),
    bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('position', 'fixed')
  },
  _isUpperIos6: function () {
    return navigator.userAgent.match(/iPad/i) || navigator.userAgent.match(/iPhone/i) || navigator.userAgent.match(/iPod/i) ? Boolean(navigator.userAgent.match(/OS [6-9]_\d[_\d]* like Mac OS X/i))  : !1
  },
  _getCss: function () {
    !function () {
      if (!document.getElementById('fb_css')) {
        var t = bds.qa.ShortCut._getCssName(),
        e = document.createElement('link');
        e.type = 'text/css',
        e.rel = 'stylesheet',
        e.id = 'fb_css',
        e.media = 'screen',
        e.href = bds.qa.ShortCut.base_url_path + '/feedback/css/' + t;
        var n = document.getElementsByTagName('head') [0];
        n.appendChild(e)
      }
    }()
  },
  _getCssName: function () {
    var t = '';
    return t = t + 'fb_' + bds.qa.ShortCut.skinStyle + '_0.3.css'
  },
  _getImg: function () {
    var t = function (t) {
      var e = new Image;
      e.src = t,
      e.complete || (e.onload = function () {
        e.onload = null
      })
    };
    t(bds.qa.ShortCut.base_url_path + '/feedback/images/cancel.png'),
    t(bds.qa.ShortCut.base_url_path + '/feedback/images/' + bds.qa.ShortCut.upImg),
    t(bds.qa.ShortCut.base_url_path + '/feedback/images/fb_ok.png'),
    t(bds.qa.ShortCut.base_url_path + '/feedback/images/fb_mouse.png')
  },
  _repaint: function () {
    bds.qa.ShortCut._getWizardPosition(),
    bds.qa.ShortCut._getDialogPosition()
  },
  _getClientHeight: function () {
    var t = 0;
    return document.documentElement && document.documentElement.clientHeight ? t = document.documentElement.clientHeight : document.body && (t = document.body.clientHeight),
    parseInt(t)
  },
  _getClientWidth: function () {
    var t = 0;
    return document.documentElement && document.documentElement.clientWidth ? t = document.documentElement.clientWidth : document.body && (t = document.body.clientWidth),
    parseInt(t)
  },
  _fixedPage: function () {
    bds.qa.ShortCut._getDialogPosition(),
    ('center' == bds.qa.ShortCut.showPosition || 'top' == bds.qa.ShortCut.showPosition) && bds.qa.ShortCut.fbJQ('.fb-footer').css('text-align', 'center'),
    bds.qa.ShortCut._isIE6() && (bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('position', 'absolute'), ('right' == bds.qa.ShortCut.showPosition || 'bottom_left' == bds.qa.ShortCut.showPosition || 'bottom_right' == bds.qa.ShortCut.showPosition) && bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').css('top', parseInt(document.documentElement.clientHeight + document.documentElement.scrollTop - bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').height() - 5) + 'px')),
    bds.qa.ShortCut.fbJQ('#fb_baidu_right_dialog').slideDown('slow')
  },
  default_options: {
    product_id: 0,
    entrance_id: 0,
    plugintitle: '意见反馈',
    issueTips: '反馈内容',
    issuePlaceholder: '欢迎提出您在使用过程中遇到的问题或宝贵建议（400字以内），感谢您对百度的支持。',
    emailPlaceholder: '请留下您的联系方式，以便我们及时回复您。',
    guide: '<span>申请删除百度快照内容，请在<a style="text-decoration:underline;" href="http://tousu.baidu.com/webmaster/add" target="_blank">网页搜索投诉中心</a>提交。</span><br><span>网站收录、流量等站长相关问题，请在<a style="text-decoration:underline;" href="http://zhanzhang.baidu.com/feedback/index" target="_blank">站长平台</a>反馈。</span>',
    cutFileTips: '点我可以上传图片哦~',
    cutCanvasTips: '&nbsp;点我可以在当前页面截图哦~&nbsp;<a style="text-decoration:underline;color:#2d9ef8;" href="http://f3.baidu.com/index.php/feedback/tiyan/steps" target="_blank">使用方法</a>',
    emailTips: '联系方式',
    needIssueTips: !0,
    needLevelType: !0,
    needIssue: !0,
    needCut: !0,
    needEmail: !0,
    needGuide: !1,
    defaultCut: !1,
    showPosition: 'right',
    onlyUpFile: !1,
    cutImg: 'jietu.png',
    upImg: 'upload.png',
    skinStyle: 'flat'
  }
},
module.exports = bds
});
; /*!searchresult:widget/ui/controls/ReportBox/ReportBox.js*/
define('searchresult:widget/ui/controls/ReportBox/ReportBox', function (e) {
function t(e) {
  this.model = e,
  this.$container = null
}
var i = e('common:widget/ui/base/base'),
n = e('searchresult:widget/ui/utils/utils'),
r = e('searchresult:widget/ui/controls/feedback/feedback'),
o = e('searchresult:widget/ui/app/page');
return i.extend(t.prototype, {
  init: function (e) {
    this.$container = i(e || '#report_link'),
    this.$feedback = i(e || '#suggest_feedback'),
    this._bindEvent()
  },
  _bindEvent: function () {
    var e = encodeURIComponent(o.model.get('queryWord')),
    t = {
      product_id: 103,
      showPosition: 'right',
      needCut: !1
    };
    this.$container.on('click', function () {
      r.qa.ShortCut.initRightBar(t, e)
    }),
    this.$feedback.on('click', function (i) {
      i.preventDefault(),
      r.qa.ShortCut.initRightBar(t, e)
    })
  },
  updateUrl: function () {
    var e = {
    },
    t = this.model.getFilterState().currFilterConf,
    i = this.model.getCurPage();
    t.tn = 'baiduimagereport',
    t.ipn = 'rpt',
    i && (t.pn = i.sPn, t.rn = i && i.ePn - t.pn + 1),
    e = n.json2Query(this.getNewURL(t)),
    this.url = '/search/baiduimagereport?' + e
  },
  getNewURL: function (e) {
    var t = n.trim(n.query2Json(n.escapeXSS(window.location.search.substring(1)))),
    r = i.extend(!0, {
    }, t);
    for (var o in e) r[o] = e[o];
    return r
  }
}),
t
});
; /*!searchresult:widget/ui/controls/RsBox/RsBox.js*/
define('searchresult:widget/ui/controls/RsBox/RsBox', function (e) {
function t(e, t) {
  this.id = 'topRS',
  this.$rsCon = null,
  this.model = e,
  this.pageModel = t,
  this.$container = r('#topInfoBar')
}
var n,
r = e('common:widget/ui/base/base'),
s = e('searchresult:widget/ui/statistic/statistic');
return r.extend(t.prototype, {
  updateRs: function () {
    n && this.renderRs(n.rsArr, n.arrRs)
  },
  init: function (e, t) {
    n = {
      rsArr: e,
      arrRs: t
    },
    this.renderRs(e, t)
  },
  renderRs: function (e, t) {
    var n = e.slice(0, 15);
    if (this.$rsCon = r('#' + this.id), this.$rsCon && !(n.length < 1)) {
      var o,
      i,
      d = t,
      l = encodeURIComponent(this.model.get('queryWord')),
      a = 0,
      u = n.length,
      p = [
        '<em class="pull-rs-title">相关搜索：</em>'
      ];
      if ('undefined' != typeof d && 'undefined' != typeof d.flag && 'undefined' != typeof d.query && 'undefined' != typeof d.url && '1' == d.flag && d.query && d.url) {
        for (p.push('<a class="recommend-Com" title="查看 ' + d.query + '" target="_blank" onmousedown="p(event,202,{event:\'click\',type:\'rsCom\',ps:\'t\',url:\'' + t.url + '\'})"  href="' + d.url + '">' + d.query + '</a>'); u > a && !(a >= 20); a++) o = n[a],
        i = '/search/index?ct=201326592&cl=2&lm=-1&nc=1&ie=utf-8&tn=baiduimage&ipn=r&rps=1&pv=&fm=rs' + (a + 1) + '&word=' + encodeURIComponent(o[0]) + '&oriquery=' + l + '&ofr=' + l + '&ctd=' + + new Date + '^00_' + r(window).width() + 'X' + window.innerHeight,
        this.pageModel.get('hs') - 0 && (i += '&hs=' + this.pageModel.get('hs')),
        p.push('<a class="pull-rs" title="查看 ' + o[0] + '" target="_self" onmousedown="p(event,10,{ps:\'t\',tp:\'a\',r:' + a + ', rq:\'' + encodeURIComponent(o[0]) + '\'})"  href="' + i + '">' + o[0] + '</a>');
        s && s(null, '2', {
          p: 202,
          event: 'show',
          type: 'rsCom',
          ps: 't',
          url: d.url
        })
      } else for (; u > a && !(a >= 20); a++) o = n[a],
      i = '/search/index?ct=201326592&cl=2&st=-1&lm=-1&nc=1&ie=utf-8&tn=baiduimage&ipn=r&rps=1&pv=&fm=rs' + (a + 1) + '&word=' + encodeURIComponent(o[0]) + '&oriquery=' + l + '&ofr=' + l + '&ctd=' + + new Date + '^00_' + r(window).width() + 'X' + window.innerHeight,
      this.pageModel.get('hs') - 0 && (i += '&hs=' + this.pageModel.get('hs')),
      p.push('<a class="pull-rs" title="查看 ' + o[0] + '"  target="_self" onmousedown="p(event,10,{ps:\'t\',tp:\'a\',r:' + a + ', rq:\'' + encodeURIComponent(o[0]) + '\'})"  href="' + i + '">' + o[0] + '</a>');
      this.$rsCon.html(p.join(''))
    }
  }
}),
t
});
; /*!searchresult:widget/ui/controls/adsearchBox/adsearchBox.js*/
define('searchresult:widget/ui/controls/adsearchBox/adsearchBox', function (a) {
function i(t) {
  this.model = t,
  this.pull = e('#adsearch'),
  this.lualu = e('#lualu'),
  this.TPL_TABLE = '<table width="100%" align="center" cellpadding="0" cellspacing="0"><tr><th valign="top" align="left"><div class="title">相关推广</div></th><td valign="center" id="rsAd"><table cellpadding="0" cellspacing="0"><tbody><tr>{{for(var i=0;i<5;i++){}}<td nowrap="nowrap">{{if(i<it.length){}}<a class="smaitem" target="_blank" href="http://search.baidu.com/s?wd={{=it[i].gbk}}&channel=pic-search&qid=' + this.model.get('aspSID') + '&sid=&pos=im-{{=i}}&sugCount={{=it.length}}&overscreen=1">{{=it[i].utf8}}{{if(i==0||i==2){}}<span class="sma-hot"></span>{{}}}</a>{{}}}</td>{{}}}</tr></tbody></table></td></tr></table><img src="" id="smaclick">'
}
{
  var e = a('common:widget/ui/base/base');
  a('searchresult:widget/ui/statistic/statistic')
}
return e.extend(i.prototype, {
  init: function () {
    var t = this;
    e.ajax({
      url: 'http://image.baidu.com/sma?q=' + this.model.get('queryWordEnc'),
      dataType: 'jsonp',
      jsonp: 'jsonpcallback',
      success: function (a) {
        a && a.length > 0 ? (t.data = a, t.render(a))  : t.renderLualu()
      }
    })
  },
  renderLualu: function () {
    this.lualu.show()
  },
  render: function (a) {
    var i = this,
    s = doT.template(this.TPL_TABLE),
    n = s(a);
    i.pull.show().append(n),
    e('#rsAd table tr:first td:not(.s)').each(function (t) {
      var a = e('#rsQuery table tr:first td:not(.s):eq(' + t + ')').width() + 38;
      a = Math.max(a, 150),
      i.data[t] && i.data[t].utf8.length > 10 && (a = Math.max(a, 150)),
      e(i).width(a)
    }),
    e('.smaitem').click(function () {
      var i = e(this).index(),
      s = 'http://sclick.baidu.com/w.gif?q=' + a[i].gbk + '&fm=SMA_IM&p1=1&p5=1&title=' + a[i].gbk + '&url=http://search.baidu.com/s?wd=' + a[i].gbk + '&qid=' + BD.IMG.tplConf.aspSID + '&sid=&pos=im-' + i + '&sugCount=' + t.data.length + '&overscreen=1&rsv_sid=&' + 100000000 * Math.random(100000000);
      e('#smaclick').attr('src', s)
    })
  }
}),
i
});
; /*!searchresult:widget/ui/controls/festivalLogo/FestivalLogo.js*/
define('searchresult:widget/ui/controls/festivalLogo/FestivalLogo', function (e, i, t) {
t.exports.init = function () {
  var e,
  i,
  t,
  n = new Date;
  if (!('undefined' == typeof window.festivalStartTime || 'undefined' == typeof window.festivalEndTime || 'undefined' == typeof window.festivalBodyStyle || n < window.festivalStartTime || n > window.festivalEndTime)) {
    e = window.festivalBodyStyle,
    t = document.body.style;
    for (i in e) e.hasOwnProperty(i) && (t[i] = e[i])
  }
}
});
; /*!searchresult:widget/ui/controls/filter/InteractFilter/InteractFilter.js*/
define('searchresult:widget/ui/controls/filter/InteractFilter/InteractFilter', function () {
});
; /*!searchresult:widget/ui/controls/filter/InteractFilter/tagData/tagData.js*/
define('searchresult:widget/ui/controls/filter/InteractFilter/tagData/tagData', function () {
});
; /*!searchresult:widget/ui/controls/filter/filterConfig/filterConfig.js*/
define('searchresult:widget/ui/controls/filter/filterConfig/filterConfig', function (t, e, a) {
a.exports = config = {
  sizeFilter: {
    data: [
      {
        value: '0',
        text: '全部尺寸',
        par: 'z',
        isD: 1
      },
      {
        value: '9',
        text: '特大尺寸',
        par: 'z'
      },
      {
        value: '3',
        text: '大尺寸',
        par: 'z'
      },
      {
        value: '2',
        text: '中尺寸',
        par: 'z'
      },
      {
        value: '1',
        text: '小尺寸',
        par: 'z'
      },
      {
        value: 'null',
        text: '电脑壁纸',
        par: 's',
        type: 2
      },
      {
        value: 'null',
        text: '手机壁纸',
        par: 's',
        type: 2
      },
      {
        value: 'null',
        text: '自定义',
        par: 'z',
        type: 1,
        width: window.screen.width || 0,
        height: window.screen.height || 0
      }
    ],
    defaultValue: 'z_0',
    defaultPcData: [
      {
        w: 1920,
        h: 1080,
        text: '1920x1080',
        par: 's'
      },
      {
        w: 1680,
        h: 1050,
        text: '1680x1050',
        par: 's'
      },
      {
        w: 1440,
        h: 900,
        text: '1440x900',
        par: 's'
      },
      {
        w: 1366,
        h: 768,
        text: '1366x768',
        par: 's'
      },
      {
        w: 1280,
        h: 1024,
        text: '1280x1024',
        par: 's'
      },
      {
        w: 1280,
        h: 800,
        text: '1280x800',
        par: 's'
      },
      {
        w: 1024,
        h: 768,
        text: '1024x768',
        par: 's'
      }
    ],
    defaultWiseData: [
      {
        w: 1440,
        h: 2560,
        text: '2560x1440',
        par: 's'
      },
      {
        w: 1080,
        h: 1920,
        text: '1920x1080',
        par: 's'
      },
      {
        w: 750,
        h: 1334,
        text: '1334x750',
        par: 's'
      },
      {
        w: 720,
        h: 1280,
        text: '1280x720',
        par: 's'
      },
      {
        w: 640,
        h: 1136,
        text: '1136x640',
        par: 's'
      },
      {
        w: 640,
        h: 960,
        text: '960x640',
        par: 's'
      },
      {
        w: 540,
        h: 960,
        text: '960x540',
        par: 's'
      },
      {
        w: 480,
        h: 854,
        text: '854x480',
        par: 's'
      },
      {
        w: 480,
        h: 800,
        text: '800x480',
        par: 's'
      },
      {
        w: 320,
        h: 480,
        text: '480x320',
        par: 's'
      }
    ]
  },
  colorFilter: {
    data: [
      {
        value: '0',
        text: '全部颜色',
        type: 1,
        tips: '不做颜色筛选',
        classShim: '',
        isD: 1
      },
      {
        value: '1',
        text: '红色',
        color: '#DE2020',
        borderC: '#CB1C1C',
        classShim: 'red'
      },
      {
        value: '256',
        text: '橙色',
        color: '#FE6C00',
        borderC: '#E96300',
        classShim: 'orange'
      },
      {
        value: '2',
        text: '黄色',
        color: '#FEBF00',
        borderC: '#E9B000',
        classShim: 'yellow'
      },
      {
        value: '4',
        text: '绿色',
        color: '#59A725',
        borderC: '#539B23',
        classShim: 'green'
      },
      {
        value: '32',
        text: '紫色',
        color: '#892BCF',
        borderC: '#7A27B7',
        classShim: 'purple'
      },
      {
        value: '64',
        text: '粉色',
        color: '#D744BA',
        borderC: '#C63FAB',
        classShim: 'pink'
      },
      {
        value: '8',
        text: '青色',
        color: '#06B7C8',
        borderC: '#07A6B7',
        classShim: 'cyan'
      },
      {
        value: '16',
        text: '蓝色',
        color: '#0065FE',
        borderC: '#005CEB',
        classShim: 'blue'
      },
      {
        value: '128',
        text: '棕色',
        color: '#733413',
        borderC: '#6B3012',
        classShim: 'gray'
      },
      {
        value: '1024',
        text: '白色',
        color: '#fff',
        borderC: '#C0BABC',
        classShim: 'white',
        type: 3
      },
      {
        value: '512',
        text: '黑色',
        color: '#000',
        borderC: '#000',
        classShim: 'black'
      },
      {
        value: '2048',
        text: '黑白',
        type: 2,
        tips: '黑白',
        classShim: 'bw',
        bg: '#fff url(//img0.bdstatic.com/static/searchresult/img/lazy_img_d398a71.png) no-repeat -1px -319px'
      }
    ],
    defaultValue: 0
  },
  typeFilter: {
    defaultValue: 'st_-1',
    data: [
      {
        value: '-1',
        text: '全部类型',
        par: 'st',
        isD: 1
      },
      {
        value: '3',
        text: '头像图片',
        par: 's'
      },
      {
        value: '1',
        text: '面部特写',
        par: 'face'
      },
      {
        value: '1',
        text: '卡通画',
        par: 'st'
      },
      {
        value: '2',
        text: '简笔画',
        par: 'st'
      },
      {
        value: '6',
        text: '动态图片',
        par: 'lm'
      },
      {
        value: '7',
        text: '静态图片',
        par: 'lm'
      }
    ]
  },
  pcSizeData: {
    data: [
      {
        w: 1024,
        h: 768,
        text: '1024x768',
        par: 's'
      },
      {
        w: 1280,
        h: 800,
        text: '1280x800',
        par: 's'
      },
      {
        w: 1280,
        h: 1024,
        text: '1280x1024',
        par: 's'
      },
      {
        w: 1366,
        h: 768,
        text: '1366x768',
        par: 's'
      },
      {
        w: 1440,
        h: 900,
        text: '1440x900',
        par: 's'
      },
      {
        w: 1680,
        h: 1050,
        text: '1680x1050',
        par: 's'
      },
      {
        w: 1920,
        h: 1080,
        text: '1920x1080',
        par: 's'
      },
      {
        value: 'null',
        text: '自定义',
        par: 'z',
        type: 1,
        width: window.screen.width || 0,
        height: window.screen.height || 0
      }
    ]
  },
  wiseSizeData: {
    data: [
      {
        w: 960,
        h: 800,
        text: '960x800',
        par: 's'
      },
      {
        w: 640,
        h: 480,
        text: '640x480',
        par: 's'
      },
      {
        w: 1080,
        h: 960,
        text: '1080x960',
        par: 's'
      },
      {
        w: 480,
        h: 320,
        text: '480x320',
        par: 's'
      },
      {
        w: 960,
        h: 854,
        text: '960x854',
        par: 's'
      },
      {
        w: 640,
        h: 960,
        text: '640x960',
        par: 's'
      },
      {
        w: 640,
        h: 1136,
        text: '640x1136',
        par: 's'
      }
    ]
  }
}
});
; /*!searchresult:widget/ui/controls/filter/filterClass/filterClass.js*/
define('searchresult:widget/ui/controls/filter/filterClass/filterClass', function (t) {
function e(t) {
  this.container = null,
  this.filterList = [
  ],
  this.curFilter = null,
  this.model = t
}
var i = t('common:widget/ui/base/base');
return i.extend(e.prototype, {
  init: function (t) {
    var e = this;
    this.$container = i('#' + t),
    this.$filter = i('.filter'),
    this.showFilter(),
    this.$filter.on('mouseover', function (t) {
      e.showPanel(t)
    }),
    this.$filter.on('mouseout', function (t) {
      e.hidePanel(t)
    }),
    this.render()
  },
  showFilter: function () {
  },
  render: function () {
  },
  remove: function () {
  },
  setOverClass: function (t) {
    i(t).addClass('hover')
  },
  setOutClass: function (t) {
    i(t).removeClass('hover')
  },
  setMouseOver: function (t) {
    var e = i(t),
    s = this;
    e.mouseover(function () {
      this != s.curFilter && s.setOverClass(this)
    }).mouseout(function () {
      s.setOutClass(this)
    })
  },
  setMouseClick: function (t) {
    var e = this;
    i(t).on('click', function () {
      if (i(this).hasClass('selected')) return !1;
      var t = e.getCurrentFilterNum();
      '0' !== this.getAttribute('val') ? e.$container.hasClass('filter-on') || t++ : t--,
      e.setCurFilter(this, !0),
      'null' == i(this).val()
    })
  },
  setDefault: function () {
    this.$container.removeClass('filter-on')
  },
  setCurFilter: function () {
  },
  showPanel: function (t) {
    t = t || window.event;
    for (var e, s = t.target || t.srcElement, r = s, n = self.filter; r && r !== n && !i(r).hasClass('subFilter'); ) r = r.parentNode;
    e = i(r),
    r && e.hasClass('subFilter') && (clearTimeout(r.timer), r.timer = setTimeout(function () {
      e.addClass('filter-hover')
    }, 250))
  },
  hidePanel: function (t) {
    t = t || window.event;
    for (var e = (t.toElement || t.relatedTarget, t.fromElement || t.target), s = self.filter, r = i(e); e && e !== s && !i(e).hasClass('subFilter'); ) e = e.parentNode;
    r = i(e),
    e && r.hasClass('subFilter') && (clearTimeout(e.timer), e.timer = setTimeout(function () {
      r.removeClass('filter-hover')
    }, 250))
  },
  setState: function (t) {
    var e = this.state;
    if (e) for (var i in e) e[i] = t[i]
  },
  getCurrentFilterNum: function () {
    var t = i('#filter');
    if (t.length > 0) {
      var e = i('.filter-on', t);
      return e.length
    }
    return - 100
  }
}),
e
});
; /*!searchresult:widget/ui/controls/filter/colorFilter/colorFilter.js*/
define('searchresult:widget/ui/controls/filter/colorFilter/colorFilter', function (t) {
function i(t) {
  this.model = t,
  this.$container = null,
  this.filterList = [
  ],
  this.curFilter = null,
  this.options = e.extend({
  }, o.colorFilter || {
  })
}
var e = t('common:widget/ui/base/base'),
s = t('searchresult:widget/ui/utils/utils'),
l = t('common:widget/ui/base/events'),
r = t('searchresult:widget/ui/statistic/statistic'),
o = t('searchresult:widget/ui/controls/filter/filterConfig/filterConfig'),
a = t('searchresult:widget/ui/controls/filter/filterClass/filterClass'),
n = {
  colorStr: [
    '<div><div class="filter-menu-item">全部颜色</div><span class="menu-con-arrow"></span><div class="filter-item-con"></div><ul></ul><div class="colorBox"></div></div>'
  ].join(''),
  0: [
    '<li val="{{=it.value}}"  data-text="{{=it.text}}" class="{{=it.classShim}}" title="{{=it.tips}}" isD={{=it.isD}}>{{=it.text}}</li>'
  ].join(''),
  1: [
    '<div val="{{=it.value}}" data-color="{{=it.color}}" data-text="{{=it.text}}" title="{{=it.text}}" class="colorBlock {{=it.classShim}}" isD={{=it.isD}}><a  href="javascript:void(0);" hidefocus="true" style="background-color:{{=it.color}};border-color:{{=it.borderC}}"></a></div>'
  ].join(''),
  2: [
    '<div val="{{=it.value}}" data-bg="{{=it.bg}}" data-text="{{=it.text}}" title="{{=it.text}}" class="colorBlock {{=it.classShim}}" isD={{=it.isD}}><span class="picbox" style="display:block;"><a   href="javascript:void(0);" hidefocus="true" ></a></span></div>'
  ].join('')
};
return e.extend(i.prototype, a.prototype, l, {
  init: function (t) {
    var i = this;
    this.$container = e('#' + t),
    this.$container.addClass('colorFilter'),
    this.showFilter(),
    this.$container.on('mouseover', function (t) {
      i.showPanel(t)
    }),
    this.$container.on('mouseleave', function (t) {
      i.hidePanel(t)
    }),
    this.render()
  },
  render: function () {
    var t = {
      isModifyHash: !1
    },
    i = {
    };
    this.options.defaultValue = this.model.get('ic'),
    i.ic = this.model.get('ic'),
    this.setInitValue(i, t)
  },
  format: function () {
  },
  showFilter: function () {
    var t = this.options.data,
    i = 0,
    l = t.length,
    r = s.format(n.colorStr, this.format());
    this.$el = e(r),
    this.$con = this.$el.find('.filter-item-con'),
    this.$currentStateCon = this.$el.find('.filter-menu-item'),
    this.$ul = this.$el.find('ul'),
    this.$colorBox = this.$el.find('.colorBox');
    for (var o = doT.compile(n[0]), a = doT.compile(n[1]), c = doT.compile(n[2]); l > i; i++) {
      var d = t[i];
      d.type && 1 == d.type ? this.addCell(d, o, this.$ul)  : d.type && 2 == d.type ? this.addCell(d, c, this.$colorBox)  : d.type && 3 == d.type ? this.addCell(d, c, this.$colorBox)  : this.addCell(d, a, this.$colorBox)
    }
    this.$con.append(this.$ul),
    this.$con.append(this.$colorBox),
    this.$container.append(this.$el)
  },
  addCell: function (t, i, l) {
    var r = s.str2dom(i(t));
    l.append(r),
    1 === t.isD && e(r).addClass('list-first-item'),
    this.setMouseClick(r),
    this.filterList[t.value] = r
  },
  setInitValue: function (t, i) {
    var e = parseInt(t.ic);
    e && !isNaN(e) ? (this.$container.addClass('filter-on'), this.setCurFilter(this.filterList[e], i.isModifyHash))  : this.setDefault(i.isModifyHash)
  },
  setCurFilter: function (t, i) {
    if (this.$curFilter = e(this.curFilter), !t) return void this.setDefault(i);
    if (this.curFilter == t) return void (this.$curFilter.val() != this.options.defaultValue && i && this.setDefault(i));
    this.removeSelected(this.$curFilter),
    this.curFilter = t,
    this.$curFilter = e(t),
    this.addSelected(this.$curFilter),
    this.$container.removeClass('filter-hover');
    var s = this.$curFilter.attr('data-color'),
    l = this.$curFilter.attr('data-text');
    if (l) {
      var r = '';
      s ? r += '<span class="menu-item-color" style=" background-color: ' + s + '"></span>' : (s = this.$curFilter.attr('data-bg')) && (r += '<span class="menu-item-color" style=" background: ' + s + '"></span>'),
      r += l,
      this.$currentStateCon.html(r)
    }
    i && this.$curFilter.attr('val') && this.setURI(this.$curFilter.attr('val'))
  },
  removeSelected: function (t) {
    t && t.children('a') ? t.children('a').removeClass()  : t && t.removeClass('selected')
  },
  addSelected: function (t) {
    t && t.children('a') ? t.children('a').addClass('selected')  : t.addClass('selected')
  },
  setMouseClick: function (t) {
    var i = this;
    e(t).on('click', function (t) {
      if (e(this).hasClass('selected')) return !1;
      var s = i.getCurrentFilterNum();
      '0' !== this.getAttribute('val') ? i.$container.hasClass('filter-on') || s++ : s--,
      r(t, 25, {
        fb: 'ic_' + this.getAttribute('val'),
        currf: 'color',
        onnum: s
      }),
      i.setCurFilter(this, !0)
    })
  },
  setURI: function (t) {
    t = parseInt(t),
    this.model.get('ic') != t && (t && !isNaN(t) ? this.$container.addClass('filter-on')  : this.$container.removeClass('filter-on'), e('#memoryBar').hide(), r(null, 56, {
      type: 'pageturn',
      curr: 1,
      fr: ''
    }), this.dispatchEvent('sizeChanged', {
      ic: t
    }))
  }
}),
i
});
; /*!searchresult:widget/ui/controls/filter/indicator/indicator.js*/
define('searchresult:widget/ui/controls/filter/indicator/indicator', function () {
});
; /*!searchresult:widget/ui/controls/filter/sizeFilter/sizeFilter.js*/
define('searchresult:widget/ui/controls/filter/sizeFilter/sizeFilter', function (t) {
function e(t, e) {
  this.model = t,
  this.$container = null,
  this.filterList = [
  ],
  this.options = e || l.sizeFilter
}
var i = t('common:widget/ui/base/base'),
s = t('searchresult:widget/ui/utils/utils'),
r = t('common:widget/ui/base/events'),
a = t('searchresult:widget/ui/controls/filter/filterClass/filterClass'),
l = t('searchresult:widget/ui/controls/filter/filterConfig/filterConfig'),
h = t('searchresult:widget/ui/statistic/statistic'),
n = {
  sizeSrt: [
    '<div><div class="filter-menu-item">全部尺寸</div><span class="menu-con-arrow"></span><ul class="filter-item-con"></ul></div>'
  ].join(''),
  0: [
    '<li val={{=it.value}} data-text="{{=it.text}}" par="{{=it.par}}" isD={{=it.isD}}>{{=it.text}}</li>'
  ].join(''),
  1: [
    '<li val={{=it.value}} data-text="{{=it.text}}" style="text-decoration: none;" par="{{=it.par}}" isD={{=it.isD}}>{{=it.text}}<p class="info">宽：<input class="default" type="text" value="{{=it.width}}" name="swidth" id="swidth" ><br/>高：<input class="default" type="text" value="{{=it.height}}" name="sheight" id="sheight" ><br /><button class="exact-size-submit" name="sizeSubmit"  id="sizeSubmit" >确定</button></p></li>'
  ].join(''),
  2: [
    '<li data-text="{{=it.text}}" class="wp-item"  w="{{=it.w}}" h="{{=it.h}}" par="{{=it.par}}" >{{=it.text}}</li>'
  ].join('')
};
return i.extend(e.prototype, a.prototype, r, {
  render: function () {
    var t = {
      isModifyHash: !1
    },
    e = {
    };
    e.z = this.model.get('z'),
    e.s = this.model.get('s'),
    e.width = this.model.get('width'),
    e.height = this.model.get('height'),
    this.options.defaultValue = 'z_' + e.z,
    this.setInitValue(e, t)
  },
  inputOnfocus: function () {
    this.value == this.defaultValue && 'default' == this.className && (this.value = '', i(this).removeClass('default'))
  },
  submitWH: function (t, e) {
    var s = this.$swidth,
    r = this.$sheight,
    a = parseInt(s.val()),
    l = parseInt(r.val()),
    n = [
    ];
    if ((!a || 0 > a || isNaN(a)) && (s.val(''), n.push(s)), (!l || 0 > l || isNaN(l)) && (r.val(''), n.push(r)), n.length > 0) return n[0].focus(),
    !1;
    this.curFilter && i(this.curFilter).removeClass('selected'),
    this.curFilter = e,
    s.value = a,
    r.value = l,
    this.$currentStateCon.html(a + 'x' + l),
    this.$container.removeClass('filter-hover wp-wise-select wp-pc-select');
    var u = this.getCurrentFilterNum();
    this.$container.hasClass('filter-on') || (u++, this.$container.addClass('filter-on')),
    h(t, 25, {
      fb: 'z_' + a + 'x' + l,
      currf: 'size',
      onnum: u
    }),
    this.setURI(this.curFilter.getAttribute('par'), s.value, r.value, '', !0)
  },
  format: function () {
  },
  addCell: function (t, e, r) {
    var a = s.str2dom(e(t));
    r.append(a),
    1 === t.isD && i(a).addClass('list-first-item'),
    this.setMouseClick(a),
    this.setMouseOver(a),
    this.filterList[t.par + '_' + t.value] = a
  },
  showFilter: function () {
    var t = 0,
    e = this.options.data,
    r = e.length,
    a = s.format(n.sizeSrt, this.format());
    this.$el = i(a),
    this.$con = this.$el.find('.filter-item-con'),
    this.$currentStateCon = this.$el.find('.filter-menu-item'),
    this.$ul = this.$el.find('ul');
    for (var l = doT.compile(n[0]), h = doT.compile(n[2]), u = doT.compile(n[1]); r > t; t++) {
      var o = e[t];
      if (o.type && 1 === o.type) this.addInputCell(o, u, this.$ul);
       else if (o.type && 2 == o.type) {
        var c = s.str2dom(u(o));
        if ('电脑壁纸' === o.text ? (childData = this.options.defaultPcData, c.hoverClass = 'wp-pc-hover', selfClass = 'wp-pc')  : '手机壁纸' === o.text && (childData = this.options.defaultWiseData, c.hoverClass = 'wp-wise-hover', selfClass = 'wp-wise'), childData) {
          var d = this.createChild(childData, h);
          d && (i(d).addClass('sub-item-container'), i(c).addClass('sub-item-parent ' + selfClass), i(c).html(o.text), i(c).append(d), i(c).on('mouseover', function (t) {
            var e = t.hoverClass;
            return function () {
              clearTimeout(t.timer),
              t.timer = setTimeout(function () {
                i(t).addClass('hover'),
                i(t.parentNode).addClass(e)
              }, 200)
            }
          }(c)), i(c).on('mouseout', function (t) {
            var e = t.hoverClass;
            return function () {
              clearTimeout(t.timer),
              t.timer = setTimeout(function () {
                i(t).removeClass('hover'),
                i(t.parentNode).removeClass(e)
              }, 200)
            }
          }(c)))
        }
        this.$ul.append(c),
        this.filterList[o.par + '_' + o.value] = c
      } else o.w ? this.addInputCell(o, h, this.$ul)  : this.addCell(o, l, this.$ul);
      this.$container.append(this.$el)
    }
  },
  addInputCell: function (t, e, r) {
    var a = this,
    l = s.str2dom(e(t));
    r.append(l);
    var h = this.$container.find(' #sizeSubmit');
    this.$swidth = this.$container.find('#swidth'),
    this.$sheight = this.$container.find('#sheight'),
    1 == t.type ? (i(l).addClass('detail-size-filter'), this.$swidth.focus(this.inputOnfocus), this.$sheight.focus(this.inputOnfocus), this.$swidth.keydown(function (t) {
      var e = t.keyCode;
      if (13 == e) a.submitWH(t, l);
       else if (!(8 === e || 9 === e || 46 === e || e >= 48 && 57 >= e || e >= 96 && 105 >= e)) return t.preventDefault(),
      !1
    }), this.$sheight.keydown(function (t) {
      var e = t.keyCode;
      if (13 == e) a.submitWH(t, l);
       else if (!(8 === e || 9 === e || 46 === e || e >= 48 && 57 >= e || e >= 96 && 105 >= e)) return t.preventDefault ? t.preventDefault()  : t.returnValue = !1,
      !1
    }), h.click(function (t) {
      a.submitWH(t, l)
    }))  : t.w && i(l).on('click', function (t) {
      var e = i(t.target);
      t.stopPropagation ? t.stopPropagation()  : t.cancelBubble = !0,
      a.selectedCur(e)
    }),
    this.filterList[t.par + '_' + t.value] = l
  },
  createChild: function (t, e) {
    if (t && !(t.length < 1)) {
      for (var r = e, a = i('<ul></ul>'), l = this, n = 0, u = t.length; u > n; n++) {
        var o = s.str2dom(r(t[n]));
        this.filterList['s_' + t[n].w + '_' + t[n].h] = o,
        i(o).on('click', function (t) {
          var e = i(t.target),
          s = this.getAttribute('w'),
          r = this.getAttribute('h');
          h(t, 25, {
            fb: 'wpz_' + s + 'x' + r,
            currf: 'size',
            onnum: 1
          }),
          t.stopPropagation ? t.stopPropagation()  : t.cancelBubble = !0,
          l.selectedCur(e)
        }),
        a.append(o)
      }
      return a
    }
  },
  selectedCur: function (t) {
    var e = this.getCurrentFilterNum();
    this.$container.hasClass('filter-on') || e++,
    this.setCurrentWP(t, !0)
  },
  setCurrentWP: function (t, e) {
    if (this.curFilter != t[0]) {
      this.curFilter && i(this.curFilter).removeClass('selected');
      var s = t[0].parentNode.parentNode,
      r = this.$container;
      if (s && ('wp-pc-hover' === s.hoverClass ? (r.removeClass('wp-wise-select'), r.addClass('wp-pc-select'))  : 'wp-wise-hover' === s.hoverClass && (r.addClass('wp-wise-select'), r.removeClass('wp-pc-select'))), this.curFilter = t[0], this.$container.removeClass('filter-hover'), t.addClass('selected'), i(t[0].parentNode).addClass('child-select'), this.$currentStateCon.html(t.attr('data-text')), e) {
        var a = t.attr('w') || t.attr('val'),
        l = t.attr('h');
        this.setURI(this.curFilter.getAttribute('par'), a, l)
      }
    }
  },
  setInitValue: function (t, e) {
    var s = parseInt(t.z),
    r = parseInt(t.s),
    a = parseInt(t.width),
    l = parseInt(t.height),
    h = e ? e.isModifyHash : !0;
    if (this.$container.addClass('filter-on'), i('.bz-indicator').removeClass('active'), (isNaN(r) || 1 != r) && 1 != r && a && l && !isNaN(a) && !isNaN(l) && this.swidth) this.swidth.value = a,
    this.sheight.value = l,
    this.setCurFilter(this.filterList.z_null),
    h && this.setURI(this.curFilter.getAttribute('par'), a, l, h);
     else if (1 != r || isNaN(r)) s && !isNaN(s) ? this.setCurFilter(this.filterList['z_' + s], h)  : this.setDefault(h);
     else {
      var n = this.filterList['s_' + t.width + '_' + t.height];
      this.setCurFilter(n, h)
    }
  },
  setDefault: function (t) {
    this.$container.removeClass('filter-on'),
    this.clearExactValue(),
    this.setCurFilter(this.filterList[this.options.defaultValue] || this.filterList.z_0, t)
  },
  clearExactValue: function () {
    var t = this.swidth,
    e = this.sheight;
    t && e && (t.value = t.defaultValue, i(t).addClass('default'), e.value = e.defaultValue, i(e).addClass('default'))
  },
  setCurFilter: function (t, e) {
    if (!t) return this.curFilter && i(this.curFilter).removeClass('selected'),
    this.$currentStateCon.html(this.options.defaultText),
    this.curFilter = null,
    void this.$container.removeClass('filter-on');
    var s,
    r;
    if (this.curFilter == t) return void (i(t).hasClass('detail-size-filter') && (s = this.swidth.value, r = this.sheight.value, this.$currentStateCon.html(s + 'x' + r)));
    if (t && i(t).hasClass('detail-size-filter')) return this.curFilter && i(this.curFilter).removeClass('selected'),
    this.curFilter = t,
    s = this.swidth.value,
    r = this.sheight.value,
    this.$currentStateCon.html(s + 'x' + r),
    void this.$container.removeClass('filter-hover wp-wise-select wp-pc-select');
    t.getAttribute('val');
    if (this.curFilter && i(this.curFilter).removeClass('selected'), this.curFilter = t, i(this.curFilter).addClass('selected'), this.$currentStateCon.html(t.getAttribute('data-text')), this.$container.removeClass('filter-hover wp-wise-select wp-pc-select'), e) {
      var a = t.getAttribute('par'),
      l = t.getAttribute('w') || t.getAttribute('val'),
      h = t.getAttribute('h');
      this.setURI(a, l, h, e)
    }
  },
  setMouseClick: function (t) {
    var e = this;
    i(t).on('click', function (t) {
      if (i(this).hasClass('selected')) return !1;
      var s = e.getCurrentFilterNum();
      '0' !== this.getAttribute('val') ? e.$container.hasClass('filter-on') || s++ : s--,
      h(t, 25, {
        fb: this.getAttribute('par') + '_' + this.getAttribute('val'),
        currf: 'size',
        onnum: s
      }),
      e.setCurFilter(this, !0)
    })
  },
  setURI: function (t, e, s) {
    var r,
    a = [
    ],
    l = this.model.get('s');
    return 1 == l && 's' != t && a.push('s'),
    's' == t ? (r = {
      width: e,
      height: s,
      cl: '',
      ct: '',
      z: ''
    }, void this.dispatchEvent('sizeChanged', r))  : (r = s || 'z' != t ? {
      z: '',
      width: e,
      height: s
    }
     : {
      z: e,
      width: '0',
      height: '0'
    }, i('#memoryBar').hide(), h(null, 56, {
      type: 'pageturn',
      curr: 1,
      fr: ''
    }), void this.dispatchEvent('sizeChanged', r))
  }
}),
e
});
; /*!searchresult:widget/ui/controls/filter/typeFilter/typeFilter.js*/
define('searchresult:widget/ui/controls/filter/typeFilter/typeFilter', function (t) {
function e(t) {
  this.model = t,
  this.$container = null,
  this.filterList = [
  ],
  this.curFilter = null,
  this.options = i.extend({
  }, a.typeFilter || {
  })
}
var i = t('common:widget/ui/base/base'),
s = t('searchresult:widget/ui/utils/utils'),
r = t('searchresult:widget/ui/statistic/statistic'),
l = t('common:widget/ui/base/events'),
a = t('searchresult:widget/ui/controls/filter/filterConfig/filterConfig'),
n = t('searchresult:widget/ui/controls/filter/filterClass/filterClass'),
u = {
  typeSrt: [
    '<div><div class="filter-menu-item">全部类型</div><span class="menu-con-arrow"></span><ul class="filter-item-con"></ul></div>'
  ].join(''),
  0: [
    '<li val={{=it.value}} data-text="{{=it.text}}" par="{{=it.par}}" isD={{=it.isD}}>{{=it.text}}</li>'
  ].join('')
};
return i.extend(e.prototype, n.prototype, l, {
  showFilter: function () {
    var t = this.options.data,
    e = 0,
    r = t.length,
    l = s.format(u.typeSrt, this.format());
    this.$el = i(l),
    this.$con = this.$el.find('.filter-item-con'),
    this.$currentStateCon = this.$el.find('.filter-menu-item'),
    this.$ul = this.$el.find('ul');
    for (var a = doT.compile(u[0]); r > e; e++) {
      var n = t[e];
      n && this.addCell(n, a, this.$ul)
    }
    this.$container.append(this.$el)
  },
  format: function () {
  },
  addCell: function (t, e, r) {
    var l = s.str2dom(e(t));
    r.append(l),
    1 === t.isD && i(l).addClass('list-first-item'),
    this.setMouseClick(l),
    this.setMouseOver(l),
    this.filterList[t.par + '_' + t.value] = l
  },
  setInitValue: function (t, e) {
    var i = this.filterList,
    s = parseInt(t.st),
    r = parseInt(t.face),
    l = parseInt(t.s),
    a = e ? e.isModifyHash : !0;
    return 0 === l ? void this.setDefault(a)  : (this.$container.addClass('filter-on'), void (r && !isNaN(r) ? this.setCurFilter(i['face_' + r], a)  : l && 1 != l && !isNaN(l) ? this.setCurFilter(i['s_' + l], a)  : s && !isNaN(s) && - 1 !== s ? this.setCurFilter(i['st_' + s], a)  : this.setCurFilter(i['st_' + s], a)))
  },
  setCurFilter: function (t, e) {
    if (this.$curFilter = i(this.curFilter), !t) return void this.setDefault(e);
    if (this.curFilter == t) return void (this.$curFilter.val() != this.options.defaultValue && e && this.setDefault(e));
    this.removeSelected(this.$curFilter),
    this.curFilter = t,
    this.$curFilter = i(t),
    this.addSelected(this.$curFilter),
    this.$container.removeClass('filter-hover');
    var s = this.$curFilter.attr('data-text');
    s && this.$currentStateCon.html(s),
    e && this.$curFilter.attr('val') && this.setURI(this.$curFilter.attr('par'), this.$curFilter.attr('val'))
  },
  removeSelected: function (t) {
    t && t.removeClass('selected')
  },
  addSelected: function (t) {
    t && t.addClass('selected')
  },
  setMouseClick: function (t) {
    var e = this;
    i(t).on('click', function (t) {
      if (i(this).hasClass('selected')) return !1;
      var s = e.getCurrentFilterNum();
      '0' !== this.getAttribute('val') ? e.$container.hasClass('filter-on') || s++ : s--,
      r(t, 25, {
        fb: this.getAttribute('par') + '_' + this.getAttribute('val'),
        currf: 'type',
        onnum: s
      }),
      e.setCurFilter(this, !0)
    })
  },
  setURI: function (t, e) {
    var s = {
      st: - 1,
      face: 0,
      s: 0,
      lm: 0
    };
    s[t] = e,
    i('#memoryBar').hide(),
    r(null, 56, {
      type: 'pageturn',
      curr: 1,
      fr: ''
    }),
    this.dispatchEvent('sizeChanged', s)
  },
  render: function () {
    var t = {
      isModifyHash: !1
    },
    e = {
    };
    this.options.defaultValue = this.model.get('s'),
    e.s = this.model.get('s'),
    e.face = this.model.get('face'),
    e.st = this.model.get('st'),
    this.setInitValue(e, t)
  }
}),
e
});
; /*!searchresult:widget/ui/controls/filter/wallpaperFliter/wallpaperFilter.js*/
define('searchresult:widget/ui/controls/filter/wallpaperFliter/wallpaperFilter', function () {
});
; /*!searchresult:widget/ui/controls/fixedSearchBox/fixedRSBox/fixedRSBox.js*/
define('searchresult:widget/ui/controls/fixedSearchBox/fixedRSBox/fixedRSBox', function (s) {
function t(s, t) {
  this.model = s,
  this.pageModel = t,
  this.$form = '',
  this.hasRS = !1,
  this.rsHeight = 0,
  this.rsVisible = !0
}
{
  var e,
  i = s('common:widget/ui/base/base'),
  r = (s('searchresult:widget/ui/utils/utils'), s('common:widget/ui/base/events'));
  s('searchresult:widget/ui/statistic/statistic')
}
return i.extend(t.prototype, r, {
  updateRs: function () {
    e && this.renderRs(e.rsArr, e.arrRs)
  },
  initRS: function (s, t) {
    e = {
      rsArr: s,
      arrRs: t
    },
    this.renderRs(s, t)
  },
  renderRs: function (s, t) {
    var e,
    r,
    o = s.slice(0, 15),
    h = (document.getElementById('topInfoBar'), 0),
    n = o.length,
    a = [
    ],
    u = encodeURIComponent(this.model.get('queryWord'));
    if (0 == n) {
      var l = i('.ma-primary-bg');
      l && l.length > 0 && l.css({
        top: '103px'
      })
    }
    if (this.$rsCon) {
      if (n >= 1) {
        for (a.push('<em class="pull-rs-title">相关搜索：</em>'), 'undefined' != typeof t && 'undefined' != typeof t.flag && 'undefined' != typeof t.query && 'undefined' != typeof t.url && '1' == t.flag && t.query && t.url && a.push('<a class="pull-rs-Com" target="_blank" ' + 'onmousedown="p(event,202,{event:\'click\',type:\'rsCom\',position:\'pullSearchBox\',url:\'' + t.url + '\'})"  href="' + t.url + '">' + t.query + '</a>'); n > h; h++) e = o[h],
        r = '/search/index?ct=201326592&st=-1&cl=2&lm=-1&nc=1&rps=2&ie=utf-8&tn=baiduimage&pv=&fm=rs' + (h + 1) + '&word=' + encodeURIComponent(e[0]) + '&oriquery=' + u + '&ofr=' + u + '&ctd=' + + new Date + '^00_' + i(window).width() + 'X' + window.innerHeight,
        this.pageModel.get('hs') - 0 && (r += '&hs=' + this.pageModel.get('hs')),
        a.push('<a class="pull-rs" target="_self" onmousedown="p(event,10,{ps:\'h\',tp:\'a\',r:' + h + ', rq:\'' + e[1] + '\'})" href="' + r + '">' + e[0] + '</a>');
        this.hasRS = !0
      }
      this.displayRS(a)
    }
  },
  displayRS: function (s) {
    this.hasRS ? this.$rsCon.html(s.join(''))  : this.$rsCon.hide()
  },
  showRS: function () {
    this.$rsCon && !this.rsVisible && this.hasRS && (this.$rsCon.animate({
      height: '23px'
    }, 300), this.rsVisible = !0)
  },
  hideRS: function () {
    this.$rsCon && this.rsVisible && this.hasRS && (this.rsVisible = !1, this.$rsCon.css('height', '0px').stop())
  },
  initValue: function (s, t) {
    s && t && t.currentTopValue !== s.value && (t.currentTopValue = t.value = s.value)
  },
  init: function (s, t) {
    this.$wrapper = i('#pullSearch'),
    this.$rsCon = i('#pullRS'),
    this.$wrapper && s && this.initRS(s, t)
  },
  update: function (s, t) {
    var e = i('#topRS');
    if (e && e.offset() && (topRsPos = e ? e.offset().top : 0), s > i('#search').height()) {
      if (i('#stsug').css('top', '0'), this.initValue(i('#pullSearch .s_ipt') [0], i('#kw') [0]), this.$wrapper.show(), !this.hasRS || !e || !e.offset()) return;
      s > topRsPos + 35 ? this.showRS()  : topRsPos + 35 >= s && this.hideRS(),
      this.trigger('search-box-switch', {
        state: 'fixed'
      })
    } else this.hideRS(),
    this.$wrapper.hide(),
    this.trigger('search-box-switch', {
      state: 'top'
    }),
    i('#stsug').css('top', '-30px')
  }
}),
t
});
; /*!searchresult:widget/ui/controls/suggBox/suggBox.js*/
define('searchresult:widget/ui/controls/suggBox/suggBox', function (t) {
function e(t) {
  this.options = {
    sugProdName: 'image',
    searchInputId: 'kw',
    pullInputID: 'kw3',
    searchID: 'search',
    pullID: 'pullSearch'
  },
  this.model = t,
  this.form = null
}
var i,
s = t('common:widget/ui/base/base'),
u = (t('searchresult:widget/ui/utils/utils'), t('common:widget/ui/base/events')),
o = t('common:widget/ui/suggest/suggestion'),
n = t('common:widget/ui/SugRec/SugRec'),
p = t('common:widget/ui/sugHistory/sugHistory');
return s.extend(e.prototype, u, {
  init: function (t) {
    var e = this.options.searchInputId,
    u = this.options.pullInputID,
    h = (this.options.sugProdName, this);
    this.$topInput = s('#' + e),
    this.$topParent = this.$topInput.parent(),
    this.topOffset = this.$topParent.offset(),
    this.inputWidth = this.$topParent.outerWidth() - 2,
    this.inputHeight = this.$topParent.outerHeight(),
    this.$win = s(window),
    this.$search = s('#' + this.options.searchID),
    this.$pull = s('#' + this.options.pullID),
    i = this;
    var a = samplekey.match('PC_INDEX_HISTORY_SUG:1'),
    r = this.$topInput.val(),
    l = function () {
      i.$win.width() < 1217 ? (i.$search.addClass('narrow'), i.$pull.addClass('narrow'))  : (i.$search.removeClass('narrow'), i.$pull.removeClass('narrow')),
      i.inputWidth = i.$topParent.outerWidth() - 2
    };
    if (l(), a) {
      var d = s.cookie.get('indexPageSugList');
      d = d ? JSON.parse(d)  : [
      ];
      var f = new p({
        historyKey: 'indexPageSugList',
        fm: 'result',
        offsetT: 4,
        offsetL: 9,
        width: i.inputWidth + 1,
        page: 1102110,
        samplekey: samplekey,
        query: r
      });
      f.init(d)
    } else {
      var c = new n({
        offsetL: 9,
        offsetT: 4,
        width: i.inputWidth + 1,
        page: 1102111,
        query: r,
        samplekey: samplekey
      });
      c.init(t)
    }
    this.topSug = new o({
      el: this.$topInput,
      formElement: document.f1
    });
    var g = (window.samplekey || '').match(/UI_PC_NAV_EXP:1/),
    m = this.topOffset.top + this.inputHeight - 1;
    this.topSug.css({
      position: g ? 'fixed' : 'absolute',
      left: this.topOffset.left,
      top: g ? m - this.$win.scrollTop()  : m,
      width: this.inputWidth + 1
    }).on('beforesubmit', this.updateParam);
    var w = document.getElementById(u);
    w && (this.$pullParent = s(w.parentNode), this.pullSug = new o({
      el: w,
      formElement: document.f1
    }), this.pullSug.css({
      left: this.topOffset.left - 20,
      top: this.topOffset.top + this.inputHeight - 1,
      width: this.inputWidth + 1
    }).on('beforesubmit', this.updateParam), (window.samplekey || '').match(/UI_PC_NAV_EXP:1/) || this.$win.scroll(function () {
      var t = h.$win.scrollTop();
      h.hideSug(t)
    }), this.$win.on('resize', function () {
      l();
      var t = {
        width: i.inputWidth + 1
      };
      i.topSug && i.topSug.css(t),
      i.pullSug && i.pullSug.css(t),
      c && c.update && c.update(t),
      f && f.update && f.update(t)
    }))
  },
  render: function () {
  },
  reSetAllInput: function (t) {
    this.topSug.inputWatcher.setValue(t.value),
    this.pullSug.inputWatcher.setValue(t.value)
  },
  updateParam: function (t) {
    this.form = t.form;
    var e = t.value,
    s = t.originValue,
    u = t.index;
    e != s && (i.reSetAllInput(t), i.createInput('f', '3', this.form), i.createInput('oq', s, this.form), i.createInput('rsp', u, this.form))
  },
  createInput: function (t, e, i) {
    if ('undefined' == typeof i.key) {
      var s = document.createElement('input');
      s.type = 'hidden',
      s.name = t,
      s.value = e,
      i.appendChild(s)
    } else i.name.value = e
  },
  hideSug: function (t) {
    44 >= t ? this.pullSug.hide()  : (this.pullSug.hide().css({
      top: this.$pullParent.offset().top + this.inputHeight - 1
    }), this.topSug.hide())
  }
}),
e
});
; /*!searchresult:widget/ui/controls/fixedSearchBox/fixedSearchBox.js*/
define('searchresult:widget/ui/controls/fixedSearchBox/fixedSearchBox', function (e) {
function t(e, t) {
  this.html = '',
  this.model = e,
  this.pageModel = t,
  this.hasResult = this.model.get('hasResult'),
  this.$container = i('body'),
  this.rsBox = new l(this.model, this.pageModel),
  this.isload = !1,
  this.sug = new o(this.model),
  this.cg = this.model && this.model.model && this.model.model.get('cg')
}
{
  var i = e('common:widget/ui/base/base'),
  s = (e('searchresult:widget/ui/utils/utils'), e('common:widget/ui/base/events')),
  l = e('searchresult:widget/ui/controls/fixedSearchBox/fixedRSBox/fixedRSBox'),
  o = e('searchresult:widget/ui/controls/suggBox/suggBox');
  e('searchresult:widget/ui/statistic/statistic')
}
return i.extend(t.prototype, s, {
  init: function (e, t) {
    if (!this.isload) {
      if (!this.hasResult) return;
      var i = (this.model.get('needIE'), this.model.get('jit'), this.model.get('showHot'));
      this._render(i),
      this._bindEvent(),
      this.rsBox.init(e, t)
    }
  },
  _render: function (e) {
    {
      var t = this.createHtml(e);
      i('#pullSearch')
    }
    i(t).appendTo(this.$container),
    i('#pullSearch').append(i('#search .s_nav .searchform').clone(!0)),
    i('#pullSearch').append(i('<div id="pullRS"></div>').clone(!0)),
    i('#pullSearch #kw') && (i('#pullSearch #kw') [0].id = 'kw3'),
    e && i('#pullSearch').append(i('<span id="pull-hot-query-con"></span>').clone(!0))
  },
  changeValue: function () {
    i('#kw').val(i('#pullSearch .s_ipt').val())
  },
  createHtml: function () {
    var e = 'display: none;';
    return ('head' === this.cg || 'wallpaper' === this.cg) && (e = 'display: none; padding-left: 20px;'),
    this.html = '<div id="pullSearch" style="' + e + '"><a href="/" class="ps-logo"><img src="//img0.bdstatic.com/img/image/ps-logo.png" width="117" height="38"></a>NaN',
    this.html
  },
  update: function (e, t) {
    if (!(window.samplekey || '').match(/UI_PC_NAV_EXP:1/)) {
      this.rsBox.update(e, t);
      var s = 'head' === this.cg || 'wallpaper' === this.cg;
      if (e > 140) {
        var l = (s ? 153 : 173) + 'px';
        i('#stcontent').css({
          position: 'fixed',
          top: '8px',
          left: l
        })
      } else i('#stcontent').css({
        position: 'absolute',
        top: '-2px',
        left: 0
      })
    }
  },
  _bindEvent: function () {
    var e = this;
    i('#pullSearch .s_ipt').keyup(function () {
      e.changeValue()
    });
    var t = '';
    e.model && e.model.model && e.model.model.tempData && (t = e.model.model.tempData.get('hotWords')),
    e.sug.init(t)
  }
}),
t
});
; /*!searchresult:widget/ui/controls/floatBox/floatBoxClass/floatBoxClass.js*/
define('searchresult:widget/ui/controls/floatBox/floatBoxClass/floatBoxClass', function (t) {
function i(t) {
  this.defaultOpts = {
    width: 300,
    height: 400,
    detailUrl: '',
    tpl: '<div class="people-wrap" style="position: absolute; overflow: hidden; background: #f7f7f7;top:0px; left:0px;padding: 0px; "><div class="people-mask"></div><div class="people-img"><a onclick = "p(event,201,{p:201,url:this.href,type:\'people\',pos:\'pic\',action:1})" target="_blank" href="{{=it.detailURL}}"><img  style="{{=it.imgCssText}}" title="" onload=""  src="{{=it.image}}"/></a></div><div id="peopleDesc" class="people-desc"><div id="peopleDescMask" class="people-desk-mask"></div><p class="desc"><a onclick = "p(event,201,{p:201,url:this.href,type:\'people\',pos:\'digest\',action:1})" target="_blank" href="{{=it.url}}">{{=it.abstract}}</a></p><p class="from-link">--<a onclick = "p(event,201,{p:201,url:this.href,type:\'people\',pos:\'fm\',action:1})" target="_blank" href="{{=it.url}}">百度百科</a></p></div></div>'
  },
  this.$container = null,
  this.$el = null,
  this.showLoged = 0,
  this.model = t,
  this.data = {
  },
  this.options = e.extend({
  }, this.defaultOpts)
}
{
  var e = t('common:widget/ui/base/base'),
  a = t('common:widget/ui/utils/utils'),
  s = t('searchresult:widget/ui/utils/utils');
  t('common:widget/ui/base/events')
}
return e.extend(i.prototype, {
  init: function (t, i, e, a) {
    if (t) {
      this.panelCtr = i,
      this.insertStrategy = e;
      {
        s.trim(this.model.get('queryWord'))
      }
      this.containerUri = a || '#imgid',
      this.data = t,
      this.bindEvent()
    }
  },
  bindEvent: function () {
    var t = this,
    i = !1;
    this.panelCtr.on('panelAppendStart', function (e) {
      if ('.pageNum' + e.pageNum == t.containerUri) {
        i = t.model.getFilterState().isDefaultFilter;
        var a = e.opt.minBaseLineHeight;
        t.options.margin = e.opt.margin,
        t.options.height = a,
        t.createHtml();
        var s = t.$el.height() > a ? 2 : 1,
        h = i ? {
          startLine: 1,
          pageNum: e.pageNum,
          width: t.$el.width() + t.options.margin,
          height: t.$el.height(),
          endLine: s
        }
         : {
        };
        t.insertStrategy.init(h)
      }
    }),
    this.panelCtr.on('panelAppendPosUpdated', function (e) {
      '.pageNum' + e.pageNum == t.containerUri && 1 == i && t.render()
    })
  },
  render: function () {
    this.show()
  },
  createHtml: function () {
    var t = this.data.imageWidth || this.data.pic_width || 0,
    i = this.data.imageHeight || this.data.pic_height || 0;
    t = parseInt(t),
    i = parseInt(i),
    i > t && i > 1.2 * this.options.height && (this.options.height = 2 * this.options.height + this.options.margin);
    var s = this.options.height,
    h = this.options.width,
    n = this.zoomImg(t, i, s, h);
    this.data.image = a.httpsTimg({
      imgUrl: this.data.image || this.data.pic
    }),
    this.data.url = this.data.url ? this.data.url : this.data.original_url,
    this.data.abstract = this.data.abstract ? this.data.abstract : this.data.content,
    this.data.imgCssText = 'display:block;width:' + n.width + 'px;left:' + n.left + 'px;top:' + n.top + 'px',
    this.data.imgurl = this.data.link || this.data.url,
    this.data.url += ( - 1 == this.data.url.indexOf('?') ? '?' : '&') + 'from=image',
    this.data.detailURL = this.getDetailURL({
    }),
    this.dotFn || (this.dotFn = doT.compile(this.options.tpl));
    var o = this.dotFn(this.data);
    this.$el = e(o),
    this.$el.height(n.height),
    this.$el.width(h),
    this.$el.find('#peopleDesc').css('width', h),
    !(i >= 300 && i / t > 1 && 1.6 > i / t) && t / i * 158 > 120 && i > 120 && e(this.defaultOpts.tpl).addClass('single-line')
  },
  show: function () {
    if (this.$container = e(this.containerUri), this.$el) {
      this.$container.append(this.$el);
      var t = Math.max(this.$container[0].offsetHeight, parseInt(this.$container.height()) || 0);
      this.$container.height(Math.max(t, 388)),
      this.$el.css('display', 'block'),
      this.showLoged++
    }
  },
  hidden: function () {
    this.defaultOpts.tpl && this.$el.hide()
  },
  getDetailURL: function (t) {
    this.detailFormat || (this.detailFormat = doT.compile(this.options.detailUrl));
    var i = this.detailFormat(t);
    return i
  },
  reset: function () {
  },
  zoomImg: function (t, i, e, a) {
    var s = {
    },
    h = t / i,
    n = a / e;
    return s.left = 0,
    s.top = 0,
    h > n ? (s.height = e, s.width = e * h, s.width > a && (s.left = (a - s.width) / 2))  : (s.height = e, s.width = a, s.height > e && (s.top = (e - s.height) / 2)),
    s.margin = this.options.margin || 0,
    s
  },
  forbidden: function () {
  }
}),
i
});
; /*!searchresult:widget/ui/controls/floatBox/AldBox/AldBox.js*/
define('searchresult:widget/ui/controls/floatBox/AldBox/AldBox', function (e) {
function i(e) {
  this.container = null,
  this.model = e
}
var t = e('common:widget/ui/base/base'),
n = (e('searchresult:widget/ui/utils/utils'), e('searchresult:widget/ui/controls/floatBox/floatBoxClass/floatBoxClass'));
return t.extend(i.prototype, n, {
  init: function (e, i, t, n) {
    window.ecom && window.ecom.ma && (this.containerUri = n || '#imgid', this.panelCtr = i, this.insertStrategy = t, setTimeout(function () {
    }, 100), window.ecom && window.ecom.ma && window.ecom.ma.image && window.ecom.ma.image.ald && this.bindEvent())
  },
  bindEvent: function () {
    var e = this,
    i = window.ecom.ma.image.ald.getArea(),
    t = !1;
    this.panelCtr.on('panelAppendStart', function (n) {
      if ('.pageNum' + n.pageNum == e.containerUri) {
        t = e.model.getFilterState().isDefaultFilter,
        e.margin = n.opt.margin,
        e.createHtml();
        var a = t ? {
          startLine: 1,
          pageNum: n.pageNum,
          width: i.width + e.margin,
          height: i.height + e.margin,
          endLine: 1
        }
         : {
        };
        e.insertStrategy.init(a)
      }
    }),
    this.panelCtr.on('panelAppendPosUpdated', function (i) {
      '.pageNum' + i.pageNum == e.containerUri && 1 == t && e.render()
    })
  },
  render: function () {
    var e = 'pl_ald_nike';
    window.ecom.ma.image.ald.getId && (e = window.ecom.ma.image.ald.getId()),
    t('<div id=\'' + e + '\' style=\'position:absolute;top:0px;left:0px;z-index:10;\'></div>').appendTo('.pageNum0'),
    window.ecom.ma.image.ald.show()
  },
  createHtml: function () {
  }
}),
i
});
; /*!searchresult:widget/ui/controls/floatBox/baikeBox/baikeBox.js*/
define('searchresult:widget/ui/controls/floatBox/baikeBox/baikeBox', function (t) {
function e(t) {
  this.defaultOpts = {
    width: 300,
    height: 400,
    detailUrl: '/search/detail?ct=503316480&z={{=it.z}}&tn=baiduimagedetail&ipn=d&word={{=it.queryWordEnc}}&ie=utf-8&in={{=it.currentIndex}}&cl={{=it.cl}}&lm={{=it.lm}}&st={{=it.st}}&cs={{=it.cs}}&os={{=it.os}}&pn=-1&rn=1&di=&ln={{=it.listNum}}&fr={{=it.fr}}&fm={{=it.fm}}&fmq={{=it.fmq}}&ic={{=it.ic}}&s={{=it.s}}&se={{=it.se}}&sme={{=it.sme}}&tab={{=it.tab}}&width={{=it.width}}&height={{=it.height}}&face={{=it.face}}&is={{=it.is}}&istype={{=it.istype}}#pn-1&-1&di&objURL{{=it.encodeurl}}&fromURL{{=it.encodefromurl}}&W{{=it.imgWidth}}&H{{=it.imgHeight}}&T&S&TP',
    tpl: '<div class="people-wrap" style="position: absolute; overflow: hidden; background: #f7f7f7;top:0px; left:0px;padding: 0px; "><div class="people-mask"></div><div class="people-img"><a onclick = "p(event,201,{p:201,url:this.href,type:\'people\',pos:\'pic\',action:1})" target="_blank" href="{{=it.detailURL}}"><img  style="{{=it.imgCssText}}" title="" onload=""  src="{{=it.image}}"/></a></div><div id="peopleDesc" class="people-desc"><div id="peopleDescMask" class="people-desk-mask"></div><p class="desc"><a onclick = "p(event,201,{p:201,url:this.href,type:\'people\',pos:\'digest\',action:1})" target="_blank" href="{{=it.url}}">{{=it.abstract}}</a></p><p class="from-link">--<a onclick = "p(event,201,{p:201,url:this.href,type:\'people\',pos:\'fm\',action:1})" target="_blank" href="{{=it.url}}">百度百科</a></p></div></div>'
  },
  this.$container = null,
  this.$el = null,
  this.showLoged = 0,
  this.model = t,
  this.data = {
  },
  this.options = i.extend({
  }, this.defaultOpts)
}
var i = t('common:widget/ui/base/base'),
s = (t('searchresult:widget/ui/utils/utils'), t('searchresult:widget/ui/controls/floatBox/floatBoxClass/floatBoxClass'));
return i.extend(e.prototype, s.prototype, {
  getDetailURL: function () {
    return '/search/detail?ct=503316480&z=' + this.model.get('z') + '&tn=baiduimagedetail&ipn=d&word=' + this.model.get('queryWord') + '&ie=utf-8&in=&cl=' + this.model.get('cl') + '&lm=' + this.model.get('lm') + '&st=' + this.model.get('st') + '&cs=' + this.model.get('cs') + '&os=' + this.model.get('os') + '&pn=-1&rn=1&di=&ln=' + this.model.get('listNum') + '&fr=' + this.model.get('fr') + '&fm=' + this.model.get('fm') + '&fmq=' + this.model.get('fmp') + '&ic=' + this.model.get('ic') + '&s=' + this.model.get('s') + '&se=' + this.model.get('se') + '&sme=' + this.model.get('sme') + '&tab=' + this.model.get('tab') + '&width=' + this.model.get('width') + '&height=' + this.model.get('height') + '&face=' + this.model.get('face') + '&is=' + this.model.get('is') + '&istype=' + this.model.get('istype') + '#pn-1&-1&di&objURL&fromURL&W&H&T&S&TP'
  }
}),
e
});
; /*!searchresult:widget/ui/controls/floatBox/comicBox/comicBox.js*/
define('searchresult:widget/ui/controls/floatBox/comicBox/comicBox', function (t) {
function i(t) {
  this.defaultOpts = {
    width: 250,
    height: 385,
    detailUrl: '',
    tpl: [
      '<div class="comic-wrap comic-border" style="position:absolute;background:#ffffff;top:0px;left:0px;padding:0px;"><div class="comic-serial-label"></div> <div class="comic-img comic-img-owner"><a onclick = "p(event,201,{p:201,url:\'{{=it.url}}\',type:\'comic\',pos:\'pic\',action:1})" target="_blank" href="{{=it.url}}"><div class="comic-cover-shadow" title="{{=it.title}}"></div><img  style="{{=it.faceCssText}}" src="{{=it.image}}"/></a></div><div class="comic-desc-serial"><div class="title"><a onclick = "p(event,201,{p:201,url:\'{{=it.url}}\',type:\'comic\',pos:\'fm\',action:1})" target="_blank" href="{{=it.url}}" title="立即阅读">{{=it.title}}</a></div><p class="author"><a onclick = "p(event,201,{p:201,url:\'{{=it.url}}\',type:\'comic\',pos:\'fm\',action:1})" target="_blank" href="{{=it.url}}" title="立即阅读">作者：{{=it.author}}</a></p><p class="from-link"><a class="button" onclick = "p(event,201,{p:201,url:\'{{=it.url}}\',type:\'comic\',pos:\'fm\',action:1})" target="_blank" href="{{=it.url}}" title="立即阅读连载漫画">点击阅读</a></p></div></a></div>',
      '<div class="comic-wrap" style="position:absolute;background:#f7f7f7;top:0px;left:0px;padding:0px;"><div class="comic-label"></div> <div class="comic-mask"></div><div class="comic-img"><a onclick = "p(event,201,{p:201,url:\'{{=it.url}}\',type:\'comic\',pos:\'pic\',action:1})" target="_blank" href="{{=it.url}}"><img  style="{{=it.imgCssText}}" title="{{=it.title}}"  src="{{=it.image}}"/></a></div><div id="comicDesc" class="comic-desc"><div id="comicDescMask" class="comic-desk-mask"></div><div class="title"><a onclick = "p(event,201,{p:201,url:\'{{=it.url}}\',type:\'comic\',pos:\'digest\',action:1})" target="_blank" href="{{=it.url}}" title="立即查阅">《{{=it.title}}》</a></div><p class="desc"><a onclick = "p(event,201,{p:201,url:\'{{=it.url}}\',type:\'comic\',pos:\'digest\',action:1})" target="_blank" href="{{=it.url}}" title="立即查阅相关漫画专题图片">{{=it.abstract}}</a></p></div></div>'
    ]
  },
  this.$container = null,
  this.$el = null,
  this.showLoged = 0,
  this.model = t,
  this.data = {
  },
  this.options = e.extend({
  }, this.defaultOpts)
}
var e = t('common:widget/ui/base/base'),
a = (t('searchresult:widget/ui/utils/utils'), t('searchresult:widget/ui/controls/floatBox/floatBoxClass/floatBoxClass'));
return e.extend(i.prototype, a.prototype, {
  createHtml: function () {
    var t = this.data.imageWidth || 0,
    i = this.data.imageHeight || 0;
    i > t && (this.options.height = 2 * this.options.height);
    var a = this.options.height,
    s = this.options.width,
    o = this.zoomImg(t, i, a, s);
    this.data.imgCssText = 'display:block;width:' + (o.width - o.margin) + 'px;left:' + o.left + 'px;top:' + o.top + 'px',
    this.data.faceCssText = 'display:block;height:287px;width:200px;left:23px;top:23px;border-top: 1px solid rgb(238, 238, 238);border: 1px solid #f1f1f1;box-shadow: 0 1px 2px 0 rgba(210, 210, 210, 0.31);-webkit-box-shadow: 0 1px 2px 0 rgba(180, 180, 180, 0.55);',
    this.data.imgurl = this.data.link || this.data.url,
    this.data.url += ( - 1 == this.data.url.indexOf('?') ? '?' : '&') + 'from=image',
    this.data.imgurl += ( - 1 == this.data.imgurl.indexOf('?') ? '?' : '&') + 'from=image',
    this.data.detailURL = this.getDetailURL({
    }),
    this.dotFn || (this.dotFn = doT.compile(this.data.id ? this.options.tpl[0] : this.options.tpl[1]));
    var l = this.dotFn(this.data);
    this.$el = e(l),
    this.$el.height(o.height),
    this.$el.width(s),
    this.$el.find('#comicDesc').css('width', s)
  },
  bindEvent: function () {
    var t = this,
    i = !1;
    this.panelCtr.on('panelAppendStart', function (e) {
      if ('.pageNum' + e.pageNum == t.containerUri) {
        i = t.model.getFilterState().isDefaultFilter;
        var a = e.opt.minBaseLineHeight;
        t.options.margin = e.opt.margin,
        t.options.height = a,
        t.createHtml();
        var s = t.$el.height() > a ? 2 : 1,
        o = i ? {
          startLine: 1,
          pageNum: e.pageNum,
          width: t.$el.width() + 3 * t.options.margin,
          height: t.$el.height(),
          endLine: s
        }
         : {
        };
        t.insertStrategy.init(o)
      }
    }),
    this.panelCtr.on('panelAppendPosUpdated', function (e) {
      '.pageNum' + e.pageNum == t.containerUri && 1 == i && t.render()
    })
  }
}),
i
});
; /*!searchresult:widget/ui/controls/floatBox/fcAdBox/fcAd.js*/
define('searchresult:widget/ui/controls/floatBox/fcAdBox/fcAd', function () {
});
; /*!searchresult:widget/ui/controls/floatBox/starBox/starBox.js*/
define('searchresult:widget/ui/controls/floatBox/starBox/starBox', function (t) {
function i(t) {
  this.defaultOpts = {
    width: 220,
    height: 260,
    detailUrl: '',
    tpl: [
      '<div class="star-wrap star-border" style="position: absolute; overflow: hidden; top:0px; left:0px;padding: 0px; "><div class="star-f-con-bg"></div><div class="star-f-con"><a class="star-icon-btn" onclick="p(null,1102101,{});" href="" target="_blank" title="来试试吧"><div class="star-i-title"><img src=//img2.bdstatic.com/static/searchresult/widget/ui/controls/floatBox/starBox/img/star_title_8644601.png /></div></a><a class="star-link-btn" onclick="p(null,1102101,{});" href="" target="_blank" title="来试试吧"><span class="star-pic-num">快去围观</span></a></div></div>'
    ]
  },
  this.$container = null,
  this.$el = null,
  this.showLoged = 0,
  this.model = t,
  this.data = {
  },
  this.options = a.extend({
  }, this.defaultOpts)
}
var a = t('common:widget/ui/base/base'),
e = (t('searchresult:widget/ui/utils/utils'), t('searchresult:widget/ui/controls/floatBox/floatBoxClass/floatBoxClass'));
return a.extend(i.prototype, e.prototype, {
  createHtml: function () {
    var t = 220,
    i = 260,
    e = this.options.height,
    s = this.options.width,
    n = this.zoomImg(t, i, e, s);
    this.data.imgCssText = 'display:block;width:' + (n.width - n.margin) + 'px;left:' + n.left + 'px;top:' + n.top + 'px',
    this.data.faceCssText = 'display:block;height:260px;width:200px;left:23px;top:23px;border-top: 1px solid rgb(238, 238, 238);border: 1px solid #f1f1f1;box-shadow: 0 1px 2px 0 rgba(210, 210, 210, 0.31);-webkit-box-shadow: 0 1px 2px 0 rgba(180, 180, 180, 0.55);',
    a('#topInfoBar').hide(),
    a('#search').height(95),
    this.dotFn || (this.dotFn = doT.compile(this.options.tpl));
    var o = window.ban_data.isInApp ? this.dotFn(this.data)  : '';
    this.$el = a(o),
    this.$el.height(n.height + 10),
    this.$el.width(s),
    window.ban_data && window.ban_data.p5 && this.$el.css('background', 'url(' + window.ban_data.p5 + ')');
    var l = 'http://image.baidu.com/app/tupian';
    this.$el.find('.star-icon-btn').attr('href', l),
    this.$el.find('.star-link-btn').attr('href', l),
    this.$el.find('.star-f-con-bg').height(n.height + 10),
    this.$el.find('.star-f-con').height(n.height + 10),
    this.$el.find('.star-f-con').width(s)
  },
  bindEvent: function () {
    var t = this,
    i = !1;
    this.panelCtr.on('panelAppendStart', function (a) {
      if ('.pageNum' + a.pageNum == t.containerUri) {
        i = t.model.getFilterState().isDefaultFilter;
        var e = a.opt.minBaseLineHeight;
        t.options.margin = a.opt.margin,
        t.options.height = e,
        t.createHtml();
        var s = i ? {
          startLine: 1,
          pageNum: a.pageNum,
          width: t.$el.width() + t.options.margin,
          height: t.$el.height(),
          endLine: 1
        }
         : {
        };
        t.insertStrategy.init(s)
      }
    }),
    this.panelCtr.on('panelAppendPosUpdated', function (a) {
      '.pageNum' + a.pageNum == t.containerUri && 1 == i && t.render()
    })
  }
}),
i
});
; /*!searchresult:widget/ui/controls/hotwordBox/hotwordBox.js*/
define('searchresult:widget/ui/controls/hotwordBox/hotwordBox', function (t) {
function a() {
  this.data = [
  ],
  this.queryObj = {
  }
}
{
  var r = t('common:widget/ui/base/base');
  t('searchresult:widget/ui/statistic/statistic')
}
return r.extend(a.prototype, {
  init: function (t) {
    this.data = window.__resultComArray || [
    ],
    this.hotword = t || null,
    this.data = this.data.concat(),
    void 0 != window.__searchRecom ? (this.queryObj.query = window.__searchRecom.query, this.queryObj.url = window.__searchRecom.url)  : (this.queryObj.query = '', this.queryObj.url = ''),
    this.render()
  },
  render: function () {
    this.createHtml(this.hotword)
  },
  createHtml: function (t) {
    if (t && t.length >= 10) {
      for (var a = '<table cellspacing="0" cellpadding="0" border="0" class="hotWordTable" ><tbody><tr><td class="title1" style="vertical-align: top;" nowrap="nowrap" height="28"><strong class="f14"><a id="hotwordlistinC" >热门推荐</a></strong></td><td class="f14" nowrap="nowrap"><table cellpadding="0" cellspacing="0"><tbody>', e = this.data.length, o = 0; e > o && 4 > o; o++) o % 5 == 0 && (a += 0 == a ? '' : '</tr>', a += '<tr style="line-height:1.5">'),
      a += '<td nowrap="nowrap"><a class="icon_a" target = "_blank" onclick="p(event, 202, {type:\'hotword_ad\',action:\'click\'})" href="' + this.data[o].url + '&fm=hotword_ad">' + this.data[o].query + '</a><span class="icon"></span></td>';
      a += '<td nowrap="nowrap"><a class="icon_a" target="_blank" onclick="p(event, 202, {type :\'searchrecom\',action:\'click\'})" href="' + this.queryObj.url + '">' + this.queryObj.query + '</a><span class="icon"></span></td>',
      this.data.length < 4 && (a += new Array(5 - e).join('<td nowrap="nowrap">&nbsp;</td>')),
      a += '</tr></tbody></table></td></tr></tbody></table>',
      r('#hotWordDiv').html(a)
    }
  }
}),
a
});
; /*!searchresult:widget/ui/utils/timeline.js*/
define('searchresult:widget/ui/utils/timeline', function (n, t, i) {
i.exports = timeLine = function (n) {
  var t,
  i,
  e = 20,
  r = 100,
  u = !0,
  o = 0,
  a = 0,
  c = function (n) {
    return n
  },
  d = function () {
  },
  f = function () {
  };
  n.rander && (d = n.rander),
  n.transition && (c = n.transition),
  n.end && (f = n.end),
  e = n.interval || e,
  r = n.duration || r;
  var s = function (n) {
    n = n || {
    },
    e = n.interval || e,
    r = n.duration || r
  },
  v = function () {
    t = (new Date).getTime(),
    i = t + (u ? r : 0),
    o = 0,
    l()
  },
  l = function () {
    var n = (new Date).getTime();
    return o = (n - t) / r,
    n >= i ? (d(c(o = 1)), void f())  : (d(c(o)), void (a = setTimeout(l, e)))
  };
  return {
    init: s,
    launch: v
  }
}
});
; /*!searchresult:widget/ui/controls/imgPopBox/imgPopBox.js*/
define('searchresult:widget/ui/controls/imgPopBox/imgPopBox', function (t, i, e) {
{
  var a = t('common:widget/ui/base/base'),
  o = t('searchresult:widget/ui/utils/utils'),
  n = t('searchresult:widget/ui/utils/timeline'),
  s = (t('common:widget/ui/base/events'), function (t, i) {
    var e = a(t),
    s = parseInt(o.getOffsetTop(t)) || 0,
    d = parseInt(o.getOffsetLeft(t)) || 0,
    r = parseInt(e.width()) || t.offsetWidth || 0,
    h = parseInt(e.height()) || t.offsetHeight || 0;
    if (!(isNaN(parseInt(i.top)) || isNaN(parseInt(i.left)) || isNaN(parseInt(i.width)) || isNaN(parseInt(i.height)))) {
      var l = i.top - s,
      g = i.left - d,
      f = i.width - r,
      m = i.height - h,
      p = n({
        rander: function (t) {
          e.width(f * t + r),
          e.height(m * t + h),
          e.offset({
            left: g * t + d,
            top: l * t + s
          })
        },
        end: i.end
      });
      p.init(),
      p.launch()
    }
  });
  e.exports = function () {
    function t(t) {
      for (var i, e = 0, a = m.length; a > e; ) {
        try {
          i = m[e],
          i.call(null, t)
        } catch (o) {
        }
        e++
      }
    }
    function i(t) {
      for (var i, e = 0, a = p.length; a > e; ) {
        try {
          i = p[e],
          i.call(null, t)
        } catch (o) {
        }
        e++
      }
    }
    function e(t) {
      m.push(t)
    }
    function n(t) {
      p.push(t)
    }
    function d(t) {
      a(t).appendTo(g)
    }
    function r() {
      return f
    }
    function h(t) {
      var i = a(window),
      e = i.height(),
      n = i.scrollTop(),
      s = o.getParentNode(t, 'li'),
      d = s.offsetHeight,
      r = o.getOffsetTop(s),
      h = a('#pullSearch').height(),
      l = 5,
      g = 3,
      f = r + d - e - n + g,
      m = n + h - r + l;
      f > 0 && window.scrollBy(0, f),
      m > 0 && window.scrollBy(0, - m)
    }
    var l,
    g,
    f,
    m = [
    ],
    p = [
    ],
    c = 0,
    u = 110,
    v = 0,
    x = 9,
    w = 0,
    b = !0,
    T = {
    },
    N = {
    },
    k = '',
    y = '',
    M = - 1,
    W = - 1,
    L = null,
    H = 100,
    I = function () {
      g.is(':hidden') || (g.css('overflow', 'hidden'), s(g, {
        top: T.originTop,
        left: T.originLeft,
        width: T.originWidth,
        height: T.originHeight,
        end: function () {
          g.hide(),
          g.css('overflow', '')
        }
      }))
    },
    A = [
      '<a name="{{=it.linkName}}" target="_blank" href="{{=it.detailURL}}" onmousedown="{{=it.clickFun}}" class="imgLink" style="width:{{=it.imgWidth}}">',
      '<img id="hoverImg" style="width:{{=it.imgWidth}};" src="{{=it.imgURL}}">',
      '</a>',
      '<p class="detailDigest">{{=it.digest}}</p>'
    ].join(''),
    z = doT.template(A),
    B = [
      '<a name="{{=it.linkName}}" target="_blank" href="{{=it.detailURL}}" onclick="{{=it.clickFun}}" class="imgLink" style="width:{{=it.imgWidth}}">',
      '<img id="hoverImg" style="position:relative;width:{{=it.imgWidth}};z-index:100;top:-1px;left:-1px;border:1px solid #dfdfdf;" src="{{=it.imgURL}}">',
      '<span class="albumBorder" style="border:1px solid #dfdfdf;position:absolute;top:0px;left:0px;display:block;width:{{=it.imgWidth}};height:{{=it.imgHeight}}px;border:1px solid #dfdfdf;z-index:99;background:#fff;"></span>',
      '<span class="albumBorder" style="position:absolute;top:2px;left:2px;display:block;width:{{=it.imgWidth}};height:{{=it.imgHeight}}px;border:1px solid #cacaca;z-index:98;background:#fff;"></span>',
      '<span class="imgSetNum" style="position:absolute;bottom:4px;right:0px;z-index:200;">',
      '<span class="imgSetBg"></span>',
      '<span style="position:relative;z-index:10;">共{{=it.imgsetNum}}张</span>',
      '</span>',
      '</a>',
      '<p class="detailDigest">{{=it.digest}}</p>'
    ].join(''),
    O = doT.template(B),
    P = [
      '<a name="{{=it.linkName}}" target="_blank" href="{{=it.detailURL}}" onclick="{{=it.clickFun}}" class="imgLink" style="width:{{=it.imgWidth}}">',
      '<img id="hoverImg" style="position:relative;width:{{=it.imgWidth}};z-index:100;top:-1px;left:-1px;border:1px solid #dfdfdf;" src="{{=it.imgURL}}">',
      '<span class="albumBorder" style="border:1px solid #dfdfdf;position:absolute;top:0px;left:0px;display:block;width:{{=it.imgWidth}};height:{{=it.imgHeight}}px;border:1px solid #dfdfdf;z-index:99;background:#fff;"></span>',
      '<span class="albumBorder" style="position:absolute;top:2px;left:2px;display:block;width:{{=it.imgWidth}};height:{{=it.imgHeight}}px;border:1px solid #cacaca;z-index:98;background:#fff;"></span>',
      '</a>',
      '<div class="imgSetNum smallImgset" style="position:relative;z-index:200;">',
      '<span class="smallimgset-inner">共{{=it.imgsetNum}}张</span>',
      '</div>',
      '<p class="detailDigest">{{=it.digest}}</p>'
    ].join(''),
    R = doT.template(P),
    U = function (t) {
      var e = a(t);
      if (t != f && e.hasClass('img-hover')) {
        var n = o.getParentNode(t, 'a'),
        d = o.getParentNode(t, 'li');
        if (n && d) {
          f = t;
          var r = t.name.replace('pn', '');
          f.pn = r;
          var h = 0,
          l = 0,
          m = 0,
          p = (d.getElementsByTagName('p') [0], z),
          c = 0;
          if ( - 1 !== d.className.indexOf('imgset')) {
            d = o.getParentNode(t, 'div'),
            h = 6,
            l = 2 + v,
            m = v,
            p = O,
            c = t.getAttribute('data-imgsetnum');
            var M = t.getAttribute('data-issmall');
            '1' === M && (p = R)
          }
          var W = o.getOffsetLeft(d) + v,
          H = o.getOffsetTop(d),
          I = Math.min(d.offsetHeight - 2 * v + 2 * m, n.offsetHeight),
          A = Math.min(d.offsetWidth - 2 * v + 2 * m, n.offsetWidth),
          B = parseInt(t.getAttribute('data-width')),
          P = parseInt(t.getAttribute('data-height')),
          U = t.offsetWidth,
          C = t.offsetHeight,
          S = f.src;
          f.contentSign = t.getAttribute('data-cs') || 0;
          var _ = t.getAttribute('data-hover'),
          j = t.getAttribute('data-large'),
          E = t.getAttribute('data-mid');
          k = o.uncompile(t.getAttribute('data-origin')),
          y = o.uncompile(t.getAttribute('data-furl'));
          var X,
          Y = N[t.name] || S;
          X = B > P ? o.zoom(B, P, 1.3 * Math.max(U, C))  : o.zoom(B, P, 1.3 * Math.max(U, C));
          var q = (X.width, X.height),
          G = o.getOffsetLeft(n) + v,
          J = o.getOffsetTop(n),
          K = n.href,
          Q = n.name,
          V = t.getAttribute('data-clickStr'),
          Z = Math.max(W, G),
          $ = Math.min(H, J),
          ti = X.width;
          u >= ti && (ti = u, ti = Math.max(ti, A));
          var ii = X.height + 55,
          ei = p({
            aHeight: X.height,
            imgURL: Y,
            imgsetNum: c,
            imgHeight: X.height,
            imgWidth: ti > X.width ? X.width + 'px' : '100%',
            detailURL: K,
            clickFun: V,
            linkName: Q
          });
          g.html(ei);
          var ai = F(Math.max(Z + Math.min(A - ti, 0) / 2 + l, 20) - x, $ + (I - q) / 2 + h - x, ti, ii),
          oi = n.offsetWidth,
          ni = n.offsetHeight,
          si = F(Z - (Math.max(A, oi) - A) / 2 - x, $ - x, Math.max(A, oi), Math.max(I, ni));
          T = {
            top: ai.top,
            left: ai.left,
            width: ti,
            height: ii,
            originTop: si.top + n.offsetTop,
            originLeft: si.left,
            originWidth: Math.max(A, oi),
            originHeight: Math.max(I, ni) + x
          },
          g.width(T.originWidth),
          g.height(T.originHeight),
          g.offset({
            left: T.originLeft,
            top: T.originTop
          }),
          g.css('overflow ', 'hidden'),
          g.show();
          {
            t.id.replace('img_', '')
          }
          s(g, {
            top: ai.top + n.offsetTop,
            left: ai.left,
            width: ti,
            height: ii,
            end: function () {
              g.css('overflow ', ''),
              g.height('auto');
              var t = g.find('img'),
              e = a('.hover-extra-info', g),
              o = e[0];
              if (t) {
                var n = t.offsetHeight,
                s = t.offsetWidth;
                n && t.height(n),
                s && t.width(s),
                o && s && o.width(s - 40),
                i(t),
                clearTimeout(L)
              }
              o && o.offsetHeight > 28 && (e.addClass('host-info-wrap'), o.width('auto'))
            }
          }),
          D([_,
          j,
          E,
          S], t.name),
          b = !1,
          w = (new Date).getTime()
        }
      }
    },
    C = new Image,
    D = function (t, i) {
      if (!N[i]) {
        var e,
        o,
        n = t.length,
        s = !1;
        for (o = 0; n > o && !(e = t[o]); o++);
        C.onerror = function () {
          for (e = ''; ++o < n && !(e = t[o]); );
          e && setTimeout(function () {
            C.src = e
          }, 0)
        },
        C.onload = function () {
          if (!s) {
            s = !0;
            var t = a('#hoverImg') [0],
            e = N[i] = C.src;
            t && (t.src = e)
          }
        },
        C.src = e
      }
    },
    F = function (t, i, e, o) {
      var n = a(window),
      s = n.scrollTop(),
      d = n.width(),
      r = n.height();
      return t = Math.min(Math.max(t, 25), d - e - 20),
      i = Math.max(Math.min(i, s + r - o - 40), Math.max(94, s)),
      {
        left: t,
        top: i
      }
    },
    S = function () {
      l = a('#imgid'),
      g = a('<div id=\'imgDetail\'></div>'),
      g.appendTo(a('body')),
      g && (g.mouseover(function () {
        clearTimeout(c)
      }), g.mouseout(function (t) {
        clearTimeout(c);
        for (var i = t.relatedTarget || t.toElement; i && i !== this; ) i = i.parentNode;
        i !== this && I()
      }), l.mousemove(function (i) {
        var e = i.target,
        n = i.clientX,
        s = i.clientY;
        if (Math.abs(n - M) <= 1 && Math.abs(s - W) <= 1) return void i.stopPropagation(i);
        M = n,
        W = s;
        var d = o.getParentNode(e, 'li'),
        r = a(e);
        if ('img' != e.tagName.toLowerCase() && r.hasClass('img-hover') && d) {
          var h = d.find('img');
          h.length > 0 && (e = h[0])
        }
        return 'img' != e.tagName.toLowerCase() ? (clearTimeout(c), void (c = setTimeout(I, 0)))  : (clearTimeout(c), void (c = setTimeout(function () {
          t(e),
          U(e)
        }, H)))
      }))
    };
    e(h);
    var _ = function (t) {
      H = t
    };
    return {
      init: S,
      addPreFn: e,
      addAfterFn: n,
      appendChild: d,
      setHoverTime: _,
      getImgDOM: r
    }
  }()
}
});
; /*!searchresult:widget/ui/controls/mapBox/DragSupport/DragSupport.js*/
define('searchresult:widget/ui/controls/mapBox/DragSupport/DragSupport', function (e) {
function t() {
  this.container = null,
  this.dragDOM = null,
  this.SENSE = 10,
  this.MOVE_CURSOR = 'url(//img0.bdstatic.com/img/image/imgsearch/texing/img/grabhand.cur), move',
  this.enableDrag = !0,
  this.triggerEvent = !0
}
var n = e('common:widget/ui/base/base'),
o = (e('searchresult:widget/ui/utils/utils'), e('common:widget/ui/base/events'));
return n.extend(t.prototype, o, {
  constructor: t,
  init: function (e, t) {
    this.container = e,
    this.dragDOM = t,
    this.dragIt()
  },
  dragIt: function () {
    function e(e) {
      if (!l) return !0;
      l.style.cursor = s.MOVE_CURSOR,
      e = e || window.event;
      var t = e.clientX - a,
      n = e.clientY - u;
      return l.style.left = t + 'px',
      l.style.top = n + 'px',
      c || (c = Math.abs(e.clientX - o) > s.SENSE || Math.abs(e.clientY - r) > s.SENSE),
      e.preventDefault ? e.preventDefault()  : e.returnValue = !1,
      s.triggerEvent && (s.triggerEvent = !1, s.trigger('JDrag', {
      })),
      !1
    }
    function t() {
      document.removeEventListener ? (document.removeEventListener('mousemove', e, !0), l.onmouseup = null)  : l.detachEvent && (l.releaseCapture(), l.detachEvent('onmousemove', e), l.detachEvent('onmouseup', n)),
      s.enableDrag || (l.style.cursor = ''),
      c = !1,
      l.onmouseup = s.enableDrag ? g : null
    }
    function n(e) {
      e = e || window.event;
      e.srcElement || e.target;
      s.enableDrag && (e.stopPropagation ? (e.stopPropagation(), e.preventDefault())  : (e.cancelBubble = !0, e.returnValue = !1)),
      t()
    }
    if (!this.container) return !1;
    var o,
    r,
    a,
    u,
    i = this.container,
    s = this,
    l = this.dragDOM,
    c = !1,
    g = function (e) {
      e = e || window.event,
      e.stopPropagation ? e.stopPropagation()  : e.cancleBubble = !0
    };
    i.onmousedown = function (t) {
      l = s.dragDOM,
      t = t || window.event;
      var i = t.srcElement || t.target;
      return i === l && s.enableDrag ? (l._unclick = !0, o = t.clientX, r = t.clientY, a = o - (parseInt(l.style.left) || 0), u = r - (parseInt(l.style.top) || 0), void (document.addEventListener ? (document.addEventListener('mousemove', e, !0), l.onmouseup = n, t.stopPropagation(), t.preventDefault())  : (l.setCapture(), l.attachEvent('onmousemove', e), l.attachEvent('onmouseup', n), t.cancelBubble = !0, t.returnValue = !1)))  : !0
    },
    i.onmouseout = function (e) {
      e = e || window.event;
      var n = e.toElement || e.relatedTarget;
      n !== l && n !== i && c && (t(), document.onmousedown = function () {
        i.onmouseup = null,
        document.onmousedown = null
      }, i.onmouseup = function (e) {
        e = e || window.event,
        e.stopPropagation ? e.stopPropagation()  : e.cancelBubble = !0,
        i.onmouseup = null
      })
    },
    this.dragDOM.style.cursor = this.MOVE_CURSOR
  },
  enable: function () {
    this.enableDrag = !0,
    this.dragDOM.style.cursor = this.MOVE_CURSOR
  },
  disable: function () {
    this.enableDrag = !1,
    this.dragDOM.style.cursor = 'default'
  }
}),
t
});
; /*!searchresult:widget/ui/controls/mapBox/ZoomProvider/ZoomProvider.js*/
define('searchresult:widget/ui/controls/mapBox/ZoomProvider/ZoomProvider', function (t, e, o) {
var i = t('common:widget/ui/base/base'),
n = t('common:widget/ui/base/events'),
s = function (t) {
  this.defaultOptions = {
    minRate: 0.1,
    maxRate: 10,
    zoomRate: 0.1,
    clickZoomRate: 0.25,
    dbClickZoomRate: 0.25,
    btnZoom: !0,
    wheelZoom: !1,
    dbClickZoom: !1
  },
  this.$bigButton = null,
  this.$smallButton = null,
  this.$con = null,
  this.options = i.extend(!0, {
  }, this.defaultOptions, t || {
  }),
  this.ZOOM_RATE = this.options.zoomRate,
  this.CLICK_ZOOM_RATE = this.options.clickZoomRate,
  this.minRate = this.options.minRate,
  this.maxRate = this.options.maxRate,
  this._listeners = {
  },
  this.enableBig = !0,
  this.enableSmall = !0
};
i.extend(s.prototype, n, {
  constructor: s,
  init: function (t, e, o) {
    function i(t) {
      n.wheel(t)
    }
    this.$bigButton = t,
    this.$smallButton = e,
    this.$con = o;
    var n = this;
    this.options.wheelZoom && (this.$con.on && this.$con.on('DOMMouseScroll', i, !0), this.$con[0].onmousewheel = i),
    this.options.btnZoom && this.buttonZoomIt(),
    this.options.dbClickZoom && this.$con.dblclick(function (t) {
      n.dbClickZoomIt(t)
    })
  },
  doZoom: function (t, e, o, n, s) {
    if (!('IMG' !== t.tagName || t.zoomRate - this.minRate <= 0.00001 && !s || t.roomRate >= this.maxRate && s || 1 != t.__loaded)) {
      var a,
      l,
      h = (i(t), parseInt(t.style.left)),
      r = parseInt(t.style.top),
      m = 100,
      c = parseFloat(t.style.width) || t.offsetWidth,
      g = (parseFloat(t.style.height) || t.offsetHeight, t.srcWidth),
      d = t.srcHeight,
      f = t.parentNode.offsetWidth,
      u = t.parentNode.offsetHeight;
      e >= this.maxRate ? e = this.maxRate : e - this.minRate < 0.000001 && (e = this.minRate),
      a = e * g,
      l = e * d;
      var Z = a / c * (h - o) + o,
      _ = a / c * (r - n) + n;
      m > Z + a ? Z = m - a : Z > f - m && (Z = f - m),
      m > _ + l ? _ = m - l : _ > u - m && (_ = u - m),
      t.__zoomed = !0,
      t.__zoomForLog = !0,
      t.zoomRate = e,
      this.currentZoomRate = e,
      this.trigger('zoom', {
        imgRenderWidth: a,
        imgRenderHeight: l,
        imgRenderLeft: Z,
        imgRenderTop: _,
        imgRenderRate: e
      })
    }
  },
  buttonZoomIt: function () {
    function t(t, e) {
      var o,
      n = i.$con.children() [0],
      s = parseInt(n.style.left) || 0,
      a = parseInt(n.style.top) || 0,
      l = parseInt(n.style.width) || n.offsetWidth,
      h = parseInt(n.style.height) || n.offsetHeight,
      r = i.$con.offsetWidth / 2,
      m = i.$con.offsetHeight / 2,
      c = l / 2,
      g = h / 2;
      e || (t *= - 1),
      o = (l + n.srcWidth * t) / n.srcWidth,
      r > s && s + l > r && m > a && a + h > m || (r = s + c, m = a + g),
      i.doZoom(n, o, r, m, e)
    }
    if (this.$con) {
      var e,
      o = 150,
      i = this;
      this.$bigButton.on('mousedown', function (n) {
        clearInterval(e),
        t(i.CLICK_ZOOM_RATE, !0),
        e = setInterval(function () {
          t(i.ZOOM_RATE, !0)
        }, o);
        var s = i.$con.children() [0];
        s && !s.__hasBigBtnLogged && (i.trigger('ImageZoomed', {
          event: n || window.event,
          target: s,
          to: 'big',
          zoom: 'btn'
        }), s.__hasBigBtnLogged = !0)
      }),
      this.$smallButton.on('mouseup', function () {
        clearInterval(e),
        e = null
      }),
      this.$bigButton.on('mouseup', function () {
        clearInterval(e),
        e = null
      }),
      this.$smallButton.on('mousedown', function (n) {
        clearInterval(e),
        t(i.CLICK_ZOOM_RATE, !1),
        e = setInterval(function () {
          t(i.ZOOM_RATE, !1)
        }, o);
        var s = i.$con.children() [0];
        s && !s.__hasSmallBtnLogged && (i.trigger('ImageZoomed', {
          event: n || window.event,
          target: s,
          to: 'small',
          zoom: 'btn'
        }), s.__hasSmallBtnLogged = !0)
      })
    }
  },
  wheel: function (t) {
    t = t || window.event;
    var e = this.getZoomCenter(t);
    if (!e) return !0;
    {
      var o,
      i = this.$con.find('img') [0],
      n = 0,
      s = parseInt(i.style.width) || i.offsetWidth,
      a = (parseInt(i.style.height) || i.offsetHeight, e.centerX),
      l = e.centerY,
      h = i.srcWidth;
      i.srcHeight
    }
    n = t.wheelDelta ? t.wheelDelta : - t.detail,
    n > 0 ? (o = (s + h * this.ZOOM_RATE) / h, this.doZoom(i, o, a, l, !0), i.__hasBigWheelLogged || (this.trigger('ImageZoomed', {
      event: t || window.event,
      target: i,
      to: 'big',
      zoom: 'wheel'
    }), i.__hasBigWheelLogged = !0))  : 0 > n && (o = (s - h * this.ZOOM_RATE) / h, this.doZoom(i, o, a, l, !1), i.__hasSmallWheelLogged || (this.trigger('ImageZoomed', {
      event: t || window.event,
      target: i,
      to: 'small',
      zoom: 'wheel'
    }), i.__hasSmallWheelLogged = !0)),
    t.preventDefault ? (t.preventDefault(), t.stopPropagation())  : (t.cancelBubble = !0, t.returnValue = !1)
  },
  dbClickZoomIt: function (t) {
    t = t || window.event;
    var e = this.getZoomCenter(t);
    if (!e) return !0;
    var o,
    i = this.$con.find('img') [0],
    n = parseInt(i.style.width) || i.offsetWidth,
    s = e.centerX,
    a = e.centerY,
    l = i.width();
    o = (n + l * this.options.dbClickZoomRate) / l,
    this.doZoom(i, o, s, a, !0),
    i.__hasDbclickLogged || (this.trigger('ImageZoomed', {
      event: t || window.event,
      target: i,
      to: 'big',
      zoom: 'dbclick'
    }), i.__hasDbclickLogged = !0)
  },
  getZoomCenter: function (t) {
    if (!this.isZoomImage(t)) return !1;
    var e = this.$con.offset(),
    o = i(document).scrollTop(),
    n = i(document).scrollLeft(),
    s = (this.$con.find('img'), t.clientX + n - e.left),
    a = t.clientY + o - e.top;
    return {
      centerX: s,
      centerY: a
    }
  },
  isZoomImage: function (t) {
    var e = t.target || t.srcElement,
    o = this.$con.find('img') [0];
    return o && o.__loaded && e === o
  },
  enableZoomBig: function () {
    this.enableBig = !0
  },
  disableZoomBig: function () {
    this.enableBig = !1
  },
  enableZoomSmall: function () {
    this.enableSmall = !0
  },
  disableZoomSmall: function () {
    this.enableSmall = !1
  }
}),
o.exports = s
});
; /*!searchresult:widget/ui/controls/mapBox/mapBox.js*/
define('searchresult:widget/ui/controls/mapBox/mapBox', function (t) {
function i(t) {
  this.defaultOpts = {
    maxZoomRate: 3,
    minZoomRate: 0.1,
    initRate: 0.7,
    containerHeight: 640,
    containerMinHeight: 400,
    topAreaHeight: 124,
    normalThumbHeight: 150,
    cursor: 'url(//img0.bdstatic.com/img/image/imgsearch/texing/img/grabhand.cur), move',
    container: '#subway-view-con',
    picContainer: '#subway-view-con > .subway-pic-con',
    zoomSmallBtn: '#subway-view-con .subway-zoom-small',
    zoomBigBtn: '#subway-view-con .subway-zoom-big',
    zoomRate: '#subway-view-con .subway-zoom-rate',
    pcSaveBtn: '#subway-view-con .subway-pc-save-btn',
    wiseSaveBtn: '#subway-view-con .subway-wise-save-btn',
    picInfo: '#subway-view-con .subway-pic-info',
    mapDetailLink: '#subway-view-con .subway-detail-link',
    helpCon: '#subway-view-con .subway-help-area',
    helpCloseBtn: '#subway-view-con .subway-help-area .subway-help-close'
  },
  this.model = t,
  this.container = null,
  this.imageRendered = !1,
  this.options = s.extend({
  }, this.defaultOpts)
}
function e(t) {
  if (g && t) {
    var i = t.width + '&#215;' + t.height;
    t.filesize && '0' != t.filesize && (i += ' , ' + t.filesize + 'KB'),
    g.innerHTML = i
  }
}
function n(t, i) {
  l.style.width = t + 'px',
  l.style.height = i + 25 + 'px',
  d.style.width = t + 'px',
  d.style.height = i + 25 + 'px',
  c.style.width = t - 90 + 'px',
  c.style.height = i - 65 + 'px',
  d.style.display = 'block'
}
function o() {
  d && (d.style.display = 'none')
}
function a(t, i, o) {
  function a(t, i) {
    var e = {
      render: 'table',
      width: 128,
      height: 128,
      typeNumber: - 1,
      correctLevel: QRErrorCorrectLevel.H,
      background: '#ffffff',
      foreground: '#000000',
      text: 'http://image.baidu.com'
    };
    if (i) for (var o in i) i[o] && (e[o] = i[o]);
    var a = new QRCode(e.typeNumber, e.correctLevel);
    a.addData(e.text),
    a.make();
    var s = 3,
    h = 3,
    r = a.getModuleCount(),
    m = a.getModuleCount();
    e.width = s * r,
    e.height = h * m;
    for (var l = '<table style=\'width:' + e.width + 'px;height:' + e.height + 'px;border:0px;margin:5px 0 5px 0;border-collapse:collapse;background-color:' + e.background + ';\'>', c = 0; r > c; c++) {
      for (var d = '<tr style=\'height:' + h + 'px;\'>', g = 0; m > g; g++) {
        var u = '<td style=\'width:' + s + 'px;background-color:' + (a.isDark(c, g) ? e.foreground : e.background) + ';\'></td>';
        d += u
      }
      l += d + '</tr>'
    }
    l += '</table>',
    t.innerHTML = l,
    n(e.width + 90, e.height + 70)
  }
  function h(t, i) {
    var e = {
      width: 128,
      height: 128,
      text: 'http://image.baidu.com'
    };
    if (i) for (var o in i) i[o] && (e[o] = i[o]);
    var a = i.text.replace(/^[\s\u3000]+|[\s\u3000]+$/g, '');
    t.innerHTML = r(a),
    t.getElementsByTagName('img') [0].style.width = i.width + 'px',
    t.getElementsByTagName('img') [0].style.height = i.height + 'px',
    n(e.width + 90, e.height + 65)
  }
  if (t = 'string' == typeof t ? document.getElementById(t)  : t, l = document.getElementById('PQbox'), c = document.getElementById('PQelement'), d = document.getElementById('phoneQrcode'), g = document.getElementById('PQsize'), !(t && l && c && d)) return null;
  var r = function (t, i, e) {
    var n = qrcode(i || 10, e || 'M');
    return n.addData(t),
    n.make(),
    n.createImgTag()
  };
  if (s.browser.ie && parseInt(s.browser.version) <= 7) try {
    a(t, i)
  } catch (m) {
    s.getScript('//img0.bdstatic.com/img/image/qrcode.min.js', function () {
      a(t, i)
    })
  } else try {
    h(t, i)
  } catch (m) {
    s.getScript('//img0.bdstatic.com/img/image/qrcode.plus.js', function () {
      h(t, i)
    })
  }
  e(o)
}
var s = t('common:widget/ui/base/base'),
h = (t('searchresult:widget/ui/utils/utils'), t('common:widget/ui/base/events')),
r = t('searchresult:widget/ui/controls/mapBox/ZoomProvider/ZoomProvider'),
m = t('searchresult:widget/ui/controls/mapBox/DragSupport/DragSupport');
s.extend(i.prototype, h, {
  init: function (t, i) {
    var e = this.options;
    if (this.$container = s(e.container), this.$picContainer = s(e.picContainer), this.$zoomSmallBtn = s(e.zoomSmallBtn), this.$zoomBigBtn = s(e.zoomBigBtn), this.$zoomRate = s(e.zoomRate), this.$pcSaveBtn = s(e.pcSaveBtn), this.$wiseSaveBtn = s(e.wiseSaveBtn), this.$mapDetailLink = s(e.mapDetailLink), this.$picInfoPan = s(e.picInfo), this.$container) {
      if (!this.calculateCity(t, i)) return void this.$container.addClass('subway-no-data');
      this._bindEvents(),
      this.render()
    }
  },
  render: function () {
    if (this.subwayData) {
      var t = s(window).width() - 13 - 90;
      if (t > 0 && t != this.containerWidth) {
        this.containerWidth = t;
        var i = this.calculateSize();
        this.$container.width(i.containerWidth),
        this.$container.height(i.containerHeight),
        this.$picContainer.width(i.picContainerWidth),
        this.$picContainer.height(i.picContainerHeight);
        var e = !0;
        this.imageRendered || (this.showImage(i), e = !1),
        this.updateImage(i, e)
      }
    }
  },
  _bindEvents: function () {
    if (this.subwayData) {
      var t = this;
      this.$pcSaveBtn.on('click', function (i) {
        return i = i || window.event,
        t.saveSubwayPC(i),
        i.returnValue = !1,
        !1
      }),
      this.$wiseSaveBtn.on('click', function (i) {
        i = i || window.event,
        t.saveSubwayWise(i),
        i.returnValue = !1
      }),
      this.$mapDetailLink.attr('href', this.subwayData.mapLink),
      this.$mapDetailLink.on('click', function () {
      });
      var i = s('#qrcodeBtn');
      i && s(i).on('click', function () {
        o()
      }),
      this.on('ImageZoomed', function (i) {
        i && ('wheel' !== i.zoom || t._wheelLoged ? 'btn' !== i.zoom || t._btnLoged ? 'dbclick' !== i.zoom || t._dbclickLoged || (t._dbclickLoged = !0)  : t._btnLoged = !0 : t._wheelLoged = !0)
      }),
      this.on('JDrag', function () {
        t._dragLoged || (t._dragLoged = !0)
      })
    }
  },
  openMapLink: function (t) {
    t = t || window.event,
    this.subwayData
  },
  saveSubwayPC: function () {
    var t = 'http://image.baidu.com/search/down?tn=download&ipn=dwnl&word=download&ie=utf8&fr=result-subway&url=' + encodeURIComponent(this.subwayData.imageURL);
    window.open(t, '_self')
  },
  saveSubwayWise: function () {
    var t = this.subwayData;
    a('PQelement', {
      width: 130,
      height: 130,
      text: t.wiseURL || t.imageURL
    }, {
      width: t.width,
      height: t.height,
      filesize: t.filesize || 0
    })
  },
  calculateCity: function (t, i) {
    if (i = s.trim(i || ''), !t || !i || t.length < 1) return !1;
    for (var e, n, o = 0, a = t.length; a > o; o++) if (n = t[o], e = new RegExp(n.name), e.test(i)) return this.subwayData = n,
    !0;
    return !1
  },
  showImage: function (t) {
    var i = 'width:{{=it.imgRenderWidth}}px;height:{{=it.imgRenderHeight}}px;left:{{=it.imgRenderLeft}}px;top:{{=it.imgRenderTop}}px;',
    e = this.subwayData;
    this.styleFormat || (this.styleFormat = doT.compile(i)),
    i = this.styleFormat(t),
    this.imgDOM = new Image;
    var n = ((new Date).getTime(), !1),
    o = this;
    if (this.imgDOM.onload = function () {
      if (n) return void (o.imgDOM.onload = o.imgDOM.onerror = null);
      n = !0;
      (new Date).getTime()
    }, this.imgDOM.onerror = function () {
      h.subwayData = !1,
      h.hide(),
      h.imgDOM.onerror = null
    }, this.imgDOM.src = e.imageURL, this.imgDOM.style.cssText = i, this.imgDOM.srcWidth = this.subwayData.width, this.imgDOM.srcHeight = this.subwayData.height, this.$picContainer.append(this.imgDOM), this.$picInfoPan) {
      var a = e.width + ' x ' + e.height;
      e.filesize && parseInt(e.filesize) > 0 && (a += '&nbsp;&nbsp;' + e.filesize + 'KB'),
      this.$picInfoPan.html(a)
    }
    this.imageRendered = !0,
    this.imgDOM.__loaded = !0,
    this.zoomObj = new r({
      wheelZoom: !0,
      dbClickZoom: !0,
      maxRate: this.options.maxZoomRate,
      minRate: this.options.minZoomRate,
      clickZoomRate: 0.05,
      zoomRate: 0.05
    }),
    this.zoomObj.init(this.$zoomBigBtn, this.$zoomSmallBtn, this.$picContainer);
    var h = this;
    this.zoomObj.on('zoom', function (t) {
      t && (h.updateImage(t), h.closeHelpArea())
    }),
    this.imgDOM.__enableDrag = !0,
    this.dragObj = new m,
    this.dragObj.init(this.$picContainer[0], this.imgDOM),
    this.imgDOM.style.cursor = this.options.cursor;
    var l = 1;
    if ('0' !== l) {
      var c = this.$helpCon = s(this.options.helpCon);
      if (c.length > 0) {
        c.addClass('subway-help-show'),
        this._helpShowed = !0;
        var d = s(this.options.helpCloseBtn);
        d && d.on('click', function () {
          h.closeHelpArea()
        })
      }
    }
  },
  closeHelpArea: function () {
    this.$helpCon && this._helpShowed && (this.$helpCon.removeClass('subway-help-show'), this._helpShowed = !1)
  },
  updateImage: function (t, i) {
    i = i !== !1,
    i && this.imgDOM && (this.imgDOM.style.cssText = 'width:' + t.imgRenderWidth + 'px; height:' + t.imgRenderHeight + 'px; left:' + t.imgRenderLeft + 'px; top:' + t.imgRenderTop + 'px; cursor:' + this.options.cursor),
    this.imgDOM.roomRate = t.imgRenderRate,
    this.updateBtns(t),
    this._visible || (this._visible = !0, this.$container.show(), this.trigger('Imgid-Top-Change', {
    }))
  },
  updateBtns: function (t) {
    t.imgRenderRate <= this.options.minZoomRate ? (this.zoomObj.disableZoomSmall(), this.$zoomSmallBtn.attr('title', ''), this.$zoomSmallBtn.addClass('subway-smallbtn-disable'))  : (this.zoomObj.enableZoomSmall(), this.$zoomSmallBtn.attr('title', '缩小图片'), this.$zoomSmallBtn.removeClass('subway-smallbtn-disable')),
    t.imgRenderRate >= this.options.maxZoomRate ? (this.zoomObj.disableZoomBig(), this.$zoomSmallBtn.attr('title', ''), this.$zoomBigBtn.addClass('subway-bigbtn-disable'))  : (this.zoomObj.enableZoomBig(), this.$zoomSmallBtn.attr('title', '放大图片'), this.$zoomBigBtn.removeClass('subway-bigbtn-disable')),
    this.$zoomRate.html(Math.ceil(100 * t.imgRenderRate) + '%')
  },
  calculateSize: function () {
    var t,
    i = s(window).height(),
    e = this.subwayData;
    this.options.normalThumbHeight = i >= 800 ? 150 : 80;
    var n = this.options;
    t = Math.max(i - n.topAreaHeight - n.normalThumbHeight, n.containerMinHeight);
    var o = t - 45,
    a = Math.max(this.containerWidth - 10, 600),
    h = this.zoomImage(e.width, e.height, a, o);
    return h.imgURL = e.imageURL,
    h.containerWidth = this.containerWidth,
    h.containerHeight = t,
    this.containerHeight = t,
    this.picContainerHeight = o,
    this.picContainerWidth = a,
    this.imageRenderInfo = h,
    h
  },
  zoomImage: function (t, i, e, n) {
    var o = t * this.options.initRate,
    a = i * this.options.initRate,
    s = (e - o) / 2,
    h = (n - a) / 2;
    return {
      picContainerWidth: e,
      picContainerHeight: n,
      imgRenderWidth: o,
      imgRenderHeight: a,
      imgRenderLeft: s,
      imgRenderTop: h,
      imgRenderRate: o / t
    }
  },
  hide: function () {
    this.$container && (this._visible = !1, this.containerWidth = 0, this.$container.hide(), this.trigger('Imgid-Top-Change', {
    }))
  }
});
var l,
c,
d,
g;
return i
});
; /*!searchresult:widget/pagelets/movie/banners/banners.js*/
define('searchresult:widget/pagelets/movie/banners/banners', function (t, o, s) {
var e = t('common:widget/ui/base/base'),
n = t('searchresult:widget/ui/controls/IqiyiVideoBox/IqiyiVideoBox'),
i = t('searchresult:widget/ui/component/component'),
a = t('searchresult:widget/ui/statistic/bdgstat'),
d = i({
  opts: {
    bannerId: 0,
    tpl: e('#banner-one-tpl').html(),
    data: {
    }
  },
  enterDocument: function () {
    var t = this.opts.bannerId;
    this._domVideo.click(function (o) {
      o.preventDefault(),
      o.stopPropagation();
      var s = e(this),
      i = new n;
      i.render({
        flashvars: s.attr('data-src')
      }),
      a.sendLog({
        as: 'yingshi',
        p: 1010101,
        pos: 'pc_result_wall_topmiddle',
        subpos: t,
        matcont: 'video'
      })
    })
  },
  init: function () {
    this._domVideo = this._element.find('.banner-video'),
    a.sendLog({
      as: 'yingshi',
      p: 1010100,
      pos: 'pc_result_wall_topmiddle',
      subpos: this.opts.bannerId,
      shownum: 1
    })
  },
  buildDom: function () {
    e.each(this.opts.data.media, function (t, o) {
      o.url = 'autoChainPlay=0&autoHideControl=1&autoPlay=1&bd=1&cid=qc_100001_300089&coop=coop_baiduBaike&isLoop=0&showControl=0&showDock=0&showFocus=0&sendLogo=0&showRecommend=0&showSearch=0&showSearchBox=0&showShare=0&' + o.url
    });
    var t = doT.template(this.opts.tpl);
    return t(this.opts.data)
  }
}),
p = i({
  opts: {
    bannerId: 1,
    tpl: e('#banner-two-tpl').html(),
    data: {
    }
  },
  enterDocument: function () {
    var t = this.opts.bannerId;
    this._domNuomiTicket.click(function () {
      a.sendLog({
        as: 'yingshi',
        p: 1010101,
        pos: 'pc_result_wall_topmiddle',
        subpos: t,
        matcont: 'nuomi'
      })
    })
  },
  init: function () {
    this._domNuomiTicket = this._element.find('.nuomi-ticket'),
    a.sendLog({
      as: 'yingshi',
      p: 1010100,
      pos: 'pc_result_wall_topmiddle',
      subpos: this.opts.bannerId,
      shownum: 1
    })
  },
  buildDom: function () {
    var t = doT.template(this.opts.tpl);
    return t(this.opts.data)
  }
}),
r = i({
  opts: {
    bannerId: 2,
    tpl: e('#banner-three-tpl').html(),
    data: {
    }
  },
  enterDocument: function () {
    var t = this.opts.bannerId;
    this._domAdTips.html('<span>本搜索结果为<a href="http://e.baidu.com/" target="_blank">商业推广</a>信息，请注意可能的风险。百度推出<a href="http://baozhang.baidu.com/guarantee/" target="_blank">网民权益保障计划</a>，<a href="https://passport.baidu.com" target="_blank">登录</a>搜索有保障。</span>'),
    this._domAd.click(function () {
      a.sendLog({
        as: 'yingshi',
        p: 1010101,
        pos: 'pc_result_wall_topmiddle',
        subpos: t,
        matcont: encodeURIComponent(e(this).attr('href'))
      })
    });
    var o = this;
    this._domAdSpread.click(function () {
      o.isLogin && o._domAdTips.html('<span>本搜索结果为<a href="http://e.baidu.com/" target="_blank">商业推广</a>信息，请注意可能的风险。您当前为登录状态，已参加<a href="http://baozhang.baidu.com/guarantee/" target="_blank">网民权益保障计划</a>。</span>'),
      o._domAdTips.show(),
      o.clickTips = setTimeout(function () {
        o._domAdTips.css('display', 'none')
      }, 4000)
    }),
    this._domAdTips.click(function () {
      o._domAdTips.css('display', 'none'),
      clearTimeout(o.clickTips)
    })
  },
  init: function () {
    this._domAd = this._element.find('.banner-ad'),
    this._domAdSpread = this._element.find('.banner-ad-spread'),
    this._domAdTips = this._element.find('.banner-ad-tips'),
    a.sendLog({
      as: 'yingshi',
      p: 1010100,
      pos: 'pc_result_wall_topmiddle',
      subpos: this.opts.bannerId,
      shownum: 1
    })
  },
  buildDom: function () {
    var t = doT.template(this.opts.tpl);
    return t(this.opts.data)
  },
  updateTipTemplate: function () {
    this.isLogin = !0
  }
});
s.exports = [
  d,
  p,
  r
]
});
; /*!searchresult:widget/ui/controls/movieBanners/bannerContainer.js*/
define('searchresult:widget/ui/controls/movieBanners/bannerContainer', function (t, n, e) {
var i = t('common:widget/ui/base/base'),
a = t('searchresult:widget/ui/component/component'),
s = t('searchresult:widget/pagelets/movie/banners/banners'),
o = a({
  opts: {
    defaultData: {
      banners: [
      ]
    }
  },
  _banners: [
  ],
  _bgType: [
  ],
  _curBannerNo: 0,
  enterDocument: function () {
    var t = this;
    this._domBannerSwitch.click(function () {
      t._switchBanner()
    }),
    this._domIndicators.click(function () {
      var n = i(this);
      if (!n.hasClass('active')) {
        var e = + n.attr('data-banner-no');
        t._switchBanner(e)
      }
    }),
    this._element.on('mouseenter', function () {
      t._autoSwitchTimeout && (clearTimeout(t._autoSwitchTimeout), t._autoSwitchTimeout = null)
    }).on('mouseleave', function () {
      t._setAutoSwitch()
    }),
    this._setAutoSwitch()
  },
  _setAutoSwitch: function () {
    if (this._banners.length) {
      this._autoSwitchTimeout && clearTimeout(this._autoSwitchTimeout);
      var t = this;
      this._autoSwitchTimeout = setTimeout(function () {
        t._switchBanner()
      }, 5000)
    }
  },
  _switchBanner: function (t) {
    var n = this._bgType[this._curBannerNo];
    this._banners[this._curBannerNo].remove(),
    this._curBannerNo = 'number' == typeof t ? t : (this._curBannerNo + 1) % this._banners.length,
    this.addChild(this._banners[this._curBannerNo]),
    this._domIndicators.removeClass('active'),
    i(this._domIndicators[this._curBannerNo]).addClass('active');
    var e = this._bgType[this._curBannerNo];
    e !== n && ('light' === n && this._element.removeClass('light-background'), 'light' === e && this._element.addClass('light-background')),
    this._setAutoSwitch()
  },
  exitDocument: function () {
    this._autoSwitchTimeout && (clearTimeout(this._autoSwitchTimeout), this._autoSwitchTimeout = null)
  },
  init: function () {
    this._adaptData();
    for (var t = this.opts.banners, n = 0, e = Math.min(s.length, t.length); e > n; n++) if (t[n].isSet) {
      var a = s[n];
      this._banners.push(new a({
        data: t[n]
      })),
      this._bgType.push(t[n].bg.colorType)
    }
    var o = this._banners.length;
    o && this.addChild(this._banners[0]),
    this._bgType.length && 'light' === this._bgType[0] && this._element.addClass('light-background'),
    this._domBannerSwitch = this._element.find('.banner-switch'),
    this._domIndicators = this._element.find('.banner-indicator');
    var h = [
      '0',
      '0',
      '34px',
      '56px'
    ];
    this._element.find('.banner-indicator-area').css('width', h[o]),
    2 > o && this._domBannerSwitch.hide(),
    o || i('#movie-banner-area').hide()
  },
  _adaptData: function () {
    return this.opts.banners ? void 0 : void (this.opts.banners = this.opts.defaultData.banners)
  },
  buildDom: function () {
    var t = doT.template(i('#banner-container-tpl').html() || '');
    return t({
      length: s.length
    })
  }
});
e.exports = o
});
; /*!searchresult:widget/ui/controls/movieTabs/tabs.js*/
define('searchresult:widget/ui/controls/movieTabs/tabs', function (t, s, a) {
var e = t('common:widget/ui/base/base'),
i = t('common:widget/ui/base/events'),
o = t('searchresult:widget/ui/component/component'),
n = t('searchresult:widget/ui/statistic/bdgstat'),
d = o({
  opts: {
    defaultData: {
      tabs: [
      ]
    }
  },
  enterDocument: function () {
    var t = this;
    this._domTabItems.click(function () {
      var s = e(this);
      if (!s.hasClass('active')) {
        t._domTabItems.removeClass('active'),
        s.addClass('active');
        var a = s.attr('data-key') || '',
        i = + s.attr('data-tab-index') || 0;
        t.dispatchEvent('tabChanged', {
          subQuery: a
        }),
        t.dispatchEvent('imagesLoaded', {
          subPos: i,
          subQuery: a
        }),
        n.sendLog({
          as: 'yingshi',
          p: 1010101,
          pos: 'pc_result_wall_tablist',
          subpos: i,
          matcont: encodeURIComponent(a || '全部')
        })
      }
    }),
    this._domTabItems.length && this.dispatchEvent('imagesLoaded', {
      subpos: 0,
      subQuery: ''
    })
  },
  init: function () {
    this._domTabItems = this._element.find('.tab-item'),
    this.opts.tabs.length || e('#movie-tabs-area').hide()
  },
  _adaptData: function () {
    return this.opts.tabs ? void 0 : void (this.opts.tabs = this.opts.defaultData.tabs)
  },
  buildDom: function () {
    this._adaptData();
    var t = doT.template(e('#tabs-container-tpl').html() || '');
    return t({
      tabs: this.opts.tabs
    })
  }
});
e.extend(d.prototype, i),
a.exports = d
});
; /*!searchresult:widget/ui/controls/newsSliderBox/pageresizer.js*/
define('searchresult:widget/ui/controls/newsSliderBox/pageresizer', function (i) {
var t = i('common:widget/ui/base/base'),
e = (i('searchresult:widget/ui/utils/utils'), i('common:widget/ui/base/events')),
n = t.extend({
  _timer: null,
  _isInit: !1,
  _isRunning: !1,
  _lastNotifyTime: - 1,
  tick: 200,
  duration: 400,
  curWidth: - 1,
  curHeight: - 1,
  init: function (i) {
    var e = t.extend({
      tick: 200,
      duration: 400
    }, i);
    return this._isInit ? this : (this.$win = t(window), t.browser.msie && t.browser.version < 8 && (this._resizeing = this.resizing, this.resizing = this.resizingIE7), this.tick = e.tick, this.duration = e.duration, this._isInit = !0, this)
  },
  isInited: function () {
    return this._isInit
  },
  start: function () {
    this._isRunning || (this.$win.bind('resize', this.resizing), this._isRunning = !0)
  },
  stop: function () {
    this.$win.unbind('resize', this.resizing),
    this._isRunning = !1
  },
  resizingIE7: function () {
    var i = this.$win.width(),
    t = this.$win.height();
    (n.curWidth != i || n.curHeight != t) && (n.curWidth = i, n.curHeight = t, n._resizeing())
  },
  resizing: function () {
    var i = new Date;
    n._timer ? (clearTimeout(n._timer), n._timer = setTimeout(n.resizeFinished, n.tick), - 1 != n._lastNotifyTime && i - n._lastNotifyTime >= n.duration && n.notifyReszing(i))  : (n.trigger('resizeBegin'), n._timer = setTimeout(n.resizeFinished, n.tick), n._lastNotifyTime = i)
  },
  resizeFinished: function () {
    n.notifyReszing(),
    n.trigger('resizeEnd'),
    n._lastNotifyTime = - 1,
    n._timer = null
  },
  notifyReszing: function (i) {
    this._lastNotifyTime = i,
    n.trigger('resizing')
  }
}, e);
return n
});
; /*!searchresult:widget/ui/controls/newsSliderBox/newsSliderBox.js*/
define('searchresult:widget/ui/controls/newsSliderBox/newsSliderBox', function (e) {
function t(e) {
  this.data = null,
  this.model = e,
  this.con = '.news-slider',
  this.imgHeight = 280,
  this.gap = 77,
  this.padding = 50,
  this.TPL = [
    '<div class="rep-img" data-index="#{imgidx}">',
    '<a href="#{link}" target="_blank">',
    '<img src="#{url}" class="slider-img" alt="#{title}" style="width:#{needWidth}px;height:#{needHeight}px"></img>',
    '</a>',
    '<div class="desp">#{summary}',
    '</div>',
    '</div>'
  ].join('')
}
var i = e('common:widget/ui/base/base'),
n = (e('searchresult:widget/ui/utils/utils'), e('common:widget/ui/slider/slider')),
s = e('common:widget/ui/base/events'),
d = e('common:widget/ui/EventEmitter/EventEmitter').eventCenter,
r = e('searchresult:widget/ui/controls/newsSliderBox/pageresizer'),
h = e('searchresult:widget/ui/statistic/statistic');
i.extend(t.prototype, s, n, {
  init: function (e) {
    if (this.data = e, this.$con = i(this.con), this.data.photos.length < 3) return void this.$con.hide();
    r.init().start(),
    this.width = this.$con.width() - this.padding,
    this.$sliderArea = i('<div class="news-slider-area"></div>').hide(),
    this.$descCon = i('<div class="news-desc-con"></div>').hide(),
    this.$title = i('<div class="news-title"></div>').hide(),
    this.append().render().show();
    var t = this;
    r.on('resizeEnd', function () {
      t.$sliderArea.children().remove(),
      t.width = i(window).width() - t.gap - t.padding,
      t.renderSlider()
    }),
    this._createHover(),
    r.on('sliderCreateEnd', function () {
      if (t._addEvent(), window.ActiveXObject) {
        var e = navigator.userAgent.toLowerCase(),
        i = e.match(/msie ([\d.]+)/);
        if (i && i.length > 1 && (i = 0 | i[1], 11 > i)) return
      }
      t.$sliderCon.append('<span class="shadow-layer"></span>')
    }),
    r.trigger('resizeEnd'),
    this._addLog()
  },
  _createHover: function () {
    this.hoverLayer = [
      '<div class="news-hover" style="height:#{hoverheight}px">',
      '<div class="news-hover-inner">',
      '<div class="content" style="width:#{contwidth}px;height:#{contheight}px;padding-top:#{paddingtop}px">#{content}',
      '</div>',
      '<div class="imgno">',
      '<span>#{curimgidx}',
      '</span>',
      '/ #{totalimgno}',
      '</div>',
      '</div>',
      '</div>'
    ].join('')
  },
  _addLog: function () {
    h(null, 69, {
      tprn: 'recomNews'
    })
  },
  _addEvent: function () {
    var e = this;
    this.$sliderCon.on('mouseenter', '.slider-cnt .rep-img', function (t) {
      e._onHover(i(this), i(t.fromElement), e)
    }),
    this.$sliderCon.on('click', '.slider-cnt .rep-img.isOnHover', function () {
      var e = i(this).find('a').attr('href');
      return window.open(e),
      !1
    }),
    this.$sliderCon.on('mouseleave', '.slider-cnt .rep-img.isOnHover', function (e) {
      i(e.toElement).hasClass('slider-img') || (i(this).removeClass('isOnHover'), i(this).find('.news-hover').remove())
    })
  },
  _onHover: function (e, t, n) {
    if (!e.hasClass('isOnHover')) {
      var s = 50,
      d = 260,
      r = e.find('.slider-img');
      if (r.css({
        opacity: 1
      }).animate({
        opacity: 0.8
      }, 80, function () {
        i(this).css({
          opacity: 1
        })
      }), !e.find('.news-hover').length) {
        var h = r.width() - 70,
        a = 20,
        l = 12,
        c = parseInt(Math.floor(h / l)),
        p = e.find('.desp').html(),
        g = p.length / c;
        g > 3 ? (g = 3, p = p.substr(0, g * c).concat('...'))  : g = parseInt(Math.ceil(g - 0.08));
        var f = (60 - g * a) / 2 + 10,
        v = {
          content: p || this.data.desc,
          contwidth: h,
          contheight: 3 * a,
          hoverheight: 3 * a + 20,
          paddingtop: f,
          curimgidx: e.attr('data-index'),
          totalimgno: 0 | this.data.photos.length
        };
        e.append(o.format(n.hoverLayer, v))
      }
      var u = i('.isOnHover', n.$sliderCon),
      w = 0,
      m = 9999,
      $ = e.offset().left,
      b = e.offset().top,
      x = 0,
      C = 0,
      y = e.width();
      u.length && (u.removeClass('isOnHover'), w = u.offset().left, m = u.offset().top),
      e.addClass('isOnHover'),
      m == b && w == $ ? C = s : m > b + s ? C = s : b - s > m ? C = - s : x = w > $ ? y : - y,
      i('.news-hover-inner', e).stop().css({
        left: x + 'px',
        top: C + 'px'
      }).animate({
        left: 0,
        top: 0,
        easing: 'linear'
      }, d),
      u.length && (C ? C = - C : x > 0 ? x = 0 - u.width()  : 0 > x && (x = u.width()), i('.news-hover-inner', u).stop().animate({
        left: x,
        top: C,
        easing: 'linear'
      }, d, function () {
        i('.news-hover', u).remove()
      }))
    }
  },
  render: function () {
    return this.data.photos.length > 0 && (this.renderDesc(), this.renderSlider()),
    this.renderTitle(),
    this
  },
  renderSlider: function () {
    var e = [
    ].concat(this.data.photos),
    t = e.length,
    n = [
    ];
    t && (this.$btn = i('<div class="slider-btn"></div>').hide(), this.$sliderCon = i('<div class="slider-con"></div>'), this.$sliderInd = i('<div class="slider-ind"></div>').hide(), this.$frag = i('<div></div>').hide(), this.btnRender(), n = this.adaptData(e, t), t = n.length, this.conRender(n, t), this.indRender(n, t), this.$sliderArea.append(this.$frag).append(this.$btn).append(this.$sliderCon).append(this.$sliderInd).show(), this.createSlider())
  },
  createSlider: function () {
    this.sliderShow = n.init('.slider-con', '.slider-cnt', {
      leftBtnSel: '.news-slide-left-btn',
      rightBtnSel: '.news-slide-right-btn',
      autoAnimate: !1,
      isCycle: !1,
      isAutoWidth: !0
    });
    var e = this.sliderShow.slidesNum,
    t = i('.news-slide-left-btn'),
    s = i('.news-slide-right-btn');
    t.hide(),
    1 == e && s.hide(),
    r.trigger('sliderCreateEnd'),
    d.on('slideMoved', function (i) {
      t.show(),
      s.show(),
      0 == i.realIdx ? t.hide()  : e - 1 == i.realIdx && s.hide()
    })
  },
  btnRender: function () {
    this.$btn.append('<a href="###" class="news-slide-left-btn slide-btn" hidefocus="true"></a>').append('<a href="###" class="news-slide-right-btn slide-btn" hidefoucs="true"></a>').show()
  },
  conRender: function (e, t) {
    var n,
    s = t || e.length,
    d = [
    ],
    r = 0,
    h = this;
    for (n = 0; s > n; n++) {
      d = e[n];
      var a,
      l,
      c = i('<div class="slider-cnt"></div>'),
      p = d.length,
      g = 0;
      for (a = 0; p > a; a++) l = d[a],
      l.imgidx = ++r,
      l.link = h.getDetailUrl(h.data.id, l.pn || l.index),
      1 == l.imgidx && this.$descTitle.find('a:first').attr('href', l.link),
      g += l.needWidth,
      c.append(o.format(h.TPL, l));
      c.width(g),
      this.$frag.append(c)
    }
  },
  indRender: function () {
  },
  renderDesc: function () {
    var e = '<a href="#" target="_blank">' + (this.data.desc || this.data.query) + '（共' + this.data.photos.length + '张）</a>';
    this.$descTitle = i('<div class="desc-title"></div>').html(e),
    this.$descCon.append(this.$descTitle).show()
  },
  renderTitle: function () {
    this.$title.show()
  },
  adaptData: function (e, t) {
    var i,
    n,
    s = this,
    d = this.width = this.$con.width() - this.padding,
    r = 0,
    h = [
    ],
    o = [
    ],
    a = [
    ],
    l = t || e.length;
    if (!l) return void (s.pageno = 0);
    for (i = 0; l > i; i++) n = e[i],
    n.index = i,
    n.width -= 0,
    n.height -= 0,
    n.needHeight = s.imgHeight,
    n.needWidth = Math.floor(n.needHeight * n.width / n.height),
    r += n.needWidth,
    r - Math.floor(n.needWidth / 2) <= d ? o.push(n)  : (h.push([].concat(o)), a.push(r - n.needWidth), r = n.needWidth, o = [
    ], o.push(n));
    if (o.length && (h.push([].concat(o)), a.push(r), r = 0, o = [
    ]), l = h.length) for (i = 0; l > i; i++) {
      o = h[i];
      var c,
      n,
      p = a[i],
      g = o.length,
      f = 0;
      for (i == l - 1 && (d = Math.min(p, d)), rangeWd = d - p, c = 0; g > c; c++) n = o[c],
      n.needWidth += Math.floor(rangeWd * n.needWidth / p),
      f += n.needWidth,
      i != l - 1 && c == g - 1 && f != d && (n.needWidth += d - f)
    }
    return h
  },
  getDetailUrl: function (e, t) {
    return 'http://image.baidu.com/detail/newindex?col=' + encodeURIComponent('资讯') + '&tag=&pn=0&pid=' + e + '&user_id=10086&setid=-1&sort=0&newsPn=' + t + '&fr=search&from=1'
  },
  show: function () {
    this.$con.show()
  },
  hide: function () {
    this.$con.hide()
  },
  append: function () {
    return this.$con.append(this.$sliderArea).append(this.$descCon).append(this.$title),
    this
  }
});
var o = i.extend({
}, {
  format: function (e, t) {
    e = String(e);
    var i = Array.prototype.slice.call(arguments, 1),
    n = Object.prototype.toString;
    return i.length ? (i = 1 == i.length && null !== t && /\[object Array\]|\[object Object\]/.test(n.call(t)) ? t : i, e.replace(/#\{(.+?)\}/g, function (e, t) {
      var s = i[t];
      return '[object Function]' == n.call(s) && (s = s(t)),
      'undefined' == typeof s ? '' : s
    }))  : e
  }
});
return t
});
; /*!searchresult:widget/ui/controls/relsearchBox/relsearchBox.js*/
define('searchresult:widget/ui/controls/relsearchBox/relsearchBox', function (e) {
function t(e) {
  this.rsType = '',
  this.$container = '',
  this.$relCon = '',
  this.model = e
}
var n = e('common:widget/ui/base/base'),
r = e('searchresult:widget/ui/statistic/statistic');
return n.extend(t.prototype, {
  init: function (e, t, l) {
    var i,
    s = e.slice(0, 15),
    o = '<a class="relsearch-a" onclick="p(null,497,{});" target="_blank" href="https://www.baidu.com/s?wd=' + encodeURIComponent(this.model.get('queryWord')) + '&tn=SE_hldp01300_ap2duck7&ie=utf-8" target="_blank">去网页搜索: <em class="relsearch-em">' + this.model.get('queryWord') + '</em></a>';
    if (n('#relsearch-p').html(o), 'undefined' == typeof s || !(i = s.length)) return !1;
    this.$container = n('#rsQuery'),
    this.$relCon = n('#relsearch'),
    'undefined' != typeof rst && (this.rsType = '&rst=' + rst);
    var h = encodeURIComponent(this.model.get('queryWord'));
    if (i > 0) {
      this.$relCon.css('display', '');
      var a = [
      ];
      a[a.length] = '<table cellpadding="0" cellspacing="0" ><tr>';
      for (var c = 0, p = i - 1; p >= c; c++) a[a.length] = '<td nowrap="nowrap">',
      a[a.length] = 'flip' == this.model.get('tpl') ? '<a title="点击搜索" href="/search/flip?ct=201326592&cl=2&lm=-1&nc=1&ipn=r&tn=baiduimage&rps=3&pv=&word=' : '<a title="点击搜索" href="/search/index?ct=201326592&cl=2&lm=-1&nc=1&ipn=r&tn=baiduimage&rps=3&pv=&word=',
      a[a.length] = s[c][0],
      a[a.length] = '&ofr=' + h,
      a[a.length] = '&oriquery=' + h,
      a[a.length] = '&ie=utf-8&istype=2&z=0&fm=rs',
      a[a.length] = c + 1,
      a[a.length] = this.rsType,
      a[a.length] = '"  onmousedown="p(event,10,{ps:\'b\',tp:\'a\',r:\'',
      a[a.length] = c,
      a[a.length] = '\',pagepos:\'',
      a[a.length] = l || 'unknown',
      a[a.length] = '\',rq:\'',
      a[a.length] = encodeURIComponent(s[c][0]),
      a[a.length] = '\'});" >',
      a[a.length] = s[c][0],
      a[a.length] = '</a></td><td class="s">&nbsp;</td>',
      4 == c && (a[a.length] = '</tr><tr>');
      5 >= i && (a[a.length] = '</tr><tr><td>&nbsp;</td>'),
      a[a.length] = '</tr></table>',
      this.$container.html(a.join('')),
      'function' != typeof String.prototype.trim && (String.prototype.trim = function () {
        return this.replace(/^\s+|\s+$/g, '')
      })
    }
    for (var d = '', c = s.length - 1; c >= 0; c--) d += encodeURIComponent(s[c][0]),
    0 != c && (d += '$');
    r(null, 502, {
      oriquery: h,
      rstr: d
    })
  }
}),
t
});
; /*!searchresult:widget/ui/controls/specicalRecBox/specialRecBox.js*/
define('searchresult:widget/ui/controls/specicalRecBox/specialRecBox', function (i) {
function t() {
  this.hotimgs = null,
  this.hotimgslist = null,
  this.page = 0,
  this.pagenum = 0,
  this.position = [
  ],
  this.timer = null
}
var s = i('common:widget/ui/base/base'),
e = i('searchresult:widget/ui/statistic/statistic');
return s.extend(t.prototype, {
  init: function () {
  },
  render: function (i) {
    var t = this,
    h = i.data;
    if (0 != h.length) {
      var n = [
      ],
      a = 0,
      o = s('#specialRecommend').width() - 110;
      this.position = [
        0
      ];
      for (var p in h) {
        var c = h[p],
        g = Math.round(210 * c.width / c.height),
        r = c.fromPageTitle;
        r = r.replace(/ /g, '');
        var m = Math.floor(g / 14);
        r.length > m && (r = r.substring(0, m)),
        a += g,
        a >= this.position[this.position.length - 1] + o && this.position.push(a - g);
        var l = '/search/index?tn=baiduimage&ipn=r&ct=201326592&cl=2&lm=-1&st=-1&fm=&fr=&sf=1&fmq=1383635220671_R&ie=utf-8&word=' + encodeURIComponent(c.recWord);
        c.recURL && (l = c.recURL),
        n.push('<a onclick="p(null,492,{pn:' + p + ',u:\'' + encodeURIComponent(c.objURL) + '\',newp:492' + (c.recURL ? ',tp:\'rec\'' : '') + '});" target="_blank" href="' + l + '" class="item" i="' + (this.position.length - 1) + '"><img class="recimg" src="' + c.hoverURL + '" width=' + g + ' height=210 /><div class="itemct">' + r + '</div></a>'),
        a += 12
      }
      this.pagenum = Math.floor((a - 12) / o) + 1,
      a - o > this.position[this.pagenum - 1] + 10 ? (this.position[this.pagenum] = a - o - 5, this.pagenum++)  : this.position[this.pagenum - 1] + o > a + 200 && (this.position[this.pagenum - 1] = a - o);
      for (var u = [
      ], p = 0; p < this.pagenum; p++) u.push('<a class="btn ' + (p ? '' : 'actbtn') + '" ></a>');
      var d = (24 * this.pagenum, [
      ]);
      d.push('<div id="hotimgs">'),
      d.push(' <a class="btnPrev"></a><a class="btnNext"></a>'),
      d.push(' <div class="wrapper">'),
      d.push('  <div class="wrapperbox">'),
      d.push('     <div id="hotimgslist" style="width:' + (this.position[this.pagenum - 1] + 2 * o) + 'px;">'),
      d.push(n.join('')),
      d.push('     </div>'),
      d.push('   </div>'),
      d.push(' </div>'),
      d.push('</div>'),
      s('#specialRecommend').prepend(d.join(''));
      {
        s('#wrapperbox').width()
      }
      this.hotimgs = s('#hotimgs'),
      this.hotimgslist = s('#hotimgslist'),
      s('#hotimgs .btnPrev').click(function () {
        t.change(t.page - 1)
      }),
      s('#hotimgs .btnNext').click(function () {
        this.page++,
        t.change(t.page + 1)
      }),
      this.checkPage(),
      e(null, 493)
    }
  },
  change: function (i) {
    var t = this;
    if (this.page != i) {
      clearTimeout(t.timer),
      s('.btn', this.hotimgs).eq(this.page).removeClass('actbtn');
      var e = - 1 * t.position[i],
      h = - 1 * t.position[i];
      s('.btn', this.hotimgs).eq(i).addClass('actbtn'),
      t.page = i,
      this.hotimgslist.animate({
        left: e
      }, 500, function () {
        t.hotimgslist.css({
          left: h
        })
      }),
      t.checkPage()
    }
  },
  checkPage: function () {
    s('#hotimgslist .item[i=' + this.page + '] .itemct').show(),
    s('#hotimgslist .item[i=' + (this.page + 1) + '] .itemct').hide(),
    0 == this.page ? s('#hotimgs .btnPrev').hide()  : s('#hotimgs .btnPrev').show(),
    this.page + 1 >= this.pagenum ? s('#hotimgs .btnNext').hide()  : s('#hotimgs .btnNext').show()
  },
  nextPage: function () {
    var i = this.page + 1;
    i >= this.pagenum && (i = 0),
    this.change(i)
  }
}),
t
});
; /*!searchresult:widget/ui/statistic/statistic-core.js*/
define('searchresult:widget/ui/statistic/statistic-core', function () {
});
; /*!searchresult:widget/ui/strategy/filterStrategy.js*/
define('searchresult:widget/ui/strategy/filterStrategy', function (e) {
function t(e, t) {
  var u = {
    ic: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    width: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    height: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    z: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    st: {
      defaultValue: '-1',
      currValue: '-1',
      emptyValue: '-1'
    },
    face: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    lm: {
      defaultValue: '-1',
      currValue: '-1',
      emptyValue: '-1'
    },
    s: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    },
    tab: {
      defaultValue: '0',
      currValue: '0',
      emptyValue: '0'
    }
  };
  this.model = e,
  this.filterConf = l.extend(u, t || {
  }),
  this.defaultFilterValue = null
}
var l = e('common:widget/ui/base/base');
return l.extend(t.prototype, {
  init: function () {
  },
  getCurrFilterConf: function () {
    var e = {
    },
    t = this.filterConf;
    for (var l in t) e[l] = '0' === this.model.get(l) ? this.model.get(l)  : this.model.get(l) || this.defaultFilterValue && this.defaultFilterValue[l] || t[l].defaultValue;
    return e
  },
  getDefaultFilterConf: function () {
    if (!this.defaultFilterValue) {
      this.defaultFilterValue = {
      };
      var e = this.filterConf;
      for (var t in e) this.defaultFilterValue[t] = e[t].defaultValue
    }
    return this.defaultFilterValue.tab = this.model.get('tab') || '0',
    this.defaultFilterValue
  },
  checkISDefaultFilter: function (e, t) {
    e = e || this.getCurrFilterConf(),
    t = t || this.getDefaultFilterConf();
    for (var l in t) if (t[l] !== e[l]) return !1;
    return !0
  },
  getFilterState: function () {
    var e = this.getCurrFilterConf(),
    t = this.getDefaultFilterConf(),
    l = this.checkISDefaultFilter(e, t);
    return {
      currFilterConf: e,
      deFaultFilterConf: t,
      isShowFilterBar: !0,
      isDefaultFilter: l
    }
  }
}),
t
});
; /*!searchresult:widget/ui/utils/imghelper.js*/
define('searchresult:widget/ui/utils/imghelper', function () {
var h = {
  zoom: function (h, t) {
    if (!(h.width && h.height && t.width && t.height)) return {
      width: h.width && t.width ? Math.min(t.width, h.width)  : 'auto',
      height: h.height && t.height ? Math.min(t.height, h.height)  : 'auto'
    };
    var i = {
    };
    return h.width / h.height > t.width / t.height ? (i.width = Math.min(h.width, t.width), i.height = Math.floor(h.height * i.width / h.width))  : (i.height = Math.min(h.height, t.height), i.width = Math.floor(h.width * i.height / h.height)),
    i
  }
};
return h
});
; /*!searchresult:widget/ui/utils/pms.js*/
define('searchresult:widget/ui/utils/pms', function () {
});
; /*!searchresult:widget/ui/utils/swf.js*/
define('searchresult:widget/ui/utils/swf', function () {
var e = e || {
  version: '1.3.9'
};
return e.guid = '$BAIDU$',
window[e.guid] = window[e.guid] || {
},
e.swf = e.swf || {
},
e.swf.version = function () {
  var e = navigator;
  if (e.plugins && e.mimeTypes.length) {
    var r = e.plugins['Shockwave Flash'];
    if (r && r.description) return r.description.replace(/([a-zA-Z]|\s)+/, '').replace(/(\s)+r/, '.') + '.0'
  } else if (window.ActiveXObject && !window.opera) for (var n = 12; n >= 2; n--) try {
    var t = new ActiveXObject('ShockwaveFlash.ShockwaveFlash.' + n);
    if (t) {
      var a = t.GetVariable('$version');
      return a.replace(/WIN/g, '').replace(/,/g, '.')
    }
  } catch (i) {
  }
}(),
e.string = e.string || {
},
e.string.encodeHTML = function (e) {
  return String(e).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;').replace(/'/g, '&#39;')
},
e.encodeHTML = e.string.encodeHTML,
e.swf.createHTML = function (r) {
  r = r || {
  };
  var n,
  t,
  a,
  i,
  o,
  s,
  l = e.swf.version,
  c = r.ver || '6.0.0',
  u = {
  },
  g = e.string.encodeHTML;
  for (i in r) u[i] = r[i];
  if (r = u, !l) return '';
  for (l = l.split('.'), c = c.split('.'), a = 0; 3 > a && (n = parseInt(l[a], 10), t = parseInt(c[a], 10), !(n > t)); a++) if (t > n) return '';
  var d = r.vars,
  f = [
    'classid',
    'codebase',
    'id',
    'width',
    'height',
    'align'
  ];
  if (r.align = r.align || 'middle', r.classid = 'clsid:d27cdb6e-ae6d-11cf-96b8-444553540000', r.codebase = 'http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0', r.movie = r.url || '', delete r.vars, delete r.url, 'string' == typeof d) r.flashvars = d;
   else {
    var p = [
    ];
    for (i in d) s = d[i],
    p.push(i + '=' + encodeURIComponent(s));
    r.flashvars = p.join('&')
  }
  var v = [
    '<object '
  ];
  for (a = 0, o = f.length; o > a; a++) s = f[a],
  v.push(' ', s, '="', g(r[s]), '"');
  v.push('>');
  var w = {
    wmode: 1,
    scale: 1,
    quality: 1,
    play: 1,
    loop: 1,
    menu: 1,
    salign: 1,
    bgcolor: 1,
    base: 1,
    allowscriptaccess: 1,
    allownetworking: 1,
    allowfullscreen: 1,
    seamlesstabbing: 1,
    devicefont: 1,
    swliveconnect: 1,
    flashvars: 1,
    movie: 1
  };
  for (i in r) s = r[i],
  i = i.toLowerCase(),
  w[i] && (s || s === !1 || 0 === s) && v.push('<param name="' + i + '" value="' + g(s) + '" />');
  r.src = r.movie,
  r.name = r.id,
  delete r.id,
  delete r.movie,
  delete r.classid,
  delete r.codebase,
  r.type = 'application/x-shockwave-flash',
  r.pluginspage = 'http://www.macromedia.com/go/getflashplayer',
  v.push('<embed');
  var h;
  for (i in r) if (s = r[i], s || s === !1 || 0 === s) {
    if (new RegExp('^salign$', 'i').test(i)) {
      h = s;
      continue
    }
    v.push(' ', i, '="', g(s), '"')
  }
  return h && v.push(' salign="', g(h), '"'),
  v.push('></embed></object>'),
  v.join('')
},
e.swf.create = function (r, n) {
  r = r || {
  };
  var t = e.swf.createHTML(r) || r.errorMessage || '';
  n && 'string' == typeof n && (n = document.getElementById(n)),
  n ? n.innerHTML = t : document.write(t)
},
e.browser = e.browser || {
},
e.browser.ie = e.ie = /msie (\d+\.\d+)/i.test(navigator.userAgent) ? document.documentMode || + RegExp.$1 : void 0,
e.array = e.array || {
},
e.array.remove = function (e, r) {
  for (var n = e.length; n--; ) n in e && e[n] === r && e.splice(n, 1);
  return e
},
e.lang = e.lang || {
},
e.lang.isArray = function (e) {
  return '[object Array]' == Object.prototype.toString.call(e)
},
e.lang.isFunction = function (e) {
  return '[object Function]' == Object.prototype.toString.call(e)
},
e.lang.toArray = function (r) {
  if (null === r || void 0 === r) return [];
  if (e.lang.isArray(r)) return r;
  if ('number' != typeof r.length || 'string' == typeof r || e.lang.isFunction(r)) return [r];
  if (r.item) {
    for (var n = r.length, t = new Array(n); n--; ) t[n] = r[n];
    return t
  }
  return [].slice.call(r)
},
e.swf.getMovie = function (r) {
  var n,
  t = document[r];
  return 9 == e.browser.ie ? t && t.length ? 1 == (n = e.array.remove(e.lang.toArray(t), function (e) {
    return 'embed' != e.tagName.toLowerCase()
  })).length ? n[0] : n : t : t || window[r]
},
e
});
; /*!searchresult:widget/searchBox/imgFilter/init.js*/
define('searchresult:widget/searchBox/imgFilter/init', function (e, i) {
var t = e('common:widget/ui/base/base');
i.init = function () {
  var e = !1,
  i = 'filter';
  t('#imgfilter-btn').click(function () {
    e = !e,
    i = e ? 'filter-close' : 'filter-open',
    t('#imgfilter-btn').removeClass('filter-close filter-open').addClass(i);
    e ? (t('#filter-holder').show(), t('.imgfilter-text').text('取消筛选'))  : (t('#filter-holder').hide(), t('.imgfilter-text').text('图片筛选'))
  })
}
});
; /*!searchresult:widget/searchBox/shitu/init.js*/
define('searchresult:widget/searchBox/shitu/init', function (e, t, i) {
var n,
s = e('common:widget/ui/base/base'),
o = e('common:widget/ui/swf/swf'),
a = e('common:widget/ui/base/events'),
l = e('searchresult:widget/ui/statistic/statistic'),
r = i.exports = function () {
  this.point = document.getElementById('point'),
  this.content = document.getElementById('stsug'),
  this.submitobj = document.getElementById('sbobj'),
  this.form = document.getElementById('form1'),
  this.form2 = document.getElementById('form2'),
  this.shituvalue = document.getElementById('shitu1'),
  this.shituvalue2 = document.getElementById('shitu2'),
  this.file = document.getElementById('stfile'),
  this.url = document.getElementById('stuurl'),
  this.entry = document.getElementById('sttb'),
  this.close = document.getElementById('closest'),
  this.tips = document.getElementById('stmore'),
  this.hpobj = document.getElementById('hp'),
  this.sthp = document.getElementById('sthelp'),
  this.draghp = document.getElementById('dragtip'),
  this.kw = document.getElementById('kw'),
  this.dragts = document.getElementById('dragtg'),
  this.clickurl = 'http://stu.baidu.com',
  this.onuploadtg = 0,
  this.ftn = document.getElementById('stftn').value || '',
  this.isDisplay = 0,
  this.isSubmit = 0,
  this.chrome = /chrome\/(\d+\.\d+)/i.test(navigator.userAgent) ? + RegExp.$1 : void 0,
  this.isIe = /msie (\d+\.\d+)/i.test(navigator.userAgent) ? document.documentMode || + RegExp.$1 : void 0,
  this.isOpera = /opera(\/| )(\d+(\.\d+)?)(.+?(version\/(\d+(\.\d+)?)))?/i.test(navigator.userAgent) ? + (RegExp.$6 || RegExp.$2)  : void 0,
  this.callbacks = {
    aftershow: {
    },
    beforehide: {
    }
  }
};
s.extend(r.prototype, a, {
  init: function () {
    var e = this,
    t = e.addEvent,
    i = e.content;
    e.initdisplay(),
    t(window, 'load', function () {
      e.initdisplay()
    }),
    t(document, 'click', function (t) {
      e.hiddenContent(t, 0),
      window.setTimeout(function () {
        e.isDisplay || e.isSubmit || e.closest()
      }, 10)
    }),
    t(document, 'mousemove', function (t) {
      e.hiddenContent(t, 1),
      window.setTimeout(function () {
        e.isDisplay || e.isSubmit || e.closest()
      }, 10)
    }),
    t(e.entry, 'click', function () {
      e.isDisplay = 1,
      e.displayst()
    }),
    t(e.sthp, 'mouseover', function () {
      e.tips.style.display = ''
    }),
    t(e.sthp, 'mouseout', function () {
      n = setTimeout(function () {
        e.tips.style.display = 'none'
      }, 500)
    }),
    t(e.tips, 'mouseover', function (t) {
      t = window.event || t,
      e.fixedMouse(t, e.tips) && n && clearTimeout(n)
    }),
    t(e.tips, 'mouseout', function (t) {
      t = window.event || t,
      e.fixedMouse(t, e.tips) && (e.tips.style.display = 'none')
    }),
    t(e.file, 'change', function () {
      e.getValue()
    }),
    t(e.submitobj, 'click', function (t) {
      var i = e.url.value,
      n = '' === i || !e.checkImgType(i),
      t = window.event || t;
      '' !== i && l(null, 1111103, {
        pos: 'paste',
        fm: 'searchresult'
      }),
      n ? (alert('您的文件格式不正确或图片网址过长。支持jpg、gif、png、jpeg、bmp格式图片及250个字符内的图片网址。'), this.form.reset())  : (s.cookie('uploadTime', (new Date).getTime(), {
        path: '/'
      }), e.shituvalue.value = 'paste', e.submitForm(!0, e.form, 'urlSearch'), e.point.style.display = 'block'),
      document.all ? t.returnValue = !1 : t.preventDefault()
    }),
    t(e.close, 'click', function () {
      return e.isIe ? window.document.execCommand('Stop')  : window.stop(),
      e.form.reset(),
      e.form2.reset(),
      e.isSubmit = 0,
      e.onuploadtg ? (e.draghp.style.display = 'none', e.point.style.display = 'none', void (e.onuploadtg = 0))  : void e.closest()
    }),
    !e.isOpera && window.FileReader && (t(e.url, 'paste', function (t) {
      var i = t.clipboardData || window.clipboardData,
      n = i.items,
      s = i.types;
      n && n.length && s && s.length && 'Files' === s[0] && e.handlerFiles2(n)
    }), t(document, 'dragenter', function () {
      e.point.style.display = 'none',
      e.displayst(),
      e.draghp.style.display = ''
    }), t(document, 'dragover', function () {
      e.point.style.display = 'none',
      e.displayst(),
      e.draghp.style.display = ''
    }), t(i, 'dragenter', function (e) {
      e.stopPropagation(),
      e.preventDefault()
    }), t(i, 'dragover', function (e) {
      e.stopPropagation(),
      e.preventDefault()
    }), t(i, 'drop', function (t) {
      if (t.stopPropagation(), t.preventDefault(), e.isSubmit = 1, s.cookie('uploadTime', (new Date).getTime(), {
        path: '/'
      }), l(null, 1111101, {
        pos: 'drag',
        fm: 'searchresult'
      }), t.dataTransfer.files.length) try {
        e.handlerFiles(t.dataTransfer.files)
      } catch (i) {
        return
      } else if (t.dataTransfer.types.indexOf && - 1 !== t.dataTransfer.types.indexOf('text/html') || t.dataTransfer.types.contains && - 1 !== t.dataTransfer.types.contains('text/html')) {
        var n = document.createElement('div');
        n.innerHTML = t.dataTransfer.getData('text/html');
        var o = n.getElementsByTagName('img');
        if (!(o && o[0] && o[0].src)) return;
        var a = document.createElement('input');
        if (a.name = 'drag', a.value = '1', a.type = 'hidden', e.form.appendChild(a), e.shituvalue.value = 'drag', 0 === o[0].src.indexOf('data:')) {
          var r = o[0].alt || o[0].title || '';
          e.submitForm2(o[0].src, r, 'image')
        } else e.url.value = o[0].src,
        e.submitForm(!0, e.form, 'urlSearch')
      } else {
        if (!t.dataTransfer.types.indexOf || - 1 === t.dataTransfer.types.indexOf('text/uri-list')) return;
        e.url.value = t.dataTransfer.getData('text/uri-list'),
        e.submitForm(!0, e.form, 'urlSearch')
      }
      e.point.style.display = 'block'
    }))
  },
  initdisplay: function () {
    var e = this;
    e.entry && (e.entry.style.display = ''),
    e.dragts && e.closedg(),
    e.form && e.form.reset(),
    e.point && (e.point.style.display = 'none')
  },
  closedg: function () {
    var e = this;
    (e.isOpera || !window.FileReader) && this.dragts && (this.dragts.style.display = 'none')
  },
  hiddenContent: function (e, t) {
    for (var i, e = window.event || e, n = e.srcElement || e.target, s = this; n && n.getAttribute && 'BODY' !== n.tagName && 'HTML' !== n.tagName && (i = n.getAttribute('id'), 'stcontent' !== i); ) n = n.parentNode;
    return 'stcontent' !== i ? 0 === t ? void s.closest()  : void (s.draghp.style.display = 'none')  : void 0
  },
  fixedMouse: function (e, t) {
    var i,
    n = e.type.toLowerCase();
    if ('mouseover' === n) i = e.relatedTarget || e.fromElement;
     else {
      if ('mouseout' !== n) return !0;
      i = e.relatedTarget || e.toElement
    }
    return i && 'xul' !== i.prefix && !this.contains(t, i) && i !== t
  },
  contains: function (e, t) {
    return e.contains ? e !== t && e.contains(t)  : !!(16 & e.compareDocumentPosition(t))
  },
  addEvent: function (e, t, i) {
    e.attachEvent ? (e['e' + t + i] = i, e[t + i] = function () {
      e['e' + t + i](window.event)
    }, e.attachEvent('on' + t, e[t + i]))  : e.addEventListener(t, i, !1)
  },
  removeEvent: function (e, t, i) {
    e.detachEvent ? (e.detachEvent('on' + t, e[t + i]), e[t + i] = null)  : e.removeEventListener(t, i, !1)
  },
  closest: function () {
    this.content.style.display = 'none',
    this.hpobj && (this.hpobj.style.display = ''),
    this.sugTg = 0,
    this.isDisplay = 0
  },
  displayst: function () {
    this.point.style.display = 'none',
    this.content.style.display = '',
    this.hpobj && (this.hpobj.style.display = 'none'),
    this.sugTg = 1,
    document.getElementById('image-sug-no-0') && (document.getElementById('image-sug-no-0').style.display = 'none'),
    document.getElementById('image-sug-no-1') && (document.getElementById('image-sug-no-1').style.display = 'none'),
    window.sugrecno = - 1,
    this.url.focus()
  },
  checkImgType: function (e) {
    return !0
  },
  getValue: function () {
    var e = this.file,
    t = this.url,
    i = this.point,
    n = this.form2;
    i.style.display = 'none';
    var s = e.value;
    t.value = s;
    var o = '' !== s && this.checkImgType(s);
    this.shituvalue2.value = 'upload',
    this.submitForm(o, n, 'uploadSearch')
  },
  handlerFiles: function (e) {
    var t = this;
    if (!t.isOpera && window.FileReader) {
      var i = e[0],
      n = (t.file, new FileReader);
      if (t.chrome && !window.useFlashUp && i && i.size >= 1048576) throw alert('拖动的图片大小不能超过1M'),
      t.point.style.display = 'none',
      new Error('image file size exceed');
      n.onload = function (e) {
        return function (i) {
          var n = i.target.result,
          s = e.type,
          a = n.split(',') [1];
          if (window.useFlashUp && a) {
            var l = o.getMovie('STUUpload');
            if (l) return void l.setImgStrData(a, s, e.name)
          }
          t.submitForm2(n, e.name, s)
        }
      }(i),
      n.readAsDataURL(i)
    }
  },
  handlerFiles2: function (e) {
    var t = this;
    if (!t.isOpera && window.FileReader) {
      t.showLoading();
      var i = e[0].getAsFile(),
      n = (t.file, new FileReader);
      if (t.chrome && !window.useFlashUp && i && i.size >= 1048576) throw alert('截取的图片大小不能超过1M'),
      t.point.style.display = 'none',
      new Error('image file size exceed');
      window.ss && window.ss({
        p: 'jpUploadSearch'
      }),
      n.onload = function (e) {
        return function (i) {
          var n = i.target.result,
          s = e.type,
          a = n.split(',') [1],
          l = 'shitu' + (new Date).getTime() + '.png';
          if (window.useFlashUp && a) {
            var r = o.getMovie('STUUpload');
            if (r) return void r.setImgStrData(a, s, l)
          }
          t.submitForm2(n, l, s)
        }
      }(i),
      n.readAsDataURL(i)
    }
  },
  _imgReq: function () {
  },
  submitForm: function (e, t, i) {
    return e ? (window.ss && window.ss({
      type: 'searchNum',
      p: i,
      form: 'searchresult'
    }), this.entry.style.zIndex = '2', this.point.style.display = 'block', this.onuploadtg = 1, t.submit(), !0)  : (alert('您的文件格式不正确或图片网址过长。支持jpg、gif、png、jpeg、bmp格式图片及250个字符内的图片网址。'), this.point.style.display = 'none', this.draghp.style.display = 'none', t.reset(), !1)
  },
  submitForm2: function (e, t, i) {
    var n,
    s = this,
    o = document.getElementById('filename'),
    a = - 1 !== i.indexOf('image'),
    l = e;
    document.getElementById('dragimage') ? n = document.getElementById('dragimage')  : (n = document.createElement('input'), n.name = 'dragimage', n.id = 'dragimage', n.type = 'hidden', s.form2.appendChild(n)),
    n.value = l,
    o.value = t || '',
    a = !0,
    s.submitForm(a, s.form2, 'uploadSearch')
  },
  showLoading: function () {
    this.point.style.display = 'block'
  },
  hideLoading: function () {
    this.point.style.display = 'none'
  },
  on: function (e, t, i) {
    this.callbacks[e] && (this.callbacks[e][t] = i)
  },
  fire: function (e, t) {
    this.callbacks[e] && (this.callbacks[e][t] = null, delete this.callbacks[e][t])
  }
})
});
; /*!searchresult:widget/ad/ecom199/init.js*/
define('searchresult:widget/ad/ecom199/init', function (e) {
function t(e) {
  this.defaultOpts = {
  },
  this.container = null,
  this.options = n.extend(this.defaultOpts, e || {
  })
}
var n = e('common:widget/ui/base/base'),
i = e('searchresult:widget/ui/statistic/statistic');
return n.extend(t.prototype, {
  init: function (e) {
    this.$container = n('#' + (e || 'relecom199')),
    i(null, 53, {
      type: 'pinzhuan',
      event: 'show'
    }),
    this._bindEvent()
  },
  render: function (e) {
    window.ecom && window.ecom.ma && window.ecom.ma.image && window.ecom.ma.image.renderBackground && (window.ecom.ma.image.renderBackground = null);
    var t,
    n,
    a,
    o,
    c;
    try {
      c = ecom.ma.image.TopBackground,
      t = c.getPrimaryBack(),
      n = c.getSecondaryBack(),
      o = parseInt(c.getSecondaryHeight()) || 0,
      a = parseInt(c.getPrimaryHeight()) || 0
    } catch (r) {
      return
    }
    var d = document.createElement('div');
    if (d.className = 'ma-primary-bg', d.style.background = t, d.style.height = a + 'px', document.body.appendChild(d), n && o > 0) {
      var s = document.createElement('div');
      s.className = 'ma-repeat-bg',
      s.style.height = o + 'px',
      s.style.background = n,
      document.body.appendChild(s)
    }
    1 != e && this.container ? this.$container.hide()  : this.$container.show(),
    i(null, 53, {
      type: 'pinzhuan',
      event: 'show'
    })
  },
  _bindEvent: function () {
    var e = this;
    e.$container.on('click', function (t) {
      var n = t.target;
      n != e.$container[0] && setTimeout(function () {
        i(null, 53, {
          type: 'pinzhuan',
          event: 'click'
        })
      }, 100)
    })
  }
}),
t
});
; /*!searchresult:widget/ad/sning1/sning1.js*/
define('searchresult:widget/ad/sning1/sning1', function (t, i, n) {
function a(t) {
  this.defaultOpts = {
  },
  this.$container = null,
  this.options = e.extend(this.defaultOpts, t || {
  })
}
var e = t('common:widget/ui/base/base'),
s = t('searchresult:widget/ui/statistic/statistic');
e.extend(a.prototype, {
  init: function (t) {
    this.$container = e('#' + t),
    this._render(),
    this._bindEvent()
  },
  _render: function () {
    this.$container.parents('#pnlBeforeContent').css({
      padding: '0 50px 0 40px'
    });
    var t = this.$container.find('img').eq(0),
    i = this.options.specialDatas.Items && this.options.specialDatas.Items[0].Images[0],
    n = this.options.specialDatas,
    a = n.Items[0].BrandName,
    e = n.Tag;
    i.ImageUrl && t.attr('src', i.ImageUrl),
    s(null, 1010100, {
      as: a,
      pos: e,
      subpos: '0',
      shownum: '1',
      matcont: i.ImageUrl,
      materialNum: '1'
    })
  },
  updateTipTemplate: function () {
    var t = '本搜索结果为<a target="_blank" href="http://e.baidu.com/">商业推广</a>信息，请注意可能的风险。您当前为登录状态，已参加<a target="_blank" href="http://baozhang.baidu.com/guarantee/">网民权益保障计划</a>。';
    e('.tuiguang-info').empty().append(t)
  },
  _bindEvent: function () {
    var t = this;
    this.$container.on('click', '.tuiguang-box', function (i) {
      var n = t.options.specialDatas,
      a = n.Items && n.Items[0],
      e = a.BrandName,
      o = n.Tag;
      i.stopPropagation(),
      s(null, 1010101, {
        as: e,
        pos: o,
        subpos: '0',
        matcont: a.Images[0].ImageUrl,
        tgTo: 1
      });
      var c = t.options.specialDatas.Items[0].Images[0].AdLink;
      c && window.open(c)
    });
    var i = this.$container,
    n = i.find('.tuiguang-btn'),
    a = i.find('.tuiguang-info');
    n.on('click', function () {
      a.show()
    }),
    t.clickTips = setTimeout(function () {
      a.hide()
    }, 4000),
    a.hover(function () {
      a.show(),
      clearTimeout(t.clickTips)
    }, function () {
      t.clickTips = setTimeout(function () {
        a.hide()
      }, 4000)
    }),
    a.on('click', function () {
      a.hide()
    })
  }
}),
n.exports = a
});
; /*!searchresult:widget/ad/sning2/sning2.js*/
define('searchresult:widget/ad/sning2/sning2', function (t, i, n) {
function e(t) {
  this.defaultOpts = {
  },
  this.$container = null,
  this.options = s.extend(this.defaultOpts, t || {
  })
}
var s = t('common:widget/ui/base/base'),
a = t('searchresult:widget/ui/statistic/statistic');
s.extend(e.prototype, {
  init: function (t) {
    this.$container = s('#' + t),
    this._render(),
    this._bindEvent()
  },
  _render: function () {
    var t = this.$container.find('img').eq(0),
    i = this.options.specialDatas.Items && this.options.specialDatas.Items[0].Images[0];
    i.ImageUrl && t.attr('src', i.ImageUrl),
    a(null, 53, {
      type: 'feibiao',
      tag: this.options.specialDatas.Tag,
      vs: window.vsid || '',
      event: 'show'
    })
  },
  _bindEvent: function () {
    var t = this;
    t.$container.on('click', '.close-btn', function (i) {
      i.stopPropagation(),
      a(null, 53, {
        type: 'feibiao',
        tag: t.options.specialDatas.Tag,
        event: 'close'
      }),
      t.$container.hide()
    }),
    t.$container.on('click', 'a', function (i) {
      i.stopPropagation(),
      a(null, 53, {
        type: 'feibiao',
        tag: t.options.specialDatas.Tag,
        tgTo: 1,
        event: 'click'
      });
      var n = t.options.specialDatas.Items[0].Images[0].AdLink;
      n && window.open(n)
    })
  }
}),
n.exports = e
});
; /*!searchresult:widget/ad/sning3/sning3.js*/
define('searchresult:widget/ad/sning3/sning3', function (t, i, n) {
function s(t) {
  this.defaultOpts = {
  },
  this.container = null,
  this.options = e.extend(this.defaultOpts, t || {
  })
}
var e = t('common:widget/ui/base/base'),
a = t('searchresult:widget/ui/statistic/statistic');
e.extend(s.prototype, {
  init: function (t) {
    this.$container = e('#' + (t || 'sning3')),
    this.render(),
    this._bindEvent()
  },
  render: function () {
    var t = this.$container.find('img').eq(0),
    i = this.options.specialDatas.Items && this.options.specialDatas.Items[0].Images[0];
    i.ImageUrl && t.attr('src', i.ImageUrl),
    a(null, 53, {
      type: 'feibiao',
      tag: this.options.specialDatas.Tag,
      vs: window.vsid || '',
      event: 'show'
    })
  },
  _bindEvent: function () {
    var t = this;
    t.$container.on('click', 'a', function () {
      a(null, 53, {
        type: 'feibiao',
        tag: t.options.specialDatas.Tag,
        tgTo: 1,
        event: 'click'
      }),
      window.open(t.options.specialDatas.Items[0].Images[0].AdLink)
    })
  }
}),
n.exports = s
});
; /*!searchresult:widget/pagelets/base/backTop/init.js*/
define('searchresult:widget/pagelets/base/backTop/init', function (e) {
function o(e) {
  var o = document;
  return void 0 !== e ? o.documentElement.scrollTop = o.body.scrollTop = e : Math.max(o.documentElement.scrollTop, o.body.scrollTop)
}
function t(e) {
  setTimeout(function () {
    e = Math.floor(0.65 * e),
    o(e),
    0 != e ? setTimeout(arguments.callee, 25)  : i(document).trigger('after-scrolltop')
  }, 25)
}
function s() {
  var e = i('#backTop');
  i(window).scrollTop() > l ? n || (c ? 'absolute' != e.css('position') && (e.css({
    position: 'absolute'
  }), e[0].style.setExpression('top', 'eval(document.documentElement.scrollTop + documentElement.clientHeight - this.clientHeight - 40) + \'px\''))  : 'fixed' != e.css('position') && e.css({
    position: 'fixed'
  }), n = !0, c ? e.show()  : e.fadeIn('slow'))  : n && (n = !1, c ? (e.css({
    position: 'relative'
  }), e.hide(), e[0].style.removeExpression('top'))  : e.fadeOut('fast', function () {
    e.css({
      position: 'relative'
    })
  }))
}
var i = e('common:widget/ui/base/base'),
n = (e('searchresult:widget/ui/statistic/statistic'), !1),
c = i.browser.msie && 6 == i.browser.version,
l = 200;
i(window).scroll(s),
i(document).ready(function () {
  i('#backTop').click(function (e) {
    e.preventDefault(),
    i(document).trigger('before-scrolltop'),
    t(o())
  })
})
});
; /*!searchresult:widget/pagelets/base/timeliness/init.js*/
define('searchresult:widget/pagelets/base/timeliness/init', function (t, i, e) {
var s = t('common:widget/ui/base/base'),
o = t('common:widget/ui/juicer/juicer'),
n = t('searchresult:widget/ui/statistic/statistic'),
r = s.browser.msie && s.browser.version < 10,
a = e.exports = function () {
};
s.extend(a.prototype, {
  init: function (t) {
    this.root = s('#timeliness'),
    this.opts = {
      data: t
    },
    this.decorate(),
    this.bindEvents()
  },
  decorate: function () {
    var t = this.opts.data,
    i = s('#timeliness-tpl').html(),
    e = s('#topRS'),
    r = s('body').width(),
    a = e.width(),
    h = t.type,
    t = this.detectionHttps(t.pc);
    'pray' === h && s.browser.msie && 10 === parseInt(s.browser.version, 10) || (260 > r - a && e.width(a - 260), this.root.html(o(i, t)), 'pray' === h && (s('#timeliness-title').html(t.searchtitle).show(), this.switchColorful(!0)), n(null, 53, {
      type: 'pctimeliness' + h + '-show'
    }))
  },
  detectionHttps: function (t) {
    for (var i in t) {
      var e = t[i];
      'string' == typeof e && 'http://' === e.substring(0, 7) ? t[i] = e.replace('http://', 'https://')  : e instanceof Object && (t[i] = this.detectionHttps(e))
    }
    return t
  },
  eggShow: function () {
    if (!(this.timeIds && this.timeIds.length > 4)) {
      this.timeIds = this.timeIds || [
      ];
      for (var t = (this.root, s('body').width()), i = s(window).height(), e = (this.opts.time, this), o = 0; 8 > o; o++) {
        {
          var n = s('.egg:eq(0)').clone();
          Math.random() > 0.5 ? '-' : '',
          60 * Math.random()
        }
        s('body').append(n),
        n.css({
          display: 'block',
          opacity: 1,
          left: Math.random() * t
        }),
        n.find('img').width(100 * Math.random()),
        r ? n.animate({
          top: '+=' + (i + 200),
          display: 'none'
        }, 4000, function () {
          s(this).hide()
        })  : n.addClass('animate-zoomout')
      }
      this.timeIds.push(setTimeout(function () {
        e.eggShow()
      }, 800))
    }
  },
  clearEgg: function () {
    var t = s('.egg:eq(0)').clone(),
    i = this.root;
    this.timeIds = [
    ],
    s('.egg').remove(),
    i.append(t)
  },
  switchColorful: function (t) {
    var i = (this.root, this.root.find('.blessing-content')),
    e = s('.blessing-img'),
    o = i.offset();
    t ? (s('body').append(e), e.css({
      position: 'absolute',
      top: o.top - 5,
      left: o.left - 28
    }))  : (e.css({
      top: o.top - 7
    }), i.parent().prepend(e))
  },
  bindEvents: function () {
    var t = this.root,
    i = this.opts.data.type,
    e = this;
    t.click('pray' === i ? function () {
      e.switchColorful(),
      n(null, 53, {
        type: 'pctimeliness' + i + '-click'
      })
    }
     : function () {
      e.clearEgg(),
      e.eggShow(),
      n(null, 53, {
        type: 'pctimeliness' + i + '-click'
      })
    })
  }
})
});
; /*!searchresult:widget/pagelets/base/topInfoBar/topInfoBar.js*/
define('searchresult:widget/pagelets/base/topInfoBar/topInfoBar', function (t, e, i) {
function s() {
  this.$el = n('#topInfoBar'),
  this.$parent = this.$el.parent(),
  this.$win = n(window)
}
var n = t('common:widget/ui/base/base');
s.prototype.update = function () {
  this.$el && (this.$win.scrollTop() > 38 ? this.$parent.addClass('child_fixed')  : this.$parent.removeClass('child_fixed'))
},
i.exports = s
});
; /*!searchresult:widget/ui/action/movie/imgcollection_setting.js*/
define('searchresult:widget/ui/action/movie/imgcollection_setting', function (e, t, i) {
function s() {
  o.apply(this, arguments)
}
var r = e('common:widget/ui/base/base'),
g = e('searchresult:widget/ui/utils/utils'),
a = e('searchresult:widget/ui/utils/lib'),
o = e('searchresult:widget/ui/action/base/imgcollectioin_setting');
r.extend(!0, s.prototype, o.prototype, {
  fieldMap: {
    detailUrl: function (e) {
      var t = this.pageModel,
      i = + t.get('rpstart') || 0,
      s = + t.get('rpnum') || 0,
      r = + e.personalized ? i : + e.pageNum >= i ? s : 0,
      o = + e.pageNum + r;
      return '/search/detail?ct=503316480&z=' + t.get('z') + '&tn=baiduimagedetail&ipn=d&word=' + t.get('queryWord') + '&step_word=' + (t.get('step_word') || '') + '&ie=' + t.get('ie') + '&in=' + e.currentIndex + '&cl=' + t.get('cl') + '&lm=' + t.get('lm') + '&st=' + t.get('st') + '&cs=' + e.cs + '&os=' + e.os + '&simid=' + e.simid + '&pn=' + o + '&rn=1&di=' + e.di + '&ln=' + t.get('listNum') + '&fr=&fmq=' + g.fmqValueSet() + '&fm=' + (t.get('fm') || '') + '&ic=' + t.get('ic') + '&s=' + t.get('s') + '&se=' + t.get('se') + '&sme=' + t.get('sme') + '&tab=' + (e.tab || 0) + '&face=' + e.face + '&is=' + e.is + '&istype=' + (t.get('istype') || 0) + '&ist=' + e.source_type + '&jit=' + t.get('jit') + '&width=&height=&bdtype=' + (e.bdSrcType || 0) + '&gsm=' + (t.get('tmpGsm') || 0) + ( + t.get('hs') ? '&hs=' + t.get('hs')  : '') + (t.get('oriquery') ? '&oriquery=' + t.get('oriquery')  : '') + '&objurl=' + encodeURIComponent(a.uncompileURL(e.objURL)) + '&rpstart=' + (t.get('rpstart') || 0) + '&rpnum=' + (t.get('rpnum') || 0) + '&adpicid=' + (e.adPicId || 0) + '&tabname=' + (t.get('tabName') || '')
    }
  }
}),
i.exports = s
});
; /*!searchresult:widget/ui/action/movie/action.js*/
define('searchresult:widget/ui/action/movie/action', function (e) {
function t() {
  a.apply(this, arguments),
  this._imgCollections = {
  }
}
var o = e('common:widget/ui/base/base'),
i = e('searchresult:widget/ui/app/page'),
n = e('searchresult:widget/ui/collections/imgcollection'),
s = e('searchresult:widget/ui/action/movie/imgcollection_setting'),
l = e('searchresult:widget/ui/strategy/imglayoutstrategy'),
a = e('searchresult:widget/ui/action/base/base'),
r = e('searchresult:widget/ui/statistic/bdgstat'),
c = null,
g = '全部',
d = '';
return o.extend(t.prototype, a.prototype, {
  initImgCollection: function () {
    d = i.model.get('queryWord'),
    c = i.imgCollection,
    new s(c, this.pageModel).process(),
    this.setImgCollection(g, c)
  },
  setImgCollection: function (e, t) {
    e && (this._imgCollections[e] = t)
  },
  getImgCollection: function (e) {
    e = e || '全部';
    var t;
    if (e in this._imgCollections) return t = this._imgCollections[e];
    t = new n,
    this.setImgCollection(e, t),
    new s(t, i.filterModel).process();
    var l = '';
    return e && '全部' !== e && (l = e),
    t.setReqParams(o.extend({
    }, t.getReqParams(), {
      tabname: l
    })),
    t
  },
  clearImgCollections: function () {
    this._imgCollections = {
    }
  },
  initHandlers: function () {
    var e = this;
    i.handlers.extend({
      onHistoryChangedHandler: function () {
      },
      onPageUnLoadedHandler: function () {
      },
      onPageResizeHandler: function () {
        i.sizeManager.update()
      },
      onFilterSizeChanged: function (t) {
        window.scrollTo(0, 0),
        i.filterModel.set('word', i.model.get('queryWord')),
        i.filterModel.set(t),
        i.model.set(t),
        e.clearImgCollections(),
        c = e.getImgCollection(g),
        i.controls.imgPageList.clear(),
        i.controls.imgPageList.reset(c, new l(i.model), i.insertStrategy, !1),
        i.controls.imgPageList.append()
      },
      onMovieTabChanged: function (t) {
        var o = d,
        n = t.subQuery || '';
        n && '全部' !== n ? (o += ' ' + n, i.model.set('tabName', n))  : i.model.set('tabName', ''),
        i.filterModel.set('queryWord', o),
        i.model.set('queryWord', o),
        g = n,
        c = e.getImgCollection(n),
        i.controls.imgPageList.clear(),
        i.controls.imgPageList.reset(c, new l(i.model), i.insertStrategy, !1),
        i.controls.imgPageList.append()
      },
      onImagesLoaded: function (e) {
        var t = 30,
        n = c || i.imgCollection;
        n.getByOffset(0, t).then(function (t) {
          var i = 0;
          o.each(t, function (e, t) {
            return '4' !== t.adType ? !1 : void i++
          }),
          r.sendLog({
            as: 'yingshi',
            p: 1010100,
            pos: 'pc_result_images_tabs',
            subpos: 0,
            matcont: e.subQuery || '全部',
            shownum: i
          })
        })
      }
    })
  }
}),
t
});
; /*!searchresult:widget/ui/app/lazyPage.js*/
define('searchresult:widget/ui/app/lazyPage', function (e) {
function t() {
}
var r = e('common:widget/ui/base/base'),
o = e('searchresult:widget/ui/controls/filter/sizeFilter/sizeFilter'),
i = e('searchresult:widget/ui/controls/filter/colorFilter/colorFilter'),
s = e('searchresult:widget/ui/controls/filter/typeFilter/typeFilter'),
n = e('searchresult:widget/ui/controls/RsBox/RsBox'),
a = e('searchresult:widget/ui/controls/relsearchBox/relsearchBox'),
l = e('searchresult:widget/ui/controls/fixedSearchBox/fixedSearchBox'),
d = e('common:widget/ui/userInfo/userInfo'),
c = e('searchresult:widget/ui/controls/ReportBox/ReportBox'),
g = e('searchresult:widget/ui/controls/hotwordBox/hotwordBox'),
u = e('searchresult:widget/ui/statistic/statistic'),
h = e('searchresult:widget/pagelets/base/topInfoBar/topInfoBar'),
p = e('searchresult:widget/ui/controls/movieBanners/bannerContainer'),
m = e('searchresult:widget/ui/controls/movieTabs/tabs'),
w = e('searchresult:widget/ui/controls/imgpagelist/FCADBox/FCADBox'),
B = e('searchresult:widget/ui/controls/imgpagelist/TJADBox/TJADBox'),
f = e('searchresult:widget/ad/sning1/sning1'),
x = e('searchresult:widget/pagelets/movie/banners/banners'),
b = !0;
return r.extend(t.prototype, {
  init: function (e) {
    this.model = e.model,
    this.page = e,
    this.createControls(),
    this.initControls(),
    this.run(),
    u(null, 56, {
      type: 'pageturn',
      curr: 1,
      picnum: 15,
      fr: this.model.get('fr')
    })
  },
  createControls: function () {
    var e = this.page,
    t = this.page.controls;
    t.rsBox = new n(e.filterModel, this.model),
    t.relsearchBox = new a(e.filterModel),
    t.userInfoBox = new d,
    t.fixBox = new l(e.filterModel, this.model),
    t.reportBox = new c(e.filterModel),
    t.hotwordBox = new g,
    t.sizeFilter = new o(e.filterModel),
    t.colorFilter = new i(e.filterModel),
    t.typeFilter = new s(e.filterModel);
    var r = e.model.tempData.get('browserRsData');
    (!r || b) && (t.movieBanners = new p({
      banners: this.model.tempData.get('movieBanners')
    }), t.movieTabs = new m({
      tabs: this.model.tempData.get('movieTabs')
    }), t.topInfoBar = new h)
  },
  run: function () {
    var e = this;
    e.bindModel(),
    e.bindEvent()
  },
  bindModel: function () {
  },
  bindEvent: function () {
    var e = this.page,
    t = this.page.controls;
    t.sizeFilter.on('sizeChanged', e.handlers.get('onFilterSizeChanged')),
    t.colorFilter.on('sizeChanged', e.handlers.get('onFilterSizeChanged')),
    t.typeFilter.on('sizeChanged', e.handlers.get('onFilterSizeChanged')),
    t.movieTabs.on('tabChanged', e.handlers.get('onMovieTabChanged')),
    e.resizer.start(),
    window.bdimgBW && window.bdimgBW > 0 && Math.abs(r(window).width() - window.bdimgBW) >= 80 && t.imgPageList.refresh();
    var o = location.href;
    o = o.replace(/&ctd=([^&]+)/, ''),
    o && window.history && window.history.replaceState && window.history.replaceState(null, '', o + ''),
    e.sizeManager.addObserver(t.rsBox, 'updateRs').addObserver(t.fixBox.rsBox, 'updateRs').notify(),
    e.scrollManager.addObserver(t.topInfoBar, 'update').addObserver(t.fixBox, 'update').notify()
  },
  initControls: function () {
    var e = this.page,
    t = this.page.controls,
    o = new f;
    t.sizeFilter.init('sizeFilter'),
    t.colorFilter.init('colorFilter'),
    t.typeFilter.init('typeFilter'),
    t.hotwordBox.init(e.model.tempData.get('hotWords')),
    t.rsBox.init(e.model.tempData.get('rsQuery'), e.model.tempData.get('rsRecommend')),
    t.relsearchBox.init(e.model.tempData.get('rsQuery'), e.model.tempData.get('rsRecommend'), 'result_bottom'),
    t.userInfoBox.init(function () {
      w.updateTipTemplate(),
      B.updateTipTemplate(),
      o.updateTipTemplate(),
      x[2].prototype.updateTipTemplate()
    }),
    t.reportBox.init(),
    t.fixBox.init(e.model.tempData.get('rsQuery'), e.model.tempData.get('rsRecommend')),
    t.movieBanners.render(r('#movie-banner-area')),
    t.movieTabs.on('imagesLoaded', e.handlers.get('onImagesLoaded')),
    t.movieTabs.render(r('#movie-tabs-area')),
    r(window).scrollTop(0)
  }
}),
t
});
