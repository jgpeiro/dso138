/*
 * imgui_layout.h
 *
 *  Created on: Apr 27, 2020
 *      Author: jose
 */

#ifndef IMGUI_IMGUI_LAYOUT_H_
#define IMGUI_IMGUI_LAYOUT_H_

#include "imgui.h"

#define WIDGETS_MAX 72+2

extern tWidget widgets[ WIDGETS_MAX ];
/*
0 TOGGLE #149#;#150#
1 COMBOBOX Auto;Normal;Single
2 TOGGLE #040#
3 TOGGLE #041#
4 TOGGLE #126#
5 TOGGLE #160#
6 TOGGLE #048#
7 TOGGLE #068#
8 STATUSBAR 10mV
9 STATUSBAR 1mS
10 STATUSBAR Status1
11 STATUSBAR Status2
12 WINDOW #040#Horizontal
13 LABEL Position
14 SLIDER #120#
15 BUTTON Auto
16 LABEL #040#Scale
17 COMBOBOX 1 uS;2 uS;5 uS;10 uS;20 uS;50 uS;100 uS;200 uS;500 uS;1 mS;2 mS;5 mS;10 mS;20 mS;50 mS;100 mS;200 mS;500 mS
18 WINDOW #041#Vertical
19 LABEL Position
20 SLIDER #119#
21 BUTTON #198#
22 BUTTON #123#
23 BUTTON Ref
24 BUTTON FFT
25 LABEL #041#Scale
26 COMBOBOX 1 mV;2 mV; 5 mV;10 mV;20 mV;50 mV;100 mV;200 mV;500 mV;1 V;2 V;5 V
27 WINDOW #126#Trigger
28 BUTTON Menu
29 LABEL Level
30 SLIDER #118#
31 BUTTON Force
32 WINDOW #160#Measure
33 BUTTON Vmax
34 BUTTON Vmin
35 BUTTON Vavg
36 BUTTON Freq
37 BUTTON Duty
38 LABEL 0.0mV
39 LABEL 0.0mV
40 LABEL 0.0mV
41 LABEL 0.0mV
42 LABEL 0.0mV
43 WINDOW #048#Cursors
44 LABEL Position
45 SLIDER #76#
46 TOGGLE Mode
47 LABEL x1
48 LABEL x2
49 LABEL dx
50 LABEL y1
51 LABEL y2
52 LABEL dy
53 LABEL
54 LABEL
55 LABEL
56 LABEL
57 LABEL
58 LABEL
59 WINDOW #068#Navigation
60 LABEL Multi
61 SLIDER #076#
62 BUTTON #052#
63 BUTTON #042#
64 BUTTON Measure
65 BUTTON Left
66 BUTTON Set/Clear
67 BUTTON Right
68 LABEL Cursors
69 CHECKBOX
70 LABEL Fine
71 CHECKBOX

72 BUTTON Vamp
73 LABEL 0.0mV
 */

#endif /* IMGUI_IMGUI_LAYOUT_H_ */
