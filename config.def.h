/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:size=11:antialias=true:style=Meduim:minspace=False:hinting=true" };
// static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:size=12" };
static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:pixelsize=16:antialias=true:style=Semibold:autohist=true" };
static const char dmenufont[]       = "SauceCodePro Nerd Font Mono:size=11:antialias=true:style=Semibold:minspace=False:hinting=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#0bbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeSel] = { "#0ccccc", col_gray1, "#ff3335" },
    [SchemeNorm]  = { "#0eeeee", "#055555", col_gray2 },
    [SchemeTest3]  = { "#00f8ff", "#055555", "#055555" },
    [SchemeTest4]  = { "#fff505", "#055555", "#ff0000" },
    [SchemeTest5]  = { "#20e270", "#055555", "#ff0000" },
    [SchemeTest6]  = { "#ff5500", "#055555", "#ff0000" },
    [SchemeTest7]  = { "#ff62b0", "#055555", "#ff0000" },
    [SchemeTest8]  = { "#ff5555", "#055555", "#ff0000" },
    [SchemeTest9]  = { "#ff62b0", "#055555", "#ff0000" },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border     */
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeTest3]  = { OPAQUE, baralpha, borderalpha },
    [SchemeTest4]  = { OPAQUE, baralpha, borderalpha },
    [SchemeTest5]  = { OPAQUE, baralpha, borderalpha },
    [SchemeTest6]  = { OPAQUE, baralpha, borderalpha },
    [SchemeTest7]  = { OPAQUE, baralpha, borderalpha },
    [SchemeTest8]  = { OPAQUE, baralpha, borderalpha },
    [SchemeTest9]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    // { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    // { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
    { "Google-chrome",  NULL,       NULL,       1 << 1,       0,           -1 },
    { "TelegramDesktop",  NULL,       NULL,       1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    // { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont,
    "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
// static const char *termcmd[]  = { "urxvt", NULL };

static const char *set_mon_large[]  = { "/usr/bin/zsh", "-c", "/home/igorek/scripts/mon_large.zsh", NULL };
static const char *set_mon_small[]  = { "/usr/bin/zsh", "-c", "/home/igorek/scripts/mon_small.zsh", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
    { MODKEY,                       XK_comma,  incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_period, incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    // { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    // { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    // { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    // { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },

    // Monitor
    { MODKEY|ShiftMask,             XK_comma,  spawn,          {.v = set_mon_large } },
    { MODKEY|ShiftMask,             XK_period, spawn,          {.v = set_mon_small } },

    // Print screen
    { 0,                          XK_Print, spawn,          SHCMD("sleep 0.1; ~/scripts/screenshot.zsh") },
    { ShiftMask,                  XK_Print, spawn,          SHCMD("sleep 0.1; ~/scripts/screenshot_capture.zsh") },
    { ControlMask,                XK_Print, spawn,          SHCMD("sleep 0.1; ~/scripts/screenshot_delay_3.zsh") },

    // Brightness
    { ControlMask|Mod1Mask,       XK_equal, spawn,          SHCMD("~/scripts/set_brightness.zsh up") },
    { ControlMask|Mod1Mask,       XK_minus, spawn,          SHCMD("~/scripts/set_brightness.zsh down") },
    { ControlMask|Mod1Mask,       XK_0,     spawn,          SHCMD("~/scripts/set_brightness.zsh toggle") },

    // Gamma correction
    { ControlMask|Mod1Mask,       XK_Up,    spawn,          SHCMD("redshift -P -O 6500 -g 1.7:1.7:1.7") },
    { ControlMask|Mod1Mask,       XK_Down,  spawn,          SHCMD("redshift -P -O 6500 -g 1:1:1") },

    // Keys backlight
    { ControlMask,                XK_Up,    spawn,          SHCMD("~/scripts/set_backlight.zsh 1") },
    { ControlMask,                XK_Down,  spawn,          SHCMD("~/scripts/set_backlight.zsh 0") },

    // Audio volume
    { Mod1Mask,                   XK_m,     spawn,          SHCMD("~/scripts/audio/volume.zsh toggle") },
    { Mod1Mask,                   XK_minus, spawn,          SHCMD("~/scripts/audio/volume.zsh down") },
    { Mod1Mask,                   XK_equal, spawn,          SHCMD("~/scripts/audio/volume.zsh up") },
    { MODKEY,                     XK_a,     spawn,          SHCMD("~/scripts/audio/reload_audio_variables.zsh") },

    // { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    // { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    // { MODKEY,                       XK_0,      tag,            {.ui = ~0 } },
    // { MODKEY|ShiftMask,             XK_0,      tag,            {0} },
    // { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    // { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    // { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    // { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)

    { MODKEY|ShiftMask,             XK_h,      quit,           {0} },
    { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("killall dwmblocks; dwmblocks &") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

