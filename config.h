/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
// static const int floatborderpx = 3;
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const char *fonts[]          = { "HurmitNerdFont:size=8", "Noto Mono:style=Regular:size=30:antialias=true", "monospace:size=10" };
/*static const char *fonts[]          = { "Jam\-icons:style=Regular", "HurmitNerdFont:size=8", "monospace:size=10"};*/
/*static const char *fonts[]          = { "-wuncon-siji-medium-r-normal--0-0-75-75-c-0-iso10646-1" "," "HurmitNerdFont:size=8" "," "monospace:size=10"};*/
/*static const char *fonts[]          = { "monospace:size=10", "Noto Color Emoji:Regular:pixelsize=10:antialias=true:autohint=true"};*/
/*static char dmenufont[]       = "monospace:size=10";*/
static char dmenufont[]       = "HurmitNerdFont:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
  	/* class      instance    title       tags mask     isfloating   monitor    float x,y,w,h         floatborderpx*/
  	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        50,50,500,500,        3 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1,        50,50,500,500,        3 },
    { "moolticute",  NULL,    NULL,       1 << 6,       1,           -1,        50,50,500,300,        3 },
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
	{ "[+]",      gaplessgrid },
	/*{ "[S]",      solo },*/

};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *webbrowser[] = { "firefox", NULL};
static const char *mailclient[] = { "thunderbird", NULL};
/*static const char *ranger[] = {"st", "-e", "ranger", NULL};*/
static const char *nmtui[] = { "st", "-t", "nmtui", "-g", "120x34", "-e", "nmtui", NULL };


#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,			XK_grave,	spawn,	SHCMD("dmenuunicode") },
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	/*{ MODKEY,			XK_minus,	spawn,		SHCMD("amixer sset Master 5%- ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_minus,	spawn,		SHCMD("amixer sset Master 15%- ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY,			XK_equal,	spawn,		SHCMD("amixer sset Master 5%+ ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("amixer sset Master 15%+ ; pkill -RTMIN+10 dwmblocks") },*/
	{ MODKEY|ShiftMask,		XK_Delete,	spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Reboot?\")\" = Yes ] && reboot") },
	{ MODKEY|ShiftMask,             XK_BackSpace,   spawn,          SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Logout?\")\" = Yes ] && pkill -u $USER ") },
	{ MODKEY,			XK_Tab,		view,		{0} },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_w,		spawn,		{.v = webbrowser } },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		{.v = nmtui } }, /* Networkmanager TUI*/
	{ MODKEY,			XK_e,		spawn,		{.v = mailclient } },
	{ MODKEY,			XK_r,		spawn,		SHCMD("st -e ranger") },
        { MODKEY|ShiftMask,             XK_r,           spawn,          SHCMD("st -e sudo ranger") },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
        { MODKEY,                       XK_y,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[3]} },
	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_backslash,		view,		{0} },

	{ MODKEY,			XK_a,		spawn,		SHCMD("st -e alsamixer ; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY,			XK_s,		togglesticky,	{0} },
	{ MODKEY,			XK_d,		spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_d,		togglegaps,	{0} },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.v = scratchpadcmd } },

	{ MODKEY,			XK_z,		incrgaps,	{.i = -20 } },
	{ MODKEY|ShiftMask,		XK_z,		incrgaps,	{.i = +20 } },
	{ MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && shutdown -h now") },
	{ MODKEY|ShiftMask,		XK_c,		spawn,		SHCMD("showclip") },
	{ MODKEY|ShiftMask,		XK_v,		spawn,		SHCMD("killall compton || compton -b -o .9") },
	{ MODKEY,			XK_b,		togglebar,	{0} },
        { MODKEY|ShiftMask,             XK_b,           spawn,          SHCMD("nitrogen ~/backgrounds --random --set-zoom-fill ") },

/*	{ MODKEY,			XK_n,		spawn,		SHCMD("st -e newsboat; pkill -RTMIN+6 dwmblocks") },*/
/*	{ MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD("spotify") },*/
/*	{ MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD("amixer sset Master toggle ; pkill -RTMIN+10 dwmblocks") },*/

        { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },

	{ MODKEY,			XK_comma,	spawn,		SHCMD("playerctl previous") },
/*	{ MODKEY|ShiftMask,		XK_comma,	spawn,		SHCMD("mpc seek 0%") },*/
	{ MODKEY,			XK_period,	spawn,		SHCMD("playerctl next") },
/*	{ MODKEY|ShiftMask,		XK_period,	spawn,		SHCMD("mpc repeat") },*/

	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = 1 } },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },

	{ MODKEY,			XK_F1,		spawn,		SHCMD("flatpak run org.gajim.Gajim") },
	{ MODKEY,			XK_F2,		spawn,		SHCMD("nmcli radio wifi on || nmcli radio wifi off") },
	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
