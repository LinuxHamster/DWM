/* See LICENSE file for copyright and license details. */
/*
For audio control
*/
#include <X11/XF86keysym.h>



/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"Ubuntu Mono:size=16:antialias=true:autohint=true","SymbolsNerdFont:size=16:antialias=true:autohint=true","NotoColorEmoji:size=16:antialias=true:autohint=true" };
static const char dmenufont[]       = "Ubuntu Mono:size=16:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
/*My Colors*/
static const char col_red[]			= "#d30f23";
static const char col_red2[]		= "#FF0000";
static const char col_blue1[]		= "#1f2241";
static const char col_blue2[]		= "#3e4482";
static const char col_blue3[]		= "#0f36d3";
static const char col_blue4[]		= "#87cefa";
static const char col_green[]		= "#23d30f";
static const char col_pink[]		= "#ba3240";
static const char col_orange[]		= "#d3360f";
static const char col_purple[]		= "#d30f85";
static const char col_yellow[]		= "#d3c90f";
static const char col_grey[] 		= "#D3D3D3";
static const char col_white[] 		= "#ffffff";
static const char col_black[]		= "#000000";
static const char col_silver[]		= "#c0c0c0";
static const char col_dark_gray[]	= "#a9a9a9";
static const char col_dark_gray2[]  = "#020202";
static const char col_rin_blue1[] 	= "#255DFE";
static const char col_rin_blue2[]	= "#000254";
static const char col_rin_violet1[] = "#A30258";
//static const char *colors[][3]      = {
//	/*               fg         bg         border   */
//	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
//};

//My first color scheme, black and red
// static const char *colors[][3]      = {
  /*               fg         bg         border   */
//  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//  [SchemeSel]  = { col_gray4, col_red,  col_red  },
// };

//Second blue and red
// static const char *colors[][3]      = {
//   /*               fg (text)   bg (behind text)  border   */
//     [SchemeNorm] = { col_white, col_blue1, col_blue1 },//for non active tabs
//     [SchemeSel]  = { col_white, col_red,  col_red }, //active tabs
// };

	static const char *colors[][3]={
		[SchemeNorm] = { col_white, col_rin_blue2, col_rin_blue2},
		[SchemeSel] = {col_white, col_rin_blue1, col_rin_blue1},
	};


//themes work like layering so fg is the foreground (text)
//bg is behind the text, border are the the edges around the window


/*
audio constants
*/
static const char *upvol[]   = { "/home/john/.scripts/dwm/set_volume.sh", "up", NULL };
static const char *downvol[]   = { "/home/john/.scripts/dwm/set_volume.sh", "down", NULL };
static const char *mutevol[] = { "/home/john/.scripts/dwm/set_volume.sh","mute",  NULL };

/*brightness constants*/
static const char *upbrightness[] = {"/home/john/.scripts/dwm/set_brightness.sh", "up", NULL};
static const char *downbrightness[] = {"/home/john/.scripts/dwm/set_brightness.sh", "down", NULL};

/*
powermenu
*/
static const char *powermenu[] = { "/home/john/.scripts/dmenu/powermenu.sh", NULL };

/*
playback menu
*/
static const char *playback[] = {"/home/john/.scripts/media/playercontrol.sh",NULL};

/*
lockscreen
*/
static const char *lockcmd[] = {"slock", NULL};

/*
screenshot
*/
static const char *screenshot[] = {"scrot", "/home/john/Pictures/Screenshots/%Y-%m-%d-%T-screenshot.jpg",NULL};



//static const char *play[] = {}

/* tagging */
static const char *tags[] = {  "???", "???", "???", "???", "???", "???", "???", "???", "???" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
//I am changing resizehints to 0. 1 = default
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_rin_blue2, "-nf", col_white, "-sb", col_rin_blue1, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,				XK_l,      spawn,          {.v = lockcmd} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = powermenu } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,              XK_p,      spawn,          {.v = playback } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	/*For audio controls*/
 	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
 	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
 	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	/*For brightness gui*/
	{0,						   XF86XK_MonBrightnessUp, spawn, {.v = upbrightness} },
	{0,						   XF86XK_MonBrightnessDown, spawn, {.v = downbrightness} },
	{0,						   XK_Print,				 spawn,{.v = screenshot}},
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

