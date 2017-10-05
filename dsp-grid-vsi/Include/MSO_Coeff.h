/* =========================================================================
 ***
 *** The MIT License (MIT)
 ***
 *** Copyright (c) 2016 uGrid
 ***
 *** Permission is hereby granted, free of charge, to any person obtaining a copy
 *** of this software and associated documentation files (the "Software"), to deal
 *** in the Software without restriction, including without limitation the rights
 *** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *** copies of the Software, and to permit persons to whom the Software is
 *** furnished to do so, subject to the following conditions:
 ***
 *** The above copyright notice and this permission notice shall be included in all
 *** copies or substantial portions of the Software.
 ***
 *** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *** SOFTWARE.
 ***
  ========================================================================= */
//--------------------------------------------------------/		
//Coeficientes para controlador PR1 		
//--------------------------------------------------------/		
#define	A1_PR1	0.0229667253339798
#define	A2_PR1	0.0911097850208762
#define	B0_PR1	0.0188620730175746
#define	B1_PR1	1.20717267312477
#define	B2_PR1	0
#define	DELTA_PR1	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador PR5 		
//--------------------------------------------------------/		
#define	A1_PR5	0.0912503504290498
#define	A2_PR5	2.27652930855947
#define	B0_PR5	0.00942600447026641
#define	B1_PR5	0.60326428609705
#define	B2_PR5	0
#define	DELTA_PR5	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador PR7 		
//--------------------------------------------------------/		
#define	A1_PR7	0.159461147347812
#define	A2_PR7	4.45961796407312
#define	B0_PR7	0.00942097779868657
#define	B1_PR7	0.602942579115941
#define	B2_PR7	0
#define	DELTA_PR7	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador PR11 		
//--------------------------------------------------------/		
#define	A1_PR11	0.363657732313122
#define	A2_PR11	10.9949359528556
#define	B0_PR11	0.00940592989986832
#define	B1_PR11	0.601979513591572
#define	B2_PR11	0
#define	DELTA_PR11	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador PR13 		
//--------------------------------------------------------/		
#define	A1_PR13	0.499426776400078
#define	A2_PR13	15.3402283890247
#define	B0_PR13	0.00939592464518485
#define	B1_PR13	0.601339177291831
#define	B2_PR13	0
#define	DELTA_PR13	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador PI 		
//--------------------------------------------------------/		
#define	B0_PIVAC	0.494342121729423
#define	B1_PIVAC	-0.305657878270577
#define	MAX_PIVAC	1000
#define	MIN_PIVAC	-1000
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Circuito de Sincronismo PLL		
//--------------------------------------------------------/		
#define	B0_PLL	61.8034088702226
#define	B1_PLL	-61.7218092663225
#define	CI_PLL	376.991118430775
#define	TS_PLL	2.5025025025025e-005
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa genérico com fc= 1Hz 		
//--------------------------------------------------------/		
#define	A1_LPF1	-0.999842775491196
#define	B0_LPF1	7.86122544021242e-005
#define	B1_LPF1	7.86122544021242e-005
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa fc=60Hz		
//--------------------------------------------------------/		
#define	A1_LPF20	-1.9779832934146
#define	A2_LPF20	0.978227821217107
#define	B0_LPF20	6.1131950626502e-005
#define	B1_LPF20	0.000122263901253004
#define	B2_LPF20	6.1131950626502e-005
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa faixa para impedância virtual		
//--------------------------------------------------------/		
#define	A1_PRS_ZV	0.203466955018357
#define	A2_PRS_ZV	0.0908527343842707
#define	B0_PRS_ZV	0.664562006447463
#define	B1_PRS_ZV	0
#define	B2_PRS_ZV	0
#define	DELTA_PRS_ZV	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa para medição de potências P e Q		
//--------------------------------------------------------/		
#define	A1_LPF1PQ	-0.99937125024709
#define	B0_LPF1PQ	0.0003143748764552
#define	B1_LPF1PQ	0.0003143748764552
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Controlador PI para Droop em P		
//--------------------------------------------------------/		
#define	B0_PI_PDROOP	0.00033333464364058
#define	B1_PI_PDROOP	-0.000333332023026087
#define	MAX_PI_PDROOP	6.28318530717959
#define	MIN_PI_PDROOP	-6.28318530717959
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para filtro passa baixa de ordem 1 para referências de tensão		
//--------------------------------------------------------/		
#define	A1_LPF_VREF	-0.984398965933017
#define	B0_LPF_VREF	0.00780051703349143
#define	B1_LPF_VREF	0.00780051703349143
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador 1P1Z		
//--------------------------------------------------------/		
#define	A1_CVAC	-0.984398965933017
#define	B0_CVAC	0.138222533464108
#define	B1_CVAC	-0.0602173631291937
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa genérico com fc= 1Hz 		
//--------------------------------------------------------/		
#define	A1_LPF1	-0.999842775491196
#define	B0_LPF1	7.86122544021242e-005
#define	B1_LPF1	7.86122544021242e-005
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa genérico com fc= 10Hz 		
//--------------------------------------------------------/		
#define	A1_LPF10	-0.998428866505072
#define	B0_LPF10	0.000785566747464228
#define	B1_LPF10	0.000785566747464228
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa genérico com fc= 100Hz 		
//--------------------------------------------------------/		
#define	A1_LPF100	-0.984398965933017
#define	B0_LPF100	0.00780051703349143
#define	B1_LPF100	0.00780051703349143
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Controlador de Corrente Proporcional + BRF		
//--------------------------------------------------------/		
#define	A1_P_BRF	18.9683844047793
#define	A2_P_BRF	352.680911198
#define	B0_P_BRF	3.50330587938488
#define	B1_P_BRF	44.08511389975
#define	B2_P_BRF	1410.723644792
#define	DELTA_P_BRF	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador PI 		
//--------------------------------------------------------/		
#define	B0_PIAC	2.15723686954904
#define	B1_PIAC	-1.84276313045096
#define	MAX_PIAC	1000
#define	MIN_PIAC	-1000
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Coeficientes para controlador PR1 		
//--------------------------------------------------------/		
#define	A1_PR1i	0.103314987885945
#define	A2_PR1i	0.090995360944703
#define	B0_PR1i	3.06279461428526
#define	B1_PR1i	4.32880027791475
#define	B2_PR1i	0.27298608283354
#define	DELTA_PR1i	0.03125
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa genérico segunda ordem com fc= 1 Hz 		
//--------------------------------------------------------/		
#define	A1_LPF2_1	-1.99977986788958
#define	A2_LPF2_1	0.99977989261029
#define	B0_LPF2_1	6.18017802190475e-009
#define	B1_LPF2_1	1.23603560438095e-008
#define	B2_LPF2_1	6.18017802190475e-009
//--------------------------------------------------------/		
		
//--------------------------------------------------------/		
//Filtro passa baixa genérico segunda ordem com fc= 10 Hz 		
//--------------------------------------------------------/		
#define	A1_LPF2_10	-1.99779863579295
#define	A2_LPF2_10	0.997801105416524
#define	B0_LPF2_10	6.17405894239342e-007
#define	B1_LPF2_10	1.23481178847868e-006
#define	B2_LPF2_10	6.17405894239342e-007
//--------------------------------------------------------/		
		