/*	{ MODKEY,			XK_F4,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo -A zzz") },*/
/*	{ MODKEY,			XK_F5,		xrdb,		{.v = NULL } },*/
/*	{ MODKEY,			XK_F6,		spawn,		SHCMD("") },*/
	{ MODKEY,			XK_F7,		spawn,		SHCMD("slock") },
/*	{ MODKEY,			XK_F8,		spawn,		SHCMD("displayselect") },*/
	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,		spawn,		SHCMD("dmenuumount") },
	{ MODKEY,			XK_F11,		spawn,		SHCMD("displaypick") },
	{ MODKEY,			XK_F12,		spawn,		SHCMD("dmenuwindowselect") },
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

/*	{ 0,				XK_Print,	spawn,		SHCMD("scrot '%Y-%m-%d_$wx$h_scrot.png' -e 'mv $f ~/Pictures/Screenshots/' && notify-send ScreenShot Taken") },*/
	{ 0,				XK_Print,	spawn,		SHCMD("maimpick && notify-send ScreenShot Taken") },
/*	{ ShiftMask,			XK_Print,	spawn,		SHCMD("maimpick") },*/
	{ MODKEY,			XK_Print,	spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,		XK_Print,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Delete,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },



        { 0, XF86XK_MonBrightnessUp,    spawn,          SHCMD("notify-send Brighter && sudo brightnessctl s 1000+") },
	{ 0, XF86XK_MonBrightnessDown,    spawn,          SHCMD("notify-send Darker && sudo brightnessctl s 1000-") },
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pactl set-sink-volume alsa_output.pci-0000_00_1b.0.analog-stereo 0% ; notify-send Muted") },
/*        { 0, XF86XK_AudioMute,          spawn,          SHCMD("amixer sset Master toggle ; pkill -RTMIN+10 dwmblocks") },*/
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD(" pulsemixer --change-volume +10 ; notify-send Louder") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD(" pulsemixer --change-volume -10 ; notify-send Softer") },
/*        { 0, XF86XK_AudioRaiseVolume,   spawn,          SHCMD(" pactl set-sink-volume alsa_output.pci-0000_00_1b.0.analog-stereo +10% ; notify-send Louder") },
        { 0, XF86XK_AudioLowerVolume,   spawn,          SHCMD(" pactl set-sink-volume alsa_output.pci-0000_00_1b.0.analog-stereo -10% ; notify-send Softer") },*/

	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("playerctl next") },
/*	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("playerctl pause") },*/
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("playerctl stop") },
/*	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("notify-sendseek -10") },*/
/*	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("notify-send seek +10") },*/
/*	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("st -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("st") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("st -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("st -e lf /") },*/
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
/*	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },*/

	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */

	/* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */

/*	 { MODKEY|Mod4Mask,              XK_n,      incrgaps,       {.i = +5 } },
	 { MODKEY|Mod4Mask,              XK_m,      incrgaps,       {.i = -5 } },*/
/*	 { MODKEY|ShiftMask,    	 XK_n,      incrogaps,      {.i = +5 } },
	 { MODKEY|ShiftMask,    	 XK_m,      incrogaps,      {.i = -5 } },
	 { MODKEY,		  	 XK_h,      incrigaps,      {.i = +5 } },
	 { MODKEY,           		 XK_l,      incrigaps,      {.i = -5 } },
*/
/*	 { MODKEY|ShiftMask,    	 XK_0,      defaultgaps,    {0} },*/
/*	 { MODKEY,                       XK_p,      incrihgaps,     {.i = +5 } },
	 { MODKEY,                       XK_o,      incrihgaps,     {.i = -5 } },
	 { MODKEY|ControlMask,           XK_p,      incrivgaps,     {.i = +5 } },
	 { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -5 } },
	 { MODKEY|Mod4Mask,              XK_p,      incrohgaps,     {.i = +5 } },
	 { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -5 } },
	 { MODKEY|ShiftMask,             XK_p,      incrovgaps,     {.i = +5 } },
	 { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -5 } },
*/

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

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "xrdb",		xrdb },
};
