/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "sfmono:size=10", "fontawesome:size=12", "fontawesome5prolight:size=12" };
static const char dmenufont[]       = "sfmono:size=10";
static const char col_gray1[]       = "#202027";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#F0F0F0";
static const char col_gray4[]       = "#FBFBFB";
static const char col_cyan[]        = /*"#4d3a4d"*/"#444450";
static const unsigned int baralpha = OPAQUE;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeGap] = { "#000000", "#000000", "#000000"  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeGap]  = { 0, 0, 0 },
};

static const char *const autostart[] = {
        "sh", "-c", "dwmblocks", NULL,
        "sh", "-c", "picom --experimental-backends", NULL,
        NULL
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

#include <X11/XF86keysym.h>
#include "shiftview.c"


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
  { "Spotify",  NULL,       NULL,       1 << 4,       1,           -1 },
	{ "moolticute",  NULL,    NULL,       1 << 6,       1,           -1 },
  { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1,        50,50,500,500,        3 },
  { "moolticute",  NULL,    NULL,       1 << 6,       1,           -1,        50,50,500,300,        3 },
  { "qjackctl",  NULL,    NULL,       1 << 6,       1,           -1,        50,50,500,300,        3 },
  // { "scratchpad",       NULL,       NULL,       0,            1,           -1,        50,50,500,300,        3 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "|M|",      centeredmaster },
	/*{ "[M]",      monocle },
	{ ">M>",      centeredfloatingmaster },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },*/
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *webbrowser[] = { "brave", NULL};
static const char *mailclient[] = { "thunderbird", NULL};
static const char *nmtui[] = { "st", "-t", "nmtui", "-g", "120x34", "-e", "nmtui", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,           XK_equal,  incrgaps,       {.i = +1 } },
  //{ MODKEY,                     XK_minus,  incrgaps,       {.i = -1 } },
  //{ MODKEY|ShiftMask,           XK_equal,  incrogaps,      {.i = +1 } },
  //{ MODKEY,                     XK_minus,  incrogaps,      {.i = -1 } },
  { MODKEY|ShiftMask|ControlMask, XK_equal,  incrigaps,      {.i = +1 } },
  { MODKEY|ControlMask,           XK_minus,  incrigaps,      {.i = -1 } },
  { MODKEY,                       XK_g,      togglegaps,     {0} },
  { MODKEY|ControlMask,           XK_equal,  defaultgaps,    {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_z,           incrgaps,       {.i = -20 } },
  { MODKEY|ShiftMask,             XK_z,           incrgaps,       {.i = +20 } },
  { MODKEY,                       XK_s,           togglesticky,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },


	//services
  { MODKEY,                       XK_a,           spawn,          SHCMD("st -e alsamixer ; pkill -RTMIN+10 dwmblocks") },
  { MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_d,           togglegaps,     {0} },
  { MODKEY,                       XK_f,           togglefullscr,  {0} },
  { MODKEY,                       XK_g,           shiftview,      { .i = -1 } },
  { MODKEY,                       XK_semicolon,   shiftview,      { .i = 1 } },
  { MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,      togglescratch,  {.v = scratchpadcmd } },
  { MODKEY|ShiftMask,             XK_x,           spawn,          SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && shutdown -h now") },
  { MODKEY|ShiftMask,             XK_Delete,      spawn,          SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Reboot?\")\" = Yes ] && reboot") },
	{ MODKEY|ShiftMask,             XK_BackSpace,   spawn,          SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Logout?\")\" = Yes ] && pkill -u $USER ") },

	{ MODKEY|ShiftMask,             XK_c,           spawn,          SHCMD("showclip") },
  { MODKEY|ShiftMask,             XK_v,           spawn,          SHCMD("killall picom || picom -b -o .9") },
  { MODKEY|ShiftMask,             XK_b,           spawn,          SHCMD("nitrogen ~/backgrounds --random --set-zoom-fill ") },
  { MODKEY,                       XK_w,           spawn,          {.v = webbrowser } },
  { MODKEY|ShiftMask,             XK_w,           spawn,          {.v = nmtui } }, /* Networkmanager TUI*/
  { MODKEY,                       XK_e,           spawn,          {.v = mailclient } },
  { MODKEY,                       XK_r,           spawn,          SHCMD("st -e ranger") },
	{ MODKEY|ShiftMask,             XK_r,           spawn,          SHCMD("st -e sudo ranger") },


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
