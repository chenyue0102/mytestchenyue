#include "il2cpp-config.h"

#ifndef _MSC_VER
# include <alloca.h>
#else
# include <malloc.h>
#endif


#include <cstring>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <assert.h>
#include <stdint.h>

#include "codegen/il2cpp-codegen.h"
#include "il2cpp-object-internals.h"

struct VirtActionInvoker0
{
	typedef void (*Action)(void*, const RuntimeMethod*);

	static inline void Invoke (Il2CppMethodSlot slot, RuntimeObject* obj)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_virtual_invoke_data(slot, obj);
		((Action)invokeData.methodPtr)(obj, invokeData.method);
	}
};
template <typename T1>
struct VirtActionInvoker1
{
	typedef void (*Action)(void*, T1, const RuntimeMethod*);

	static inline void Invoke (Il2CppMethodSlot slot, RuntimeObject* obj, T1 p1)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_virtual_invoke_data(slot, obj);
		((Action)invokeData.methodPtr)(obj, p1, invokeData.method);
	}
};
template <typename T1, typename T2, typename T3, typename T4>
struct VirtActionInvoker4
{
	typedef void (*Action)(void*, T1, T2, T3, T4, const RuntimeMethod*);

	static inline void Invoke (Il2CppMethodSlot slot, RuntimeObject* obj, T1 p1, T2 p2, T3 p3, T4 p4)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_virtual_invoke_data(slot, obj);
		((Action)invokeData.methodPtr)(obj, p1, p2, p3, p4, invokeData.method);
	}
};
struct GenericVirtActionInvoker0
{
	typedef void (*Action)(void*, const RuntimeMethod*);

	static inline void Invoke (const RuntimeMethod* method, RuntimeObject* obj)
	{
		VirtualInvokeData invokeData;
		il2cpp_codegen_get_generic_virtual_invoke_data(method, obj, &invokeData);
		((Action)invokeData.methodPtr)(obj, invokeData.method);
	}
};
template <typename T1>
struct GenericVirtActionInvoker1
{
	typedef void (*Action)(void*, T1, const RuntimeMethod*);

	static inline void Invoke (const RuntimeMethod* method, RuntimeObject* obj, T1 p1)
	{
		VirtualInvokeData invokeData;
		il2cpp_codegen_get_generic_virtual_invoke_data(method, obj, &invokeData);
		((Action)invokeData.methodPtr)(obj, p1, invokeData.method);
	}
};
template <typename T1>
struct InterfaceActionInvoker1
{
	typedef void (*Action)(void*, T1, const RuntimeMethod*);

	static inline void Invoke (Il2CppMethodSlot slot, RuntimeClass* declaringInterface, RuntimeObject* obj, T1 p1)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_interface_invoke_data(slot, obj, declaringInterface);
		((Action)invokeData.methodPtr)(obj, p1, invokeData.method);
	}
};
struct InterfaceActionInvoker0
{
	typedef void (*Action)(void*, const RuntimeMethod*);

	static inline void Invoke (Il2CppMethodSlot slot, RuntimeClass* declaringInterface, RuntimeObject* obj)
	{
		const VirtualInvokeData& invokeData = il2cpp_codegen_get_interface_invoke_data(slot, obj, declaringInterface);
		((Action)invokeData.methodPtr)(obj, invokeData.method);
	}
};
struct GenericInterfaceActionInvoker0
{
	typedef void (*Action)(void*, const RuntimeMethod*);

	static inline void Invoke (const RuntimeMethod* method, RuntimeObject* obj)
	{
		VirtualInvokeData invokeData;
		il2cpp_codegen_get_generic_interface_invoke_data(method, obj, &invokeData);
		((Action)invokeData.methodPtr)(obj, invokeData.method);
	}
};
template <typename T1>
struct GenericInterfaceActionInvoker1
{
	typedef void (*Action)(void*, T1, const RuntimeMethod*);

	static inline void Invoke (const RuntimeMethod* method, RuntimeObject* obj, T1 p1)
	{
		VirtualInvokeData invokeData;
		il2cpp_codegen_get_generic_interface_invoke_data(method, obj, &invokeData);
		((Action)invokeData.methodPtr)(obj, p1, invokeData.method);
	}
};

// AttachState
struct AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF;
// BaldPirate
struct BaldPirate_tFDAA12DAAC29E182FB9209202DB889303C1D9C6E;
// BigGuy
struct BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8;
// Bomb
struct Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2;
// Bomb/ExplotionNotify
struct ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C;
// Captain
struct Captain_t1F5D011033A017D26E7A27822CC00CC4059C7F61;
// Cucumber
struct Cucumber_t6A12FD6C9556AB3D9546BEAE41ADC29CFD9E7046;
// Door
struct Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1;
// DynamicJoystick
struct DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3;
// Enemy
struct Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6;
// Enemy/<OnAlaram>d__32
struct U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D;
// EnemyBaseState
struct EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79;
// Enemy[]
struct EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7;
// FixedJoystick
struct FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909;
// FloatingJoystick
struct FloatingJoystick_tBA7C79E5FC21EE9F117E0583A6A5FD38EFF5F8FE;
// GameManager
struct GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89;
// HitPoint
struct HitPoint_tF69A6E412F64826CB64FF60F3547291915F7E775;
// IDamageable
struct IDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD;
// Joystick
struct Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153;
// JoystickPlayerExample
struct JoystickPlayerExample_tC21BF4F29E220888E49AD1C28ED50EA82E0C583B;
// JoystickSetterExample
struct JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435;
// JumpFX
struct JumpFX_t077C76BEDFE7B2C69067FB2FA0A32FFC1BE03902;
// LandFX
struct LandFX_t0B2698938110490929788E8E0F39A5EE7F7287D5;
// PatrolState
struct PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302;
// PickUpState
struct PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B;
// PlayerAnimation
struct PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD;
// PlayerController
struct PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85;
// System.AsyncCallback
struct AsyncCallback_t3F3DA3BEDAEE81DD1D24125DF8EB30E85EE14DA4;
// System.Char[]
struct CharU5BU5D_t4CC6ABF0AD71BEC97E3C2F1E9C5677E46D3A75C2;
// System.Collections.Generic.List`1<Enemy>
struct List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A;
// System.Collections.Generic.List`1<System.Object>
struct List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D;
// System.Collections.Generic.List`1<UnityEngine.CanvasGroup>
struct List_1_t053DAB6E2110E276A0339D73497193F464BC1F82;
// System.Collections.Generic.List`1<UnityEngine.GameObject>
struct List_1_t3D4152882C54B77C712688E910390D5C8E030463;
// System.Collections.Generic.List`1<UnityEngine.Transform>
struct List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE;
// System.Collections.Generic.List`1<UnityEngine.UI.Image>
struct List_1_tB46CB6C7789F514A8BE08EB5A4F3D9D26AE5E4DA;
// System.Collections.IDictionary
struct IDictionary_t1BD5C1546718A374EA8122FBD6C6EE45331E8CE7;
// System.Collections.IEnumerator
struct IEnumerator_t8789118187258CC88B77AFAC6315B5AF87D3E18A;
// System.Delegate
struct Delegate_t;
// System.DelegateData
struct DelegateData_t1BF9F691B56DAE5F8C28C5E084FDE94F15F27BBE;
// System.Delegate[]
struct DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86;
// System.Diagnostics.StackTrace[]
struct StackTraceU5BU5D_t855F09649EA34DEE7C1B6F088E0538E3CCC3F196;
// System.IAsyncResult
struct IAsyncResult_t8E194308510B375B42432981AE5E7488C458D598;
// System.IntPtr[]
struct IntPtrU5BU5D_t4DC01DCB9A6DF6C9792A6513595D7A11E637DCDD;
// System.NotSupportedException
struct NotSupportedException_tE75B318D6590A02A5D9B29FD97409B1750FA0010;
// System.Object[]
struct ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A;
// System.Reflection.MethodInfo
struct MethodInfo_t;
// System.Runtime.Serialization.SafeSerializationManager
struct SafeSerializationManager_t4A754D86B0F784B18CBC36C073BA564BED109770;
// System.String
struct String_t;
// System.Void
struct Void_t22962CB4C05B1D89B55A6E1139F0E87A90987017;
// UIManager
struct UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C;
// UnityEngine.AnimationClip
struct AnimationClip_t336CFC94F6275526DC0B9BEEF833D4D89D6DEDDE;
// UnityEngine.Animator
struct Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A;
// UnityEngine.AnimatorClipInfo[]
struct AnimatorClipInfoU5BU5D_tCAC39F9AE6CEE1EA08285D9D5C44DB3ADD6C1ED6;
// UnityEngine.Behaviour
struct Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8;
// UnityEngine.BoxCollider2D
struct BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87;
// UnityEngine.Camera
struct Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34;
// UnityEngine.Camera/CameraCallback
struct CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0;
// UnityEngine.Canvas
struct Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591;
// UnityEngine.Canvas/WillRenderCanvases
struct WillRenderCanvases_tBD5AD090B5938021DEAA679A5AEEA790F60A8BEE;
// UnityEngine.CanvasRenderer
struct CanvasRenderer_tB4D9C9FE77FD5C9C4546FC022D6E956960BC2B72;
// UnityEngine.Collider2D
struct Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379;
// UnityEngine.Collider2D[]
struct Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE;
// UnityEngine.Component
struct Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621;
// UnityEngine.Coroutine
struct Coroutine_tAE7DB2FC70A0AE6477F896F852057CB0754F06EC;
// UnityEngine.EventSystems.BaseRaycaster
struct BaseRaycaster_tC7F6105A89F54A38FBFC2659901855FDBB0E3966;
// UnityEngine.EventSystems.EventSystem
struct EventSystem_t06ACEF1C8D95D44D3A7F57ED4BAA577101B4EA77;
// UnityEngine.EventSystems.PointerEventData
struct PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63;
// UnityEngine.Events.UnityAction
struct UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4;
// UnityEngine.GameObject
struct GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F;
// UnityEngine.Material
struct Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598;
// UnityEngine.Mesh
struct Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C;
// UnityEngine.MonoBehaviour
struct MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429;
// UnityEngine.Object
struct Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0;
// UnityEngine.RectTransform
struct RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20;
// UnityEngine.RectTransform/ReapplyDrivenProperties
struct ReapplyDrivenProperties_t431F4FBD9C59AE097FE33C4354CC6251B01B527D;
// UnityEngine.Renderer
struct Renderer_t0556D67DD582620D1F495627EDE30D03284151F4;
// UnityEngine.Rigidbody
struct Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5;
// UnityEngine.Rigidbody2D
struct Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE;
// UnityEngine.Sprite
struct Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198;
// UnityEngine.SpriteRenderer
struct SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F;
// UnityEngine.Sprite[]
struct SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7;
// UnityEngine.TextGenerator
struct TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8;
// UnityEngine.Texture2D
struct Texture2D_tBBF96AC337723E2EF156DF17E09D4379FD05DE1C;
// UnityEngine.Transform
struct Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA;
// UnityEngine.Transform[]
struct TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804;
// UnityEngine.UI.AnimationTriggers
struct AnimationTriggers_t164EF8B310E294B7D0F6BF1A87376731EBD06DC5;
// UnityEngine.UI.CoroutineTween.TweenRunner`1<UnityEngine.UI.CoroutineTween.ColorTween>
struct TweenRunner_1_t56CEB168ADE3739A1BDDBF258FDC759DF8927172;
// UnityEngine.UI.FontData
struct FontData_t29F4568F4FB8C463AAFE6DD21FA7A812B4FF1494;
// UnityEngine.UI.Graphic
struct Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8;
// UnityEngine.UI.Image
struct Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E;
// UnityEngine.UI.MaskableGraphic/CullStateChangedEvent
struct CullStateChangedEvent_t6BC3E87DBC04B585798460D55F56B86C23B62FE4;
// UnityEngine.UI.RectMask2D
struct RectMask2D_tF2CF19F2A4FE2D2FFC7E6F7809374757CA2F377B;
// UnityEngine.UI.Selectable
struct Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A;
// UnityEngine.UI.Selectable[]
struct SelectableU5BU5D_t98F7C5A863B20CD5DBE49CE288038BA954C83F02;
// UnityEngine.UI.Slider
struct Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09;
// UnityEngine.UI.Slider/SliderEvent
struct SliderEvent_t64A824F56F80FC8E2F233F0A0FB0821702DF416C;
// UnityEngine.UI.Text
struct Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030;
// UnityEngine.UI.VertexHelper
struct VertexHelper_t27373EA2CF0F5810EC8CF873D0A6D6C0B23DAC3F;
// UnityEngine.UIVertex[]
struct UIVertexU5BU5D_tB560F9F9269864891FCE1677971F603A08AA857A;
// UnityEngine.Vector2[]
struct Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6;
// UnityEngine.Vector3[]
struct Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28;
// UnityEngine.WaitForSeconds
struct WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8;
// VariableJoystick
struct VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1;
// Whale
struct Whale_t11A3C3495AC360DE58A5FE06BAAA3384761EA301;

IL2CPP_EXTERN_C RuntimeClass* AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Debug_t7B5FCB117E2FD63B6838BC52821B252E2BFB61C4_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* IDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* NotSupportedException_tE75B318D6590A02A5D9B29FD97409B1750FA0010_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Physics2D_tB21970F986016656D66D2922594F336E1EE7D5C7_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* RectTransformUtility_t9B90669A72B05A33DD88BEBB817BC9CDBB614BBA_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C RuntimeClass* WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8_il2cpp_TypeInfo_var;
IL2CPP_EXTERN_C String_t* _stringLiteral1B81F28B5AFBFCAAF5253D26B7DBA4028A92A860;
IL2CPP_EXTERN_C String_t* _stringLiteral1EBA140FDD9C6860A1730C408E3064AA417CA2A3;
IL2CPP_EXTERN_C String_t* _stringLiteral23A6C6DEBC5A87766313E2F1563C2CA4C4FB4E6C;
IL2CPP_EXTERN_C String_t* _stringLiteral271E9A568C0E9E562431CCB1F5DA3422162DE7B8;
IL2CPP_EXTERN_C String_t* _stringLiteral34B33E00B199D35FF4CDA21DF27122784573256B;
IL2CPP_EXTERN_C String_t* _stringLiteral3F0B67BCB7ECF77640A7DD122D98182E7BC9ADD4;
IL2CPP_EXTERN_C String_t* _stringLiteral5EB965DD8C804A3A2833AC61FE1D1F6B1960735A;
IL2CPP_EXTERN_C String_t* _stringLiteral92B6320812D86ABE48E76FBFBBE8BDE7170BF036;
IL2CPP_EXTERN_C String_t* _stringLiteral9713091C5752573EEED6D3557DDE0F3E1C0451D9;
IL2CPP_EXTERN_C String_t* _stringLiteralA25632F8F4FF9659997A848C2EBEEF27D0974164;
IL2CPP_EXTERN_C String_t* _stringLiteralA6D81694B1FEA544CFA7910FBC7133AC5E140813;
IL2CPP_EXTERN_C String_t* _stringLiteralAA4A5F8125F234182E2DEA92805AFDFB747A86BE;
IL2CPP_EXTERN_C String_t* _stringLiteralAD9EDCF2B05FBB1E0B62FCD911EC901DEECF9843;
IL2CPP_EXTERN_C String_t* _stringLiteralB294858A96AAF5BD4F57C1ABF5EB3A23D5C5390C;
IL2CPP_EXTERN_C String_t* _stringLiteralB8C11F366B0D4FEA18776C4D87C022E46BB29C77;
IL2CPP_EXTERN_C String_t* _stringLiteralBD85366453B6F73432017F1B07C44AC7605B218E;
IL2CPP_EXTERN_C String_t* _stringLiteralBE51B119CB46BF201B86E3CA8FAF61471F8CBEB9;
IL2CPP_EXTERN_C String_t* _stringLiteralCC1EBDD04E76A4B8BAFFB29A22FA00446D382B18;
IL2CPP_EXTERN_C String_t* _stringLiteralCD12AF96FA5C9A02893BDC7E05D1255A23036407;
IL2CPP_EXTERN_C String_t* _stringLiteralCF9B77061F7B3126B49D50A6FA68F7CA8C26B7A3;
IL2CPP_EXTERN_C String_t* _stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808;
IL2CPP_EXTERN_C String_t* _stringLiteralD7D390BD9EBAC6BFA0B17AB10695FE73916EBCC2;
IL2CPP_EXTERN_C String_t* _stringLiteralE53407CFE1A5156B9F0D1EED3BAB5EF3AE75CFD8;
IL2CPP_EXTERN_C String_t* _stringLiteralEA490AAA629A0704301CF91E7A4910B910278662;
IL2CPP_EXTERN_C String_t* _stringLiteralEC9F630C8693BDEC93FF52A93E822AC67FF55503;
IL2CPP_EXTERN_C String_t* _stringLiteralF0CD420723AAE840116C8EF7DB5CAF1E0DFF2AEF;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponentInParent_TisCanvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591_mD91B8112B5688783ACAEA46BB2C82C6EC4C4B33B_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisBoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87_mD4BABFD1DC7C524ACC853125D82D011DC1CC5E5B_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisCollider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379_m2AF5C85C582A45B02A4E940C7E8B19A065A37405_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_m503EAA28F55B66971C880C00538F81DCCB8C1629_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisRectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20_mEF939F54B6B56187EC11E16F51DCB12EB62C2103_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Component_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mCC209A7A6A8D6878F0CB813ED5722A59C2262693_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* GameObject_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_m9904EA7E80165F7771F8AB3967F417D7C2B09996_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* GameObject_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mDDB82F02C3053DCC0D60C420752A11EC11CBACC0_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* GameObject_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mD25CEAAA219FA1235F8E88F914D2F8AC57303538_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_Add_m6ED0FB3ABA16A3A8AF0D48619D15B4B947333F5B_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_Add_mEB0CDED8A9ADCC0F235881A5D34D41085EC4780C_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_Contains_m37CE7FF0E6F1024460701CAC16B6657BEBB8BF1B_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_Remove_m8E1311599BA3E940469F201FE770645882E0783A_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_Remove_m947F635E58C7D238ADF2ACCB2C0EAE33670197C6_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1__ctor_m0046B0A356552D7B951C2CEEE5F1375DAF72054A_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1__ctor_m4DBD7BFCF2ABB429466D1A3CA5ECA1D15C1FEEC6_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_get_Count_m2EA40FDD7BE2FB22B8227B533BAA8D316CC4BE3E_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Object_FindObjectOfType_TisDoor_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1_m693E2656B1274ACB963744178B6A9C91B0D289D4_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Object_FindObjectOfType_TisFixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909_m15640DCFA39A3D28A6190EB0A4D8775B029FC5E8_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Object_FindObjectOfType_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_mBC133F50DBE6E9017FBA685EC7B283C09AE9EB61_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* Object_Instantiate_TisGameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F_m4F397BCC6697902B40033E61129D4EA6FE93570F_RuntimeMethod_var;
IL2CPP_EXTERN_C const RuntimeMethod* U3COnAlaramU3Ed__32_System_Collections_IEnumerator_Reset_m482AEADD8285A780061F6543287BD9C92C6576C0_RuntimeMethod_var;
IL2CPP_EXTERN_C const uint32_t AttachState_OnEnterState_m90BCF2B9BE847C4CF96035372DEF4D2570E8DB6D_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t AttachState_OnUpdate_m5F611E55C81227D824A540AE30D67ECBCDB386F0_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t BigGuy_PickUp_m0FB6B02B80A702737E98AD4723BADC8A14181833_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t BigGuy_Throw_m478A03D4B917C8DA808702AAF018276617C08E83_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t BigGuy_Update_mB6D9727BBA85AD81BF96DB93A0CBAF209024D71D_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t BigGuy__ctor_mE427A5EC79B196B00D13DEA279CDE8DF25854E77_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Bomb_DestroyThis_m1F33C8D0E1DD2A906F83DA8B718B91FA3026B3EC_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Bomb_Explotion_m16ABDF7E7E4F5FFE24353FB4E31385A2B56111EC_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Bomb_SetExplotionNotify_m72EA3979F8FF5C949EFC9AC1B15E752AA4349768_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Bomb_Start_m4FA5C4D6B068CCC485980698EFD6C46A0FF7BD3E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Bomb_TurnOff_mAF8955158FE03383BD5C734628B71CCA19ABE778_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Bomb_TurnOn_m2581D46C074B7BBE84864715A3960531E943D466_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Bomb_Update_m10BDA079BD63F54E823DD971093D902436199792_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Captain_Init_m279514E43671147A816DB46395961F7F5CB81AB0_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Captain_SkillAttack_mB9C66D63254DE157CE78F97C0186BE2FED20BBCB_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Cucumber_SetOff_m29170B94935D177B7E458DF9CE8476E1075C7D49_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Door_OnTriggerEnter2D_m650AD506F66F579681729162E1696ED800F7C609_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Door_OpenDoor_mD650E2A85F5958F335166BA83EA91EB3923F992E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Door_Start_m1ED335570A6A1CD834EA36D60B936A530BF00154_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t DynamicJoystick_HandleInput_mB6316E3D97C617061C01DC49DD829C0C4E91BB27_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t DynamicJoystick_set_MoveThreshold_m41DF6070CB77AD666C343C6FCD04F2D013FF7171_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_Attack_mD7E35AB2C1AE961F3625A6DFD081E932CEA461D7_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_FilpDirection_m25112DA9C4BB354136EF9E35420C69AE0C19B054_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_GetHit_mDB9FE12807AABA2F5977FC320DA0AF2F692AB8C0_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_Init_m33CE279B856CE404151706EBC893C8604099927E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_MoveToTarget_mCDF98A78E7279630FBE34E9183ACAE017D025132_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_OnAlaram_mA62FEB896193F9E36363BD9E98DA1F0F9CA510FA_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_OnTriggerEnter2D_mB5D8A9A3E7CFA603912813FE5D11B43F5F83634E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_OnTriggerExit2D_m263722EF78331D173E6EED57784FD2F48C2BF37E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_OnTriggerStay2D_m098504D6D16E60A6509C4B859814A66F9FFD9F8E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_SkillAttack_m4E4DA6E8B23FB444ED5D8F3EF20F8BF818AA766E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_Start_m0681B66D4522F045EB7A33A21467994960D1E435_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_SwitchPoint_mEB5076531D4C2544BD715A31A29A7355F19EDE11_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy_Update_mE957FE3BFB8CBB7C30E43D4A81C13E02B1C1FC32_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager_Awake_mE60F41F3186E80B2BAB293918745366D18508C0F_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager_GameOver_m658E745BE197CC36CFAE422F8037F41A1B7FFFD3_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager_LoadHealth_mC037637C61400A7CFE7D50A9751533B40070B43A_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager_SaveData_mCA8C4D89F3C20776CAA9E31AA4AF2193A518048E_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager__cctor_m050E3CF18ED59B480951819A6C68DEA9C0EB1D45_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager__ctor_mF7F1107D38DE91EB8A57C1C3BB1A932C50CD9693_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager_addEnemy_mA2B4C6231982E68641C4B0BBF19B0B1B5E2A726A_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t GameManager_removeEnemy_m08DDE78A0B9872B6C07147887AA03E8A2FB6F56D_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t HitPoint_OnTriggerEnter2D_m32B1A41DAD0B3117F608137BF807B8F996EC6A46_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t JoystickPlayerExample_FixedUpdate_m01D558819D864B0B36B12AECB92B7A9FE76D63B3_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t JoystickSetterExample_Update_m27F40165A6AE141735CD9680F90F53599D2CFFC2_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_HandleInput_mA2FF5AE57290471865DC02DC2ED3BDA3FDBA2506_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_OnDrag_m5C8DBE5110822CAF8A7DEDDE6AC240D2C1BDD7C4_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_OnPointerUp_m771F7519F51F02DAADA7DE0A562F82710FA721BC_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_ScreenPointToAnchoredPosition_mE4C429E76D0FA78FD1567EB1361AF68141706201_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_SnapFloat_mCEF2520CAC111659A65B73C418F5E6FF1CFF05C2_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_Start_mA4B921AF2FEC7B830AC4F0D5E49AF8934ECAD201_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_set_DeadZone_mF8F4688B5A32363F2EF7DE0A0FF90B7D65F11C8B_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Joystick_set_HandleRange_m93B28B83AB3DC010C509C16A76BE34896C27B647_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PatrolState_OnUpdate_mA50004332BBE077481208FBCD08CDD752CF5E6F4_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PickUpState_OnUpdate_m9BF02BCE6E486D29D1FD23DF826FB6DFA42D7264_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerAnimation_Start_mA10B085DFC8D13CEC6453122FECBB665F460557D_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerAnimation_Update_mB996F7F54E3FED0EF71D0D584DB4965103650724_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_Attack_m763538E8539EF73BF10B02AC22C9882C8F8006F2_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_CheckInput_mAC03BF1E0CD4690383608EFCB41FFBD962F86FDF_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_FixedUpdate_m914EA3E3CCE4DF6AEB2E78317FFC1D507DACEBDE_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_GetHit_m430DA9E36AD2C9CAE846AA22C840B3ECAEEC2493_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_Jump_m3056E2DF0CD8445804DCDAB6521E81541F0218A1_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_KickBomb_m57A89383EE50DA2C527DC6BDA51F79A80AA0E2C5_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_OnTriggerEnter2D_m4BFC3BB96B7F16C5F0E6A7BE6795149716478A74_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_OnTriggerExit2D_m8E5A01B8FA14061A9E824E3B4AA6E702BC32A870_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_PhysicsCheck_mF0842B47CA0495F34DE0891387C9AB27614396D5_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_Start_mC0C9B9461D0BDAC48EC43715818A4BA63C4F45EF_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController__ctor_m648E40092E37395F4307411E855445886113CD60_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t PlayerController_landFX_mAD14E42C2F9C123BA802624DB9DFD14A5FD1F3F1_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t U3COnAlaramU3Ed__32_MoveNext_m989CD7423B94BF5F2D3CD7FF4A2E2C5CD34284B2_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t U3COnAlaramU3Ed__32_System_Collections_IEnumerator_Reset_m482AEADD8285A780061F6543287BD9C92C6576C0_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t UIManager_Awake_mA946658D43E2FC2C3479BB9322CED4FF4C5D2EA0_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t VariableJoystick_HandleInput_m83CA8AFC5C395DE4C684F2C478D1DE36CAD0BF19_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t VariableJoystick__ctor_m8A6171BB962558D6833C6CF80E3E0092DF768D84_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t VariableJoystick_set_MoveThreshold_m70CF65250847566A28B2A418C3EE55004987552F_MetadataUsageId;
IL2CPP_EXTERN_C const uint32_t Whale_Swalow_m11F219ABC08F833B8DF7CD739847C202D4ECF96E_MetadataUsageId;
struct Delegate_t_marshaled_com;
struct Delegate_t_marshaled_pinvoke;
struct Exception_t_marshaled_com;
struct Exception_t_marshaled_pinvoke;

struct DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86;
struct ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A;
struct AnimatorClipInfoU5BU5D_tCAC39F9AE6CEE1EA08285D9D5C44DB3ADD6C1ED6;
struct Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE;
struct SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7;

IL2CPP_EXTERN_C_BEGIN
IL2CPP_EXTERN_C_END

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

// <Module>
struct  U3CModuleU3E_t6CDDDF959E7E18A6744E43B613F41CDAC780256A 
{
public:

public:
};


// System.Object


// Enemy_<OnAlaram>d__32
struct  U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D  : public RuntimeObject
{
public:
	// System.Int32 Enemy_<OnAlaram>d__32::<>1__state
	int32_t ___U3CU3E1__state_0;
	// System.Object Enemy_<OnAlaram>d__32::<>2__current
	RuntimeObject * ___U3CU3E2__current_1;
	// Enemy Enemy_<OnAlaram>d__32::<>4__this
	Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___U3CU3E4__this_2;

public:
	inline static int32_t get_offset_of_U3CU3E1__state_0() { return static_cast<int32_t>(offsetof(U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D, ___U3CU3E1__state_0)); }
	inline int32_t get_U3CU3E1__state_0() const { return ___U3CU3E1__state_0; }
	inline int32_t* get_address_of_U3CU3E1__state_0() { return &___U3CU3E1__state_0; }
	inline void set_U3CU3E1__state_0(int32_t value)
	{
		___U3CU3E1__state_0 = value;
	}

	inline static int32_t get_offset_of_U3CU3E2__current_1() { return static_cast<int32_t>(offsetof(U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D, ___U3CU3E2__current_1)); }
	inline RuntimeObject * get_U3CU3E2__current_1() const { return ___U3CU3E2__current_1; }
	inline RuntimeObject ** get_address_of_U3CU3E2__current_1() { return &___U3CU3E2__current_1; }
	inline void set_U3CU3E2__current_1(RuntimeObject * value)
	{
		___U3CU3E2__current_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___U3CU3E2__current_1), (void*)value);
	}

	inline static int32_t get_offset_of_U3CU3E4__this_2() { return static_cast<int32_t>(offsetof(U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D, ___U3CU3E4__this_2)); }
	inline Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * get_U3CU3E4__this_2() const { return ___U3CU3E4__this_2; }
	inline Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 ** get_address_of_U3CU3E4__this_2() { return &___U3CU3E4__this_2; }
	inline void set_U3CU3E4__this_2(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * value)
	{
		___U3CU3E4__this_2 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___U3CU3E4__this_2), (void*)value);
	}
};


// EnemyBaseState
struct  EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79  : public RuntimeObject
{
public:

public:
};

struct Il2CppArrayBounds;

// System.Array


// System.Collections.Generic.List`1<Enemy>
struct  List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A  : public RuntimeObject
{
public:
	// T[] System.Collections.Generic.List`1::_items
	EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7* ____items_1;
	// System.Int32 System.Collections.Generic.List`1::_size
	int32_t ____size_2;
	// System.Int32 System.Collections.Generic.List`1::_version
	int32_t ____version_3;
	// System.Object System.Collections.Generic.List`1::_syncRoot
	RuntimeObject * ____syncRoot_4;

public:
	inline static int32_t get_offset_of__items_1() { return static_cast<int32_t>(offsetof(List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A, ____items_1)); }
	inline EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7* get__items_1() const { return ____items_1; }
	inline EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7** get_address_of__items_1() { return &____items_1; }
	inline void set__items_1(EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7* value)
	{
		____items_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____items_1), (void*)value);
	}

	inline static int32_t get_offset_of__size_2() { return static_cast<int32_t>(offsetof(List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A, ____size_2)); }
	inline int32_t get__size_2() const { return ____size_2; }
	inline int32_t* get_address_of__size_2() { return &____size_2; }
	inline void set__size_2(int32_t value)
	{
		____size_2 = value;
	}

	inline static int32_t get_offset_of__version_3() { return static_cast<int32_t>(offsetof(List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A, ____version_3)); }
	inline int32_t get__version_3() const { return ____version_3; }
	inline int32_t* get_address_of__version_3() { return &____version_3; }
	inline void set__version_3(int32_t value)
	{
		____version_3 = value;
	}

	inline static int32_t get_offset_of__syncRoot_4() { return static_cast<int32_t>(offsetof(List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A, ____syncRoot_4)); }
	inline RuntimeObject * get__syncRoot_4() const { return ____syncRoot_4; }
	inline RuntimeObject ** get_address_of__syncRoot_4() { return &____syncRoot_4; }
	inline void set__syncRoot_4(RuntimeObject * value)
	{
		____syncRoot_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____syncRoot_4), (void*)value);
	}
};

struct List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A_StaticFields
{
public:
	// T[] System.Collections.Generic.List`1::_emptyArray
	EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7* ____emptyArray_5;

public:
	inline static int32_t get_offset_of__emptyArray_5() { return static_cast<int32_t>(offsetof(List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A_StaticFields, ____emptyArray_5)); }
	inline EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7* get__emptyArray_5() const { return ____emptyArray_5; }
	inline EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7** get_address_of__emptyArray_5() { return &____emptyArray_5; }
	inline void set__emptyArray_5(EnemyU5BU5D_t062459143EC5B464AA6ACC259C3344E81A2858F7* value)
	{
		____emptyArray_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____emptyArray_5), (void*)value);
	}
};


// System.Collections.Generic.List`1<System.Object>
struct  List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D  : public RuntimeObject
{
public:
	// T[] System.Collections.Generic.List`1::_items
	ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A* ____items_1;
	// System.Int32 System.Collections.Generic.List`1::_size
	int32_t ____size_2;
	// System.Int32 System.Collections.Generic.List`1::_version
	int32_t ____version_3;
	// System.Object System.Collections.Generic.List`1::_syncRoot
	RuntimeObject * ____syncRoot_4;

public:
	inline static int32_t get_offset_of__items_1() { return static_cast<int32_t>(offsetof(List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D, ____items_1)); }
	inline ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A* get__items_1() const { return ____items_1; }
	inline ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A** get_address_of__items_1() { return &____items_1; }
	inline void set__items_1(ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A* value)
	{
		____items_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____items_1), (void*)value);
	}

	inline static int32_t get_offset_of__size_2() { return static_cast<int32_t>(offsetof(List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D, ____size_2)); }
	inline int32_t get__size_2() const { return ____size_2; }
	inline int32_t* get_address_of__size_2() { return &____size_2; }
	inline void set__size_2(int32_t value)
	{
		____size_2 = value;
	}

	inline static int32_t get_offset_of__version_3() { return static_cast<int32_t>(offsetof(List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D, ____version_3)); }
	inline int32_t get__version_3() const { return ____version_3; }
	inline int32_t* get_address_of__version_3() { return &____version_3; }
	inline void set__version_3(int32_t value)
	{
		____version_3 = value;
	}

	inline static int32_t get_offset_of__syncRoot_4() { return static_cast<int32_t>(offsetof(List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D, ____syncRoot_4)); }
	inline RuntimeObject * get__syncRoot_4() const { return ____syncRoot_4; }
	inline RuntimeObject ** get_address_of__syncRoot_4() { return &____syncRoot_4; }
	inline void set__syncRoot_4(RuntimeObject * value)
	{
		____syncRoot_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____syncRoot_4), (void*)value);
	}
};

struct List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D_StaticFields
{
public:
	// T[] System.Collections.Generic.List`1::_emptyArray
	ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A* ____emptyArray_5;

public:
	inline static int32_t get_offset_of__emptyArray_5() { return static_cast<int32_t>(offsetof(List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D_StaticFields, ____emptyArray_5)); }
	inline ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A* get__emptyArray_5() const { return ____emptyArray_5; }
	inline ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A** get_address_of__emptyArray_5() { return &____emptyArray_5; }
	inline void set__emptyArray_5(ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A* value)
	{
		____emptyArray_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____emptyArray_5), (void*)value);
	}
};


// System.Collections.Generic.List`1<UnityEngine.Transform>
struct  List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE  : public RuntimeObject
{
public:
	// T[] System.Collections.Generic.List`1::_items
	TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804* ____items_1;
	// System.Int32 System.Collections.Generic.List`1::_size
	int32_t ____size_2;
	// System.Int32 System.Collections.Generic.List`1::_version
	int32_t ____version_3;
	// System.Object System.Collections.Generic.List`1::_syncRoot
	RuntimeObject * ____syncRoot_4;

public:
	inline static int32_t get_offset_of__items_1() { return static_cast<int32_t>(offsetof(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE, ____items_1)); }
	inline TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804* get__items_1() const { return ____items_1; }
	inline TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804** get_address_of__items_1() { return &____items_1; }
	inline void set__items_1(TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804* value)
	{
		____items_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____items_1), (void*)value);
	}

	inline static int32_t get_offset_of__size_2() { return static_cast<int32_t>(offsetof(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE, ____size_2)); }
	inline int32_t get__size_2() const { return ____size_2; }
	inline int32_t* get_address_of__size_2() { return &____size_2; }
	inline void set__size_2(int32_t value)
	{
		____size_2 = value;
	}

	inline static int32_t get_offset_of__version_3() { return static_cast<int32_t>(offsetof(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE, ____version_3)); }
	inline int32_t get__version_3() const { return ____version_3; }
	inline int32_t* get_address_of__version_3() { return &____version_3; }
	inline void set__version_3(int32_t value)
	{
		____version_3 = value;
	}

	inline static int32_t get_offset_of__syncRoot_4() { return static_cast<int32_t>(offsetof(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE, ____syncRoot_4)); }
	inline RuntimeObject * get__syncRoot_4() const { return ____syncRoot_4; }
	inline RuntimeObject ** get_address_of__syncRoot_4() { return &____syncRoot_4; }
	inline void set__syncRoot_4(RuntimeObject * value)
	{
		____syncRoot_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____syncRoot_4), (void*)value);
	}
};

struct List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE_StaticFields
{
public:
	// T[] System.Collections.Generic.List`1::_emptyArray
	TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804* ____emptyArray_5;

public:
	inline static int32_t get_offset_of__emptyArray_5() { return static_cast<int32_t>(offsetof(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE_StaticFields, ____emptyArray_5)); }
	inline TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804* get__emptyArray_5() const { return ____emptyArray_5; }
	inline TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804** get_address_of__emptyArray_5() { return &____emptyArray_5; }
	inline void set__emptyArray_5(TransformU5BU5D_t4F5A1132877D8BA66ABC0A9A7FADA4E0237A7804* value)
	{
		____emptyArray_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____emptyArray_5), (void*)value);
	}
};


// System.String
struct  String_t  : public RuntimeObject
{
public:
	// System.Int32 System.String::m_stringLength
	int32_t ___m_stringLength_0;
	// System.Char System.String::m_firstChar
	Il2CppChar ___m_firstChar_1;

public:
	inline static int32_t get_offset_of_m_stringLength_0() { return static_cast<int32_t>(offsetof(String_t, ___m_stringLength_0)); }
	inline int32_t get_m_stringLength_0() const { return ___m_stringLength_0; }
	inline int32_t* get_address_of_m_stringLength_0() { return &___m_stringLength_0; }
	inline void set_m_stringLength_0(int32_t value)
	{
		___m_stringLength_0 = value;
	}

	inline static int32_t get_offset_of_m_firstChar_1() { return static_cast<int32_t>(offsetof(String_t, ___m_firstChar_1)); }
	inline Il2CppChar get_m_firstChar_1() const { return ___m_firstChar_1; }
	inline Il2CppChar* get_address_of_m_firstChar_1() { return &___m_firstChar_1; }
	inline void set_m_firstChar_1(Il2CppChar value)
	{
		___m_firstChar_1 = value;
	}
};

struct String_t_StaticFields
{
public:
	// System.String System.String::Empty
	String_t* ___Empty_5;

public:
	inline static int32_t get_offset_of_Empty_5() { return static_cast<int32_t>(offsetof(String_t_StaticFields, ___Empty_5)); }
	inline String_t* get_Empty_5() const { return ___Empty_5; }
	inline String_t** get_address_of_Empty_5() { return &___Empty_5; }
	inline void set_Empty_5(String_t* value)
	{
		___Empty_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___Empty_5), (void*)value);
	}
};


// System.ValueType
struct  ValueType_t4D0C27076F7C36E76190FB3328E232BCB1CD1FFF  : public RuntimeObject
{
public:

public:
};

// Native definition for P/Invoke marshalling of System.ValueType
struct ValueType_t4D0C27076F7C36E76190FB3328E232BCB1CD1FFF_marshaled_pinvoke
{
};
// Native definition for COM marshalling of System.ValueType
struct ValueType_t4D0C27076F7C36E76190FB3328E232BCB1CD1FFF_marshaled_com
{
};

// UnityEngine.EventSystems.AbstractEventData
struct  AbstractEventData_t636F385820C291DAE25897BCEB4FBCADDA3B75F6  : public RuntimeObject
{
public:
	// System.Boolean UnityEngine.EventSystems.AbstractEventData::m_Used
	bool ___m_Used_0;

public:
	inline static int32_t get_offset_of_m_Used_0() { return static_cast<int32_t>(offsetof(AbstractEventData_t636F385820C291DAE25897BCEB4FBCADDA3B75F6, ___m_Used_0)); }
	inline bool get_m_Used_0() const { return ___m_Used_0; }
	inline bool* get_address_of_m_Used_0() { return &___m_Used_0; }
	inline void set_m_Used_0(bool value)
	{
		___m_Used_0 = value;
	}
};


// UnityEngine.YieldInstruction
struct  YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44  : public RuntimeObject
{
public:

public:
};

// Native definition for P/Invoke marshalling of UnityEngine.YieldInstruction
struct YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44_marshaled_pinvoke
{
};
// Native definition for COM marshalling of UnityEngine.YieldInstruction
struct YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44_marshaled_com
{
};

// AttachState
struct  AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF  : public EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79
{
public:

public:
};


// PatrolState
struct  PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302  : public EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79
{
public:

public:
};


// PickUpState
struct  PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B  : public EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79
{
public:

public:
};


// System.Boolean
struct  Boolean_tB53F6830F670160873277339AA58F15CAED4399C 
{
public:
	// System.Boolean System.Boolean::m_value
	bool ___m_value_0;

public:
	inline static int32_t get_offset_of_m_value_0() { return static_cast<int32_t>(offsetof(Boolean_tB53F6830F670160873277339AA58F15CAED4399C, ___m_value_0)); }
	inline bool get_m_value_0() const { return ___m_value_0; }
	inline bool* get_address_of_m_value_0() { return &___m_value_0; }
	inline void set_m_value_0(bool value)
	{
		___m_value_0 = value;
	}
};

struct Boolean_tB53F6830F670160873277339AA58F15CAED4399C_StaticFields
{
public:
	// System.String System.Boolean::TrueString
	String_t* ___TrueString_5;
	// System.String System.Boolean::FalseString
	String_t* ___FalseString_6;

public:
	inline static int32_t get_offset_of_TrueString_5() { return static_cast<int32_t>(offsetof(Boolean_tB53F6830F670160873277339AA58F15CAED4399C_StaticFields, ___TrueString_5)); }
	inline String_t* get_TrueString_5() const { return ___TrueString_5; }
	inline String_t** get_address_of_TrueString_5() { return &___TrueString_5; }
	inline void set_TrueString_5(String_t* value)
	{
		___TrueString_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___TrueString_5), (void*)value);
	}

	inline static int32_t get_offset_of_FalseString_6() { return static_cast<int32_t>(offsetof(Boolean_tB53F6830F670160873277339AA58F15CAED4399C_StaticFields, ___FalseString_6)); }
	inline String_t* get_FalseString_6() const { return ___FalseString_6; }
	inline String_t** get_address_of_FalseString_6() { return &___FalseString_6; }
	inline void set_FalseString_6(String_t* value)
	{
		___FalseString_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___FalseString_6), (void*)value);
	}
};


// System.Enum
struct  Enum_t2AF27C02B8653AE29442467390005ABC74D8F521  : public ValueType_t4D0C27076F7C36E76190FB3328E232BCB1CD1FFF
{
public:

public:
};

struct Enum_t2AF27C02B8653AE29442467390005ABC74D8F521_StaticFields
{
public:
	// System.Char[] System.Enum::enumSeperatorCharArray
	CharU5BU5D_t4CC6ABF0AD71BEC97E3C2F1E9C5677E46D3A75C2* ___enumSeperatorCharArray_0;

public:
	inline static int32_t get_offset_of_enumSeperatorCharArray_0() { return static_cast<int32_t>(offsetof(Enum_t2AF27C02B8653AE29442467390005ABC74D8F521_StaticFields, ___enumSeperatorCharArray_0)); }
	inline CharU5BU5D_t4CC6ABF0AD71BEC97E3C2F1E9C5677E46D3A75C2* get_enumSeperatorCharArray_0() const { return ___enumSeperatorCharArray_0; }
	inline CharU5BU5D_t4CC6ABF0AD71BEC97E3C2F1E9C5677E46D3A75C2** get_address_of_enumSeperatorCharArray_0() { return &___enumSeperatorCharArray_0; }
	inline void set_enumSeperatorCharArray_0(CharU5BU5D_t4CC6ABF0AD71BEC97E3C2F1E9C5677E46D3A75C2* value)
	{
		___enumSeperatorCharArray_0 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___enumSeperatorCharArray_0), (void*)value);
	}
};

// Native definition for P/Invoke marshalling of System.Enum
struct Enum_t2AF27C02B8653AE29442467390005ABC74D8F521_marshaled_pinvoke
{
};
// Native definition for COM marshalling of System.Enum
struct Enum_t2AF27C02B8653AE29442467390005ABC74D8F521_marshaled_com
{
};

// System.Int32
struct  Int32_t585191389E07734F19F3156FF88FB3EF4800D102 
{
public:
	// System.Int32 System.Int32::m_value
	int32_t ___m_value_0;

public:
	inline static int32_t get_offset_of_m_value_0() { return static_cast<int32_t>(offsetof(Int32_t585191389E07734F19F3156FF88FB3EF4800D102, ___m_value_0)); }
	inline int32_t get_m_value_0() const { return ___m_value_0; }
	inline int32_t* get_address_of_m_value_0() { return &___m_value_0; }
	inline void set_m_value_0(int32_t value)
	{
		___m_value_0 = value;
	}
};


// System.IntPtr
struct  IntPtr_t 
{
public:
	// System.Void* System.IntPtr::m_value
	void* ___m_value_0;

public:
	inline static int32_t get_offset_of_m_value_0() { return static_cast<int32_t>(offsetof(IntPtr_t, ___m_value_0)); }
	inline void* get_m_value_0() const { return ___m_value_0; }
	inline void** get_address_of_m_value_0() { return &___m_value_0; }
	inline void set_m_value_0(void* value)
	{
		___m_value_0 = value;
	}
};

struct IntPtr_t_StaticFields
{
public:
	// System.IntPtr System.IntPtr::Zero
	intptr_t ___Zero_1;

public:
	inline static int32_t get_offset_of_Zero_1() { return static_cast<int32_t>(offsetof(IntPtr_t_StaticFields, ___Zero_1)); }
	inline intptr_t get_Zero_1() const { return ___Zero_1; }
	inline intptr_t* get_address_of_Zero_1() { return &___Zero_1; }
	inline void set_Zero_1(intptr_t value)
	{
		___Zero_1 = value;
	}
};


// System.Single
struct  Single_tDDDA9169C4E4E308AC6D7A824F9B28DC82204AE1 
{
public:
	// System.Single System.Single::m_value
	float ___m_value_0;

public:
	inline static int32_t get_offset_of_m_value_0() { return static_cast<int32_t>(offsetof(Single_tDDDA9169C4E4E308AC6D7A824F9B28DC82204AE1, ___m_value_0)); }
	inline float get_m_value_0() const { return ___m_value_0; }
	inline float* get_address_of_m_value_0() { return &___m_value_0; }
	inline void set_m_value_0(float value)
	{
		___m_value_0 = value;
	}
};


// System.Void
struct  Void_t22962CB4C05B1D89B55A6E1139F0E87A90987017 
{
public:
	union
	{
		struct
		{
		};
		uint8_t Void_t22962CB4C05B1D89B55A6E1139F0E87A90987017__padding[1];
	};

public:
};


// UnityEngine.AnimatorClipInfo
struct  AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180 
{
public:
	// System.Int32 UnityEngine.AnimatorClipInfo::m_ClipInstanceID
	int32_t ___m_ClipInstanceID_0;
	// System.Single UnityEngine.AnimatorClipInfo::m_Weight
	float ___m_Weight_1;

public:
	inline static int32_t get_offset_of_m_ClipInstanceID_0() { return static_cast<int32_t>(offsetof(AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180, ___m_ClipInstanceID_0)); }
	inline int32_t get_m_ClipInstanceID_0() const { return ___m_ClipInstanceID_0; }
	inline int32_t* get_address_of_m_ClipInstanceID_0() { return &___m_ClipInstanceID_0; }
	inline void set_m_ClipInstanceID_0(int32_t value)
	{
		___m_ClipInstanceID_0 = value;
	}

	inline static int32_t get_offset_of_m_Weight_1() { return static_cast<int32_t>(offsetof(AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180, ___m_Weight_1)); }
	inline float get_m_Weight_1() const { return ___m_Weight_1; }
	inline float* get_address_of_m_Weight_1() { return &___m_Weight_1; }
	inline void set_m_Weight_1(float value)
	{
		___m_Weight_1 = value;
	}
};


// UnityEngine.AnimatorStateInfo
struct  AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 
{
public:
	// System.Int32 UnityEngine.AnimatorStateInfo::m_Name
	int32_t ___m_Name_0;
	// System.Int32 UnityEngine.AnimatorStateInfo::m_Path
	int32_t ___m_Path_1;
	// System.Int32 UnityEngine.AnimatorStateInfo::m_FullPath
	int32_t ___m_FullPath_2;
	// System.Single UnityEngine.AnimatorStateInfo::m_NormalizedTime
	float ___m_NormalizedTime_3;
	// System.Single UnityEngine.AnimatorStateInfo::m_Length
	float ___m_Length_4;
	// System.Single UnityEngine.AnimatorStateInfo::m_Speed
	float ___m_Speed_5;
	// System.Single UnityEngine.AnimatorStateInfo::m_SpeedMultiplier
	float ___m_SpeedMultiplier_6;
	// System.Int32 UnityEngine.AnimatorStateInfo::m_Tag
	int32_t ___m_Tag_7;
	// System.Int32 UnityEngine.AnimatorStateInfo::m_Loop
	int32_t ___m_Loop_8;

public:
	inline static int32_t get_offset_of_m_Name_0() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_Name_0)); }
	inline int32_t get_m_Name_0() const { return ___m_Name_0; }
	inline int32_t* get_address_of_m_Name_0() { return &___m_Name_0; }
	inline void set_m_Name_0(int32_t value)
	{
		___m_Name_0 = value;
	}

	inline static int32_t get_offset_of_m_Path_1() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_Path_1)); }
	inline int32_t get_m_Path_1() const { return ___m_Path_1; }
	inline int32_t* get_address_of_m_Path_1() { return &___m_Path_1; }
	inline void set_m_Path_1(int32_t value)
	{
		___m_Path_1 = value;
	}

	inline static int32_t get_offset_of_m_FullPath_2() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_FullPath_2)); }
	inline int32_t get_m_FullPath_2() const { return ___m_FullPath_2; }
	inline int32_t* get_address_of_m_FullPath_2() { return &___m_FullPath_2; }
	inline void set_m_FullPath_2(int32_t value)
	{
		___m_FullPath_2 = value;
	}

	inline static int32_t get_offset_of_m_NormalizedTime_3() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_NormalizedTime_3)); }
	inline float get_m_NormalizedTime_3() const { return ___m_NormalizedTime_3; }
	inline float* get_address_of_m_NormalizedTime_3() { return &___m_NormalizedTime_3; }
	inline void set_m_NormalizedTime_3(float value)
	{
		___m_NormalizedTime_3 = value;
	}

	inline static int32_t get_offset_of_m_Length_4() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_Length_4)); }
	inline float get_m_Length_4() const { return ___m_Length_4; }
	inline float* get_address_of_m_Length_4() { return &___m_Length_4; }
	inline void set_m_Length_4(float value)
	{
		___m_Length_4 = value;
	}

	inline static int32_t get_offset_of_m_Speed_5() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_Speed_5)); }
	inline float get_m_Speed_5() const { return ___m_Speed_5; }
	inline float* get_address_of_m_Speed_5() { return &___m_Speed_5; }
	inline void set_m_Speed_5(float value)
	{
		___m_Speed_5 = value;
	}

	inline static int32_t get_offset_of_m_SpeedMultiplier_6() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_SpeedMultiplier_6)); }
	inline float get_m_SpeedMultiplier_6() const { return ___m_SpeedMultiplier_6; }
	inline float* get_address_of_m_SpeedMultiplier_6() { return &___m_SpeedMultiplier_6; }
	inline void set_m_SpeedMultiplier_6(float value)
	{
		___m_SpeedMultiplier_6 = value;
	}

	inline static int32_t get_offset_of_m_Tag_7() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_Tag_7)); }
	inline int32_t get_m_Tag_7() const { return ___m_Tag_7; }
	inline int32_t* get_address_of_m_Tag_7() { return &___m_Tag_7; }
	inline void set_m_Tag_7(int32_t value)
	{
		___m_Tag_7 = value;
	}

	inline static int32_t get_offset_of_m_Loop_8() { return static_cast<int32_t>(offsetof(AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2, ___m_Loop_8)); }
	inline int32_t get_m_Loop_8() const { return ___m_Loop_8; }
	inline int32_t* get_address_of_m_Loop_8() { return &___m_Loop_8; }
	inline void set_m_Loop_8(int32_t value)
	{
		___m_Loop_8 = value;
	}
};


// UnityEngine.Color
struct  Color_t119BCA590009762C7223FDD3AF9706653AC84ED2 
{
public:
	// System.Single UnityEngine.Color::r
	float ___r_0;
	// System.Single UnityEngine.Color::g
	float ___g_1;
	// System.Single UnityEngine.Color::b
	float ___b_2;
	// System.Single UnityEngine.Color::a
	float ___a_3;

public:
	inline static int32_t get_offset_of_r_0() { return static_cast<int32_t>(offsetof(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2, ___r_0)); }
	inline float get_r_0() const { return ___r_0; }
	inline float* get_address_of_r_0() { return &___r_0; }
	inline void set_r_0(float value)
	{
		___r_0 = value;
	}

	inline static int32_t get_offset_of_g_1() { return static_cast<int32_t>(offsetof(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2, ___g_1)); }
	inline float get_g_1() const { return ___g_1; }
	inline float* get_address_of_g_1() { return &___g_1; }
	inline void set_g_1(float value)
	{
		___g_1 = value;
	}

	inline static int32_t get_offset_of_b_2() { return static_cast<int32_t>(offsetof(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2, ___b_2)); }
	inline float get_b_2() const { return ___b_2; }
	inline float* get_address_of_b_2() { return &___b_2; }
	inline void set_b_2(float value)
	{
		___b_2 = value;
	}

	inline static int32_t get_offset_of_a_3() { return static_cast<int32_t>(offsetof(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2, ___a_3)); }
	inline float get_a_3() const { return ___a_3; }
	inline float* get_address_of_a_3() { return &___a_3; }
	inline void set_a_3(float value)
	{
		___a_3 = value;
	}
};


// UnityEngine.DrivenRectTransformTracker
struct  DrivenRectTransformTracker_tB8FBBE24EEE9618CA32E4B3CF52F4AD7FDDEBE03 
{
public:
	union
	{
		struct
		{
		};
		uint8_t DrivenRectTransformTracker_tB8FBBE24EEE9618CA32E4B3CF52F4AD7FDDEBE03__padding[1];
	};

public:
};


// UnityEngine.EventSystems.BaseEventData
struct  BaseEventData_t46C9D2AE3183A742EDE89944AF64A23DBF1B80A5  : public AbstractEventData_t636F385820C291DAE25897BCEB4FBCADDA3B75F6
{
public:
	// UnityEngine.EventSystems.EventSystem UnityEngine.EventSystems.BaseEventData::m_EventSystem
	EventSystem_t06ACEF1C8D95D44D3A7F57ED4BAA577101B4EA77 * ___m_EventSystem_1;

public:
	inline static int32_t get_offset_of_m_EventSystem_1() { return static_cast<int32_t>(offsetof(BaseEventData_t46C9D2AE3183A742EDE89944AF64A23DBF1B80A5, ___m_EventSystem_1)); }
	inline EventSystem_t06ACEF1C8D95D44D3A7F57ED4BAA577101B4EA77 * get_m_EventSystem_1() const { return ___m_EventSystem_1; }
	inline EventSystem_t06ACEF1C8D95D44D3A7F57ED4BAA577101B4EA77 ** get_address_of_m_EventSystem_1() { return &___m_EventSystem_1; }
	inline void set_m_EventSystem_1(EventSystem_t06ACEF1C8D95D44D3A7F57ED4BAA577101B4EA77 * value)
	{
		___m_EventSystem_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_EventSystem_1), (void*)value);
	}
};


// UnityEngine.LayerMask
struct  LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0 
{
public:
	// System.Int32 UnityEngine.LayerMask::m_Mask
	int32_t ___m_Mask_0;

public:
	inline static int32_t get_offset_of_m_Mask_0() { return static_cast<int32_t>(offsetof(LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0, ___m_Mask_0)); }
	inline int32_t get_m_Mask_0() const { return ___m_Mask_0; }
	inline int32_t* get_address_of_m_Mask_0() { return &___m_Mask_0; }
	inline void set_m_Mask_0(int32_t value)
	{
		___m_Mask_0 = value;
	}
};


// UnityEngine.Quaternion
struct  Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357 
{
public:
	// System.Single UnityEngine.Quaternion::x
	float ___x_0;
	// System.Single UnityEngine.Quaternion::y
	float ___y_1;
	// System.Single UnityEngine.Quaternion::z
	float ___z_2;
	// System.Single UnityEngine.Quaternion::w
	float ___w_3;

public:
	inline static int32_t get_offset_of_x_0() { return static_cast<int32_t>(offsetof(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357, ___x_0)); }
	inline float get_x_0() const { return ___x_0; }
	inline float* get_address_of_x_0() { return &___x_0; }
	inline void set_x_0(float value)
	{
		___x_0 = value;
	}

	inline static int32_t get_offset_of_y_1() { return static_cast<int32_t>(offsetof(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357, ___y_1)); }
	inline float get_y_1() const { return ___y_1; }
	inline float* get_address_of_y_1() { return &___y_1; }
	inline void set_y_1(float value)
	{
		___y_1 = value;
	}

	inline static int32_t get_offset_of_z_2() { return static_cast<int32_t>(offsetof(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357, ___z_2)); }
	inline float get_z_2() const { return ___z_2; }
	inline float* get_address_of_z_2() { return &___z_2; }
	inline void set_z_2(float value)
	{
		___z_2 = value;
	}

	inline static int32_t get_offset_of_w_3() { return static_cast<int32_t>(offsetof(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357, ___w_3)); }
	inline float get_w_3() const { return ___w_3; }
	inline float* get_address_of_w_3() { return &___w_3; }
	inline void set_w_3(float value)
	{
		___w_3 = value;
	}
};

struct Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357_StaticFields
{
public:
	// UnityEngine.Quaternion UnityEngine.Quaternion::identityQuaternion
	Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  ___identityQuaternion_4;

public:
	inline static int32_t get_offset_of_identityQuaternion_4() { return static_cast<int32_t>(offsetof(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357_StaticFields, ___identityQuaternion_4)); }
	inline Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  get_identityQuaternion_4() const { return ___identityQuaternion_4; }
	inline Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357 * get_address_of_identityQuaternion_4() { return &___identityQuaternion_4; }
	inline void set_identityQuaternion_4(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  value)
	{
		___identityQuaternion_4 = value;
	}
};


// UnityEngine.SceneManagement.Scene
struct  Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2 
{
public:
	// System.Int32 UnityEngine.SceneManagement.Scene::m_Handle
	int32_t ___m_Handle_0;

public:
	inline static int32_t get_offset_of_m_Handle_0() { return static_cast<int32_t>(offsetof(Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2, ___m_Handle_0)); }
	inline int32_t get_m_Handle_0() const { return ___m_Handle_0; }
	inline int32_t* get_address_of_m_Handle_0() { return &___m_Handle_0; }
	inline void set_m_Handle_0(int32_t value)
	{
		___m_Handle_0 = value;
	}
};


// UnityEngine.UI.SpriteState
struct  SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A 
{
public:
	// UnityEngine.Sprite UnityEngine.UI.SpriteState::m_HighlightedSprite
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_HighlightedSprite_0;
	// UnityEngine.Sprite UnityEngine.UI.SpriteState::m_PressedSprite
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_PressedSprite_1;
	// UnityEngine.Sprite UnityEngine.UI.SpriteState::m_SelectedSprite
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_SelectedSprite_2;
	// UnityEngine.Sprite UnityEngine.UI.SpriteState::m_DisabledSprite
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_DisabledSprite_3;

public:
	inline static int32_t get_offset_of_m_HighlightedSprite_0() { return static_cast<int32_t>(offsetof(SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A, ___m_HighlightedSprite_0)); }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * get_m_HighlightedSprite_0() const { return ___m_HighlightedSprite_0; }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** get_address_of_m_HighlightedSprite_0() { return &___m_HighlightedSprite_0; }
	inline void set_m_HighlightedSprite_0(Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		___m_HighlightedSprite_0 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_HighlightedSprite_0), (void*)value);
	}

	inline static int32_t get_offset_of_m_PressedSprite_1() { return static_cast<int32_t>(offsetof(SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A, ___m_PressedSprite_1)); }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * get_m_PressedSprite_1() const { return ___m_PressedSprite_1; }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** get_address_of_m_PressedSprite_1() { return &___m_PressedSprite_1; }
	inline void set_m_PressedSprite_1(Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		___m_PressedSprite_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_PressedSprite_1), (void*)value);
	}

	inline static int32_t get_offset_of_m_SelectedSprite_2() { return static_cast<int32_t>(offsetof(SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A, ___m_SelectedSprite_2)); }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * get_m_SelectedSprite_2() const { return ___m_SelectedSprite_2; }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** get_address_of_m_SelectedSprite_2() { return &___m_SelectedSprite_2; }
	inline void set_m_SelectedSprite_2(Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		___m_SelectedSprite_2 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_SelectedSprite_2), (void*)value);
	}

	inline static int32_t get_offset_of_m_DisabledSprite_3() { return static_cast<int32_t>(offsetof(SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A, ___m_DisabledSprite_3)); }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * get_m_DisabledSprite_3() const { return ___m_DisabledSprite_3; }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** get_address_of_m_DisabledSprite_3() { return &___m_DisabledSprite_3; }
	inline void set_m_DisabledSprite_3(Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		___m_DisabledSprite_3 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_DisabledSprite_3), (void*)value);
	}
};

// Native definition for P/Invoke marshalling of UnityEngine.UI.SpriteState
struct SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A_marshaled_pinvoke
{
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_HighlightedSprite_0;
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_PressedSprite_1;
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_SelectedSprite_2;
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_DisabledSprite_3;
};
// Native definition for COM marshalling of UnityEngine.UI.SpriteState
struct SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A_marshaled_com
{
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_HighlightedSprite_0;
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_PressedSprite_1;
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_SelectedSprite_2;
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_DisabledSprite_3;
};

// UnityEngine.Vector2
struct  Vector2_tA85D2DD88578276CA8A8796756458277E72D073D 
{
public:
	// System.Single UnityEngine.Vector2::x
	float ___x_0;
	// System.Single UnityEngine.Vector2::y
	float ___y_1;

public:
	inline static int32_t get_offset_of_x_0() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D, ___x_0)); }
	inline float get_x_0() const { return ___x_0; }
	inline float* get_address_of_x_0() { return &___x_0; }
	inline void set_x_0(float value)
	{
		___x_0 = value;
	}

	inline static int32_t get_offset_of_y_1() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D, ___y_1)); }
	inline float get_y_1() const { return ___y_1; }
	inline float* get_address_of_y_1() { return &___y_1; }
	inline void set_y_1(float value)
	{
		___y_1 = value;
	}
};

struct Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields
{
public:
	// UnityEngine.Vector2 UnityEngine.Vector2::zeroVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___zeroVector_2;
	// UnityEngine.Vector2 UnityEngine.Vector2::oneVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___oneVector_3;
	// UnityEngine.Vector2 UnityEngine.Vector2::upVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___upVector_4;
	// UnityEngine.Vector2 UnityEngine.Vector2::downVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___downVector_5;
	// UnityEngine.Vector2 UnityEngine.Vector2::leftVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___leftVector_6;
	// UnityEngine.Vector2 UnityEngine.Vector2::rightVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___rightVector_7;
	// UnityEngine.Vector2 UnityEngine.Vector2::positiveInfinityVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___positiveInfinityVector_8;
	// UnityEngine.Vector2 UnityEngine.Vector2::negativeInfinityVector
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___negativeInfinityVector_9;

public:
	inline static int32_t get_offset_of_zeroVector_2() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___zeroVector_2)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_zeroVector_2() const { return ___zeroVector_2; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_zeroVector_2() { return &___zeroVector_2; }
	inline void set_zeroVector_2(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___zeroVector_2 = value;
	}

	inline static int32_t get_offset_of_oneVector_3() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___oneVector_3)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_oneVector_3() const { return ___oneVector_3; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_oneVector_3() { return &___oneVector_3; }
	inline void set_oneVector_3(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___oneVector_3 = value;
	}

	inline static int32_t get_offset_of_upVector_4() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___upVector_4)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_upVector_4() const { return ___upVector_4; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_upVector_4() { return &___upVector_4; }
	inline void set_upVector_4(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___upVector_4 = value;
	}

	inline static int32_t get_offset_of_downVector_5() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___downVector_5)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_downVector_5() const { return ___downVector_5; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_downVector_5() { return &___downVector_5; }
	inline void set_downVector_5(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___downVector_5 = value;
	}

	inline static int32_t get_offset_of_leftVector_6() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___leftVector_6)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_leftVector_6() const { return ___leftVector_6; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_leftVector_6() { return &___leftVector_6; }
	inline void set_leftVector_6(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___leftVector_6 = value;
	}

	inline static int32_t get_offset_of_rightVector_7() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___rightVector_7)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_rightVector_7() const { return ___rightVector_7; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_rightVector_7() { return &___rightVector_7; }
	inline void set_rightVector_7(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___rightVector_7 = value;
	}

	inline static int32_t get_offset_of_positiveInfinityVector_8() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___positiveInfinityVector_8)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_positiveInfinityVector_8() const { return ___positiveInfinityVector_8; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_positiveInfinityVector_8() { return &___positiveInfinityVector_8; }
	inline void set_positiveInfinityVector_8(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___positiveInfinityVector_8 = value;
	}

	inline static int32_t get_offset_of_negativeInfinityVector_9() { return static_cast<int32_t>(offsetof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_StaticFields, ___negativeInfinityVector_9)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_negativeInfinityVector_9() const { return ___negativeInfinityVector_9; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_negativeInfinityVector_9() { return &___negativeInfinityVector_9; }
	inline void set_negativeInfinityVector_9(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___negativeInfinityVector_9 = value;
	}
};


// UnityEngine.Vector3
struct  Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 
{
public:
	// System.Single UnityEngine.Vector3::x
	float ___x_2;
	// System.Single UnityEngine.Vector3::y
	float ___y_3;
	// System.Single UnityEngine.Vector3::z
	float ___z_4;

public:
	inline static int32_t get_offset_of_x_2() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720, ___x_2)); }
	inline float get_x_2() const { return ___x_2; }
	inline float* get_address_of_x_2() { return &___x_2; }
	inline void set_x_2(float value)
	{
		___x_2 = value;
	}

	inline static int32_t get_offset_of_y_3() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720, ___y_3)); }
	inline float get_y_3() const { return ___y_3; }
	inline float* get_address_of_y_3() { return &___y_3; }
	inline void set_y_3(float value)
	{
		___y_3 = value;
	}

	inline static int32_t get_offset_of_z_4() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720, ___z_4)); }
	inline float get_z_4() const { return ___z_4; }
	inline float* get_address_of_z_4() { return &___z_4; }
	inline void set_z_4(float value)
	{
		___z_4 = value;
	}
};

struct Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields
{
public:
	// UnityEngine.Vector3 UnityEngine.Vector3::zeroVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___zeroVector_5;
	// UnityEngine.Vector3 UnityEngine.Vector3::oneVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___oneVector_6;
	// UnityEngine.Vector3 UnityEngine.Vector3::upVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___upVector_7;
	// UnityEngine.Vector3 UnityEngine.Vector3::downVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___downVector_8;
	// UnityEngine.Vector3 UnityEngine.Vector3::leftVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___leftVector_9;
	// UnityEngine.Vector3 UnityEngine.Vector3::rightVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___rightVector_10;
	// UnityEngine.Vector3 UnityEngine.Vector3::forwardVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___forwardVector_11;
	// UnityEngine.Vector3 UnityEngine.Vector3::backVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___backVector_12;
	// UnityEngine.Vector3 UnityEngine.Vector3::positiveInfinityVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___positiveInfinityVector_13;
	// UnityEngine.Vector3 UnityEngine.Vector3::negativeInfinityVector
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___negativeInfinityVector_14;

public:
	inline static int32_t get_offset_of_zeroVector_5() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___zeroVector_5)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_zeroVector_5() const { return ___zeroVector_5; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_zeroVector_5() { return &___zeroVector_5; }
	inline void set_zeroVector_5(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___zeroVector_5 = value;
	}

	inline static int32_t get_offset_of_oneVector_6() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___oneVector_6)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_oneVector_6() const { return ___oneVector_6; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_oneVector_6() { return &___oneVector_6; }
	inline void set_oneVector_6(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___oneVector_6 = value;
	}

	inline static int32_t get_offset_of_upVector_7() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___upVector_7)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_upVector_7() const { return ___upVector_7; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_upVector_7() { return &___upVector_7; }
	inline void set_upVector_7(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___upVector_7 = value;
	}

	inline static int32_t get_offset_of_downVector_8() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___downVector_8)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_downVector_8() const { return ___downVector_8; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_downVector_8() { return &___downVector_8; }
	inline void set_downVector_8(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___downVector_8 = value;
	}

	inline static int32_t get_offset_of_leftVector_9() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___leftVector_9)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_leftVector_9() const { return ___leftVector_9; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_leftVector_9() { return &___leftVector_9; }
	inline void set_leftVector_9(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___leftVector_9 = value;
	}

	inline static int32_t get_offset_of_rightVector_10() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___rightVector_10)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_rightVector_10() const { return ___rightVector_10; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_rightVector_10() { return &___rightVector_10; }
	inline void set_rightVector_10(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___rightVector_10 = value;
	}

	inline static int32_t get_offset_of_forwardVector_11() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___forwardVector_11)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_forwardVector_11() const { return ___forwardVector_11; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_forwardVector_11() { return &___forwardVector_11; }
	inline void set_forwardVector_11(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___forwardVector_11 = value;
	}

	inline static int32_t get_offset_of_backVector_12() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___backVector_12)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_backVector_12() const { return ___backVector_12; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_backVector_12() { return &___backVector_12; }
	inline void set_backVector_12(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___backVector_12 = value;
	}

	inline static int32_t get_offset_of_positiveInfinityVector_13() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___positiveInfinityVector_13)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_positiveInfinityVector_13() const { return ___positiveInfinityVector_13; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_positiveInfinityVector_13() { return &___positiveInfinityVector_13; }
	inline void set_positiveInfinityVector_13(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___positiveInfinityVector_13 = value;
	}

	inline static int32_t get_offset_of_negativeInfinityVector_14() { return static_cast<int32_t>(offsetof(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_StaticFields, ___negativeInfinityVector_14)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_negativeInfinityVector_14() const { return ___negativeInfinityVector_14; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_negativeInfinityVector_14() { return &___negativeInfinityVector_14; }
	inline void set_negativeInfinityVector_14(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___negativeInfinityVector_14 = value;
	}
};


// UnityEngine.WaitForSeconds
struct  WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8  : public YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44
{
public:
	// System.Single UnityEngine.WaitForSeconds::m_Seconds
	float ___m_Seconds_0;

public:
	inline static int32_t get_offset_of_m_Seconds_0() { return static_cast<int32_t>(offsetof(WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8, ___m_Seconds_0)); }
	inline float get_m_Seconds_0() const { return ___m_Seconds_0; }
	inline float* get_address_of_m_Seconds_0() { return &___m_Seconds_0; }
	inline void set_m_Seconds_0(float value)
	{
		___m_Seconds_0 = value;
	}
};

// Native definition for P/Invoke marshalling of UnityEngine.WaitForSeconds
struct WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8_marshaled_pinvoke : public YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44_marshaled_pinvoke
{
	float ___m_Seconds_0;
};
// Native definition for COM marshalling of UnityEngine.WaitForSeconds
struct WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8_marshaled_com : public YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44_marshaled_com
{
	float ___m_Seconds_0;
};

// AxisOptions
struct  AxisOptions_t5AC84B43FFEB20E770F1E4CF5EC2D3AADA9D18D0 
{
public:
	// System.Int32 AxisOptions::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(AxisOptions_t5AC84B43FFEB20E770F1E4CF5EC2D3AADA9D18D0, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// JoystickType
struct  JoystickType_t8F089F639C0CED5CA78941C78E1CC72EB61892B6 
{
public:
	// System.Int32 JoystickType::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(JoystickType_t8F089F639C0CED5CA78941C78E1CC72EB61892B6, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// System.Delegate
struct  Delegate_t  : public RuntimeObject
{
public:
	// System.IntPtr System.Delegate::method_ptr
	Il2CppMethodPointer ___method_ptr_0;
	// System.IntPtr System.Delegate::invoke_impl
	intptr_t ___invoke_impl_1;
	// System.Object System.Delegate::m_target
	RuntimeObject * ___m_target_2;
	// System.IntPtr System.Delegate::method
	intptr_t ___method_3;
	// System.IntPtr System.Delegate::delegate_trampoline
	intptr_t ___delegate_trampoline_4;
	// System.IntPtr System.Delegate::extra_arg
	intptr_t ___extra_arg_5;
	// System.IntPtr System.Delegate::method_code
	intptr_t ___method_code_6;
	// System.Reflection.MethodInfo System.Delegate::method_info
	MethodInfo_t * ___method_info_7;
	// System.Reflection.MethodInfo System.Delegate::original_method_info
	MethodInfo_t * ___original_method_info_8;
	// System.DelegateData System.Delegate::data
	DelegateData_t1BF9F691B56DAE5F8C28C5E084FDE94F15F27BBE * ___data_9;
	// System.Boolean System.Delegate::method_is_virtual
	bool ___method_is_virtual_10;

public:
	inline static int32_t get_offset_of_method_ptr_0() { return static_cast<int32_t>(offsetof(Delegate_t, ___method_ptr_0)); }
	inline Il2CppMethodPointer get_method_ptr_0() const { return ___method_ptr_0; }
	inline Il2CppMethodPointer* get_address_of_method_ptr_0() { return &___method_ptr_0; }
	inline void set_method_ptr_0(Il2CppMethodPointer value)
	{
		___method_ptr_0 = value;
	}

	inline static int32_t get_offset_of_invoke_impl_1() { return static_cast<int32_t>(offsetof(Delegate_t, ___invoke_impl_1)); }
	inline intptr_t get_invoke_impl_1() const { return ___invoke_impl_1; }
	inline intptr_t* get_address_of_invoke_impl_1() { return &___invoke_impl_1; }
	inline void set_invoke_impl_1(intptr_t value)
	{
		___invoke_impl_1 = value;
	}

	inline static int32_t get_offset_of_m_target_2() { return static_cast<int32_t>(offsetof(Delegate_t, ___m_target_2)); }
	inline RuntimeObject * get_m_target_2() const { return ___m_target_2; }
	inline RuntimeObject ** get_address_of_m_target_2() { return &___m_target_2; }
	inline void set_m_target_2(RuntimeObject * value)
	{
		___m_target_2 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_target_2), (void*)value);
	}

	inline static int32_t get_offset_of_method_3() { return static_cast<int32_t>(offsetof(Delegate_t, ___method_3)); }
	inline intptr_t get_method_3() const { return ___method_3; }
	inline intptr_t* get_address_of_method_3() { return &___method_3; }
	inline void set_method_3(intptr_t value)
	{
		___method_3 = value;
	}

	inline static int32_t get_offset_of_delegate_trampoline_4() { return static_cast<int32_t>(offsetof(Delegate_t, ___delegate_trampoline_4)); }
	inline intptr_t get_delegate_trampoline_4() const { return ___delegate_trampoline_4; }
	inline intptr_t* get_address_of_delegate_trampoline_4() { return &___delegate_trampoline_4; }
	inline void set_delegate_trampoline_4(intptr_t value)
	{
		___delegate_trampoline_4 = value;
	}

	inline static int32_t get_offset_of_extra_arg_5() { return static_cast<int32_t>(offsetof(Delegate_t, ___extra_arg_5)); }
	inline intptr_t get_extra_arg_5() const { return ___extra_arg_5; }
	inline intptr_t* get_address_of_extra_arg_5() { return &___extra_arg_5; }
	inline void set_extra_arg_5(intptr_t value)
	{
		___extra_arg_5 = value;
	}

	inline static int32_t get_offset_of_method_code_6() { return static_cast<int32_t>(offsetof(Delegate_t, ___method_code_6)); }
	inline intptr_t get_method_code_6() const { return ___method_code_6; }
	inline intptr_t* get_address_of_method_code_6() { return &___method_code_6; }
	inline void set_method_code_6(intptr_t value)
	{
		___method_code_6 = value;
	}

	inline static int32_t get_offset_of_method_info_7() { return static_cast<int32_t>(offsetof(Delegate_t, ___method_info_7)); }
	inline MethodInfo_t * get_method_info_7() const { return ___method_info_7; }
	inline MethodInfo_t ** get_address_of_method_info_7() { return &___method_info_7; }
	inline void set_method_info_7(MethodInfo_t * value)
	{
		___method_info_7 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___method_info_7), (void*)value);
	}

	inline static int32_t get_offset_of_original_method_info_8() { return static_cast<int32_t>(offsetof(Delegate_t, ___original_method_info_8)); }
	inline MethodInfo_t * get_original_method_info_8() const { return ___original_method_info_8; }
	inline MethodInfo_t ** get_address_of_original_method_info_8() { return &___original_method_info_8; }
	inline void set_original_method_info_8(MethodInfo_t * value)
	{
		___original_method_info_8 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___original_method_info_8), (void*)value);
	}

	inline static int32_t get_offset_of_data_9() { return static_cast<int32_t>(offsetof(Delegate_t, ___data_9)); }
	inline DelegateData_t1BF9F691B56DAE5F8C28C5E084FDE94F15F27BBE * get_data_9() const { return ___data_9; }
	inline DelegateData_t1BF9F691B56DAE5F8C28C5E084FDE94F15F27BBE ** get_address_of_data_9() { return &___data_9; }
	inline void set_data_9(DelegateData_t1BF9F691B56DAE5F8C28C5E084FDE94F15F27BBE * value)
	{
		___data_9 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___data_9), (void*)value);
	}

	inline static int32_t get_offset_of_method_is_virtual_10() { return static_cast<int32_t>(offsetof(Delegate_t, ___method_is_virtual_10)); }
	inline bool get_method_is_virtual_10() const { return ___method_is_virtual_10; }
	inline bool* get_address_of_method_is_virtual_10() { return &___method_is_virtual_10; }
	inline void set_method_is_virtual_10(bool value)
	{
		___method_is_virtual_10 = value;
	}
};

// Native definition for P/Invoke marshalling of System.Delegate
struct Delegate_t_marshaled_pinvoke
{
	intptr_t ___method_ptr_0;
	intptr_t ___invoke_impl_1;
	Il2CppIUnknown* ___m_target_2;
	intptr_t ___method_3;
	intptr_t ___delegate_trampoline_4;
	intptr_t ___extra_arg_5;
	intptr_t ___method_code_6;
	MethodInfo_t * ___method_info_7;
	MethodInfo_t * ___original_method_info_8;
	DelegateData_t1BF9F691B56DAE5F8C28C5E084FDE94F15F27BBE * ___data_9;
	int32_t ___method_is_virtual_10;
};
// Native definition for COM marshalling of System.Delegate
struct Delegate_t_marshaled_com
{
	intptr_t ___method_ptr_0;
	intptr_t ___invoke_impl_1;
	Il2CppIUnknown* ___m_target_2;
	intptr_t ___method_3;
	intptr_t ___delegate_trampoline_4;
	intptr_t ___extra_arg_5;
	intptr_t ___method_code_6;
	MethodInfo_t * ___method_info_7;
	MethodInfo_t * ___original_method_info_8;
	DelegateData_t1BF9F691B56DAE5F8C28C5E084FDE94F15F27BBE * ___data_9;
	int32_t ___method_is_virtual_10;
};

// System.Exception
struct  Exception_t  : public RuntimeObject
{
public:
	// System.String System.Exception::_className
	String_t* ____className_1;
	// System.String System.Exception::_message
	String_t* ____message_2;
	// System.Collections.IDictionary System.Exception::_data
	RuntimeObject* ____data_3;
	// System.Exception System.Exception::_innerException
	Exception_t * ____innerException_4;
	// System.String System.Exception::_helpURL
	String_t* ____helpURL_5;
	// System.Object System.Exception::_stackTrace
	RuntimeObject * ____stackTrace_6;
	// System.String System.Exception::_stackTraceString
	String_t* ____stackTraceString_7;
	// System.String System.Exception::_remoteStackTraceString
	String_t* ____remoteStackTraceString_8;
	// System.Int32 System.Exception::_remoteStackIndex
	int32_t ____remoteStackIndex_9;
	// System.Object System.Exception::_dynamicMethods
	RuntimeObject * ____dynamicMethods_10;
	// System.Int32 System.Exception::_HResult
	int32_t ____HResult_11;
	// System.String System.Exception::_source
	String_t* ____source_12;
	// System.Runtime.Serialization.SafeSerializationManager System.Exception::_safeSerializationManager
	SafeSerializationManager_t4A754D86B0F784B18CBC36C073BA564BED109770 * ____safeSerializationManager_13;
	// System.Diagnostics.StackTrace[] System.Exception::captured_traces
	StackTraceU5BU5D_t855F09649EA34DEE7C1B6F088E0538E3CCC3F196* ___captured_traces_14;
	// System.IntPtr[] System.Exception::native_trace_ips
	IntPtrU5BU5D_t4DC01DCB9A6DF6C9792A6513595D7A11E637DCDD* ___native_trace_ips_15;

public:
	inline static int32_t get_offset_of__className_1() { return static_cast<int32_t>(offsetof(Exception_t, ____className_1)); }
	inline String_t* get__className_1() const { return ____className_1; }
	inline String_t** get_address_of__className_1() { return &____className_1; }
	inline void set__className_1(String_t* value)
	{
		____className_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____className_1), (void*)value);
	}

	inline static int32_t get_offset_of__message_2() { return static_cast<int32_t>(offsetof(Exception_t, ____message_2)); }
	inline String_t* get__message_2() const { return ____message_2; }
	inline String_t** get_address_of__message_2() { return &____message_2; }
	inline void set__message_2(String_t* value)
	{
		____message_2 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____message_2), (void*)value);
	}

	inline static int32_t get_offset_of__data_3() { return static_cast<int32_t>(offsetof(Exception_t, ____data_3)); }
	inline RuntimeObject* get__data_3() const { return ____data_3; }
	inline RuntimeObject** get_address_of__data_3() { return &____data_3; }
	inline void set__data_3(RuntimeObject* value)
	{
		____data_3 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____data_3), (void*)value);
	}

	inline static int32_t get_offset_of__innerException_4() { return static_cast<int32_t>(offsetof(Exception_t, ____innerException_4)); }
	inline Exception_t * get__innerException_4() const { return ____innerException_4; }
	inline Exception_t ** get_address_of__innerException_4() { return &____innerException_4; }
	inline void set__innerException_4(Exception_t * value)
	{
		____innerException_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____innerException_4), (void*)value);
	}

	inline static int32_t get_offset_of__helpURL_5() { return static_cast<int32_t>(offsetof(Exception_t, ____helpURL_5)); }
	inline String_t* get__helpURL_5() const { return ____helpURL_5; }
	inline String_t** get_address_of__helpURL_5() { return &____helpURL_5; }
	inline void set__helpURL_5(String_t* value)
	{
		____helpURL_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____helpURL_5), (void*)value);
	}

	inline static int32_t get_offset_of__stackTrace_6() { return static_cast<int32_t>(offsetof(Exception_t, ____stackTrace_6)); }
	inline RuntimeObject * get__stackTrace_6() const { return ____stackTrace_6; }
	inline RuntimeObject ** get_address_of__stackTrace_6() { return &____stackTrace_6; }
	inline void set__stackTrace_6(RuntimeObject * value)
	{
		____stackTrace_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____stackTrace_6), (void*)value);
	}

	inline static int32_t get_offset_of__stackTraceString_7() { return static_cast<int32_t>(offsetof(Exception_t, ____stackTraceString_7)); }
	inline String_t* get__stackTraceString_7() const { return ____stackTraceString_7; }
	inline String_t** get_address_of__stackTraceString_7() { return &____stackTraceString_7; }
	inline void set__stackTraceString_7(String_t* value)
	{
		____stackTraceString_7 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____stackTraceString_7), (void*)value);
	}

	inline static int32_t get_offset_of__remoteStackTraceString_8() { return static_cast<int32_t>(offsetof(Exception_t, ____remoteStackTraceString_8)); }
	inline String_t* get__remoteStackTraceString_8() const { return ____remoteStackTraceString_8; }
	inline String_t** get_address_of__remoteStackTraceString_8() { return &____remoteStackTraceString_8; }
	inline void set__remoteStackTraceString_8(String_t* value)
	{
		____remoteStackTraceString_8 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____remoteStackTraceString_8), (void*)value);
	}

	inline static int32_t get_offset_of__remoteStackIndex_9() { return static_cast<int32_t>(offsetof(Exception_t, ____remoteStackIndex_9)); }
	inline int32_t get__remoteStackIndex_9() const { return ____remoteStackIndex_9; }
	inline int32_t* get_address_of__remoteStackIndex_9() { return &____remoteStackIndex_9; }
	inline void set__remoteStackIndex_9(int32_t value)
	{
		____remoteStackIndex_9 = value;
	}

	inline static int32_t get_offset_of__dynamicMethods_10() { return static_cast<int32_t>(offsetof(Exception_t, ____dynamicMethods_10)); }
	inline RuntimeObject * get__dynamicMethods_10() const { return ____dynamicMethods_10; }
	inline RuntimeObject ** get_address_of__dynamicMethods_10() { return &____dynamicMethods_10; }
	inline void set__dynamicMethods_10(RuntimeObject * value)
	{
		____dynamicMethods_10 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____dynamicMethods_10), (void*)value);
	}

	inline static int32_t get_offset_of__HResult_11() { return static_cast<int32_t>(offsetof(Exception_t, ____HResult_11)); }
	inline int32_t get__HResult_11() const { return ____HResult_11; }
	inline int32_t* get_address_of__HResult_11() { return &____HResult_11; }
	inline void set__HResult_11(int32_t value)
	{
		____HResult_11 = value;
	}

	inline static int32_t get_offset_of__source_12() { return static_cast<int32_t>(offsetof(Exception_t, ____source_12)); }
	inline String_t* get__source_12() const { return ____source_12; }
	inline String_t** get_address_of__source_12() { return &____source_12; }
	inline void set__source_12(String_t* value)
	{
		____source_12 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____source_12), (void*)value);
	}

	inline static int32_t get_offset_of__safeSerializationManager_13() { return static_cast<int32_t>(offsetof(Exception_t, ____safeSerializationManager_13)); }
	inline SafeSerializationManager_t4A754D86B0F784B18CBC36C073BA564BED109770 * get__safeSerializationManager_13() const { return ____safeSerializationManager_13; }
	inline SafeSerializationManager_t4A754D86B0F784B18CBC36C073BA564BED109770 ** get_address_of__safeSerializationManager_13() { return &____safeSerializationManager_13; }
	inline void set__safeSerializationManager_13(SafeSerializationManager_t4A754D86B0F784B18CBC36C073BA564BED109770 * value)
	{
		____safeSerializationManager_13 = value;
		Il2CppCodeGenWriteBarrier((void**)(&____safeSerializationManager_13), (void*)value);
	}

	inline static int32_t get_offset_of_captured_traces_14() { return static_cast<int32_t>(offsetof(Exception_t, ___captured_traces_14)); }
	inline StackTraceU5BU5D_t855F09649EA34DEE7C1B6F088E0538E3CCC3F196* get_captured_traces_14() const { return ___captured_traces_14; }
	inline StackTraceU5BU5D_t855F09649EA34DEE7C1B6F088E0538E3CCC3F196** get_address_of_captured_traces_14() { return &___captured_traces_14; }
	inline void set_captured_traces_14(StackTraceU5BU5D_t855F09649EA34DEE7C1B6F088E0538E3CCC3F196* value)
	{
		___captured_traces_14 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___captured_traces_14), (void*)value);
	}

	inline static int32_t get_offset_of_native_trace_ips_15() { return static_cast<int32_t>(offsetof(Exception_t, ___native_trace_ips_15)); }
	inline IntPtrU5BU5D_t4DC01DCB9A6DF6C9792A6513595D7A11E637DCDD* get_native_trace_ips_15() const { return ___native_trace_ips_15; }
	inline IntPtrU5BU5D_t4DC01DCB9A6DF6C9792A6513595D7A11E637DCDD** get_address_of_native_trace_ips_15() { return &___native_trace_ips_15; }
	inline void set_native_trace_ips_15(IntPtrU5BU5D_t4DC01DCB9A6DF6C9792A6513595D7A11E637DCDD* value)
	{
		___native_trace_ips_15 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___native_trace_ips_15), (void*)value);
	}
};

struct Exception_t_StaticFields
{
public:
	// System.Object System.Exception::s_EDILock
	RuntimeObject * ___s_EDILock_0;

public:
	inline static int32_t get_offset_of_s_EDILock_0() { return static_cast<int32_t>(offsetof(Exception_t_StaticFields, ___s_EDILock_0)); }
	inline RuntimeObject * get_s_EDILock_0() const { return ___s_EDILock_0; }
	inline RuntimeObject ** get_address_of_s_EDILock_0() { return &___s_EDILock_0; }
	inline void set_s_EDILock_0(RuntimeObject * value)
	{
		___s_EDILock_0 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_EDILock_0), (void*)value);
	}
};

// Native definition for P/Invoke marshalling of System.Exception
struct Exception_t_marshaled_pinvoke
{
	char* ____className_1;
	char* ____message_2;
	RuntimeObject* ____data_3;
	Exception_t_marshaled_pinvoke* ____innerException_4;
	char* ____helpURL_5;
	Il2CppIUnknown* ____stackTrace_6;
	char* ____stackTraceString_7;
	char* ____remoteStackTraceString_8;
	int32_t ____remoteStackIndex_9;
	Il2CppIUnknown* ____dynamicMethods_10;
	int32_t ____HResult_11;
	char* ____source_12;
	SafeSerializationManager_t4A754D86B0F784B18CBC36C073BA564BED109770 * ____safeSerializationManager_13;
	StackTraceU5BU5D_t855F09649EA34DEE7C1B6F088E0538E3CCC3F196* ___captured_traces_14;
	Il2CppSafeArray/*NONE*/* ___native_trace_ips_15;
};
// Native definition for COM marshalling of System.Exception
struct Exception_t_marshaled_com
{
	Il2CppChar* ____className_1;
	Il2CppChar* ____message_2;
	RuntimeObject* ____data_3;
	Exception_t_marshaled_com* ____innerException_4;
	Il2CppChar* ____helpURL_5;
	Il2CppIUnknown* ____stackTrace_6;
	Il2CppChar* ____stackTraceString_7;
	Il2CppChar* ____remoteStackTraceString_8;
	int32_t ____remoteStackIndex_9;
	Il2CppIUnknown* ____dynamicMethods_10;
	int32_t ____HResult_11;
	Il2CppChar* ____source_12;
	SafeSerializationManager_t4A754D86B0F784B18CBC36C073BA564BED109770 * ____safeSerializationManager_13;
	StackTraceU5BU5D_t855F09649EA34DEE7C1B6F088E0538E3CCC3F196* ___captured_traces_14;
	Il2CppSafeArray/*NONE*/* ___native_trace_ips_15;
};

// UnityEngine.Coroutine
struct  Coroutine_tAE7DB2FC70A0AE6477F896F852057CB0754F06EC  : public YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44
{
public:
	// System.IntPtr UnityEngine.Coroutine::m_Ptr
	intptr_t ___m_Ptr_0;

public:
	inline static int32_t get_offset_of_m_Ptr_0() { return static_cast<int32_t>(offsetof(Coroutine_tAE7DB2FC70A0AE6477F896F852057CB0754F06EC, ___m_Ptr_0)); }
	inline intptr_t get_m_Ptr_0() const { return ___m_Ptr_0; }
	inline intptr_t* get_address_of_m_Ptr_0() { return &___m_Ptr_0; }
	inline void set_m_Ptr_0(intptr_t value)
	{
		___m_Ptr_0 = value;
	}
};

// Native definition for P/Invoke marshalling of UnityEngine.Coroutine
struct Coroutine_tAE7DB2FC70A0AE6477F896F852057CB0754F06EC_marshaled_pinvoke : public YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44_marshaled_pinvoke
{
	intptr_t ___m_Ptr_0;
};
// Native definition for COM marshalling of UnityEngine.Coroutine
struct Coroutine_tAE7DB2FC70A0AE6477F896F852057CB0754F06EC_marshaled_com : public YieldInstruction_t836035AC7BD07A3C7909F7AD2A5B42DE99D91C44_marshaled_com
{
	intptr_t ___m_Ptr_0;
};

// UnityEngine.EventSystems.PointerEventData_InputButton
struct  InputButton_tCC7470F9FD2AFE525243394F0215B47D4BF86AB0 
{
public:
	// System.Int32 UnityEngine.EventSystems.PointerEventData_InputButton::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(InputButton_tCC7470F9FD2AFE525243394F0215B47D4BF86AB0, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.EventSystems.RaycastResult
struct  RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91 
{
public:
	// UnityEngine.GameObject UnityEngine.EventSystems.RaycastResult::m_GameObject
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___m_GameObject_0;
	// UnityEngine.EventSystems.BaseRaycaster UnityEngine.EventSystems.RaycastResult::module
	BaseRaycaster_tC7F6105A89F54A38FBFC2659901855FDBB0E3966 * ___module_1;
	// System.Single UnityEngine.EventSystems.RaycastResult::distance
	float ___distance_2;
	// System.Single UnityEngine.EventSystems.RaycastResult::index
	float ___index_3;
	// System.Int32 UnityEngine.EventSystems.RaycastResult::depth
	int32_t ___depth_4;
	// System.Int32 UnityEngine.EventSystems.RaycastResult::sortingLayer
	int32_t ___sortingLayer_5;
	// System.Int32 UnityEngine.EventSystems.RaycastResult::sortingOrder
	int32_t ___sortingOrder_6;
	// UnityEngine.Vector3 UnityEngine.EventSystems.RaycastResult::worldPosition
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___worldPosition_7;
	// UnityEngine.Vector3 UnityEngine.EventSystems.RaycastResult::worldNormal
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___worldNormal_8;
	// UnityEngine.Vector2 UnityEngine.EventSystems.RaycastResult::screenPosition
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___screenPosition_9;
	// System.Int32 UnityEngine.EventSystems.RaycastResult::displayIndex
	int32_t ___displayIndex_10;

public:
	inline static int32_t get_offset_of_m_GameObject_0() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___m_GameObject_0)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_m_GameObject_0() const { return ___m_GameObject_0; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_m_GameObject_0() { return &___m_GameObject_0; }
	inline void set_m_GameObject_0(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___m_GameObject_0 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_GameObject_0), (void*)value);
	}

	inline static int32_t get_offset_of_module_1() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___module_1)); }
	inline BaseRaycaster_tC7F6105A89F54A38FBFC2659901855FDBB0E3966 * get_module_1() const { return ___module_1; }
	inline BaseRaycaster_tC7F6105A89F54A38FBFC2659901855FDBB0E3966 ** get_address_of_module_1() { return &___module_1; }
	inline void set_module_1(BaseRaycaster_tC7F6105A89F54A38FBFC2659901855FDBB0E3966 * value)
	{
		___module_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___module_1), (void*)value);
	}

	inline static int32_t get_offset_of_distance_2() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___distance_2)); }
	inline float get_distance_2() const { return ___distance_2; }
	inline float* get_address_of_distance_2() { return &___distance_2; }
	inline void set_distance_2(float value)
	{
		___distance_2 = value;
	}

	inline static int32_t get_offset_of_index_3() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___index_3)); }
	inline float get_index_3() const { return ___index_3; }
	inline float* get_address_of_index_3() { return &___index_3; }
	inline void set_index_3(float value)
	{
		___index_3 = value;
	}

	inline static int32_t get_offset_of_depth_4() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___depth_4)); }
	inline int32_t get_depth_4() const { return ___depth_4; }
	inline int32_t* get_address_of_depth_4() { return &___depth_4; }
	inline void set_depth_4(int32_t value)
	{
		___depth_4 = value;
	}

	inline static int32_t get_offset_of_sortingLayer_5() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___sortingLayer_5)); }
	inline int32_t get_sortingLayer_5() const { return ___sortingLayer_5; }
	inline int32_t* get_address_of_sortingLayer_5() { return &___sortingLayer_5; }
	inline void set_sortingLayer_5(int32_t value)
	{
		___sortingLayer_5 = value;
	}

	inline static int32_t get_offset_of_sortingOrder_6() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___sortingOrder_6)); }
	inline int32_t get_sortingOrder_6() const { return ___sortingOrder_6; }
	inline int32_t* get_address_of_sortingOrder_6() { return &___sortingOrder_6; }
	inline void set_sortingOrder_6(int32_t value)
	{
		___sortingOrder_6 = value;
	}

	inline static int32_t get_offset_of_worldPosition_7() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___worldPosition_7)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_worldPosition_7() const { return ___worldPosition_7; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_worldPosition_7() { return &___worldPosition_7; }
	inline void set_worldPosition_7(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___worldPosition_7 = value;
	}

	inline static int32_t get_offset_of_worldNormal_8() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___worldNormal_8)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_worldNormal_8() const { return ___worldNormal_8; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_worldNormal_8() { return &___worldNormal_8; }
	inline void set_worldNormal_8(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___worldNormal_8 = value;
	}

	inline static int32_t get_offset_of_screenPosition_9() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___screenPosition_9)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_screenPosition_9() const { return ___screenPosition_9; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_screenPosition_9() { return &___screenPosition_9; }
	inline void set_screenPosition_9(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___screenPosition_9 = value;
	}

	inline static int32_t get_offset_of_displayIndex_10() { return static_cast<int32_t>(offsetof(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91, ___displayIndex_10)); }
	inline int32_t get_displayIndex_10() const { return ___displayIndex_10; }
	inline int32_t* get_address_of_displayIndex_10() { return &___displayIndex_10; }
	inline void set_displayIndex_10(int32_t value)
	{
		___displayIndex_10 = value;
	}
};

// Native definition for P/Invoke marshalling of UnityEngine.EventSystems.RaycastResult
struct RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91_marshaled_pinvoke
{
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___m_GameObject_0;
	BaseRaycaster_tC7F6105A89F54A38FBFC2659901855FDBB0E3966 * ___module_1;
	float ___distance_2;
	float ___index_3;
	int32_t ___depth_4;
	int32_t ___sortingLayer_5;
	int32_t ___sortingOrder_6;
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___worldPosition_7;
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___worldNormal_8;
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___screenPosition_9;
	int32_t ___displayIndex_10;
};
// Native definition for COM marshalling of UnityEngine.EventSystems.RaycastResult
struct RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91_marshaled_com
{
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___m_GameObject_0;
	BaseRaycaster_tC7F6105A89F54A38FBFC2659901855FDBB0E3966 * ___module_1;
	float ___distance_2;
	float ___index_3;
	int32_t ___depth_4;
	int32_t ___sortingLayer_5;
	int32_t ___sortingOrder_6;
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___worldPosition_7;
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___worldNormal_8;
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___screenPosition_9;
	int32_t ___displayIndex_10;
};

// UnityEngine.ForceMode
struct  ForceMode_t76188FF14D0038E184106555207A81218E97D0A5 
{
public:
	// System.Int32 UnityEngine.ForceMode::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(ForceMode_t76188FF14D0038E184106555207A81218E97D0A5, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.ForceMode2D
struct  ForceMode2D_t80F82E2BBC1733F0B88593968BA9CE9BC96A7E36 
{
public:
	// System.Int32 UnityEngine.ForceMode2D::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(ForceMode2D_t80F82E2BBC1733F0B88593968BA9CE9BC96A7E36, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.KeyCode
struct  KeyCode_tC93EA87C5A6901160B583ADFCD3EF6726570DC3C 
{
public:
	// System.Int32 UnityEngine.KeyCode::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(KeyCode_tC93EA87C5A6901160B583ADFCD3EF6726570DC3C, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.Object
struct  Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0  : public RuntimeObject
{
public:
	// System.IntPtr UnityEngine.Object::m_CachedPtr
	intptr_t ___m_CachedPtr_0;

public:
	inline static int32_t get_offset_of_m_CachedPtr_0() { return static_cast<int32_t>(offsetof(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0, ___m_CachedPtr_0)); }
	inline intptr_t get_m_CachedPtr_0() const { return ___m_CachedPtr_0; }
	inline intptr_t* get_address_of_m_CachedPtr_0() { return &___m_CachedPtr_0; }
	inline void set_m_CachedPtr_0(intptr_t value)
	{
		___m_CachedPtr_0 = value;
	}
};

struct Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_StaticFields
{
public:
	// System.Int32 UnityEngine.Object::OffsetOfInstanceIDInCPlusPlusObject
	int32_t ___OffsetOfInstanceIDInCPlusPlusObject_1;

public:
	inline static int32_t get_offset_of_OffsetOfInstanceIDInCPlusPlusObject_1() { return static_cast<int32_t>(offsetof(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_StaticFields, ___OffsetOfInstanceIDInCPlusPlusObject_1)); }
	inline int32_t get_OffsetOfInstanceIDInCPlusPlusObject_1() const { return ___OffsetOfInstanceIDInCPlusPlusObject_1; }
	inline int32_t* get_address_of_OffsetOfInstanceIDInCPlusPlusObject_1() { return &___OffsetOfInstanceIDInCPlusPlusObject_1; }
	inline void set_OffsetOfInstanceIDInCPlusPlusObject_1(int32_t value)
	{
		___OffsetOfInstanceIDInCPlusPlusObject_1 = value;
	}
};

// Native definition for P/Invoke marshalling of UnityEngine.Object
struct Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_marshaled_pinvoke
{
	intptr_t ___m_CachedPtr_0;
};
// Native definition for COM marshalling of UnityEngine.Object
struct Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_marshaled_com
{
	intptr_t ___m_CachedPtr_0;
};

// UnityEngine.RenderMode
struct  RenderMode_tB54632E74CDC4A990E815EB8C3CC515D3A9E2F60 
{
public:
	// System.Int32 UnityEngine.RenderMode::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(RenderMode_tB54632E74CDC4A990E815EB8C3CC515D3A9E2F60, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.RigidbodyType2D
struct  RigidbodyType2D_t968036685C41EDC99F7D8B6293D3DA20B177DA49 
{
public:
	// System.Int32 UnityEngine.RigidbodyType2D::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(RigidbodyType2D_t968036685C41EDC99F7D8B6293D3DA20B177DA49, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.UI.ColorBlock
struct  ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA 
{
public:
	// UnityEngine.Color UnityEngine.UI.ColorBlock::m_NormalColor
	Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  ___m_NormalColor_0;
	// UnityEngine.Color UnityEngine.UI.ColorBlock::m_HighlightedColor
	Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  ___m_HighlightedColor_1;
	// UnityEngine.Color UnityEngine.UI.ColorBlock::m_PressedColor
	Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  ___m_PressedColor_2;
	// UnityEngine.Color UnityEngine.UI.ColorBlock::m_SelectedColor
	Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  ___m_SelectedColor_3;
	// UnityEngine.Color UnityEngine.UI.ColorBlock::m_DisabledColor
	Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  ___m_DisabledColor_4;
	// System.Single UnityEngine.UI.ColorBlock::m_ColorMultiplier
	float ___m_ColorMultiplier_5;
	// System.Single UnityEngine.UI.ColorBlock::m_FadeDuration
	float ___m_FadeDuration_6;

public:
	inline static int32_t get_offset_of_m_NormalColor_0() { return static_cast<int32_t>(offsetof(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA, ___m_NormalColor_0)); }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  get_m_NormalColor_0() const { return ___m_NormalColor_0; }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2 * get_address_of_m_NormalColor_0() { return &___m_NormalColor_0; }
	inline void set_m_NormalColor_0(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  value)
	{
		___m_NormalColor_0 = value;
	}

	inline static int32_t get_offset_of_m_HighlightedColor_1() { return static_cast<int32_t>(offsetof(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA, ___m_HighlightedColor_1)); }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  get_m_HighlightedColor_1() const { return ___m_HighlightedColor_1; }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2 * get_address_of_m_HighlightedColor_1() { return &___m_HighlightedColor_1; }
	inline void set_m_HighlightedColor_1(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  value)
	{
		___m_HighlightedColor_1 = value;
	}

	inline static int32_t get_offset_of_m_PressedColor_2() { return static_cast<int32_t>(offsetof(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA, ___m_PressedColor_2)); }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  get_m_PressedColor_2() const { return ___m_PressedColor_2; }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2 * get_address_of_m_PressedColor_2() { return &___m_PressedColor_2; }
	inline void set_m_PressedColor_2(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  value)
	{
		___m_PressedColor_2 = value;
	}

	inline static int32_t get_offset_of_m_SelectedColor_3() { return static_cast<int32_t>(offsetof(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA, ___m_SelectedColor_3)); }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  get_m_SelectedColor_3() const { return ___m_SelectedColor_3; }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2 * get_address_of_m_SelectedColor_3() { return &___m_SelectedColor_3; }
	inline void set_m_SelectedColor_3(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  value)
	{
		___m_SelectedColor_3 = value;
	}

	inline static int32_t get_offset_of_m_DisabledColor_4() { return static_cast<int32_t>(offsetof(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA, ___m_DisabledColor_4)); }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  get_m_DisabledColor_4() const { return ___m_DisabledColor_4; }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2 * get_address_of_m_DisabledColor_4() { return &___m_DisabledColor_4; }
	inline void set_m_DisabledColor_4(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  value)
	{
		___m_DisabledColor_4 = value;
	}

	inline static int32_t get_offset_of_m_ColorMultiplier_5() { return static_cast<int32_t>(offsetof(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA, ___m_ColorMultiplier_5)); }
	inline float get_m_ColorMultiplier_5() const { return ___m_ColorMultiplier_5; }
	inline float* get_address_of_m_ColorMultiplier_5() { return &___m_ColorMultiplier_5; }
	inline void set_m_ColorMultiplier_5(float value)
	{
		___m_ColorMultiplier_5 = value;
	}

	inline static int32_t get_offset_of_m_FadeDuration_6() { return static_cast<int32_t>(offsetof(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA, ___m_FadeDuration_6)); }
	inline float get_m_FadeDuration_6() const { return ___m_FadeDuration_6; }
	inline float* get_address_of_m_FadeDuration_6() { return &___m_FadeDuration_6; }
	inline void set_m_FadeDuration_6(float value)
	{
		___m_FadeDuration_6 = value;
	}
};


// UnityEngine.UI.Image_FillMethod
struct  FillMethod_t0DB7332683118B7C7D2748BE74CFBF19CD19F8C5 
{
public:
	// System.Int32 UnityEngine.UI.Image_FillMethod::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(FillMethod_t0DB7332683118B7C7D2748BE74CFBF19CD19F8C5, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.UI.Image_Type
struct  Type_t96B8A259B84ADA5E7D3B1F13AEAE22175937F38A 
{
public:
	// System.Int32 UnityEngine.UI.Image_Type::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(Type_t96B8A259B84ADA5E7D3B1F13AEAE22175937F38A, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.UI.Navigation_Mode
struct  Mode_t93F92BD50B147AE38D82BA33FA77FD247A59FE26 
{
public:
	// System.Int32 UnityEngine.UI.Navigation_Mode::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(Mode_t93F92BD50B147AE38D82BA33FA77FD247A59FE26, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.UI.Selectable_Transition
struct  Transition_tA9261C608B54C52324084A0B080E7A3E0548A181 
{
public:
	// System.Int32 UnityEngine.UI.Selectable_Transition::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(Transition_tA9261C608B54C52324084A0B080E7A3E0548A181, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// UnityEngine.UI.Slider_Direction
struct  Direction_tAAEBCB52D43F1B8F5DBB1A6F1025F9D02852B67E 
{
public:
	// System.Int32 UnityEngine.UI.Slider_Direction::value__
	int32_t ___value___2;

public:
	inline static int32_t get_offset_of_value___2() { return static_cast<int32_t>(offsetof(Direction_tAAEBCB52D43F1B8F5DBB1A6F1025F9D02852B67E, ___value___2)); }
	inline int32_t get_value___2() const { return ___value___2; }
	inline int32_t* get_address_of_value___2() { return &___value___2; }
	inline void set_value___2(int32_t value)
	{
		___value___2 = value;
	}
};


// System.MulticastDelegate
struct  MulticastDelegate_t  : public Delegate_t
{
public:
	// System.Delegate[] System.MulticastDelegate::delegates
	DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86* ___delegates_11;

public:
	inline static int32_t get_offset_of_delegates_11() { return static_cast<int32_t>(offsetof(MulticastDelegate_t, ___delegates_11)); }
	inline DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86* get_delegates_11() const { return ___delegates_11; }
	inline DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86** get_address_of_delegates_11() { return &___delegates_11; }
	inline void set_delegates_11(DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86* value)
	{
		___delegates_11 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___delegates_11), (void*)value);
	}
};

// Native definition for P/Invoke marshalling of System.MulticastDelegate
struct MulticastDelegate_t_marshaled_pinvoke : public Delegate_t_marshaled_pinvoke
{
	Delegate_t_marshaled_pinvoke** ___delegates_11;
};
// Native definition for COM marshalling of System.MulticastDelegate
struct MulticastDelegate_t_marshaled_com : public Delegate_t_marshaled_com
{
	Delegate_t_marshaled_com** ___delegates_11;
};

// System.SystemException
struct  SystemException_t5380468142AA850BE4A341D7AF3EAB9C78746782  : public Exception_t
{
public:

public:
};


// UnityEngine.Component
struct  Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621  : public Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0
{
public:

public:
};


// UnityEngine.EventSystems.PointerEventData
struct  PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63  : public BaseEventData_t46C9D2AE3183A742EDE89944AF64A23DBF1B80A5
{
public:
	// UnityEngine.GameObject UnityEngine.EventSystems.PointerEventData::<pointerEnter>k__BackingField
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___U3CpointerEnterU3Ek__BackingField_2;
	// UnityEngine.GameObject UnityEngine.EventSystems.PointerEventData::m_PointerPress
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___m_PointerPress_3;
	// UnityEngine.GameObject UnityEngine.EventSystems.PointerEventData::<lastPress>k__BackingField
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___U3ClastPressU3Ek__BackingField_4;
	// UnityEngine.GameObject UnityEngine.EventSystems.PointerEventData::<rawPointerPress>k__BackingField
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___U3CrawPointerPressU3Ek__BackingField_5;
	// UnityEngine.GameObject UnityEngine.EventSystems.PointerEventData::<pointerDrag>k__BackingField
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___U3CpointerDragU3Ek__BackingField_6;
	// UnityEngine.EventSystems.RaycastResult UnityEngine.EventSystems.PointerEventData::<pointerCurrentRaycast>k__BackingField
	RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91  ___U3CpointerCurrentRaycastU3Ek__BackingField_7;
	// UnityEngine.EventSystems.RaycastResult UnityEngine.EventSystems.PointerEventData::<pointerPressRaycast>k__BackingField
	RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91  ___U3CpointerPressRaycastU3Ek__BackingField_8;
	// System.Collections.Generic.List`1<UnityEngine.GameObject> UnityEngine.EventSystems.PointerEventData::hovered
	List_1_t3D4152882C54B77C712688E910390D5C8E030463 * ___hovered_9;
	// System.Boolean UnityEngine.EventSystems.PointerEventData::<eligibleForClick>k__BackingField
	bool ___U3CeligibleForClickU3Ek__BackingField_10;
	// System.Int32 UnityEngine.EventSystems.PointerEventData::<pointerId>k__BackingField
	int32_t ___U3CpointerIdU3Ek__BackingField_11;
	// UnityEngine.Vector2 UnityEngine.EventSystems.PointerEventData::<position>k__BackingField
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___U3CpositionU3Ek__BackingField_12;
	// UnityEngine.Vector2 UnityEngine.EventSystems.PointerEventData::<delta>k__BackingField
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___U3CdeltaU3Ek__BackingField_13;
	// UnityEngine.Vector2 UnityEngine.EventSystems.PointerEventData::<pressPosition>k__BackingField
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___U3CpressPositionU3Ek__BackingField_14;
	// UnityEngine.Vector3 UnityEngine.EventSystems.PointerEventData::<worldPosition>k__BackingField
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___U3CworldPositionU3Ek__BackingField_15;
	// UnityEngine.Vector3 UnityEngine.EventSystems.PointerEventData::<worldNormal>k__BackingField
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___U3CworldNormalU3Ek__BackingField_16;
	// System.Single UnityEngine.EventSystems.PointerEventData::<clickTime>k__BackingField
	float ___U3CclickTimeU3Ek__BackingField_17;
	// System.Int32 UnityEngine.EventSystems.PointerEventData::<clickCount>k__BackingField
	int32_t ___U3CclickCountU3Ek__BackingField_18;
	// UnityEngine.Vector2 UnityEngine.EventSystems.PointerEventData::<scrollDelta>k__BackingField
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___U3CscrollDeltaU3Ek__BackingField_19;
	// System.Boolean UnityEngine.EventSystems.PointerEventData::<useDragThreshold>k__BackingField
	bool ___U3CuseDragThresholdU3Ek__BackingField_20;
	// System.Boolean UnityEngine.EventSystems.PointerEventData::<dragging>k__BackingField
	bool ___U3CdraggingU3Ek__BackingField_21;
	// UnityEngine.EventSystems.PointerEventData_InputButton UnityEngine.EventSystems.PointerEventData::<button>k__BackingField
	int32_t ___U3CbuttonU3Ek__BackingField_22;

public:
	inline static int32_t get_offset_of_U3CpointerEnterU3Ek__BackingField_2() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CpointerEnterU3Ek__BackingField_2)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_U3CpointerEnterU3Ek__BackingField_2() const { return ___U3CpointerEnterU3Ek__BackingField_2; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_U3CpointerEnterU3Ek__BackingField_2() { return &___U3CpointerEnterU3Ek__BackingField_2; }
	inline void set_U3CpointerEnterU3Ek__BackingField_2(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___U3CpointerEnterU3Ek__BackingField_2 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___U3CpointerEnterU3Ek__BackingField_2), (void*)value);
	}

	inline static int32_t get_offset_of_m_PointerPress_3() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___m_PointerPress_3)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_m_PointerPress_3() const { return ___m_PointerPress_3; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_m_PointerPress_3() { return &___m_PointerPress_3; }
	inline void set_m_PointerPress_3(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___m_PointerPress_3 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_PointerPress_3), (void*)value);
	}

	inline static int32_t get_offset_of_U3ClastPressU3Ek__BackingField_4() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3ClastPressU3Ek__BackingField_4)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_U3ClastPressU3Ek__BackingField_4() const { return ___U3ClastPressU3Ek__BackingField_4; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_U3ClastPressU3Ek__BackingField_4() { return &___U3ClastPressU3Ek__BackingField_4; }
	inline void set_U3ClastPressU3Ek__BackingField_4(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___U3ClastPressU3Ek__BackingField_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___U3ClastPressU3Ek__BackingField_4), (void*)value);
	}

	inline static int32_t get_offset_of_U3CrawPointerPressU3Ek__BackingField_5() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CrawPointerPressU3Ek__BackingField_5)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_U3CrawPointerPressU3Ek__BackingField_5() const { return ___U3CrawPointerPressU3Ek__BackingField_5; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_U3CrawPointerPressU3Ek__BackingField_5() { return &___U3CrawPointerPressU3Ek__BackingField_5; }
	inline void set_U3CrawPointerPressU3Ek__BackingField_5(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___U3CrawPointerPressU3Ek__BackingField_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___U3CrawPointerPressU3Ek__BackingField_5), (void*)value);
	}

	inline static int32_t get_offset_of_U3CpointerDragU3Ek__BackingField_6() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CpointerDragU3Ek__BackingField_6)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_U3CpointerDragU3Ek__BackingField_6() const { return ___U3CpointerDragU3Ek__BackingField_6; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_U3CpointerDragU3Ek__BackingField_6() { return &___U3CpointerDragU3Ek__BackingField_6; }
	inline void set_U3CpointerDragU3Ek__BackingField_6(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___U3CpointerDragU3Ek__BackingField_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___U3CpointerDragU3Ek__BackingField_6), (void*)value);
	}

	inline static int32_t get_offset_of_U3CpointerCurrentRaycastU3Ek__BackingField_7() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CpointerCurrentRaycastU3Ek__BackingField_7)); }
	inline RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91  get_U3CpointerCurrentRaycastU3Ek__BackingField_7() const { return ___U3CpointerCurrentRaycastU3Ek__BackingField_7; }
	inline RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91 * get_address_of_U3CpointerCurrentRaycastU3Ek__BackingField_7() { return &___U3CpointerCurrentRaycastU3Ek__BackingField_7; }
	inline void set_U3CpointerCurrentRaycastU3Ek__BackingField_7(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91  value)
	{
		___U3CpointerCurrentRaycastU3Ek__BackingField_7 = value;
		Il2CppCodeGenWriteBarrier((void**)&(((&___U3CpointerCurrentRaycastU3Ek__BackingField_7))->___m_GameObject_0), (void*)NULL);
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___U3CpointerCurrentRaycastU3Ek__BackingField_7))->___module_1), (void*)NULL);
		#endif
	}

	inline static int32_t get_offset_of_U3CpointerPressRaycastU3Ek__BackingField_8() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CpointerPressRaycastU3Ek__BackingField_8)); }
	inline RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91  get_U3CpointerPressRaycastU3Ek__BackingField_8() const { return ___U3CpointerPressRaycastU3Ek__BackingField_8; }
	inline RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91 * get_address_of_U3CpointerPressRaycastU3Ek__BackingField_8() { return &___U3CpointerPressRaycastU3Ek__BackingField_8; }
	inline void set_U3CpointerPressRaycastU3Ek__BackingField_8(RaycastResult_t991BCED43A91EDD8580F39631DA07B1F88C58B91  value)
	{
		___U3CpointerPressRaycastU3Ek__BackingField_8 = value;
		Il2CppCodeGenWriteBarrier((void**)&(((&___U3CpointerPressRaycastU3Ek__BackingField_8))->___m_GameObject_0), (void*)NULL);
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___U3CpointerPressRaycastU3Ek__BackingField_8))->___module_1), (void*)NULL);
		#endif
	}

	inline static int32_t get_offset_of_hovered_9() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___hovered_9)); }
	inline List_1_t3D4152882C54B77C712688E910390D5C8E030463 * get_hovered_9() const { return ___hovered_9; }
	inline List_1_t3D4152882C54B77C712688E910390D5C8E030463 ** get_address_of_hovered_9() { return &___hovered_9; }
	inline void set_hovered_9(List_1_t3D4152882C54B77C712688E910390D5C8E030463 * value)
	{
		___hovered_9 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___hovered_9), (void*)value);
	}

	inline static int32_t get_offset_of_U3CeligibleForClickU3Ek__BackingField_10() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CeligibleForClickU3Ek__BackingField_10)); }
	inline bool get_U3CeligibleForClickU3Ek__BackingField_10() const { return ___U3CeligibleForClickU3Ek__BackingField_10; }
	inline bool* get_address_of_U3CeligibleForClickU3Ek__BackingField_10() { return &___U3CeligibleForClickU3Ek__BackingField_10; }
	inline void set_U3CeligibleForClickU3Ek__BackingField_10(bool value)
	{
		___U3CeligibleForClickU3Ek__BackingField_10 = value;
	}

	inline static int32_t get_offset_of_U3CpointerIdU3Ek__BackingField_11() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CpointerIdU3Ek__BackingField_11)); }
	inline int32_t get_U3CpointerIdU3Ek__BackingField_11() const { return ___U3CpointerIdU3Ek__BackingField_11; }
	inline int32_t* get_address_of_U3CpointerIdU3Ek__BackingField_11() { return &___U3CpointerIdU3Ek__BackingField_11; }
	inline void set_U3CpointerIdU3Ek__BackingField_11(int32_t value)
	{
		___U3CpointerIdU3Ek__BackingField_11 = value;
	}

	inline static int32_t get_offset_of_U3CpositionU3Ek__BackingField_12() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CpositionU3Ek__BackingField_12)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_U3CpositionU3Ek__BackingField_12() const { return ___U3CpositionU3Ek__BackingField_12; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_U3CpositionU3Ek__BackingField_12() { return &___U3CpositionU3Ek__BackingField_12; }
	inline void set_U3CpositionU3Ek__BackingField_12(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___U3CpositionU3Ek__BackingField_12 = value;
	}

	inline static int32_t get_offset_of_U3CdeltaU3Ek__BackingField_13() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CdeltaU3Ek__BackingField_13)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_U3CdeltaU3Ek__BackingField_13() const { return ___U3CdeltaU3Ek__BackingField_13; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_U3CdeltaU3Ek__BackingField_13() { return &___U3CdeltaU3Ek__BackingField_13; }
	inline void set_U3CdeltaU3Ek__BackingField_13(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___U3CdeltaU3Ek__BackingField_13 = value;
	}

	inline static int32_t get_offset_of_U3CpressPositionU3Ek__BackingField_14() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CpressPositionU3Ek__BackingField_14)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_U3CpressPositionU3Ek__BackingField_14() const { return ___U3CpressPositionU3Ek__BackingField_14; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_U3CpressPositionU3Ek__BackingField_14() { return &___U3CpressPositionU3Ek__BackingField_14; }
	inline void set_U3CpressPositionU3Ek__BackingField_14(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___U3CpressPositionU3Ek__BackingField_14 = value;
	}

	inline static int32_t get_offset_of_U3CworldPositionU3Ek__BackingField_15() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CworldPositionU3Ek__BackingField_15)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_U3CworldPositionU3Ek__BackingField_15() const { return ___U3CworldPositionU3Ek__BackingField_15; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_U3CworldPositionU3Ek__BackingField_15() { return &___U3CworldPositionU3Ek__BackingField_15; }
	inline void set_U3CworldPositionU3Ek__BackingField_15(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___U3CworldPositionU3Ek__BackingField_15 = value;
	}

	inline static int32_t get_offset_of_U3CworldNormalU3Ek__BackingField_16() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CworldNormalU3Ek__BackingField_16)); }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  get_U3CworldNormalU3Ek__BackingField_16() const { return ___U3CworldNormalU3Ek__BackingField_16; }
	inline Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * get_address_of_U3CworldNormalU3Ek__BackingField_16() { return &___U3CworldNormalU3Ek__BackingField_16; }
	inline void set_U3CworldNormalU3Ek__BackingField_16(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  value)
	{
		___U3CworldNormalU3Ek__BackingField_16 = value;
	}

	inline static int32_t get_offset_of_U3CclickTimeU3Ek__BackingField_17() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CclickTimeU3Ek__BackingField_17)); }
	inline float get_U3CclickTimeU3Ek__BackingField_17() const { return ___U3CclickTimeU3Ek__BackingField_17; }
	inline float* get_address_of_U3CclickTimeU3Ek__BackingField_17() { return &___U3CclickTimeU3Ek__BackingField_17; }
	inline void set_U3CclickTimeU3Ek__BackingField_17(float value)
	{
		___U3CclickTimeU3Ek__BackingField_17 = value;
	}

	inline static int32_t get_offset_of_U3CclickCountU3Ek__BackingField_18() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CclickCountU3Ek__BackingField_18)); }
	inline int32_t get_U3CclickCountU3Ek__BackingField_18() const { return ___U3CclickCountU3Ek__BackingField_18; }
	inline int32_t* get_address_of_U3CclickCountU3Ek__BackingField_18() { return &___U3CclickCountU3Ek__BackingField_18; }
	inline void set_U3CclickCountU3Ek__BackingField_18(int32_t value)
	{
		___U3CclickCountU3Ek__BackingField_18 = value;
	}

	inline static int32_t get_offset_of_U3CscrollDeltaU3Ek__BackingField_19() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CscrollDeltaU3Ek__BackingField_19)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_U3CscrollDeltaU3Ek__BackingField_19() const { return ___U3CscrollDeltaU3Ek__BackingField_19; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_U3CscrollDeltaU3Ek__BackingField_19() { return &___U3CscrollDeltaU3Ek__BackingField_19; }
	inline void set_U3CscrollDeltaU3Ek__BackingField_19(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___U3CscrollDeltaU3Ek__BackingField_19 = value;
	}

	inline static int32_t get_offset_of_U3CuseDragThresholdU3Ek__BackingField_20() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CuseDragThresholdU3Ek__BackingField_20)); }
	inline bool get_U3CuseDragThresholdU3Ek__BackingField_20() const { return ___U3CuseDragThresholdU3Ek__BackingField_20; }
	inline bool* get_address_of_U3CuseDragThresholdU3Ek__BackingField_20() { return &___U3CuseDragThresholdU3Ek__BackingField_20; }
	inline void set_U3CuseDragThresholdU3Ek__BackingField_20(bool value)
	{
		___U3CuseDragThresholdU3Ek__BackingField_20 = value;
	}

	inline static int32_t get_offset_of_U3CdraggingU3Ek__BackingField_21() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CdraggingU3Ek__BackingField_21)); }
	inline bool get_U3CdraggingU3Ek__BackingField_21() const { return ___U3CdraggingU3Ek__BackingField_21; }
	inline bool* get_address_of_U3CdraggingU3Ek__BackingField_21() { return &___U3CdraggingU3Ek__BackingField_21; }
	inline void set_U3CdraggingU3Ek__BackingField_21(bool value)
	{
		___U3CdraggingU3Ek__BackingField_21 = value;
	}

	inline static int32_t get_offset_of_U3CbuttonU3Ek__BackingField_22() { return static_cast<int32_t>(offsetof(PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63, ___U3CbuttonU3Ek__BackingField_22)); }
	inline int32_t get_U3CbuttonU3Ek__BackingField_22() const { return ___U3CbuttonU3Ek__BackingField_22; }
	inline int32_t* get_address_of_U3CbuttonU3Ek__BackingField_22() { return &___U3CbuttonU3Ek__BackingField_22; }
	inline void set_U3CbuttonU3Ek__BackingField_22(int32_t value)
	{
		___U3CbuttonU3Ek__BackingField_22 = value;
	}
};


// UnityEngine.GameObject
struct  GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F  : public Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0
{
public:

public:
};


// UnityEngine.Motion
struct  Motion_t497BF9244B6A769D1AE925C3876B187C56C8CF8F  : public Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0
{
public:

public:
};


// UnityEngine.Sprite
struct  Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198  : public Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0
{
public:

public:
};


// UnityEngine.UI.Navigation
struct  Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07 
{
public:
	// UnityEngine.UI.Navigation_Mode UnityEngine.UI.Navigation::m_Mode
	int32_t ___m_Mode_0;
	// UnityEngine.UI.Selectable UnityEngine.UI.Navigation::m_SelectOnUp
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnUp_1;
	// UnityEngine.UI.Selectable UnityEngine.UI.Navigation::m_SelectOnDown
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnDown_2;
	// UnityEngine.UI.Selectable UnityEngine.UI.Navigation::m_SelectOnLeft
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnLeft_3;
	// UnityEngine.UI.Selectable UnityEngine.UI.Navigation::m_SelectOnRight
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnRight_4;

public:
	inline static int32_t get_offset_of_m_Mode_0() { return static_cast<int32_t>(offsetof(Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07, ___m_Mode_0)); }
	inline int32_t get_m_Mode_0() const { return ___m_Mode_0; }
	inline int32_t* get_address_of_m_Mode_0() { return &___m_Mode_0; }
	inline void set_m_Mode_0(int32_t value)
	{
		___m_Mode_0 = value;
	}

	inline static int32_t get_offset_of_m_SelectOnUp_1() { return static_cast<int32_t>(offsetof(Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07, ___m_SelectOnUp_1)); }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * get_m_SelectOnUp_1() const { return ___m_SelectOnUp_1; }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A ** get_address_of_m_SelectOnUp_1() { return &___m_SelectOnUp_1; }
	inline void set_m_SelectOnUp_1(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * value)
	{
		___m_SelectOnUp_1 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_SelectOnUp_1), (void*)value);
	}

	inline static int32_t get_offset_of_m_SelectOnDown_2() { return static_cast<int32_t>(offsetof(Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07, ___m_SelectOnDown_2)); }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * get_m_SelectOnDown_2() const { return ___m_SelectOnDown_2; }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A ** get_address_of_m_SelectOnDown_2() { return &___m_SelectOnDown_2; }
	inline void set_m_SelectOnDown_2(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * value)
	{
		___m_SelectOnDown_2 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_SelectOnDown_2), (void*)value);
	}

	inline static int32_t get_offset_of_m_SelectOnLeft_3() { return static_cast<int32_t>(offsetof(Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07, ___m_SelectOnLeft_3)); }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * get_m_SelectOnLeft_3() const { return ___m_SelectOnLeft_3; }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A ** get_address_of_m_SelectOnLeft_3() { return &___m_SelectOnLeft_3; }
	inline void set_m_SelectOnLeft_3(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * value)
	{
		___m_SelectOnLeft_3 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_SelectOnLeft_3), (void*)value);
	}

	inline static int32_t get_offset_of_m_SelectOnRight_4() { return static_cast<int32_t>(offsetof(Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07, ___m_SelectOnRight_4)); }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * get_m_SelectOnRight_4() const { return ___m_SelectOnRight_4; }
	inline Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A ** get_address_of_m_SelectOnRight_4() { return &___m_SelectOnRight_4; }
	inline void set_m_SelectOnRight_4(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * value)
	{
		___m_SelectOnRight_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_SelectOnRight_4), (void*)value);
	}
};

// Native definition for P/Invoke marshalling of UnityEngine.UI.Navigation
struct Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07_marshaled_pinvoke
{
	int32_t ___m_Mode_0;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnUp_1;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnDown_2;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnLeft_3;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnRight_4;
};
// Native definition for COM marshalling of UnityEngine.UI.Navigation
struct Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07_marshaled_com
{
	int32_t ___m_Mode_0;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnUp_1;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnDown_2;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnLeft_3;
	Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A * ___m_SelectOnRight_4;
};

// Bomb_ExplotionNotify
struct  ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C  : public MulticastDelegate_t
{
public:

public:
};


// System.AsyncCallback
struct  AsyncCallback_t3F3DA3BEDAEE81DD1D24125DF8EB30E85EE14DA4  : public MulticastDelegate_t
{
public:

public:
};


// System.NotSupportedException
struct  NotSupportedException_tE75B318D6590A02A5D9B29FD97409B1750FA0010  : public SystemException_t5380468142AA850BE4A341D7AF3EAB9C78746782
{
public:

public:
};


// UnityEngine.AnimationClip
struct  AnimationClip_t336CFC94F6275526DC0B9BEEF833D4D89D6DEDDE  : public Motion_t497BF9244B6A769D1AE925C3876B187C56C8CF8F
{
public:

public:
};


// UnityEngine.Behaviour
struct  Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8  : public Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621
{
public:

public:
};


// UnityEngine.Renderer
struct  Renderer_t0556D67DD582620D1F495627EDE30D03284151F4  : public Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621
{
public:

public:
};


// UnityEngine.Rigidbody
struct  Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5  : public Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621
{
public:

public:
};


// UnityEngine.Rigidbody2D
struct  Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE  : public Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621
{
public:

public:
};


// UnityEngine.Transform
struct  Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA  : public Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621
{
public:

public:
};


// UnityEngine.Animator
struct  Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A  : public Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8
{
public:

public:
};


// UnityEngine.Camera
struct  Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34  : public Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8
{
public:

public:
};

struct Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34_StaticFields
{
public:
	// UnityEngine.Camera_CameraCallback UnityEngine.Camera::onPreCull
	CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * ___onPreCull_4;
	// UnityEngine.Camera_CameraCallback UnityEngine.Camera::onPreRender
	CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * ___onPreRender_5;
	// UnityEngine.Camera_CameraCallback UnityEngine.Camera::onPostRender
	CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * ___onPostRender_6;

public:
	inline static int32_t get_offset_of_onPreCull_4() { return static_cast<int32_t>(offsetof(Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34_StaticFields, ___onPreCull_4)); }
	inline CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * get_onPreCull_4() const { return ___onPreCull_4; }
	inline CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 ** get_address_of_onPreCull_4() { return &___onPreCull_4; }
	inline void set_onPreCull_4(CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * value)
	{
		___onPreCull_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___onPreCull_4), (void*)value);
	}

	inline static int32_t get_offset_of_onPreRender_5() { return static_cast<int32_t>(offsetof(Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34_StaticFields, ___onPreRender_5)); }
	inline CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * get_onPreRender_5() const { return ___onPreRender_5; }
	inline CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 ** get_address_of_onPreRender_5() { return &___onPreRender_5; }
	inline void set_onPreRender_5(CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * value)
	{
		___onPreRender_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___onPreRender_5), (void*)value);
	}

	inline static int32_t get_offset_of_onPostRender_6() { return static_cast<int32_t>(offsetof(Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34_StaticFields, ___onPostRender_6)); }
	inline CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * get_onPostRender_6() const { return ___onPostRender_6; }
	inline CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 ** get_address_of_onPostRender_6() { return &___onPostRender_6; }
	inline void set_onPostRender_6(CameraCallback_t8BBB42AA08D7498DFC11F4128117055BC7F0B9D0 * value)
	{
		___onPostRender_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___onPostRender_6), (void*)value);
	}
};


// UnityEngine.Canvas
struct  Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591  : public Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8
{
public:

public:
};

struct Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591_StaticFields
{
public:
	// UnityEngine.Canvas_WillRenderCanvases UnityEngine.Canvas::willRenderCanvases
	WillRenderCanvases_tBD5AD090B5938021DEAA679A5AEEA790F60A8BEE * ___willRenderCanvases_4;

public:
	inline static int32_t get_offset_of_willRenderCanvases_4() { return static_cast<int32_t>(offsetof(Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591_StaticFields, ___willRenderCanvases_4)); }
	inline WillRenderCanvases_tBD5AD090B5938021DEAA679A5AEEA790F60A8BEE * get_willRenderCanvases_4() const { return ___willRenderCanvases_4; }
	inline WillRenderCanvases_tBD5AD090B5938021DEAA679A5AEEA790F60A8BEE ** get_address_of_willRenderCanvases_4() { return &___willRenderCanvases_4; }
	inline void set_willRenderCanvases_4(WillRenderCanvases_tBD5AD090B5938021DEAA679A5AEEA790F60A8BEE * value)
	{
		___willRenderCanvases_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___willRenderCanvases_4), (void*)value);
	}
};


// UnityEngine.Collider2D
struct  Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379  : public Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8
{
public:

public:
};


// UnityEngine.MonoBehaviour
struct  MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429  : public Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8
{
public:

public:
};


// UnityEngine.RectTransform
struct  RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20  : public Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA
{
public:

public:
};

struct RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20_StaticFields
{
public:
	// UnityEngine.RectTransform_ReapplyDrivenProperties UnityEngine.RectTransform::reapplyDrivenProperties
	ReapplyDrivenProperties_t431F4FBD9C59AE097FE33C4354CC6251B01B527D * ___reapplyDrivenProperties_4;

public:
	inline static int32_t get_offset_of_reapplyDrivenProperties_4() { return static_cast<int32_t>(offsetof(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20_StaticFields, ___reapplyDrivenProperties_4)); }
	inline ReapplyDrivenProperties_t431F4FBD9C59AE097FE33C4354CC6251B01B527D * get_reapplyDrivenProperties_4() const { return ___reapplyDrivenProperties_4; }
	inline ReapplyDrivenProperties_t431F4FBD9C59AE097FE33C4354CC6251B01B527D ** get_address_of_reapplyDrivenProperties_4() { return &___reapplyDrivenProperties_4; }
	inline void set_reapplyDrivenProperties_4(ReapplyDrivenProperties_t431F4FBD9C59AE097FE33C4354CC6251B01B527D * value)
	{
		___reapplyDrivenProperties_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___reapplyDrivenProperties_4), (void*)value);
	}
};


// UnityEngine.SpriteRenderer
struct  SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F  : public Renderer_t0556D67DD582620D1F495627EDE30D03284151F4
{
public:

public:
};


// Bomb
struct  Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// Bomb_ExplotionNotify Bomb::explotionNotify
	ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * ___explotionNotify_4;
	// UnityEngine.Animator Bomb::anim
	Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * ___anim_5;
	// UnityEngine.Rigidbody2D Bomb::rb
	Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * ___rb_6;
	// UnityEngine.Collider2D Bomb::coll
	Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___coll_7;
	// UnityEngine.LayerMask Bomb::targeLayer
	LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  ___targeLayer_8;
	// System.Single Bomb::startTime
	float ___startTime_9;
	// System.Single Bomb::waitTime
	float ___waitTime_10;
	// System.Single Bomb::radius
	float ___radius_11;
	// System.Single Bomb::bombForce
	float ___bombForce_12;

public:
	inline static int32_t get_offset_of_explotionNotify_4() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___explotionNotify_4)); }
	inline ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * get_explotionNotify_4() const { return ___explotionNotify_4; }
	inline ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C ** get_address_of_explotionNotify_4() { return &___explotionNotify_4; }
	inline void set_explotionNotify_4(ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * value)
	{
		___explotionNotify_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___explotionNotify_4), (void*)value);
	}

	inline static int32_t get_offset_of_anim_5() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___anim_5)); }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * get_anim_5() const { return ___anim_5; }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A ** get_address_of_anim_5() { return &___anim_5; }
	inline void set_anim_5(Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * value)
	{
		___anim_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___anim_5), (void*)value);
	}

	inline static int32_t get_offset_of_rb_6() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___rb_6)); }
	inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * get_rb_6() const { return ___rb_6; }
	inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE ** get_address_of_rb_6() { return &___rb_6; }
	inline void set_rb_6(Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * value)
	{
		___rb_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___rb_6), (void*)value);
	}

	inline static int32_t get_offset_of_coll_7() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___coll_7)); }
	inline Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * get_coll_7() const { return ___coll_7; }
	inline Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 ** get_address_of_coll_7() { return &___coll_7; }
	inline void set_coll_7(Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * value)
	{
		___coll_7 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___coll_7), (void*)value);
	}

	inline static int32_t get_offset_of_targeLayer_8() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___targeLayer_8)); }
	inline LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  get_targeLayer_8() const { return ___targeLayer_8; }
	inline LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0 * get_address_of_targeLayer_8() { return &___targeLayer_8; }
	inline void set_targeLayer_8(LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  value)
	{
		___targeLayer_8 = value;
	}

	inline static int32_t get_offset_of_startTime_9() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___startTime_9)); }
	inline float get_startTime_9() const { return ___startTime_9; }
	inline float* get_address_of_startTime_9() { return &___startTime_9; }
	inline void set_startTime_9(float value)
	{
		___startTime_9 = value;
	}

	inline static int32_t get_offset_of_waitTime_10() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___waitTime_10)); }
	inline float get_waitTime_10() const { return ___waitTime_10; }
	inline float* get_address_of_waitTime_10() { return &___waitTime_10; }
	inline void set_waitTime_10(float value)
	{
		___waitTime_10 = value;
	}

	inline static int32_t get_offset_of_radius_11() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___radius_11)); }
	inline float get_radius_11() const { return ___radius_11; }
	inline float* get_address_of_radius_11() { return &___radius_11; }
	inline void set_radius_11(float value)
	{
		___radius_11 = value;
	}

	inline static int32_t get_offset_of_bombForce_12() { return static_cast<int32_t>(offsetof(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2, ___bombForce_12)); }
	inline float get_bombForce_12() const { return ___bombForce_12; }
	inline float* get_address_of_bombForce_12() { return &___bombForce_12; }
	inline void set_bombForce_12(float value)
	{
		___bombForce_12 = value;
	}
};


// Door
struct  Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// UnityEngine.Animator Door::anim
	Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * ___anim_4;
	// UnityEngine.BoxCollider2D Door::coll
	BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * ___coll_5;

public:
	inline static int32_t get_offset_of_anim_4() { return static_cast<int32_t>(offsetof(Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1, ___anim_4)); }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * get_anim_4() const { return ___anim_4; }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A ** get_address_of_anim_4() { return &___anim_4; }
	inline void set_anim_4(Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * value)
	{
		___anim_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___anim_4), (void*)value);
	}

	inline static int32_t get_offset_of_coll_5() { return static_cast<int32_t>(offsetof(Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1, ___coll_5)); }
	inline BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * get_coll_5() const { return ___coll_5; }
	inline BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 ** get_address_of_coll_5() { return &___coll_5; }
	inline void set_coll_5(BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * value)
	{
		___coll_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___coll_5), (void*)value);
	}
};


// Enemy
struct  Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// EnemyBaseState Enemy::currentState
	EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * ___currentState_4;
	// System.Single Enemy::speed
	float ___speed_5;
	// UnityEngine.Transform Enemy::pointA
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___pointA_6;
	// UnityEngine.Transform Enemy::pointB
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___pointB_7;
	// UnityEngine.Transform Enemy::targetPoint
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___targetPoint_8;
	// System.Collections.Generic.List`1<UnityEngine.Transform> Enemy::attackList
	List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * ___attackList_9;
	// UnityEngine.GameObject Enemy::checkArea
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___checkArea_10;
	// UnityEngine.Animator Enemy::anim
	Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * ___anim_11;
	// System.Int32 Enemy::animState
	int32_t ___animState_12;
	// System.Boolean Enemy::isBoss
	bool ___isBoss_13;
	// PatrolState Enemy::patrolState
	PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * ___patrolState_14;
	// AttachState Enemy::attachState
	AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * ___attachState_15;
	// UnityEngine.GameObject Enemy::alarmSign
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___alarmSign_16;
	// System.Single Enemy::attackRange
	float ___attackRange_17;
	// System.Single Enemy::skillRange
	float ___skillRange_18;
	// System.Single Enemy::attackRate
	float ___attackRate_19;
	// System.Single Enemy::nextAttack
	float ___nextAttack_20;
	// System.Single Enemy::health
	float ___health_21;
	// System.Boolean Enemy::isDead
	bool ___isDead_22;

public:
	inline static int32_t get_offset_of_currentState_4() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___currentState_4)); }
	inline EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * get_currentState_4() const { return ___currentState_4; }
	inline EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 ** get_address_of_currentState_4() { return &___currentState_4; }
	inline void set_currentState_4(EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * value)
	{
		___currentState_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___currentState_4), (void*)value);
	}

	inline static int32_t get_offset_of_speed_5() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___speed_5)); }
	inline float get_speed_5() const { return ___speed_5; }
	inline float* get_address_of_speed_5() { return &___speed_5; }
	inline void set_speed_5(float value)
	{
		___speed_5 = value;
	}

	inline static int32_t get_offset_of_pointA_6() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___pointA_6)); }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * get_pointA_6() const { return ___pointA_6; }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA ** get_address_of_pointA_6() { return &___pointA_6; }
	inline void set_pointA_6(Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * value)
	{
		___pointA_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___pointA_6), (void*)value);
	}

	inline static int32_t get_offset_of_pointB_7() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___pointB_7)); }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * get_pointB_7() const { return ___pointB_7; }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA ** get_address_of_pointB_7() { return &___pointB_7; }
	inline void set_pointB_7(Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * value)
	{
		___pointB_7 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___pointB_7), (void*)value);
	}

	inline static int32_t get_offset_of_targetPoint_8() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___targetPoint_8)); }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * get_targetPoint_8() const { return ___targetPoint_8; }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA ** get_address_of_targetPoint_8() { return &___targetPoint_8; }
	inline void set_targetPoint_8(Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * value)
	{
		___targetPoint_8 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___targetPoint_8), (void*)value);
	}

	inline static int32_t get_offset_of_attackList_9() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___attackList_9)); }
	inline List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * get_attackList_9() const { return ___attackList_9; }
	inline List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE ** get_address_of_attackList_9() { return &___attackList_9; }
	inline void set_attackList_9(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * value)
	{
		___attackList_9 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___attackList_9), (void*)value);
	}

	inline static int32_t get_offset_of_checkArea_10() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___checkArea_10)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_checkArea_10() const { return ___checkArea_10; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_checkArea_10() { return &___checkArea_10; }
	inline void set_checkArea_10(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___checkArea_10 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___checkArea_10), (void*)value);
	}

	inline static int32_t get_offset_of_anim_11() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___anim_11)); }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * get_anim_11() const { return ___anim_11; }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A ** get_address_of_anim_11() { return &___anim_11; }
	inline void set_anim_11(Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * value)
	{
		___anim_11 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___anim_11), (void*)value);
	}

	inline static int32_t get_offset_of_animState_12() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___animState_12)); }
	inline int32_t get_animState_12() const { return ___animState_12; }
	inline int32_t* get_address_of_animState_12() { return &___animState_12; }
	inline void set_animState_12(int32_t value)
	{
		___animState_12 = value;
	}

	inline static int32_t get_offset_of_isBoss_13() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___isBoss_13)); }
	inline bool get_isBoss_13() const { return ___isBoss_13; }
	inline bool* get_address_of_isBoss_13() { return &___isBoss_13; }
	inline void set_isBoss_13(bool value)
	{
		___isBoss_13 = value;
	}

	inline static int32_t get_offset_of_patrolState_14() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___patrolState_14)); }
	inline PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * get_patrolState_14() const { return ___patrolState_14; }
	inline PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 ** get_address_of_patrolState_14() { return &___patrolState_14; }
	inline void set_patrolState_14(PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * value)
	{
		___patrolState_14 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___patrolState_14), (void*)value);
	}

	inline static int32_t get_offset_of_attachState_15() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___attachState_15)); }
	inline AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * get_attachState_15() const { return ___attachState_15; }
	inline AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF ** get_address_of_attachState_15() { return &___attachState_15; }
	inline void set_attachState_15(AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * value)
	{
		___attachState_15 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___attachState_15), (void*)value);
	}

	inline static int32_t get_offset_of_alarmSign_16() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___alarmSign_16)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_alarmSign_16() const { return ___alarmSign_16; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_alarmSign_16() { return &___alarmSign_16; }
	inline void set_alarmSign_16(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___alarmSign_16 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___alarmSign_16), (void*)value);
	}

	inline static int32_t get_offset_of_attackRange_17() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___attackRange_17)); }
	inline float get_attackRange_17() const { return ___attackRange_17; }
	inline float* get_address_of_attackRange_17() { return &___attackRange_17; }
	inline void set_attackRange_17(float value)
	{
		___attackRange_17 = value;
	}

	inline static int32_t get_offset_of_skillRange_18() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___skillRange_18)); }
	inline float get_skillRange_18() const { return ___skillRange_18; }
	inline float* get_address_of_skillRange_18() { return &___skillRange_18; }
	inline void set_skillRange_18(float value)
	{
		___skillRange_18 = value;
	}

	inline static int32_t get_offset_of_attackRate_19() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___attackRate_19)); }
	inline float get_attackRate_19() const { return ___attackRate_19; }
	inline float* get_address_of_attackRate_19() { return &___attackRate_19; }
	inline void set_attackRate_19(float value)
	{
		___attackRate_19 = value;
	}

	inline static int32_t get_offset_of_nextAttack_20() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___nextAttack_20)); }
	inline float get_nextAttack_20() const { return ___nextAttack_20; }
	inline float* get_address_of_nextAttack_20() { return &___nextAttack_20; }
	inline void set_nextAttack_20(float value)
	{
		___nextAttack_20 = value;
	}

	inline static int32_t get_offset_of_health_21() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___health_21)); }
	inline float get_health_21() const { return ___health_21; }
	inline float* get_address_of_health_21() { return &___health_21; }
	inline void set_health_21(float value)
	{
		___health_21 = value;
	}

	inline static int32_t get_offset_of_isDead_22() { return static_cast<int32_t>(offsetof(Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6, ___isDead_22)); }
	inline bool get_isDead_22() const { return ___isDead_22; }
	inline bool* get_address_of_isDead_22() { return &___isDead_22; }
	inline void set_isDead_22(bool value)
	{
		___isDead_22 = value;
	}
};


// GameManager
struct  GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// PlayerController GameManager::player
	PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * ___player_6;
	// System.Boolean GameManager::gameOver
	bool ___gameOver_7;
	// System.Collections.Generic.List`1<Enemy> GameManager::liveEnemy
	List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * ___liveEnemy_8;
	// Door GameManager::doorExit
	Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * ___doorExit_9;

public:
	inline static int32_t get_offset_of_player_6() { return static_cast<int32_t>(offsetof(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89, ___player_6)); }
	inline PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * get_player_6() const { return ___player_6; }
	inline PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 ** get_address_of_player_6() { return &___player_6; }
	inline void set_player_6(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * value)
	{
		___player_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___player_6), (void*)value);
	}

	inline static int32_t get_offset_of_gameOver_7() { return static_cast<int32_t>(offsetof(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89, ___gameOver_7)); }
	inline bool get_gameOver_7() const { return ___gameOver_7; }
	inline bool* get_address_of_gameOver_7() { return &___gameOver_7; }
	inline void set_gameOver_7(bool value)
	{
		___gameOver_7 = value;
	}

	inline static int32_t get_offset_of_liveEnemy_8() { return static_cast<int32_t>(offsetof(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89, ___liveEnemy_8)); }
	inline List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * get_liveEnemy_8() const { return ___liveEnemy_8; }
	inline List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A ** get_address_of_liveEnemy_8() { return &___liveEnemy_8; }
	inline void set_liveEnemy_8(List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * value)
	{
		___liveEnemy_8 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___liveEnemy_8), (void*)value);
	}

	inline static int32_t get_offset_of_doorExit_9() { return static_cast<int32_t>(offsetof(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89, ___doorExit_9)); }
	inline Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * get_doorExit_9() const { return ___doorExit_9; }
	inline Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 ** get_address_of_doorExit_9() { return &___doorExit_9; }
	inline void set_doorExit_9(Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * value)
	{
		___doorExit_9 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___doorExit_9), (void*)value);
	}
};

struct GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields
{
public:
	// System.String GameManager::HEALTH_NAME
	String_t* ___HEALTH_NAME_4;
	// GameManager GameManager::instance
	GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * ___instance_5;

public:
	inline static int32_t get_offset_of_HEALTH_NAME_4() { return static_cast<int32_t>(offsetof(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields, ___HEALTH_NAME_4)); }
	inline String_t* get_HEALTH_NAME_4() const { return ___HEALTH_NAME_4; }
	inline String_t** get_address_of_HEALTH_NAME_4() { return &___HEALTH_NAME_4; }
	inline void set_HEALTH_NAME_4(String_t* value)
	{
		___HEALTH_NAME_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___HEALTH_NAME_4), (void*)value);
	}

	inline static int32_t get_offset_of_instance_5() { return static_cast<int32_t>(offsetof(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields, ___instance_5)); }
	inline GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * get_instance_5() const { return ___instance_5; }
	inline GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 ** get_address_of_instance_5() { return &___instance_5; }
	inline void set_instance_5(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * value)
	{
		___instance_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___instance_5), (void*)value);
	}
};


// HitPoint
struct  HitPoint_tF69A6E412F64826CB64FF60F3547291915F7E775  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// System.Boolean HitPoint::bombAvilable
	bool ___bombAvilable_4;
	// System.Int32 HitPoint::dir
	int32_t ___dir_5;

public:
	inline static int32_t get_offset_of_bombAvilable_4() { return static_cast<int32_t>(offsetof(HitPoint_tF69A6E412F64826CB64FF60F3547291915F7E775, ___bombAvilable_4)); }
	inline bool get_bombAvilable_4() const { return ___bombAvilable_4; }
	inline bool* get_address_of_bombAvilable_4() { return &___bombAvilable_4; }
	inline void set_bombAvilable_4(bool value)
	{
		___bombAvilable_4 = value;
	}

	inline static int32_t get_offset_of_dir_5() { return static_cast<int32_t>(offsetof(HitPoint_tF69A6E412F64826CB64FF60F3547291915F7E775, ___dir_5)); }
	inline int32_t get_dir_5() const { return ___dir_5; }
	inline int32_t* get_address_of_dir_5() { return &___dir_5; }
	inline void set_dir_5(int32_t value)
	{
		___dir_5 = value;
	}
};


// Joystick
struct  Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// System.Single Joystick::handleRange
	float ___handleRange_4;
	// System.Single Joystick::deadZone
	float ___deadZone_5;
	// AxisOptions Joystick::axisOptions
	int32_t ___axisOptions_6;
	// System.Boolean Joystick::snapX
	bool ___snapX_7;
	// System.Boolean Joystick::snapY
	bool ___snapY_8;
	// UnityEngine.RectTransform Joystick::background
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___background_9;
	// UnityEngine.RectTransform Joystick::handle
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___handle_10;
	// UnityEngine.RectTransform Joystick::baseRect
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___baseRect_11;
	// UnityEngine.Canvas Joystick::canvas
	Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * ___canvas_12;
	// UnityEngine.Camera Joystick::cam
	Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * ___cam_13;
	// UnityEngine.Vector2 Joystick::input
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___input_14;

public:
	inline static int32_t get_offset_of_handleRange_4() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___handleRange_4)); }
	inline float get_handleRange_4() const { return ___handleRange_4; }
	inline float* get_address_of_handleRange_4() { return &___handleRange_4; }
	inline void set_handleRange_4(float value)
	{
		___handleRange_4 = value;
	}

	inline static int32_t get_offset_of_deadZone_5() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___deadZone_5)); }
	inline float get_deadZone_5() const { return ___deadZone_5; }
	inline float* get_address_of_deadZone_5() { return &___deadZone_5; }
	inline void set_deadZone_5(float value)
	{
		___deadZone_5 = value;
	}

	inline static int32_t get_offset_of_axisOptions_6() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___axisOptions_6)); }
	inline int32_t get_axisOptions_6() const { return ___axisOptions_6; }
	inline int32_t* get_address_of_axisOptions_6() { return &___axisOptions_6; }
	inline void set_axisOptions_6(int32_t value)
	{
		___axisOptions_6 = value;
	}

	inline static int32_t get_offset_of_snapX_7() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___snapX_7)); }
	inline bool get_snapX_7() const { return ___snapX_7; }
	inline bool* get_address_of_snapX_7() { return &___snapX_7; }
	inline void set_snapX_7(bool value)
	{
		___snapX_7 = value;
	}

	inline static int32_t get_offset_of_snapY_8() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___snapY_8)); }
	inline bool get_snapY_8() const { return ___snapY_8; }
	inline bool* get_address_of_snapY_8() { return &___snapY_8; }
	inline void set_snapY_8(bool value)
	{
		___snapY_8 = value;
	}

	inline static int32_t get_offset_of_background_9() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___background_9)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_background_9() const { return ___background_9; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_background_9() { return &___background_9; }
	inline void set_background_9(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___background_9 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___background_9), (void*)value);
	}

	inline static int32_t get_offset_of_handle_10() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___handle_10)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_handle_10() const { return ___handle_10; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_handle_10() { return &___handle_10; }
	inline void set_handle_10(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___handle_10 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___handle_10), (void*)value);
	}

	inline static int32_t get_offset_of_baseRect_11() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___baseRect_11)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_baseRect_11() const { return ___baseRect_11; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_baseRect_11() { return &___baseRect_11; }
	inline void set_baseRect_11(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___baseRect_11 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___baseRect_11), (void*)value);
	}

	inline static int32_t get_offset_of_canvas_12() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___canvas_12)); }
	inline Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * get_canvas_12() const { return ___canvas_12; }
	inline Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 ** get_address_of_canvas_12() { return &___canvas_12; }
	inline void set_canvas_12(Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * value)
	{
		___canvas_12 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___canvas_12), (void*)value);
	}

	inline static int32_t get_offset_of_cam_13() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___cam_13)); }
	inline Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * get_cam_13() const { return ___cam_13; }
	inline Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 ** get_address_of_cam_13() { return &___cam_13; }
	inline void set_cam_13(Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * value)
	{
		___cam_13 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___cam_13), (void*)value);
	}

	inline static int32_t get_offset_of_input_14() { return static_cast<int32_t>(offsetof(Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153, ___input_14)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_input_14() const { return ___input_14; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_input_14() { return &___input_14; }
	inline void set_input_14(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___input_14 = value;
	}
};


// JoystickPlayerExample
struct  JoystickPlayerExample_tC21BF4F29E220888E49AD1C28ED50EA82E0C583B  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// System.Single JoystickPlayerExample::speed
	float ___speed_4;
	// VariableJoystick JoystickPlayerExample::variableJoystick
	VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * ___variableJoystick_5;
	// UnityEngine.Rigidbody JoystickPlayerExample::rb
	Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5 * ___rb_6;

public:
	inline static int32_t get_offset_of_speed_4() { return static_cast<int32_t>(offsetof(JoystickPlayerExample_tC21BF4F29E220888E49AD1C28ED50EA82E0C583B, ___speed_4)); }
	inline float get_speed_4() const { return ___speed_4; }
	inline float* get_address_of_speed_4() { return &___speed_4; }
	inline void set_speed_4(float value)
	{
		___speed_4 = value;
	}

	inline static int32_t get_offset_of_variableJoystick_5() { return static_cast<int32_t>(offsetof(JoystickPlayerExample_tC21BF4F29E220888E49AD1C28ED50EA82E0C583B, ___variableJoystick_5)); }
	inline VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * get_variableJoystick_5() const { return ___variableJoystick_5; }
	inline VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 ** get_address_of_variableJoystick_5() { return &___variableJoystick_5; }
	inline void set_variableJoystick_5(VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * value)
	{
		___variableJoystick_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___variableJoystick_5), (void*)value);
	}

	inline static int32_t get_offset_of_rb_6() { return static_cast<int32_t>(offsetof(JoystickPlayerExample_tC21BF4F29E220888E49AD1C28ED50EA82E0C583B, ___rb_6)); }
	inline Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5 * get_rb_6() const { return ___rb_6; }
	inline Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5 ** get_address_of_rb_6() { return &___rb_6; }
	inline void set_rb_6(Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5 * value)
	{
		___rb_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___rb_6), (void*)value);
	}
};


// JoystickSetterExample
struct  JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// VariableJoystick JoystickSetterExample::variableJoystick
	VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * ___variableJoystick_4;
	// UnityEngine.UI.Text JoystickSetterExample::valueText
	Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030 * ___valueText_5;
	// UnityEngine.UI.Image JoystickSetterExample::background
	Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * ___background_6;
	// UnityEngine.Sprite[] JoystickSetterExample::axisSprites
	SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7* ___axisSprites_7;

public:
	inline static int32_t get_offset_of_variableJoystick_4() { return static_cast<int32_t>(offsetof(JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435, ___variableJoystick_4)); }
	inline VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * get_variableJoystick_4() const { return ___variableJoystick_4; }
	inline VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 ** get_address_of_variableJoystick_4() { return &___variableJoystick_4; }
	inline void set_variableJoystick_4(VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * value)
	{
		___variableJoystick_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___variableJoystick_4), (void*)value);
	}

	inline static int32_t get_offset_of_valueText_5() { return static_cast<int32_t>(offsetof(JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435, ___valueText_5)); }
	inline Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030 * get_valueText_5() const { return ___valueText_5; }
	inline Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030 ** get_address_of_valueText_5() { return &___valueText_5; }
	inline void set_valueText_5(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030 * value)
	{
		___valueText_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___valueText_5), (void*)value);
	}

	inline static int32_t get_offset_of_background_6() { return static_cast<int32_t>(offsetof(JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435, ___background_6)); }
	inline Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * get_background_6() const { return ___background_6; }
	inline Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E ** get_address_of_background_6() { return &___background_6; }
	inline void set_background_6(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * value)
	{
		___background_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___background_6), (void*)value);
	}

	inline static int32_t get_offset_of_axisSprites_7() { return static_cast<int32_t>(offsetof(JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435, ___axisSprites_7)); }
	inline SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7* get_axisSprites_7() const { return ___axisSprites_7; }
	inline SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7** get_address_of_axisSprites_7() { return &___axisSprites_7; }
	inline void set_axisSprites_7(SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7* value)
	{
		___axisSprites_7 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___axisSprites_7), (void*)value);
	}
};


// JumpFX
struct  JumpFX_t077C76BEDFE7B2C69067FB2FA0A32FFC1BE03902  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:

public:
};


// LandFX
struct  LandFX_t0B2698938110490929788E8E0F39A5EE7F7287D5  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:

public:
};


// PlayerAnimation
struct  PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// UnityEngine.Animator PlayerAnimation::anim
	Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * ___anim_4;
	// UnityEngine.Rigidbody2D PlayerAnimation::rb
	Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * ___rb_5;
	// PlayerController PlayerAnimation::controller
	PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * ___controller_6;

public:
	inline static int32_t get_offset_of_anim_4() { return static_cast<int32_t>(offsetof(PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD, ___anim_4)); }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * get_anim_4() const { return ___anim_4; }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A ** get_address_of_anim_4() { return &___anim_4; }
	inline void set_anim_4(Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * value)
	{
		___anim_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___anim_4), (void*)value);
	}

	inline static int32_t get_offset_of_rb_5() { return static_cast<int32_t>(offsetof(PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD, ___rb_5)); }
	inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * get_rb_5() const { return ___rb_5; }
	inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE ** get_address_of_rb_5() { return &___rb_5; }
	inline void set_rb_5(Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * value)
	{
		___rb_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___rb_5), (void*)value);
	}

	inline static int32_t get_offset_of_controller_6() { return static_cast<int32_t>(offsetof(PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD, ___controller_6)); }
	inline PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * get_controller_6() const { return ___controller_6; }
	inline PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 ** get_address_of_controller_6() { return &___controller_6; }
	inline void set_controller_6(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * value)
	{
		___controller_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___controller_6), (void*)value);
	}
};


// PlayerController
struct  PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// UnityEngine.Rigidbody2D PlayerController::rb
	Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * ___rb_4;
	// UnityEngine.Animator PlayerController::anim
	Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * ___anim_5;
	// FixedJoystick PlayerController::joystick
	FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * ___joystick_6;
	// System.Single PlayerController::speed
	float ___speed_7;
	// System.Single PlayerController::jumpForce
	float ___jumpForce_8;
	// UnityEngine.Transform PlayerController::groundCheck
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___groundCheck_9;
	// System.Single PlayerController::checkRadius
	float ___checkRadius_10;
	// UnityEngine.LayerMask PlayerController::groundLayer
	LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  ___groundLayer_11;
	// System.Boolean PlayerController::isGround
	bool ___isGround_12;
	// System.Boolean PlayerController::isJump
	bool ___isJump_13;
	// System.Boolean PlayerController::canJump
	bool ___canJump_14;
	// UnityEngine.GameObject PlayerController::gameObjectJump
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___gameObjectJump_15;
	// UnityEngine.GameObject PlayerController::gameObjectLand
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___gameObjectLand_16;
	// UnityEngine.GameObject PlayerController::bombObject
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___bombObject_17;
	// System.Single PlayerController::nextAttack
	float ___nextAttack_18;
	// System.Single PlayerController::attackRate
	float ___attackRate_19;
	// System.Single PlayerController::health
	float ___health_20;
	// System.Boolean PlayerController::isDead
	bool ___isDead_21;
	// System.Collections.Generic.List`1<UnityEngine.Transform> PlayerController::bombs
	List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * ___bombs_22;

public:
	inline static int32_t get_offset_of_rb_4() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___rb_4)); }
	inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * get_rb_4() const { return ___rb_4; }
	inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE ** get_address_of_rb_4() { return &___rb_4; }
	inline void set_rb_4(Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * value)
	{
		___rb_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___rb_4), (void*)value);
	}

	inline static int32_t get_offset_of_anim_5() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___anim_5)); }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * get_anim_5() const { return ___anim_5; }
	inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A ** get_address_of_anim_5() { return &___anim_5; }
	inline void set_anim_5(Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * value)
	{
		___anim_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___anim_5), (void*)value);
	}

	inline static int32_t get_offset_of_joystick_6() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___joystick_6)); }
	inline FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * get_joystick_6() const { return ___joystick_6; }
	inline FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 ** get_address_of_joystick_6() { return &___joystick_6; }
	inline void set_joystick_6(FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * value)
	{
		___joystick_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___joystick_6), (void*)value);
	}

	inline static int32_t get_offset_of_speed_7() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___speed_7)); }
	inline float get_speed_7() const { return ___speed_7; }
	inline float* get_address_of_speed_7() { return &___speed_7; }
	inline void set_speed_7(float value)
	{
		___speed_7 = value;
	}

	inline static int32_t get_offset_of_jumpForce_8() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___jumpForce_8)); }
	inline float get_jumpForce_8() const { return ___jumpForce_8; }
	inline float* get_address_of_jumpForce_8() { return &___jumpForce_8; }
	inline void set_jumpForce_8(float value)
	{
		___jumpForce_8 = value;
	}

	inline static int32_t get_offset_of_groundCheck_9() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___groundCheck_9)); }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * get_groundCheck_9() const { return ___groundCheck_9; }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA ** get_address_of_groundCheck_9() { return &___groundCheck_9; }
	inline void set_groundCheck_9(Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * value)
	{
		___groundCheck_9 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___groundCheck_9), (void*)value);
	}

	inline static int32_t get_offset_of_checkRadius_10() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___checkRadius_10)); }
	inline float get_checkRadius_10() const { return ___checkRadius_10; }
	inline float* get_address_of_checkRadius_10() { return &___checkRadius_10; }
	inline void set_checkRadius_10(float value)
	{
		___checkRadius_10 = value;
	}

	inline static int32_t get_offset_of_groundLayer_11() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___groundLayer_11)); }
	inline LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  get_groundLayer_11() const { return ___groundLayer_11; }
	inline LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0 * get_address_of_groundLayer_11() { return &___groundLayer_11; }
	inline void set_groundLayer_11(LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  value)
	{
		___groundLayer_11 = value;
	}

	inline static int32_t get_offset_of_isGround_12() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___isGround_12)); }
	inline bool get_isGround_12() const { return ___isGround_12; }
	inline bool* get_address_of_isGround_12() { return &___isGround_12; }
	inline void set_isGround_12(bool value)
	{
		___isGround_12 = value;
	}

	inline static int32_t get_offset_of_isJump_13() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___isJump_13)); }
	inline bool get_isJump_13() const { return ___isJump_13; }
	inline bool* get_address_of_isJump_13() { return &___isJump_13; }
	inline void set_isJump_13(bool value)
	{
		___isJump_13 = value;
	}

	inline static int32_t get_offset_of_canJump_14() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___canJump_14)); }
	inline bool get_canJump_14() const { return ___canJump_14; }
	inline bool* get_address_of_canJump_14() { return &___canJump_14; }
	inline void set_canJump_14(bool value)
	{
		___canJump_14 = value;
	}

	inline static int32_t get_offset_of_gameObjectJump_15() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___gameObjectJump_15)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_gameObjectJump_15() const { return ___gameObjectJump_15; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_gameObjectJump_15() { return &___gameObjectJump_15; }
	inline void set_gameObjectJump_15(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___gameObjectJump_15 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___gameObjectJump_15), (void*)value);
	}

	inline static int32_t get_offset_of_gameObjectLand_16() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___gameObjectLand_16)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_gameObjectLand_16() const { return ___gameObjectLand_16; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_gameObjectLand_16() { return &___gameObjectLand_16; }
	inline void set_gameObjectLand_16(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___gameObjectLand_16 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___gameObjectLand_16), (void*)value);
	}

	inline static int32_t get_offset_of_bombObject_17() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___bombObject_17)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_bombObject_17() const { return ___bombObject_17; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_bombObject_17() { return &___bombObject_17; }
	inline void set_bombObject_17(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___bombObject_17 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___bombObject_17), (void*)value);
	}

	inline static int32_t get_offset_of_nextAttack_18() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___nextAttack_18)); }
	inline float get_nextAttack_18() const { return ___nextAttack_18; }
	inline float* get_address_of_nextAttack_18() { return &___nextAttack_18; }
	inline void set_nextAttack_18(float value)
	{
		___nextAttack_18 = value;
	}

	inline static int32_t get_offset_of_attackRate_19() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___attackRate_19)); }
	inline float get_attackRate_19() const { return ___attackRate_19; }
	inline float* get_address_of_attackRate_19() { return &___attackRate_19; }
	inline void set_attackRate_19(float value)
	{
		___attackRate_19 = value;
	}

	inline static int32_t get_offset_of_health_20() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___health_20)); }
	inline float get_health_20() const { return ___health_20; }
	inline float* get_address_of_health_20() { return &___health_20; }
	inline void set_health_20(float value)
	{
		___health_20 = value;
	}

	inline static int32_t get_offset_of_isDead_21() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___isDead_21)); }
	inline bool get_isDead_21() const { return ___isDead_21; }
	inline bool* get_address_of_isDead_21() { return &___isDead_21; }
	inline void set_isDead_21(bool value)
	{
		___isDead_21 = value;
	}

	inline static int32_t get_offset_of_bombs_22() { return static_cast<int32_t>(offsetof(PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85, ___bombs_22)); }
	inline List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * get_bombs_22() const { return ___bombs_22; }
	inline List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE ** get_address_of_bombs_22() { return &___bombs_22; }
	inline void set_bombs_22(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * value)
	{
		___bombs_22 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___bombs_22), (void*)value);
	}
};


// UIManager
struct  UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:
	// UnityEngine.GameObject UIManager::healthBar
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___healthBar_5;
	// UnityEngine.GameObject UIManager::pauseMenu
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___pauseMenu_6;
	// UnityEngine.GameObject UIManager::gameOverPanel
	GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___gameOverPanel_7;
	// UnityEngine.UI.Slider UIManager::bossHealthBar
	Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 * ___bossHealthBar_8;

public:
	inline static int32_t get_offset_of_healthBar_5() { return static_cast<int32_t>(offsetof(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C, ___healthBar_5)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_healthBar_5() const { return ___healthBar_5; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_healthBar_5() { return &___healthBar_5; }
	inline void set_healthBar_5(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___healthBar_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___healthBar_5), (void*)value);
	}

	inline static int32_t get_offset_of_pauseMenu_6() { return static_cast<int32_t>(offsetof(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C, ___pauseMenu_6)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_pauseMenu_6() const { return ___pauseMenu_6; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_pauseMenu_6() { return &___pauseMenu_6; }
	inline void set_pauseMenu_6(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___pauseMenu_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___pauseMenu_6), (void*)value);
	}

	inline static int32_t get_offset_of_gameOverPanel_7() { return static_cast<int32_t>(offsetof(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C, ___gameOverPanel_7)); }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * get_gameOverPanel_7() const { return ___gameOverPanel_7; }
	inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F ** get_address_of_gameOverPanel_7() { return &___gameOverPanel_7; }
	inline void set_gameOverPanel_7(GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * value)
	{
		___gameOverPanel_7 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___gameOverPanel_7), (void*)value);
	}

	inline static int32_t get_offset_of_bossHealthBar_8() { return static_cast<int32_t>(offsetof(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C, ___bossHealthBar_8)); }
	inline Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 * get_bossHealthBar_8() const { return ___bossHealthBar_8; }
	inline Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 ** get_address_of_bossHealthBar_8() { return &___bossHealthBar_8; }
	inline void set_bossHealthBar_8(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 * value)
	{
		___bossHealthBar_8 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___bossHealthBar_8), (void*)value);
	}
};

struct UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields
{
public:
	// UIManager UIManager::instance
	UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * ___instance_4;

public:
	inline static int32_t get_offset_of_instance_4() { return static_cast<int32_t>(offsetof(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields, ___instance_4)); }
	inline UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * get_instance_4() const { return ___instance_4; }
	inline UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C ** get_address_of_instance_4() { return &___instance_4; }
	inline void set_instance_4(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * value)
	{
		___instance_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___instance_4), (void*)value);
	}
};


// UnityEngine.BoxCollider2D
struct  BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87  : public Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379
{
public:

public:
};


// UnityEngine.EventSystems.UIBehaviour
struct  UIBehaviour_t3C3C339CD5677BA7FC27C352FED8B78052A3FE70  : public MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429
{
public:

public:
};


// BaldPirate
struct  BaldPirate_tFDAA12DAAC29E182FB9209202DB889303C1D9C6E  : public Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6
{
public:

public:
};


// BigGuy
struct  BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8  : public Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6
{
public:
	// UnityEngine.Transform BigGuy::pickPoint
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___pickPoint_23;
	// System.Boolean BigGuy::hasBomb
	bool ___hasBomb_24;
	// PickUpState BigGuy::pickUpState
	PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * ___pickUpState_25;
	// Bomb BigGuy::pickUpBomp
	Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * ___pickUpBomp_26;

public:
	inline static int32_t get_offset_of_pickPoint_23() { return static_cast<int32_t>(offsetof(BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8, ___pickPoint_23)); }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * get_pickPoint_23() const { return ___pickPoint_23; }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA ** get_address_of_pickPoint_23() { return &___pickPoint_23; }
	inline void set_pickPoint_23(Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * value)
	{
		___pickPoint_23 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___pickPoint_23), (void*)value);
	}

	inline static int32_t get_offset_of_hasBomb_24() { return static_cast<int32_t>(offsetof(BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8, ___hasBomb_24)); }
	inline bool get_hasBomb_24() const { return ___hasBomb_24; }
	inline bool* get_address_of_hasBomb_24() { return &___hasBomb_24; }
	inline void set_hasBomb_24(bool value)
	{
		___hasBomb_24 = value;
	}

	inline static int32_t get_offset_of_pickUpState_25() { return static_cast<int32_t>(offsetof(BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8, ___pickUpState_25)); }
	inline PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * get_pickUpState_25() const { return ___pickUpState_25; }
	inline PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B ** get_address_of_pickUpState_25() { return &___pickUpState_25; }
	inline void set_pickUpState_25(PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * value)
	{
		___pickUpState_25 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___pickUpState_25), (void*)value);
	}

	inline static int32_t get_offset_of_pickUpBomp_26() { return static_cast<int32_t>(offsetof(BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8, ___pickUpBomp_26)); }
	inline Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * get_pickUpBomp_26() const { return ___pickUpBomp_26; }
	inline Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 ** get_address_of_pickUpBomp_26() { return &___pickUpBomp_26; }
	inline void set_pickUpBomp_26(Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * value)
	{
		___pickUpBomp_26 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___pickUpBomp_26), (void*)value);
	}
};


// Captain
struct  Captain_t1F5D011033A017D26E7A27822CC00CC4059C7F61  : public Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6
{
public:
	// UnityEngine.SpriteRenderer Captain::spriteRenderer
	SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * ___spriteRenderer_23;

public:
	inline static int32_t get_offset_of_spriteRenderer_23() { return static_cast<int32_t>(offsetof(Captain_t1F5D011033A017D26E7A27822CC00CC4059C7F61, ___spriteRenderer_23)); }
	inline SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * get_spriteRenderer_23() const { return ___spriteRenderer_23; }
	inline SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F ** get_address_of_spriteRenderer_23() { return &___spriteRenderer_23; }
	inline void set_spriteRenderer_23(SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * value)
	{
		___spriteRenderer_23 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___spriteRenderer_23), (void*)value);
	}
};


// Cucumber
struct  Cucumber_t6A12FD6C9556AB3D9546BEAE41ADC29CFD9E7046  : public Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6
{
public:

public:
};


// DynamicJoystick
struct  DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3  : public Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153
{
public:
	// System.Single DynamicJoystick::moveThreshold
	float ___moveThreshold_15;

public:
	inline static int32_t get_offset_of_moveThreshold_15() { return static_cast<int32_t>(offsetof(DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3, ___moveThreshold_15)); }
	inline float get_moveThreshold_15() const { return ___moveThreshold_15; }
	inline float* get_address_of_moveThreshold_15() { return &___moveThreshold_15; }
	inline void set_moveThreshold_15(float value)
	{
		___moveThreshold_15 = value;
	}
};


// FixedJoystick
struct  FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909  : public Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153
{
public:

public:
};


// FloatingJoystick
struct  FloatingJoystick_tBA7C79E5FC21EE9F117E0583A6A5FD38EFF5F8FE  : public Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153
{
public:

public:
};


// UnityEngine.UI.Graphic
struct  Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8  : public UIBehaviour_t3C3C339CD5677BA7FC27C352FED8B78052A3FE70
{
public:
	// UnityEngine.Material UnityEngine.UI.Graphic::m_Material
	Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * ___m_Material_6;
	// UnityEngine.Color UnityEngine.UI.Graphic::m_Color
	Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  ___m_Color_7;
	// System.Boolean UnityEngine.UI.Graphic::m_SkipLayoutUpdate
	bool ___m_SkipLayoutUpdate_8;
	// System.Boolean UnityEngine.UI.Graphic::m_SkipMaterialUpdate
	bool ___m_SkipMaterialUpdate_9;
	// System.Boolean UnityEngine.UI.Graphic::m_RaycastTarget
	bool ___m_RaycastTarget_10;
	// UnityEngine.RectTransform UnityEngine.UI.Graphic::m_RectTransform
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___m_RectTransform_11;
	// UnityEngine.CanvasRenderer UnityEngine.UI.Graphic::m_CanvasRenderer
	CanvasRenderer_tB4D9C9FE77FD5C9C4546FC022D6E956960BC2B72 * ___m_CanvasRenderer_12;
	// UnityEngine.Canvas UnityEngine.UI.Graphic::m_Canvas
	Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * ___m_Canvas_13;
	// System.Boolean UnityEngine.UI.Graphic::m_VertsDirty
	bool ___m_VertsDirty_14;
	// System.Boolean UnityEngine.UI.Graphic::m_MaterialDirty
	bool ___m_MaterialDirty_15;
	// UnityEngine.Events.UnityAction UnityEngine.UI.Graphic::m_OnDirtyLayoutCallback
	UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * ___m_OnDirtyLayoutCallback_16;
	// UnityEngine.Events.UnityAction UnityEngine.UI.Graphic::m_OnDirtyVertsCallback
	UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * ___m_OnDirtyVertsCallback_17;
	// UnityEngine.Events.UnityAction UnityEngine.UI.Graphic::m_OnDirtyMaterialCallback
	UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * ___m_OnDirtyMaterialCallback_18;
	// UnityEngine.Mesh UnityEngine.UI.Graphic::m_CachedMesh
	Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C * ___m_CachedMesh_21;
	// UnityEngine.Vector2[] UnityEngine.UI.Graphic::m_CachedUvs
	Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* ___m_CachedUvs_22;
	// UnityEngine.UI.CoroutineTween.TweenRunner`1<UnityEngine.UI.CoroutineTween.ColorTween> UnityEngine.UI.Graphic::m_ColorTweenRunner
	TweenRunner_1_t56CEB168ADE3739A1BDDBF258FDC759DF8927172 * ___m_ColorTweenRunner_23;
	// System.Boolean UnityEngine.UI.Graphic::<useLegacyMeshGeneration>k__BackingField
	bool ___U3CuseLegacyMeshGenerationU3Ek__BackingField_24;

public:
	inline static int32_t get_offset_of_m_Material_6() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_Material_6)); }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * get_m_Material_6() const { return ___m_Material_6; }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 ** get_address_of_m_Material_6() { return &___m_Material_6; }
	inline void set_m_Material_6(Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * value)
	{
		___m_Material_6 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_Material_6), (void*)value);
	}

	inline static int32_t get_offset_of_m_Color_7() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_Color_7)); }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  get_m_Color_7() const { return ___m_Color_7; }
	inline Color_t119BCA590009762C7223FDD3AF9706653AC84ED2 * get_address_of_m_Color_7() { return &___m_Color_7; }
	inline void set_m_Color_7(Color_t119BCA590009762C7223FDD3AF9706653AC84ED2  value)
	{
		___m_Color_7 = value;
	}

	inline static int32_t get_offset_of_m_SkipLayoutUpdate_8() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_SkipLayoutUpdate_8)); }
	inline bool get_m_SkipLayoutUpdate_8() const { return ___m_SkipLayoutUpdate_8; }
	inline bool* get_address_of_m_SkipLayoutUpdate_8() { return &___m_SkipLayoutUpdate_8; }
	inline void set_m_SkipLayoutUpdate_8(bool value)
	{
		___m_SkipLayoutUpdate_8 = value;
	}

	inline static int32_t get_offset_of_m_SkipMaterialUpdate_9() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_SkipMaterialUpdate_9)); }
	inline bool get_m_SkipMaterialUpdate_9() const { return ___m_SkipMaterialUpdate_9; }
	inline bool* get_address_of_m_SkipMaterialUpdate_9() { return &___m_SkipMaterialUpdate_9; }
	inline void set_m_SkipMaterialUpdate_9(bool value)
	{
		___m_SkipMaterialUpdate_9 = value;
	}

	inline static int32_t get_offset_of_m_RaycastTarget_10() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_RaycastTarget_10)); }
	inline bool get_m_RaycastTarget_10() const { return ___m_RaycastTarget_10; }
	inline bool* get_address_of_m_RaycastTarget_10() { return &___m_RaycastTarget_10; }
	inline void set_m_RaycastTarget_10(bool value)
	{
		___m_RaycastTarget_10 = value;
	}

	inline static int32_t get_offset_of_m_RectTransform_11() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_RectTransform_11)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_m_RectTransform_11() const { return ___m_RectTransform_11; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_m_RectTransform_11() { return &___m_RectTransform_11; }
	inline void set_m_RectTransform_11(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___m_RectTransform_11 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_RectTransform_11), (void*)value);
	}

	inline static int32_t get_offset_of_m_CanvasRenderer_12() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_CanvasRenderer_12)); }
	inline CanvasRenderer_tB4D9C9FE77FD5C9C4546FC022D6E956960BC2B72 * get_m_CanvasRenderer_12() const { return ___m_CanvasRenderer_12; }
	inline CanvasRenderer_tB4D9C9FE77FD5C9C4546FC022D6E956960BC2B72 ** get_address_of_m_CanvasRenderer_12() { return &___m_CanvasRenderer_12; }
	inline void set_m_CanvasRenderer_12(CanvasRenderer_tB4D9C9FE77FD5C9C4546FC022D6E956960BC2B72 * value)
	{
		___m_CanvasRenderer_12 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_CanvasRenderer_12), (void*)value);
	}

	inline static int32_t get_offset_of_m_Canvas_13() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_Canvas_13)); }
	inline Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * get_m_Canvas_13() const { return ___m_Canvas_13; }
	inline Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 ** get_address_of_m_Canvas_13() { return &___m_Canvas_13; }
	inline void set_m_Canvas_13(Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * value)
	{
		___m_Canvas_13 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_Canvas_13), (void*)value);
	}

	inline static int32_t get_offset_of_m_VertsDirty_14() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_VertsDirty_14)); }
	inline bool get_m_VertsDirty_14() const { return ___m_VertsDirty_14; }
	inline bool* get_address_of_m_VertsDirty_14() { return &___m_VertsDirty_14; }
	inline void set_m_VertsDirty_14(bool value)
	{
		___m_VertsDirty_14 = value;
	}

	inline static int32_t get_offset_of_m_MaterialDirty_15() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_MaterialDirty_15)); }
	inline bool get_m_MaterialDirty_15() const { return ___m_MaterialDirty_15; }
	inline bool* get_address_of_m_MaterialDirty_15() { return &___m_MaterialDirty_15; }
	inline void set_m_MaterialDirty_15(bool value)
	{
		___m_MaterialDirty_15 = value;
	}

	inline static int32_t get_offset_of_m_OnDirtyLayoutCallback_16() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_OnDirtyLayoutCallback_16)); }
	inline UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * get_m_OnDirtyLayoutCallback_16() const { return ___m_OnDirtyLayoutCallback_16; }
	inline UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 ** get_address_of_m_OnDirtyLayoutCallback_16() { return &___m_OnDirtyLayoutCallback_16; }
	inline void set_m_OnDirtyLayoutCallback_16(UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * value)
	{
		___m_OnDirtyLayoutCallback_16 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_OnDirtyLayoutCallback_16), (void*)value);
	}

	inline static int32_t get_offset_of_m_OnDirtyVertsCallback_17() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_OnDirtyVertsCallback_17)); }
	inline UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * get_m_OnDirtyVertsCallback_17() const { return ___m_OnDirtyVertsCallback_17; }
	inline UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 ** get_address_of_m_OnDirtyVertsCallback_17() { return &___m_OnDirtyVertsCallback_17; }
	inline void set_m_OnDirtyVertsCallback_17(UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * value)
	{
		___m_OnDirtyVertsCallback_17 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_OnDirtyVertsCallback_17), (void*)value);
	}

	inline static int32_t get_offset_of_m_OnDirtyMaterialCallback_18() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_OnDirtyMaterialCallback_18)); }
	inline UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * get_m_OnDirtyMaterialCallback_18() const { return ___m_OnDirtyMaterialCallback_18; }
	inline UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 ** get_address_of_m_OnDirtyMaterialCallback_18() { return &___m_OnDirtyMaterialCallback_18; }
	inline void set_m_OnDirtyMaterialCallback_18(UnityAction_tD19B26F1B2C048E38FD5801A33573BE01064CAF4 * value)
	{
		___m_OnDirtyMaterialCallback_18 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_OnDirtyMaterialCallback_18), (void*)value);
	}

	inline static int32_t get_offset_of_m_CachedMesh_21() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_CachedMesh_21)); }
	inline Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C * get_m_CachedMesh_21() const { return ___m_CachedMesh_21; }
	inline Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C ** get_address_of_m_CachedMesh_21() { return &___m_CachedMesh_21; }
	inline void set_m_CachedMesh_21(Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C * value)
	{
		___m_CachedMesh_21 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_CachedMesh_21), (void*)value);
	}

	inline static int32_t get_offset_of_m_CachedUvs_22() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_CachedUvs_22)); }
	inline Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* get_m_CachedUvs_22() const { return ___m_CachedUvs_22; }
	inline Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6** get_address_of_m_CachedUvs_22() { return &___m_CachedUvs_22; }
	inline void set_m_CachedUvs_22(Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* value)
	{
		___m_CachedUvs_22 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_CachedUvs_22), (void*)value);
	}

	inline static int32_t get_offset_of_m_ColorTweenRunner_23() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___m_ColorTweenRunner_23)); }
	inline TweenRunner_1_t56CEB168ADE3739A1BDDBF258FDC759DF8927172 * get_m_ColorTweenRunner_23() const { return ___m_ColorTweenRunner_23; }
	inline TweenRunner_1_t56CEB168ADE3739A1BDDBF258FDC759DF8927172 ** get_address_of_m_ColorTweenRunner_23() { return &___m_ColorTweenRunner_23; }
	inline void set_m_ColorTweenRunner_23(TweenRunner_1_t56CEB168ADE3739A1BDDBF258FDC759DF8927172 * value)
	{
		___m_ColorTweenRunner_23 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_ColorTweenRunner_23), (void*)value);
	}

	inline static int32_t get_offset_of_U3CuseLegacyMeshGenerationU3Ek__BackingField_24() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8, ___U3CuseLegacyMeshGenerationU3Ek__BackingField_24)); }
	inline bool get_U3CuseLegacyMeshGenerationU3Ek__BackingField_24() const { return ___U3CuseLegacyMeshGenerationU3Ek__BackingField_24; }
	inline bool* get_address_of_U3CuseLegacyMeshGenerationU3Ek__BackingField_24() { return &___U3CuseLegacyMeshGenerationU3Ek__BackingField_24; }
	inline void set_U3CuseLegacyMeshGenerationU3Ek__BackingField_24(bool value)
	{
		___U3CuseLegacyMeshGenerationU3Ek__BackingField_24 = value;
	}
};

struct Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8_StaticFields
{
public:
	// UnityEngine.Material UnityEngine.UI.Graphic::s_DefaultUI
	Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * ___s_DefaultUI_4;
	// UnityEngine.Texture2D UnityEngine.UI.Graphic::s_WhiteTexture
	Texture2D_tBBF96AC337723E2EF156DF17E09D4379FD05DE1C * ___s_WhiteTexture_5;
	// UnityEngine.Mesh UnityEngine.UI.Graphic::s_Mesh
	Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C * ___s_Mesh_19;
	// UnityEngine.UI.VertexHelper UnityEngine.UI.Graphic::s_VertexHelper
	VertexHelper_t27373EA2CF0F5810EC8CF873D0A6D6C0B23DAC3F * ___s_VertexHelper_20;

public:
	inline static int32_t get_offset_of_s_DefaultUI_4() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8_StaticFields, ___s_DefaultUI_4)); }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * get_s_DefaultUI_4() const { return ___s_DefaultUI_4; }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 ** get_address_of_s_DefaultUI_4() { return &___s_DefaultUI_4; }
	inline void set_s_DefaultUI_4(Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * value)
	{
		___s_DefaultUI_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_DefaultUI_4), (void*)value);
	}

	inline static int32_t get_offset_of_s_WhiteTexture_5() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8_StaticFields, ___s_WhiteTexture_5)); }
	inline Texture2D_tBBF96AC337723E2EF156DF17E09D4379FD05DE1C * get_s_WhiteTexture_5() const { return ___s_WhiteTexture_5; }
	inline Texture2D_tBBF96AC337723E2EF156DF17E09D4379FD05DE1C ** get_address_of_s_WhiteTexture_5() { return &___s_WhiteTexture_5; }
	inline void set_s_WhiteTexture_5(Texture2D_tBBF96AC337723E2EF156DF17E09D4379FD05DE1C * value)
	{
		___s_WhiteTexture_5 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_WhiteTexture_5), (void*)value);
	}

	inline static int32_t get_offset_of_s_Mesh_19() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8_StaticFields, ___s_Mesh_19)); }
	inline Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C * get_s_Mesh_19() const { return ___s_Mesh_19; }
	inline Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C ** get_address_of_s_Mesh_19() { return &___s_Mesh_19; }
	inline void set_s_Mesh_19(Mesh_t6106B8D8E4C691321581AB0445552EC78B947B8C * value)
	{
		___s_Mesh_19 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_Mesh_19), (void*)value);
	}

	inline static int32_t get_offset_of_s_VertexHelper_20() { return static_cast<int32_t>(offsetof(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8_StaticFields, ___s_VertexHelper_20)); }
	inline VertexHelper_t27373EA2CF0F5810EC8CF873D0A6D6C0B23DAC3F * get_s_VertexHelper_20() const { return ___s_VertexHelper_20; }
	inline VertexHelper_t27373EA2CF0F5810EC8CF873D0A6D6C0B23DAC3F ** get_address_of_s_VertexHelper_20() { return &___s_VertexHelper_20; }
	inline void set_s_VertexHelper_20(VertexHelper_t27373EA2CF0F5810EC8CF873D0A6D6C0B23DAC3F * value)
	{
		___s_VertexHelper_20 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_VertexHelper_20), (void*)value);
	}
};


// UnityEngine.UI.Selectable
struct  Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A  : public UIBehaviour_t3C3C339CD5677BA7FC27C352FED8B78052A3FE70
{
public:
	// UnityEngine.UI.Navigation UnityEngine.UI.Selectable::m_Navigation
	Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07  ___m_Navigation_6;
	// UnityEngine.UI.Selectable_Transition UnityEngine.UI.Selectable::m_Transition
	int32_t ___m_Transition_7;
	// UnityEngine.UI.ColorBlock UnityEngine.UI.Selectable::m_Colors
	ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA  ___m_Colors_8;
	// UnityEngine.UI.SpriteState UnityEngine.UI.Selectable::m_SpriteState
	SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A  ___m_SpriteState_9;
	// UnityEngine.UI.AnimationTriggers UnityEngine.UI.Selectable::m_AnimationTriggers
	AnimationTriggers_t164EF8B310E294B7D0F6BF1A87376731EBD06DC5 * ___m_AnimationTriggers_10;
	// System.Boolean UnityEngine.UI.Selectable::m_Interactable
	bool ___m_Interactable_11;
	// UnityEngine.UI.Graphic UnityEngine.UI.Selectable::m_TargetGraphic
	Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8 * ___m_TargetGraphic_12;
	// System.Boolean UnityEngine.UI.Selectable::m_GroupsAllowInteraction
	bool ___m_GroupsAllowInteraction_13;
	// System.Int32 UnityEngine.UI.Selectable::m_CurrentIndex
	int32_t ___m_CurrentIndex_14;
	// System.Boolean UnityEngine.UI.Selectable::<isPointerInside>k__BackingField
	bool ___U3CisPointerInsideU3Ek__BackingField_15;
	// System.Boolean UnityEngine.UI.Selectable::<isPointerDown>k__BackingField
	bool ___U3CisPointerDownU3Ek__BackingField_16;
	// System.Boolean UnityEngine.UI.Selectable::<hasSelection>k__BackingField
	bool ___U3ChasSelectionU3Ek__BackingField_17;
	// System.Collections.Generic.List`1<UnityEngine.CanvasGroup> UnityEngine.UI.Selectable::m_CanvasGroupCache
	List_1_t053DAB6E2110E276A0339D73497193F464BC1F82 * ___m_CanvasGroupCache_18;

public:
	inline static int32_t get_offset_of_m_Navigation_6() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_Navigation_6)); }
	inline Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07  get_m_Navigation_6() const { return ___m_Navigation_6; }
	inline Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07 * get_address_of_m_Navigation_6() { return &___m_Navigation_6; }
	inline void set_m_Navigation_6(Navigation_t761250C05C09773B75F5E0D52DDCBBFE60288A07  value)
	{
		___m_Navigation_6 = value;
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_Navigation_6))->___m_SelectOnUp_1), (void*)NULL);
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_Navigation_6))->___m_SelectOnDown_2), (void*)NULL);
		#endif
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_Navigation_6))->___m_SelectOnLeft_3), (void*)NULL);
		#endif
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_Navigation_6))->___m_SelectOnRight_4), (void*)NULL);
		#endif
	}

	inline static int32_t get_offset_of_m_Transition_7() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_Transition_7)); }
	inline int32_t get_m_Transition_7() const { return ___m_Transition_7; }
	inline int32_t* get_address_of_m_Transition_7() { return &___m_Transition_7; }
	inline void set_m_Transition_7(int32_t value)
	{
		___m_Transition_7 = value;
	}

	inline static int32_t get_offset_of_m_Colors_8() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_Colors_8)); }
	inline ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA  get_m_Colors_8() const { return ___m_Colors_8; }
	inline ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA * get_address_of_m_Colors_8() { return &___m_Colors_8; }
	inline void set_m_Colors_8(ColorBlock_t93B54DF6E8D65D24CEA9726CA745E48C53E3B1EA  value)
	{
		___m_Colors_8 = value;
	}

	inline static int32_t get_offset_of_m_SpriteState_9() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_SpriteState_9)); }
	inline SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A  get_m_SpriteState_9() const { return ___m_SpriteState_9; }
	inline SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A * get_address_of_m_SpriteState_9() { return &___m_SpriteState_9; }
	inline void set_m_SpriteState_9(SpriteState_t58B9DD66A79CD69AB4CFC3AD0C41E45DC2192C0A  value)
	{
		___m_SpriteState_9 = value;
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_SpriteState_9))->___m_HighlightedSprite_0), (void*)NULL);
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_SpriteState_9))->___m_PressedSprite_1), (void*)NULL);
		#endif
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_SpriteState_9))->___m_SelectedSprite_2), (void*)NULL);
		#endif
		#if IL2CPP_ENABLE_STRICT_WRITE_BARRIERS
		Il2CppCodeGenWriteBarrier((void**)&(((&___m_SpriteState_9))->___m_DisabledSprite_3), (void*)NULL);
		#endif
	}

	inline static int32_t get_offset_of_m_AnimationTriggers_10() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_AnimationTriggers_10)); }
	inline AnimationTriggers_t164EF8B310E294B7D0F6BF1A87376731EBD06DC5 * get_m_AnimationTriggers_10() const { return ___m_AnimationTriggers_10; }
	inline AnimationTriggers_t164EF8B310E294B7D0F6BF1A87376731EBD06DC5 ** get_address_of_m_AnimationTriggers_10() { return &___m_AnimationTriggers_10; }
	inline void set_m_AnimationTriggers_10(AnimationTriggers_t164EF8B310E294B7D0F6BF1A87376731EBD06DC5 * value)
	{
		___m_AnimationTriggers_10 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_AnimationTriggers_10), (void*)value);
	}

	inline static int32_t get_offset_of_m_Interactable_11() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_Interactable_11)); }
	inline bool get_m_Interactable_11() const { return ___m_Interactable_11; }
	inline bool* get_address_of_m_Interactable_11() { return &___m_Interactable_11; }
	inline void set_m_Interactable_11(bool value)
	{
		___m_Interactable_11 = value;
	}

	inline static int32_t get_offset_of_m_TargetGraphic_12() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_TargetGraphic_12)); }
	inline Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8 * get_m_TargetGraphic_12() const { return ___m_TargetGraphic_12; }
	inline Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8 ** get_address_of_m_TargetGraphic_12() { return &___m_TargetGraphic_12; }
	inline void set_m_TargetGraphic_12(Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8 * value)
	{
		___m_TargetGraphic_12 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_TargetGraphic_12), (void*)value);
	}

	inline static int32_t get_offset_of_m_GroupsAllowInteraction_13() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_GroupsAllowInteraction_13)); }
	inline bool get_m_GroupsAllowInteraction_13() const { return ___m_GroupsAllowInteraction_13; }
	inline bool* get_address_of_m_GroupsAllowInteraction_13() { return &___m_GroupsAllowInteraction_13; }
	inline void set_m_GroupsAllowInteraction_13(bool value)
	{
		___m_GroupsAllowInteraction_13 = value;
	}

	inline static int32_t get_offset_of_m_CurrentIndex_14() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_CurrentIndex_14)); }
	inline int32_t get_m_CurrentIndex_14() const { return ___m_CurrentIndex_14; }
	inline int32_t* get_address_of_m_CurrentIndex_14() { return &___m_CurrentIndex_14; }
	inline void set_m_CurrentIndex_14(int32_t value)
	{
		___m_CurrentIndex_14 = value;
	}

	inline static int32_t get_offset_of_U3CisPointerInsideU3Ek__BackingField_15() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___U3CisPointerInsideU3Ek__BackingField_15)); }
	inline bool get_U3CisPointerInsideU3Ek__BackingField_15() const { return ___U3CisPointerInsideU3Ek__BackingField_15; }
	inline bool* get_address_of_U3CisPointerInsideU3Ek__BackingField_15() { return &___U3CisPointerInsideU3Ek__BackingField_15; }
	inline void set_U3CisPointerInsideU3Ek__BackingField_15(bool value)
	{
		___U3CisPointerInsideU3Ek__BackingField_15 = value;
	}

	inline static int32_t get_offset_of_U3CisPointerDownU3Ek__BackingField_16() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___U3CisPointerDownU3Ek__BackingField_16)); }
	inline bool get_U3CisPointerDownU3Ek__BackingField_16() const { return ___U3CisPointerDownU3Ek__BackingField_16; }
	inline bool* get_address_of_U3CisPointerDownU3Ek__BackingField_16() { return &___U3CisPointerDownU3Ek__BackingField_16; }
	inline void set_U3CisPointerDownU3Ek__BackingField_16(bool value)
	{
		___U3CisPointerDownU3Ek__BackingField_16 = value;
	}

	inline static int32_t get_offset_of_U3ChasSelectionU3Ek__BackingField_17() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___U3ChasSelectionU3Ek__BackingField_17)); }
	inline bool get_U3ChasSelectionU3Ek__BackingField_17() const { return ___U3ChasSelectionU3Ek__BackingField_17; }
	inline bool* get_address_of_U3ChasSelectionU3Ek__BackingField_17() { return &___U3ChasSelectionU3Ek__BackingField_17; }
	inline void set_U3ChasSelectionU3Ek__BackingField_17(bool value)
	{
		___U3ChasSelectionU3Ek__BackingField_17 = value;
	}

	inline static int32_t get_offset_of_m_CanvasGroupCache_18() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A, ___m_CanvasGroupCache_18)); }
	inline List_1_t053DAB6E2110E276A0339D73497193F464BC1F82 * get_m_CanvasGroupCache_18() const { return ___m_CanvasGroupCache_18; }
	inline List_1_t053DAB6E2110E276A0339D73497193F464BC1F82 ** get_address_of_m_CanvasGroupCache_18() { return &___m_CanvasGroupCache_18; }
	inline void set_m_CanvasGroupCache_18(List_1_t053DAB6E2110E276A0339D73497193F464BC1F82 * value)
	{
		___m_CanvasGroupCache_18 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_CanvasGroupCache_18), (void*)value);
	}
};

struct Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A_StaticFields
{
public:
	// UnityEngine.UI.Selectable[] UnityEngine.UI.Selectable::s_Selectables
	SelectableU5BU5D_t98F7C5A863B20CD5DBE49CE288038BA954C83F02* ___s_Selectables_4;
	// System.Int32 UnityEngine.UI.Selectable::s_SelectableCount
	int32_t ___s_SelectableCount_5;

public:
	inline static int32_t get_offset_of_s_Selectables_4() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A_StaticFields, ___s_Selectables_4)); }
	inline SelectableU5BU5D_t98F7C5A863B20CD5DBE49CE288038BA954C83F02* get_s_Selectables_4() const { return ___s_Selectables_4; }
	inline SelectableU5BU5D_t98F7C5A863B20CD5DBE49CE288038BA954C83F02** get_address_of_s_Selectables_4() { return &___s_Selectables_4; }
	inline void set_s_Selectables_4(SelectableU5BU5D_t98F7C5A863B20CD5DBE49CE288038BA954C83F02* value)
	{
		___s_Selectables_4 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_Selectables_4), (void*)value);
	}

	inline static int32_t get_offset_of_s_SelectableCount_5() { return static_cast<int32_t>(offsetof(Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A_StaticFields, ___s_SelectableCount_5)); }
	inline int32_t get_s_SelectableCount_5() const { return ___s_SelectableCount_5; }
	inline int32_t* get_address_of_s_SelectableCount_5() { return &___s_SelectableCount_5; }
	inline void set_s_SelectableCount_5(int32_t value)
	{
		___s_SelectableCount_5 = value;
	}
};


// VariableJoystick
struct  VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1  : public Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153
{
public:
	// System.Single VariableJoystick::moveThreshold
	float ___moveThreshold_15;
	// JoystickType VariableJoystick::joystickType
	int32_t ___joystickType_16;
	// UnityEngine.Vector2 VariableJoystick::fixedPosition
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___fixedPosition_17;

public:
	inline static int32_t get_offset_of_moveThreshold_15() { return static_cast<int32_t>(offsetof(VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1, ___moveThreshold_15)); }
	inline float get_moveThreshold_15() const { return ___moveThreshold_15; }
	inline float* get_address_of_moveThreshold_15() { return &___moveThreshold_15; }
	inline void set_moveThreshold_15(float value)
	{
		___moveThreshold_15 = value;
	}

	inline static int32_t get_offset_of_joystickType_16() { return static_cast<int32_t>(offsetof(VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1, ___joystickType_16)); }
	inline int32_t get_joystickType_16() const { return ___joystickType_16; }
	inline int32_t* get_address_of_joystickType_16() { return &___joystickType_16; }
	inline void set_joystickType_16(int32_t value)
	{
		___joystickType_16 = value;
	}

	inline static int32_t get_offset_of_fixedPosition_17() { return static_cast<int32_t>(offsetof(VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1, ___fixedPosition_17)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_fixedPosition_17() const { return ___fixedPosition_17; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_fixedPosition_17() { return &___fixedPosition_17; }
	inline void set_fixedPosition_17(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___fixedPosition_17 = value;
	}
};


// Whale
struct  Whale_t11A3C3495AC360DE58A5FE06BAAA3384761EA301  : public Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6
{
public:
	// System.Single Whale::scaleStep
	float ___scaleStep_23;
	// System.Single Whale::maxScale
	float ___maxScale_24;

public:
	inline static int32_t get_offset_of_scaleStep_23() { return static_cast<int32_t>(offsetof(Whale_t11A3C3495AC360DE58A5FE06BAAA3384761EA301, ___scaleStep_23)); }
	inline float get_scaleStep_23() const { return ___scaleStep_23; }
	inline float* get_address_of_scaleStep_23() { return &___scaleStep_23; }
	inline void set_scaleStep_23(float value)
	{
		___scaleStep_23 = value;
	}

	inline static int32_t get_offset_of_maxScale_24() { return static_cast<int32_t>(offsetof(Whale_t11A3C3495AC360DE58A5FE06BAAA3384761EA301, ___maxScale_24)); }
	inline float get_maxScale_24() const { return ___maxScale_24; }
	inline float* get_address_of_maxScale_24() { return &___maxScale_24; }
	inline void set_maxScale_24(float value)
	{
		___maxScale_24 = value;
	}
};


// UnityEngine.UI.MaskableGraphic
struct  MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F  : public Graphic_tBA2C3EF11D3DAEBB57F6879AB0BB4F8BD40D00D8
{
public:
	// System.Boolean UnityEngine.UI.MaskableGraphic::m_ShouldRecalculateStencil
	bool ___m_ShouldRecalculateStencil_25;
	// UnityEngine.Material UnityEngine.UI.MaskableGraphic::m_MaskMaterial
	Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * ___m_MaskMaterial_26;
	// UnityEngine.UI.RectMask2D UnityEngine.UI.MaskableGraphic::m_ParentMask
	RectMask2D_tF2CF19F2A4FE2D2FFC7E6F7809374757CA2F377B * ___m_ParentMask_27;
	// System.Boolean UnityEngine.UI.MaskableGraphic::m_Maskable
	bool ___m_Maskable_28;
	// System.Boolean UnityEngine.UI.MaskableGraphic::m_IsMaskingGraphic
	bool ___m_IsMaskingGraphic_29;
	// System.Boolean UnityEngine.UI.MaskableGraphic::m_IncludeForMasking
	bool ___m_IncludeForMasking_30;
	// UnityEngine.UI.MaskableGraphic_CullStateChangedEvent UnityEngine.UI.MaskableGraphic::m_OnCullStateChanged
	CullStateChangedEvent_t6BC3E87DBC04B585798460D55F56B86C23B62FE4 * ___m_OnCullStateChanged_31;
	// System.Boolean UnityEngine.UI.MaskableGraphic::m_ShouldRecalculate
	bool ___m_ShouldRecalculate_32;
	// System.Int32 UnityEngine.UI.MaskableGraphic::m_StencilValue
	int32_t ___m_StencilValue_33;
	// UnityEngine.Vector3[] UnityEngine.UI.MaskableGraphic::m_Corners
	Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* ___m_Corners_34;

public:
	inline static int32_t get_offset_of_m_ShouldRecalculateStencil_25() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_ShouldRecalculateStencil_25)); }
	inline bool get_m_ShouldRecalculateStencil_25() const { return ___m_ShouldRecalculateStencil_25; }
	inline bool* get_address_of_m_ShouldRecalculateStencil_25() { return &___m_ShouldRecalculateStencil_25; }
	inline void set_m_ShouldRecalculateStencil_25(bool value)
	{
		___m_ShouldRecalculateStencil_25 = value;
	}

	inline static int32_t get_offset_of_m_MaskMaterial_26() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_MaskMaterial_26)); }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * get_m_MaskMaterial_26() const { return ___m_MaskMaterial_26; }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 ** get_address_of_m_MaskMaterial_26() { return &___m_MaskMaterial_26; }
	inline void set_m_MaskMaterial_26(Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * value)
	{
		___m_MaskMaterial_26 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_MaskMaterial_26), (void*)value);
	}

	inline static int32_t get_offset_of_m_ParentMask_27() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_ParentMask_27)); }
	inline RectMask2D_tF2CF19F2A4FE2D2FFC7E6F7809374757CA2F377B * get_m_ParentMask_27() const { return ___m_ParentMask_27; }
	inline RectMask2D_tF2CF19F2A4FE2D2FFC7E6F7809374757CA2F377B ** get_address_of_m_ParentMask_27() { return &___m_ParentMask_27; }
	inline void set_m_ParentMask_27(RectMask2D_tF2CF19F2A4FE2D2FFC7E6F7809374757CA2F377B * value)
	{
		___m_ParentMask_27 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_ParentMask_27), (void*)value);
	}

	inline static int32_t get_offset_of_m_Maskable_28() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_Maskable_28)); }
	inline bool get_m_Maskable_28() const { return ___m_Maskable_28; }
	inline bool* get_address_of_m_Maskable_28() { return &___m_Maskable_28; }
	inline void set_m_Maskable_28(bool value)
	{
		___m_Maskable_28 = value;
	}

	inline static int32_t get_offset_of_m_IsMaskingGraphic_29() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_IsMaskingGraphic_29)); }
	inline bool get_m_IsMaskingGraphic_29() const { return ___m_IsMaskingGraphic_29; }
	inline bool* get_address_of_m_IsMaskingGraphic_29() { return &___m_IsMaskingGraphic_29; }
	inline void set_m_IsMaskingGraphic_29(bool value)
	{
		___m_IsMaskingGraphic_29 = value;
	}

	inline static int32_t get_offset_of_m_IncludeForMasking_30() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_IncludeForMasking_30)); }
	inline bool get_m_IncludeForMasking_30() const { return ___m_IncludeForMasking_30; }
	inline bool* get_address_of_m_IncludeForMasking_30() { return &___m_IncludeForMasking_30; }
	inline void set_m_IncludeForMasking_30(bool value)
	{
		___m_IncludeForMasking_30 = value;
	}

	inline static int32_t get_offset_of_m_OnCullStateChanged_31() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_OnCullStateChanged_31)); }
	inline CullStateChangedEvent_t6BC3E87DBC04B585798460D55F56B86C23B62FE4 * get_m_OnCullStateChanged_31() const { return ___m_OnCullStateChanged_31; }
	inline CullStateChangedEvent_t6BC3E87DBC04B585798460D55F56B86C23B62FE4 ** get_address_of_m_OnCullStateChanged_31() { return &___m_OnCullStateChanged_31; }
	inline void set_m_OnCullStateChanged_31(CullStateChangedEvent_t6BC3E87DBC04B585798460D55F56B86C23B62FE4 * value)
	{
		___m_OnCullStateChanged_31 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_OnCullStateChanged_31), (void*)value);
	}

	inline static int32_t get_offset_of_m_ShouldRecalculate_32() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_ShouldRecalculate_32)); }
	inline bool get_m_ShouldRecalculate_32() const { return ___m_ShouldRecalculate_32; }
	inline bool* get_address_of_m_ShouldRecalculate_32() { return &___m_ShouldRecalculate_32; }
	inline void set_m_ShouldRecalculate_32(bool value)
	{
		___m_ShouldRecalculate_32 = value;
	}

	inline static int32_t get_offset_of_m_StencilValue_33() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_StencilValue_33)); }
	inline int32_t get_m_StencilValue_33() const { return ___m_StencilValue_33; }
	inline int32_t* get_address_of_m_StencilValue_33() { return &___m_StencilValue_33; }
	inline void set_m_StencilValue_33(int32_t value)
	{
		___m_StencilValue_33 = value;
	}

	inline static int32_t get_offset_of_m_Corners_34() { return static_cast<int32_t>(offsetof(MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F, ___m_Corners_34)); }
	inline Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* get_m_Corners_34() const { return ___m_Corners_34; }
	inline Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28** get_address_of_m_Corners_34() { return &___m_Corners_34; }
	inline void set_m_Corners_34(Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* value)
	{
		___m_Corners_34 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_Corners_34), (void*)value);
	}
};


// UnityEngine.UI.Slider
struct  Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09  : public Selectable_tAA9065030FE0468018DEC880302F95FEA9C0133A
{
public:
	// UnityEngine.RectTransform UnityEngine.UI.Slider::m_FillRect
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___m_FillRect_19;
	// UnityEngine.RectTransform UnityEngine.UI.Slider::m_HandleRect
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___m_HandleRect_20;
	// UnityEngine.UI.Slider_Direction UnityEngine.UI.Slider::m_Direction
	int32_t ___m_Direction_21;
	// System.Single UnityEngine.UI.Slider::m_MinValue
	float ___m_MinValue_22;
	// System.Single UnityEngine.UI.Slider::m_MaxValue
	float ___m_MaxValue_23;
	// System.Boolean UnityEngine.UI.Slider::m_WholeNumbers
	bool ___m_WholeNumbers_24;
	// System.Single UnityEngine.UI.Slider::m_Value
	float ___m_Value_25;
	// UnityEngine.UI.Slider_SliderEvent UnityEngine.UI.Slider::m_OnValueChanged
	SliderEvent_t64A824F56F80FC8E2F233F0A0FB0821702DF416C * ___m_OnValueChanged_26;
	// UnityEngine.UI.Image UnityEngine.UI.Slider::m_FillImage
	Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * ___m_FillImage_27;
	// UnityEngine.Transform UnityEngine.UI.Slider::m_FillTransform
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___m_FillTransform_28;
	// UnityEngine.RectTransform UnityEngine.UI.Slider::m_FillContainerRect
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___m_FillContainerRect_29;
	// UnityEngine.Transform UnityEngine.UI.Slider::m_HandleTransform
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___m_HandleTransform_30;
	// UnityEngine.RectTransform UnityEngine.UI.Slider::m_HandleContainerRect
	RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___m_HandleContainerRect_31;
	// UnityEngine.Vector2 UnityEngine.UI.Slider::m_Offset
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___m_Offset_32;
	// UnityEngine.DrivenRectTransformTracker UnityEngine.UI.Slider::m_Tracker
	DrivenRectTransformTracker_tB8FBBE24EEE9618CA32E4B3CF52F4AD7FDDEBE03  ___m_Tracker_33;
	// System.Boolean UnityEngine.UI.Slider::m_DelayedUpdateVisuals
	bool ___m_DelayedUpdateVisuals_34;

public:
	inline static int32_t get_offset_of_m_FillRect_19() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_FillRect_19)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_m_FillRect_19() const { return ___m_FillRect_19; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_m_FillRect_19() { return &___m_FillRect_19; }
	inline void set_m_FillRect_19(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___m_FillRect_19 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_FillRect_19), (void*)value);
	}

	inline static int32_t get_offset_of_m_HandleRect_20() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_HandleRect_20)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_m_HandleRect_20() const { return ___m_HandleRect_20; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_m_HandleRect_20() { return &___m_HandleRect_20; }
	inline void set_m_HandleRect_20(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___m_HandleRect_20 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_HandleRect_20), (void*)value);
	}

	inline static int32_t get_offset_of_m_Direction_21() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_Direction_21)); }
	inline int32_t get_m_Direction_21() const { return ___m_Direction_21; }
	inline int32_t* get_address_of_m_Direction_21() { return &___m_Direction_21; }
	inline void set_m_Direction_21(int32_t value)
	{
		___m_Direction_21 = value;
	}

	inline static int32_t get_offset_of_m_MinValue_22() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_MinValue_22)); }
	inline float get_m_MinValue_22() const { return ___m_MinValue_22; }
	inline float* get_address_of_m_MinValue_22() { return &___m_MinValue_22; }
	inline void set_m_MinValue_22(float value)
	{
		___m_MinValue_22 = value;
	}

	inline static int32_t get_offset_of_m_MaxValue_23() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_MaxValue_23)); }
	inline float get_m_MaxValue_23() const { return ___m_MaxValue_23; }
	inline float* get_address_of_m_MaxValue_23() { return &___m_MaxValue_23; }
	inline void set_m_MaxValue_23(float value)
	{
		___m_MaxValue_23 = value;
	}

	inline static int32_t get_offset_of_m_WholeNumbers_24() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_WholeNumbers_24)); }
	inline bool get_m_WholeNumbers_24() const { return ___m_WholeNumbers_24; }
	inline bool* get_address_of_m_WholeNumbers_24() { return &___m_WholeNumbers_24; }
	inline void set_m_WholeNumbers_24(bool value)
	{
		___m_WholeNumbers_24 = value;
	}

	inline static int32_t get_offset_of_m_Value_25() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_Value_25)); }
	inline float get_m_Value_25() const { return ___m_Value_25; }
	inline float* get_address_of_m_Value_25() { return &___m_Value_25; }
	inline void set_m_Value_25(float value)
	{
		___m_Value_25 = value;
	}

	inline static int32_t get_offset_of_m_OnValueChanged_26() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_OnValueChanged_26)); }
	inline SliderEvent_t64A824F56F80FC8E2F233F0A0FB0821702DF416C * get_m_OnValueChanged_26() const { return ___m_OnValueChanged_26; }
	inline SliderEvent_t64A824F56F80FC8E2F233F0A0FB0821702DF416C ** get_address_of_m_OnValueChanged_26() { return &___m_OnValueChanged_26; }
	inline void set_m_OnValueChanged_26(SliderEvent_t64A824F56F80FC8E2F233F0A0FB0821702DF416C * value)
	{
		___m_OnValueChanged_26 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_OnValueChanged_26), (void*)value);
	}

	inline static int32_t get_offset_of_m_FillImage_27() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_FillImage_27)); }
	inline Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * get_m_FillImage_27() const { return ___m_FillImage_27; }
	inline Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E ** get_address_of_m_FillImage_27() { return &___m_FillImage_27; }
	inline void set_m_FillImage_27(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * value)
	{
		___m_FillImage_27 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_FillImage_27), (void*)value);
	}

	inline static int32_t get_offset_of_m_FillTransform_28() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_FillTransform_28)); }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * get_m_FillTransform_28() const { return ___m_FillTransform_28; }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA ** get_address_of_m_FillTransform_28() { return &___m_FillTransform_28; }
	inline void set_m_FillTransform_28(Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * value)
	{
		___m_FillTransform_28 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_FillTransform_28), (void*)value);
	}

	inline static int32_t get_offset_of_m_FillContainerRect_29() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_FillContainerRect_29)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_m_FillContainerRect_29() const { return ___m_FillContainerRect_29; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_m_FillContainerRect_29() { return &___m_FillContainerRect_29; }
	inline void set_m_FillContainerRect_29(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___m_FillContainerRect_29 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_FillContainerRect_29), (void*)value);
	}

	inline static int32_t get_offset_of_m_HandleTransform_30() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_HandleTransform_30)); }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * get_m_HandleTransform_30() const { return ___m_HandleTransform_30; }
	inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA ** get_address_of_m_HandleTransform_30() { return &___m_HandleTransform_30; }
	inline void set_m_HandleTransform_30(Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * value)
	{
		___m_HandleTransform_30 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_HandleTransform_30), (void*)value);
	}

	inline static int32_t get_offset_of_m_HandleContainerRect_31() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_HandleContainerRect_31)); }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * get_m_HandleContainerRect_31() const { return ___m_HandleContainerRect_31; }
	inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 ** get_address_of_m_HandleContainerRect_31() { return &___m_HandleContainerRect_31; }
	inline void set_m_HandleContainerRect_31(RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * value)
	{
		___m_HandleContainerRect_31 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_HandleContainerRect_31), (void*)value);
	}

	inline static int32_t get_offset_of_m_Offset_32() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_Offset_32)); }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  get_m_Offset_32() const { return ___m_Offset_32; }
	inline Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * get_address_of_m_Offset_32() { return &___m_Offset_32; }
	inline void set_m_Offset_32(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  value)
	{
		___m_Offset_32 = value;
	}

	inline static int32_t get_offset_of_m_Tracker_33() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_Tracker_33)); }
	inline DrivenRectTransformTracker_tB8FBBE24EEE9618CA32E4B3CF52F4AD7FDDEBE03  get_m_Tracker_33() const { return ___m_Tracker_33; }
	inline DrivenRectTransformTracker_tB8FBBE24EEE9618CA32E4B3CF52F4AD7FDDEBE03 * get_address_of_m_Tracker_33() { return &___m_Tracker_33; }
	inline void set_m_Tracker_33(DrivenRectTransformTracker_tB8FBBE24EEE9618CA32E4B3CF52F4AD7FDDEBE03  value)
	{
		___m_Tracker_33 = value;
	}

	inline static int32_t get_offset_of_m_DelayedUpdateVisuals_34() { return static_cast<int32_t>(offsetof(Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09, ___m_DelayedUpdateVisuals_34)); }
	inline bool get_m_DelayedUpdateVisuals_34() const { return ___m_DelayedUpdateVisuals_34; }
	inline bool* get_address_of_m_DelayedUpdateVisuals_34() { return &___m_DelayedUpdateVisuals_34; }
	inline void set_m_DelayedUpdateVisuals_34(bool value)
	{
		___m_DelayedUpdateVisuals_34 = value;
	}
};


// UnityEngine.UI.Image
struct  Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E  : public MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F
{
public:
	// UnityEngine.Sprite UnityEngine.UI.Image::m_Sprite
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_Sprite_36;
	// UnityEngine.Sprite UnityEngine.UI.Image::m_OverrideSprite
	Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___m_OverrideSprite_37;
	// UnityEngine.UI.Image_Type UnityEngine.UI.Image::m_Type
	int32_t ___m_Type_38;
	// System.Boolean UnityEngine.UI.Image::m_PreserveAspect
	bool ___m_PreserveAspect_39;
	// System.Boolean UnityEngine.UI.Image::m_FillCenter
	bool ___m_FillCenter_40;
	// UnityEngine.UI.Image_FillMethod UnityEngine.UI.Image::m_FillMethod
	int32_t ___m_FillMethod_41;
	// System.Single UnityEngine.UI.Image::m_FillAmount
	float ___m_FillAmount_42;
	// System.Boolean UnityEngine.UI.Image::m_FillClockwise
	bool ___m_FillClockwise_43;
	// System.Int32 UnityEngine.UI.Image::m_FillOrigin
	int32_t ___m_FillOrigin_44;
	// System.Single UnityEngine.UI.Image::m_AlphaHitTestMinimumThreshold
	float ___m_AlphaHitTestMinimumThreshold_45;
	// System.Boolean UnityEngine.UI.Image::m_Tracked
	bool ___m_Tracked_46;
	// System.Boolean UnityEngine.UI.Image::m_UseSpriteMesh
	bool ___m_UseSpriteMesh_47;
	// System.Single UnityEngine.UI.Image::m_PixelsPerUnitMultiplier
	float ___m_PixelsPerUnitMultiplier_48;
	// System.Single UnityEngine.UI.Image::m_CachedReferencePixelsPerUnit
	float ___m_CachedReferencePixelsPerUnit_49;

public:
	inline static int32_t get_offset_of_m_Sprite_36() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_Sprite_36)); }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * get_m_Sprite_36() const { return ___m_Sprite_36; }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** get_address_of_m_Sprite_36() { return &___m_Sprite_36; }
	inline void set_m_Sprite_36(Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		___m_Sprite_36 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_Sprite_36), (void*)value);
	}

	inline static int32_t get_offset_of_m_OverrideSprite_37() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_OverrideSprite_37)); }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * get_m_OverrideSprite_37() const { return ___m_OverrideSprite_37; }
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** get_address_of_m_OverrideSprite_37() { return &___m_OverrideSprite_37; }
	inline void set_m_OverrideSprite_37(Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		___m_OverrideSprite_37 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_OverrideSprite_37), (void*)value);
	}

	inline static int32_t get_offset_of_m_Type_38() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_Type_38)); }
	inline int32_t get_m_Type_38() const { return ___m_Type_38; }
	inline int32_t* get_address_of_m_Type_38() { return &___m_Type_38; }
	inline void set_m_Type_38(int32_t value)
	{
		___m_Type_38 = value;
	}

	inline static int32_t get_offset_of_m_PreserveAspect_39() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_PreserveAspect_39)); }
	inline bool get_m_PreserveAspect_39() const { return ___m_PreserveAspect_39; }
	inline bool* get_address_of_m_PreserveAspect_39() { return &___m_PreserveAspect_39; }
	inline void set_m_PreserveAspect_39(bool value)
	{
		___m_PreserveAspect_39 = value;
	}

	inline static int32_t get_offset_of_m_FillCenter_40() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_FillCenter_40)); }
	inline bool get_m_FillCenter_40() const { return ___m_FillCenter_40; }
	inline bool* get_address_of_m_FillCenter_40() { return &___m_FillCenter_40; }
	inline void set_m_FillCenter_40(bool value)
	{
		___m_FillCenter_40 = value;
	}

	inline static int32_t get_offset_of_m_FillMethod_41() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_FillMethod_41)); }
	inline int32_t get_m_FillMethod_41() const { return ___m_FillMethod_41; }
	inline int32_t* get_address_of_m_FillMethod_41() { return &___m_FillMethod_41; }
	inline void set_m_FillMethod_41(int32_t value)
	{
		___m_FillMethod_41 = value;
	}

	inline static int32_t get_offset_of_m_FillAmount_42() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_FillAmount_42)); }
	inline float get_m_FillAmount_42() const { return ___m_FillAmount_42; }
	inline float* get_address_of_m_FillAmount_42() { return &___m_FillAmount_42; }
	inline void set_m_FillAmount_42(float value)
	{
		___m_FillAmount_42 = value;
	}

	inline static int32_t get_offset_of_m_FillClockwise_43() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_FillClockwise_43)); }
	inline bool get_m_FillClockwise_43() const { return ___m_FillClockwise_43; }
	inline bool* get_address_of_m_FillClockwise_43() { return &___m_FillClockwise_43; }
	inline void set_m_FillClockwise_43(bool value)
	{
		___m_FillClockwise_43 = value;
	}

	inline static int32_t get_offset_of_m_FillOrigin_44() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_FillOrigin_44)); }
	inline int32_t get_m_FillOrigin_44() const { return ___m_FillOrigin_44; }
	inline int32_t* get_address_of_m_FillOrigin_44() { return &___m_FillOrigin_44; }
	inline void set_m_FillOrigin_44(int32_t value)
	{
		___m_FillOrigin_44 = value;
	}

	inline static int32_t get_offset_of_m_AlphaHitTestMinimumThreshold_45() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_AlphaHitTestMinimumThreshold_45)); }
	inline float get_m_AlphaHitTestMinimumThreshold_45() const { return ___m_AlphaHitTestMinimumThreshold_45; }
	inline float* get_address_of_m_AlphaHitTestMinimumThreshold_45() { return &___m_AlphaHitTestMinimumThreshold_45; }
	inline void set_m_AlphaHitTestMinimumThreshold_45(float value)
	{
		___m_AlphaHitTestMinimumThreshold_45 = value;
	}

	inline static int32_t get_offset_of_m_Tracked_46() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_Tracked_46)); }
	inline bool get_m_Tracked_46() const { return ___m_Tracked_46; }
	inline bool* get_address_of_m_Tracked_46() { return &___m_Tracked_46; }
	inline void set_m_Tracked_46(bool value)
	{
		___m_Tracked_46 = value;
	}

	inline static int32_t get_offset_of_m_UseSpriteMesh_47() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_UseSpriteMesh_47)); }
	inline bool get_m_UseSpriteMesh_47() const { return ___m_UseSpriteMesh_47; }
	inline bool* get_address_of_m_UseSpriteMesh_47() { return &___m_UseSpriteMesh_47; }
	inline void set_m_UseSpriteMesh_47(bool value)
	{
		___m_UseSpriteMesh_47 = value;
	}

	inline static int32_t get_offset_of_m_PixelsPerUnitMultiplier_48() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_PixelsPerUnitMultiplier_48)); }
	inline float get_m_PixelsPerUnitMultiplier_48() const { return ___m_PixelsPerUnitMultiplier_48; }
	inline float* get_address_of_m_PixelsPerUnitMultiplier_48() { return &___m_PixelsPerUnitMultiplier_48; }
	inline void set_m_PixelsPerUnitMultiplier_48(float value)
	{
		___m_PixelsPerUnitMultiplier_48 = value;
	}

	inline static int32_t get_offset_of_m_CachedReferencePixelsPerUnit_49() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E, ___m_CachedReferencePixelsPerUnit_49)); }
	inline float get_m_CachedReferencePixelsPerUnit_49() const { return ___m_CachedReferencePixelsPerUnit_49; }
	inline float* get_address_of_m_CachedReferencePixelsPerUnit_49() { return &___m_CachedReferencePixelsPerUnit_49; }
	inline void set_m_CachedReferencePixelsPerUnit_49(float value)
	{
		___m_CachedReferencePixelsPerUnit_49 = value;
	}
};

struct Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields
{
public:
	// UnityEngine.Material UnityEngine.UI.Image::s_ETC1DefaultUI
	Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * ___s_ETC1DefaultUI_35;
	// UnityEngine.Vector2[] UnityEngine.UI.Image::s_VertScratch
	Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* ___s_VertScratch_50;
	// UnityEngine.Vector2[] UnityEngine.UI.Image::s_UVScratch
	Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* ___s_UVScratch_51;
	// UnityEngine.Vector3[] UnityEngine.UI.Image::s_Xy
	Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* ___s_Xy_52;
	// UnityEngine.Vector3[] UnityEngine.UI.Image::s_Uv
	Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* ___s_Uv_53;
	// System.Collections.Generic.List`1<UnityEngine.UI.Image> UnityEngine.UI.Image::m_TrackedTexturelessImages
	List_1_tB46CB6C7789F514A8BE08EB5A4F3D9D26AE5E4DA * ___m_TrackedTexturelessImages_54;
	// System.Boolean UnityEngine.UI.Image::s_Initialized
	bool ___s_Initialized_55;

public:
	inline static int32_t get_offset_of_s_ETC1DefaultUI_35() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields, ___s_ETC1DefaultUI_35)); }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * get_s_ETC1DefaultUI_35() const { return ___s_ETC1DefaultUI_35; }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 ** get_address_of_s_ETC1DefaultUI_35() { return &___s_ETC1DefaultUI_35; }
	inline void set_s_ETC1DefaultUI_35(Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * value)
	{
		___s_ETC1DefaultUI_35 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_ETC1DefaultUI_35), (void*)value);
	}

	inline static int32_t get_offset_of_s_VertScratch_50() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields, ___s_VertScratch_50)); }
	inline Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* get_s_VertScratch_50() const { return ___s_VertScratch_50; }
	inline Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6** get_address_of_s_VertScratch_50() { return &___s_VertScratch_50; }
	inline void set_s_VertScratch_50(Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* value)
	{
		___s_VertScratch_50 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_VertScratch_50), (void*)value);
	}

	inline static int32_t get_offset_of_s_UVScratch_51() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields, ___s_UVScratch_51)); }
	inline Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* get_s_UVScratch_51() const { return ___s_UVScratch_51; }
	inline Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6** get_address_of_s_UVScratch_51() { return &___s_UVScratch_51; }
	inline void set_s_UVScratch_51(Vector2U5BU5D_tA065A07DFC060C1B8786BBAA5F3A6577CCEB27D6* value)
	{
		___s_UVScratch_51 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_UVScratch_51), (void*)value);
	}

	inline static int32_t get_offset_of_s_Xy_52() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields, ___s_Xy_52)); }
	inline Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* get_s_Xy_52() const { return ___s_Xy_52; }
	inline Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28** get_address_of_s_Xy_52() { return &___s_Xy_52; }
	inline void set_s_Xy_52(Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* value)
	{
		___s_Xy_52 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_Xy_52), (void*)value);
	}

	inline static int32_t get_offset_of_s_Uv_53() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields, ___s_Uv_53)); }
	inline Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* get_s_Uv_53() const { return ___s_Uv_53; }
	inline Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28** get_address_of_s_Uv_53() { return &___s_Uv_53; }
	inline void set_s_Uv_53(Vector3U5BU5D_tB9EC3346CC4A0EA5447D968E84A9AC1F6F372C28* value)
	{
		___s_Uv_53 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_Uv_53), (void*)value);
	}

	inline static int32_t get_offset_of_m_TrackedTexturelessImages_54() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields, ___m_TrackedTexturelessImages_54)); }
	inline List_1_tB46CB6C7789F514A8BE08EB5A4F3D9D26AE5E4DA * get_m_TrackedTexturelessImages_54() const { return ___m_TrackedTexturelessImages_54; }
	inline List_1_tB46CB6C7789F514A8BE08EB5A4F3D9D26AE5E4DA ** get_address_of_m_TrackedTexturelessImages_54() { return &___m_TrackedTexturelessImages_54; }
	inline void set_m_TrackedTexturelessImages_54(List_1_tB46CB6C7789F514A8BE08EB5A4F3D9D26AE5E4DA * value)
	{
		___m_TrackedTexturelessImages_54 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_TrackedTexturelessImages_54), (void*)value);
	}

	inline static int32_t get_offset_of_s_Initialized_55() { return static_cast<int32_t>(offsetof(Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E_StaticFields, ___s_Initialized_55)); }
	inline bool get_s_Initialized_55() const { return ___s_Initialized_55; }
	inline bool* get_address_of_s_Initialized_55() { return &___s_Initialized_55; }
	inline void set_s_Initialized_55(bool value)
	{
		___s_Initialized_55 = value;
	}
};


// UnityEngine.UI.Text
struct  Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030  : public MaskableGraphic_tDA46A5925C6A2101217C9F52C855B5C1A36A7A0F
{
public:
	// UnityEngine.UI.FontData UnityEngine.UI.Text::m_FontData
	FontData_t29F4568F4FB8C463AAFE6DD21FA7A812B4FF1494 * ___m_FontData_35;
	// System.String UnityEngine.UI.Text::m_Text
	String_t* ___m_Text_36;
	// UnityEngine.TextGenerator UnityEngine.UI.Text::m_TextCache
	TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 * ___m_TextCache_37;
	// UnityEngine.TextGenerator UnityEngine.UI.Text::m_TextCacheForLayout
	TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 * ___m_TextCacheForLayout_38;
	// System.Boolean UnityEngine.UI.Text::m_DisableFontTextureRebuiltCallback
	bool ___m_DisableFontTextureRebuiltCallback_40;
	// UnityEngine.UIVertex[] UnityEngine.UI.Text::m_TempVerts
	UIVertexU5BU5D_tB560F9F9269864891FCE1677971F603A08AA857A* ___m_TempVerts_41;

public:
	inline static int32_t get_offset_of_m_FontData_35() { return static_cast<int32_t>(offsetof(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030, ___m_FontData_35)); }
	inline FontData_t29F4568F4FB8C463AAFE6DD21FA7A812B4FF1494 * get_m_FontData_35() const { return ___m_FontData_35; }
	inline FontData_t29F4568F4FB8C463AAFE6DD21FA7A812B4FF1494 ** get_address_of_m_FontData_35() { return &___m_FontData_35; }
	inline void set_m_FontData_35(FontData_t29F4568F4FB8C463AAFE6DD21FA7A812B4FF1494 * value)
	{
		___m_FontData_35 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_FontData_35), (void*)value);
	}

	inline static int32_t get_offset_of_m_Text_36() { return static_cast<int32_t>(offsetof(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030, ___m_Text_36)); }
	inline String_t* get_m_Text_36() const { return ___m_Text_36; }
	inline String_t** get_address_of_m_Text_36() { return &___m_Text_36; }
	inline void set_m_Text_36(String_t* value)
	{
		___m_Text_36 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_Text_36), (void*)value);
	}

	inline static int32_t get_offset_of_m_TextCache_37() { return static_cast<int32_t>(offsetof(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030, ___m_TextCache_37)); }
	inline TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 * get_m_TextCache_37() const { return ___m_TextCache_37; }
	inline TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 ** get_address_of_m_TextCache_37() { return &___m_TextCache_37; }
	inline void set_m_TextCache_37(TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 * value)
	{
		___m_TextCache_37 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_TextCache_37), (void*)value);
	}

	inline static int32_t get_offset_of_m_TextCacheForLayout_38() { return static_cast<int32_t>(offsetof(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030, ___m_TextCacheForLayout_38)); }
	inline TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 * get_m_TextCacheForLayout_38() const { return ___m_TextCacheForLayout_38; }
	inline TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 ** get_address_of_m_TextCacheForLayout_38() { return &___m_TextCacheForLayout_38; }
	inline void set_m_TextCacheForLayout_38(TextGenerator_tD455BE18A64C7DDF854F6DB3CCEBF705121C58A8 * value)
	{
		___m_TextCacheForLayout_38 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_TextCacheForLayout_38), (void*)value);
	}

	inline static int32_t get_offset_of_m_DisableFontTextureRebuiltCallback_40() { return static_cast<int32_t>(offsetof(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030, ___m_DisableFontTextureRebuiltCallback_40)); }
	inline bool get_m_DisableFontTextureRebuiltCallback_40() const { return ___m_DisableFontTextureRebuiltCallback_40; }
	inline bool* get_address_of_m_DisableFontTextureRebuiltCallback_40() { return &___m_DisableFontTextureRebuiltCallback_40; }
	inline void set_m_DisableFontTextureRebuiltCallback_40(bool value)
	{
		___m_DisableFontTextureRebuiltCallback_40 = value;
	}

	inline static int32_t get_offset_of_m_TempVerts_41() { return static_cast<int32_t>(offsetof(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030, ___m_TempVerts_41)); }
	inline UIVertexU5BU5D_tB560F9F9269864891FCE1677971F603A08AA857A* get_m_TempVerts_41() const { return ___m_TempVerts_41; }
	inline UIVertexU5BU5D_tB560F9F9269864891FCE1677971F603A08AA857A** get_address_of_m_TempVerts_41() { return &___m_TempVerts_41; }
	inline void set_m_TempVerts_41(UIVertexU5BU5D_tB560F9F9269864891FCE1677971F603A08AA857A* value)
	{
		___m_TempVerts_41 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___m_TempVerts_41), (void*)value);
	}
};

struct Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030_StaticFields
{
public:
	// UnityEngine.Material UnityEngine.UI.Text::s_DefaultText
	Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * ___s_DefaultText_39;

public:
	inline static int32_t get_offset_of_s_DefaultText_39() { return static_cast<int32_t>(offsetof(Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030_StaticFields, ___s_DefaultText_39)); }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * get_s_DefaultText_39() const { return ___s_DefaultText_39; }
	inline Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 ** get_address_of_s_DefaultText_39() { return &___s_DefaultText_39; }
	inline void set_s_DefaultText_39(Material_tF7DB3BF0C24DEC2FE0CB51E5DF5053D5223C8598 * value)
	{
		___s_DefaultText_39 = value;
		Il2CppCodeGenWriteBarrier((void**)(&___s_DefaultText_39), (void*)value);
	}
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif
// UnityEngine.Collider2D[]
struct Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE  : public RuntimeArray
{
public:
	ALIGN_FIELD (8) Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * m_Items[1];

public:
	inline Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * GetAt(il2cpp_array_size_t index) const
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items[index];
	}
	inline Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 ** GetAddressAt(il2cpp_array_size_t index)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items + index;
	}
	inline void SetAt(il2cpp_array_size_t index, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * value)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
	inline Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * GetAtUnchecked(il2cpp_array_size_t index) const
	{
		return m_Items[index];
	}
	inline Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 ** GetAddressAtUnchecked(il2cpp_array_size_t index)
	{
		return m_Items + index;
	}
	inline void SetAtUnchecked(il2cpp_array_size_t index, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * value)
	{
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
};
// System.Delegate[]
struct DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86  : public RuntimeArray
{
public:
	ALIGN_FIELD (8) Delegate_t * m_Items[1];

public:
	inline Delegate_t * GetAt(il2cpp_array_size_t index) const
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items[index];
	}
	inline Delegate_t ** GetAddressAt(il2cpp_array_size_t index)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items + index;
	}
	inline void SetAt(il2cpp_array_size_t index, Delegate_t * value)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
	inline Delegate_t * GetAtUnchecked(il2cpp_array_size_t index) const
	{
		return m_Items[index];
	}
	inline Delegate_t ** GetAddressAtUnchecked(il2cpp_array_size_t index)
	{
		return m_Items + index;
	}
	inline void SetAtUnchecked(il2cpp_array_size_t index, Delegate_t * value)
	{
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
};
// UnityEngine.AnimatorClipInfo[]
struct AnimatorClipInfoU5BU5D_tCAC39F9AE6CEE1EA08285D9D5C44DB3ADD6C1ED6  : public RuntimeArray
{
public:
	ALIGN_FIELD (8) AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180  m_Items[1];

public:
	inline AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180  GetAt(il2cpp_array_size_t index) const
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items[index];
	}
	inline AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180 * GetAddressAt(il2cpp_array_size_t index)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items + index;
	}
	inline void SetAt(il2cpp_array_size_t index, AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180  value)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		m_Items[index] = value;
	}
	inline AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180  GetAtUnchecked(il2cpp_array_size_t index) const
	{
		return m_Items[index];
	}
	inline AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180 * GetAddressAtUnchecked(il2cpp_array_size_t index)
	{
		return m_Items + index;
	}
	inline void SetAtUnchecked(il2cpp_array_size_t index, AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180  value)
	{
		m_Items[index] = value;
	}
};
// UnityEngine.Sprite[]
struct SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7  : public RuntimeArray
{
public:
	ALIGN_FIELD (8) Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * m_Items[1];

public:
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * GetAt(il2cpp_array_size_t index) const
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items[index];
	}
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** GetAddressAt(il2cpp_array_size_t index)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items + index;
	}
	inline void SetAt(il2cpp_array_size_t index, Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * GetAtUnchecked(il2cpp_array_size_t index) const
	{
		return m_Items[index];
	}
	inline Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 ** GetAddressAtUnchecked(il2cpp_array_size_t index)
	{
		return m_Items + index;
	}
	inline void SetAtUnchecked(il2cpp_array_size_t index, Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * value)
	{
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
};
// System.Object[]
struct ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A  : public RuntimeArray
{
public:
	ALIGN_FIELD (8) RuntimeObject * m_Items[1];

public:
	inline RuntimeObject * GetAt(il2cpp_array_size_t index) const
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items[index];
	}
	inline RuntimeObject ** GetAddressAt(il2cpp_array_size_t index)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		return m_Items + index;
	}
	inline void SetAt(il2cpp_array_size_t index, RuntimeObject * value)
	{
		IL2CPP_ARRAY_BOUNDS_CHECK(index, (uint32_t)(this)->max_length);
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
	inline RuntimeObject * GetAtUnchecked(il2cpp_array_size_t index) const
	{
		return m_Items[index];
	}
	inline RuntimeObject ** GetAddressAtUnchecked(il2cpp_array_size_t index)
	{
		return m_Items + index;
	}
	inline void SetAtUnchecked(il2cpp_array_size_t index, RuntimeObject * value)
	{
		m_Items[index] = value;
		Il2CppCodeGenWriteBarrier((void**)m_Items + index, (void*)value);
	}
};


// !0 System.Collections.Generic.List`1<System.Object>::get_Item(System.Int32)
IL2CPP_EXTERN_C inline IL2CPP_METHOD_ATTR RuntimeObject * List_1_get_Item_mFDB8AD680C600072736579BBF5F38F7416396588_gshared_inline (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, int32_t ___index0, const RuntimeMethod* method);
// System.Int32 System.Collections.Generic.List`1<System.Object>::get_Count()
IL2CPP_EXTERN_C inline IL2CPP_METHOD_ATTR int32_t List_1_get_Count_m507C9149FF7F83AAC72C29091E745D557DA47D22_gshared_inline (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<System.Object>()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject * Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Object::FindObjectOfType<System.Object>()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject * Object_FindObjectOfType_TisRuntimeObject_mE3957366B74863C807E6E8A23D239A0CB079BB9C_gshared (const RuntimeMethod* method);
// !!0 UnityEngine.GameObject::GetComponent<System.Object>()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject * GameObject_GetComponent_TisRuntimeObject_mD4382B2843BA9A61A01A8F9D7B9813D060F9C9CA_gshared (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * __this, const RuntimeMethod* method);
// System.Boolean System.Collections.Generic.List`1<System.Object>::Contains(!0)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool List_1_Contains_mE08D561E86879A26245096C572A8593279383FDB_gshared (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, RuntimeObject * ___item0, const RuntimeMethod* method);
// System.Void System.Collections.Generic.List`1<System.Object>::Add(!0)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void List_1_Add_m6930161974C7504C80F52EC379EF012387D43138_gshared (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, RuntimeObject * ___item0, const RuntimeMethod* method);
// System.Boolean System.Collections.Generic.List`1<System.Object>::Remove(!0)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool List_1_Remove_m908B647BB9F807676DACE34E3E73475C3C3751D4_gshared (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, RuntimeObject * ___item0, const RuntimeMethod* method);
// System.Void System.Collections.Generic.List`1<System.Object>::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void List_1__ctor_mC832F1AC0F814BAEB19175F5D7972A7507508BC3_gshared (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponentInParent<System.Object>()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject * Component_GetComponentInParent_TisRuntimeObject_m3D5E351D50C60522BD31D282D044F6527C382749_gshared (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Object::Instantiate<System.Object>(!!0,UnityEngine.Vector3,UnityEngine.Quaternion)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject * Object_Instantiate_TisRuntimeObject_m352D452C728667C9C76C942525CDE26444568ECD_gshared (RuntimeObject * ___original0, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___position1, Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  ___rotation2, const RuntimeMethod* method);

// !0 System.Collections.Generic.List`1<UnityEngine.Transform>::get_Item(System.Int32)
inline Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_inline (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * __this, int32_t ___index0, const RuntimeMethod* method)
{
	return ((  Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * (*) (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *, int32_t, const RuntimeMethod*))List_1_get_Item_mFDB8AD680C600072736579BBF5F38F7416396588_gshared_inline)(__this, ___index0, method);
}
// System.Int32 System.Collections.Generic.List`1<UnityEngine.Transform>::get_Count()
inline int32_t List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * __this, const RuntimeMethod* method)
{
	return ((  int32_t (*) (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *, const RuntimeMethod*))List_1_get_Count_m507C9149FF7F83AAC72C29091E745D557DA47D22_gshared_inline)(__this, method);
}
// System.Void Enemy::TransitionToState(EnemyBaseState)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * ___state0, const RuntimeMethod* method);
// UnityEngine.Transform UnityEngine.Component::get_transform()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Transform::get_position()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294 (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, const RuntimeMethod* method);
// System.Boolean UnityEngine.Component::CompareTag(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, String_t* ___tag0, const RuntimeMethod* method);
// System.Void Enemy::MoveToTarget()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_MoveToTarget_mCDF98A78E7279630FBE34E9183ACAE017D025132 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// System.Void EnemyBaseState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void EnemyBaseState__ctor_m57F25EC153F6DA435937264866B5DAFB8A7531FA (EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * __this, const RuntimeMethod* method);
// System.Void Enemy::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<Bomb>()
inline Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// UnityEngine.GameObject UnityEngine.Component::get_gameObject()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method);
// UnityEngine.Transform UnityEngine.GameObject::get_transform()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * __this, const RuntimeMethod* method);
// System.Void UnityEngine.Transform::set_position(UnityEngine.Vector3)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Transform_set_position_mDA89E4893F14ECA5CBEEE7FB80A5BF7C1B8EA6DC (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___value0, const RuntimeMethod* method);
// System.Void UnityEngine.Transform::SetParent(UnityEngine.Transform)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Transform_SetParent_mFAF9209CAB6A864552074BA065D740924A4BF979 (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___p0, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<UnityEngine.Rigidbody2D>()
inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// System.Void UnityEngine.Rigidbody2D::set_bodyType(UnityEngine.RigidbodyType2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Rigidbody2D_set_bodyType_m239CDB6FFA033FD3B5BAC061A3F96DC9264D9900 (Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * __this, int32_t ___value0, const RuntimeMethod* method);
// System.Int32 UnityEngine.LayerMask::NameToLayer(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t LayerMask_NameToLayer_m6491D9EA75F68B1F8AE15A9B4F193FFB9352B901 (String_t* ___layerName0, const RuntimeMethod* method);
// System.Void UnityEngine.GameObject::set_layer(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameObject_set_layer_mDAC8037FCFD0CE62DB66004C4342EA20CF604907 (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * __this, int32_t ___value0, const RuntimeMethod* method);
// System.Void Enemy::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_Update_mE957FE3BFB8CBB7C30E43D4A81C13E02B1C1FC32 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// System.Void UnityEngine.Animator::SetBool(System.String,System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Animator_SetBool_m497805BA217139E42808899782FA05C15BC9879E (Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * __this, String_t* ___name0, bool ___value1, const RuntimeMethod* method);
// System.Boolean UnityEngine.Object::op_Inequality(UnityEngine.Object,UnityEngine.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Object_op_Inequality_m31EF58E217E8F4BDD3E409DEF79E1AEE95874FC1 (Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 * ___x0, Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 * ___y1, const RuntimeMethod* method);
// UnityEngine.Transform UnityEngine.Transform::get_parent()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * Transform_get_parent_m8FA24E38A1FA29D90CBF3CDC9F9F017C65BB3403 (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Object::FindObjectOfType<PlayerController>()
inline PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * Object_FindObjectOfType_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_mBC133F50DBE6E9017FBA685EC7B283C09AE9EB61 (const RuntimeMethod* method)
{
	return ((  PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * (*) (const RuntimeMethod*))Object_FindObjectOfType_TisRuntimeObject_mE3957366B74863C807E6E8A23D239A0CB079BB9C_gshared)(method);
}
// System.Void UnityEngine.Vector2::.ctor(System.Single,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * __this, float ___x0, float ___y1, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::op_Multiply(UnityEngine.Vector2,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___a0, float ___d1, const RuntimeMethod* method);
// System.Void UnityEngine.Rigidbody2D::AddForce(UnityEngine.Vector2,UnityEngine.ForceMode2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Rigidbody2D_AddForce_m09E1A2E24DABA5BBC613E35772AE2C1C35C6E40C (Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___force0, int32_t ___mode1, const RuntimeMethod* method);
// System.Void Enemy::OnTriggerStay2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_OnTriggerStay2D_m098504D6D16E60A6509C4B859814A66F9FFD9F8E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method);
// System.Void PickUpState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PickUpState__ctor_mADC8DE8CCF7682F0788AF688F1ADBCD0057180F4 (PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * __this, const RuntimeMethod* method);
// System.Single UnityEngine.Time::get_time()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8 (const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<UnityEngine.Animator>()
inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// !!0 UnityEngine.Component::GetComponent<UnityEngine.Collider2D>()
inline Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * Component_GetComponent_TisCollider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379_m2AF5C85C582A45B02A4E940C7E8B19A065A37405 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// UnityEngine.AnimatorStateInfo UnityEngine.Animator::GetCurrentAnimatorStateInfo(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  Animator_GetCurrentAnimatorStateInfo_mBE5ED0D60A6F5CD0EDD40AF1494098D4E7BF84F2 (Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * __this, int32_t ___layerIndex0, const RuntimeMethod* method);
// System.Boolean UnityEngine.AnimatorStateInfo::IsName(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool AnimatorStateInfo_IsName_mD133471910C1ACE0979F3FD11462C9B8BB24CA96 (AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 * __this, String_t* ___name0, const RuntimeMethod* method);
// System.Void UnityEngine.Animator::Play(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Animator_Play_m254CA699DF64E86856EC8C54D1A739E3C0A49793 (Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * __this, String_t* ___stateName0, const RuntimeMethod* method);
// System.Void UnityEngine.Gizmos::DrawWireSphere(UnityEngine.Vector3,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Gizmos_DrawWireSphere_mF6F2BC5CDF7B3F312FE9AB579CDC1C6B72154BCF (Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___center0, float ___radius1, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::op_Implicit(UnityEngine.Vector3)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28 (Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___v0, const RuntimeMethod* method);
// System.Int32 UnityEngine.LayerMask::op_Implicit(UnityEngine.LayerMask)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t LayerMask_op_Implicit_m2AFFC7F931005437E8F356C953F439829AF4CFA5 (LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  ___mask0, const RuntimeMethod* method);
// UnityEngine.Collider2D[] UnityEngine.Physics2D::OverlapCircleAll(UnityEngine.Vector2,System.Single,System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE* Physics2D_OverlapCircleAll_m9711B169E5705A2B07AF64095E8271CD21E05FD8 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___point0, float ___radius1, int32_t ___layerMask2, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::op_Subtraction(UnityEngine.Vector3,UnityEngine.Vector3)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_op_Subtraction_mF9846B723A5034F8B9F5F5DCB78E3D67649143D3 (Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___a0, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___b1, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::op_UnaryNegation(UnityEngine.Vector3)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_op_UnaryNegation_m2AFBBF22801F9BCA5A4EBE642A29F433FE1339C2 (Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___a0, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::get_up()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_get_up_m6309EBC4E42D6D0B3D28056BD23D0331275306F7 (const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::op_Addition(UnityEngine.Vector3,UnityEngine.Vector3)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_op_Addition_m929F9C17E5D11B94D50B4AFF1D730B70CB59B50E (Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___a0, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___b1, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::op_Multiply(UnityEngine.Vector3,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_op_Multiply_m1C5F07723615156ACF035D88A1280A9E8F35A04E (Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___a0, float ___d1, const RuntimeMethod* method);
// System.Void Bomb::TurnOn()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_TurnOn_m2581D46C074B7BBE84864715A3960531E943D466 (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<IDamageable>()
inline RuntimeObject* Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  RuntimeObject* (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// System.Void Bomb/ExplotionNotify::Invoke(UnityEngine.Transform)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ExplotionNotify_Invoke_m222C621FC0219AADEC8ED8666986B2B240CFBA39 (ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * __this, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___transform0, const RuntimeMethod* method);
// System.Void UnityEngine.Object::Destroy(UnityEngine.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Object_Destroy_m23B4562495BA35A74266D4372D45368F8C05109A (Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 * ___obj0, const RuntimeMethod* method);
// !!0 UnityEngine.GameObject::GetComponent<UnityEngine.SpriteRenderer>()
inline SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * GameObject_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mD25CEAAA219FA1235F8E88F914D2F8AC57303538 (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * __this, const RuntimeMethod* method)
{
	return ((  SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * (*) (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F *, const RuntimeMethod*))GameObject_GetComponent_TisRuntimeObject_mD4382B2843BA9A61A01A8F9D7B9813D060F9C9CA_gshared)(__this, method);
}
// System.Void UnityEngine.Renderer::set_sortingLayerName(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Renderer_set_sortingLayerName_m8DCB7B753F22739F79E065922F6201E8EDD08E8F (Renderer_t0556D67DD582620D1F495627EDE30D03284151F4 * __this, String_t* ___value0, const RuntimeMethod* method);
// System.Delegate System.Delegate::Combine(System.Delegate,System.Delegate)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Delegate_t * Delegate_Combine_mC25D2F7DECAFBA6D9A2F9EBA8A77063F0658ECF1 (Delegate_t * ___a0, Delegate_t * ___b1, const RuntimeMethod* method);
// System.Void UnityEngine.MonoBehaviour::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97 (MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429 * __this, const RuntimeMethod* method);
// System.Void Enemy::Init()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_Init_m33CE279B856CE404151706EBC893C8604099927E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<UnityEngine.SpriteRenderer>()
inline SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * Component_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mCC209A7A6A8D6878F0CB813ED5722A59C2262693 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// System.Void UnityEngine.SpriteRenderer::set_flipX(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void SpriteRenderer_set_flipX_mF9A738B8149D48B7B1319EBFA5787BAE38DD8DD6 (SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * __this, bool ___value0, const RuntimeMethod* method);
// System.Void Enemy::SkillAttack()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_SkillAttack_m4E4DA6E8B23FB444ED5D8F3EF20F8BF818AA766E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::get_right()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_get_right_m6DD9559CA0C75BBA42D9140021C4C2A9AAA9B3F5 (const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::get_left()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_get_left_m74B52D8CFD8C62138067B2EB6846B6E9E51B7C20 (const RuntimeMethod* method);
// System.Single UnityEngine.Time::get_deltaTime()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Time_get_deltaTime_m16F98FC9BA931581236008C288E3B25CBCB7C81E (const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::MoveTowards(UnityEngine.Vector2,UnityEngine.Vector2,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_MoveTowards_m5CE85293E9619514164A685D1D4673E2A6E43DFA (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___current0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___target1, float ___maxDistanceDelta2, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector2::op_Implicit(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector2_op_Implicit_mD152B6A34B4DB7FFECC2844D74718568FE867D6F (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___v0, const RuntimeMethod* method);
// System.Void Bomb::TurnOff()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_TurnOff_mAF8955158FE03383BD5C734628B71CCA19ABE778 (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<UnityEngine.BoxCollider2D>()
inline BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * Component_GetComponent_TisBoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87_mD4BABFD1DC7C524ACC853125D82D011DC1CC5E5B (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// System.Void UnityEngine.Behaviour::set_enabled(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Behaviour_set_enabled_m9755D3B17D7022D23D1E4C618BD9A6B66A5ADC6B (Behaviour_tBDC7E9C3C898AD8348891B82D3E345801D920CA8 * __this, bool ___value0, const RuntimeMethod* method);
// System.Void GameManager::NextLevel()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_NextLevel_mF6C956ECA09992B9D36B913E2273B39C076B71F2 (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method);
// System.Void DynamicJoystick::set_MoveThreshold(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DynamicJoystick_set_MoveThreshold_m41DF6070CB77AD666C343C6FCD04F2D013FF7171 (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, float ___value0, const RuntimeMethod* method);
// System.Void Joystick::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_Start_mA4B921AF2FEC7B830AC4F0D5E49AF8934ECAD201 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method);
// System.Void UnityEngine.GameObject::SetActive(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04 (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * __this, bool ___value0, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.EventSystems.PointerEventData::get_position()
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  PointerEventData_get_position_mF25FC495A9C968C65BF34B5984616CBFB6332D55_inline (PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 Joystick::ScreenPointToAnchoredPosition(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Joystick_ScreenPointToAnchoredPosition_mE4C429E76D0FA78FD1567EB1361AF68141706201 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___screenPosition0, const RuntimeMethod* method);
// System.Void UnityEngine.RectTransform::set_anchoredPosition(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___value0, const RuntimeMethod* method);
// System.Void Joystick::OnPointerDown(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_OnPointerDown_m408D43BE6A49862DFD49B5198E0B61B85A162703 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method);
// System.Void Joystick::OnPointerUp(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_OnPointerUp_m771F7519F51F02DAADA7DE0A562F82710FA721BC (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::op_Multiply(UnityEngine.Vector2,UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_op_Multiply_mEDF9FDDF3BFFAEC997FBCDE5FA34871F2955E7C4 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___a0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___b1, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.RectTransform::get_anchoredPosition()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  RectTransform_get_anchoredPosition_mCB2171DBADBC572F354CCFE3ACA19F9506F97907 (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::op_Addition(UnityEngine.Vector2,UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_op_Addition_m81A4D928B8E399DA3A4E3ACD8937EDFDCB014682 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___a0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___b1, const RuntimeMethod* method);
// System.Void Joystick::HandleInput(System.Single,UnityEngine.Vector2,UnityEngine.Vector2,UnityEngine.Camera)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_HandleInput_mA2FF5AE57290471865DC02DC2ED3BDA3FDBA2506 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___magnitude0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___normalised1, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___radius2, Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * ___cam3, const RuntimeMethod* method);
// System.Void Joystick::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method);
// UnityEngine.Transform UnityEngine.Transform::GetChild(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * Transform_GetChild_mC86B9B61E4EC086A571B09EA7A33FFBF50DF52D3 (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, int32_t ___index0, const RuntimeMethod* method);
// System.Void UIManager::SetBossMaxHealth(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_SetBossMaxHealth_m7990FC8C3142CF8AEC5BE6F5948DB37DF9B1B03D (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, float ___health0, const RuntimeMethod* method);
// System.Void GameManager::addEnemy(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_addEnemy_mA2B4C6231982E68641C4B0BBF19B0B1B5E2A726A (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method);
// System.Void UnityEngine.Animator::SetInteger(System.String,System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Animator_SetInteger_m1E6D66416F48D6E02E7618A0142D70F5232BCC22 (Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * __this, String_t* ___name0, int32_t ___value1, const RuntimeMethod* method);
// System.Void Enemy::FilpDirection()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_FilpDirection_m25112DA9C4BB354136EF9E35420C69AE0C19B054 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// UnityEngine.Quaternion UnityEngine.Quaternion::Euler(System.Single,System.Single,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  Quaternion_Euler_m537DD6CEAE0AD4274D8A84414C24C30730427D05 (float ___x0, float ___y1, float ___z2, const RuntimeMethod* method);
// System.Void UnityEngine.Transform::set_rotation(UnityEngine.Quaternion)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Transform_set_rotation_m429694E264117C6DC682EC6AF45C7864E5155935 (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  ___value0, const RuntimeMethod* method);
// System.Void UnityEngine.Debug::Log(System.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Debug_Log_m4B7C70BAFD477C6BDB59C88A0934F0B018D03708 (RuntimeObject * ___message0, const RuntimeMethod* method);
// System.Single UnityEngine.Vector2::Distance(UnityEngine.Vector2,UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Vector2_Distance_mB07492BC42EC582754AD11554BE5B7F8D0E93CF4 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___a0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___b1, const RuntimeMethod* method);
// System.Void UnityEngine.Animator::SetTrigger(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Animator_SetTrigger_m68D29B7FA54C2F230F5AD780D462612B18E74245 (Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * __this, String_t* ___name0, const RuntimeMethod* method);
// System.Boolean System.Collections.Generic.List`1<UnityEngine.Transform>::Contains(!0)
inline bool List_1_Contains_m37CE7FF0E6F1024460701CAC16B6657BEBB8BF1B (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * __this, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___item0, const RuntimeMethod* method)
{
	return ((  bool (*) (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*))List_1_Contains_mE08D561E86879A26245096C572A8593279383FDB_gshared)(__this, ___item0, method);
}
// System.Void System.Collections.Generic.List`1<UnityEngine.Transform>::Add(!0)
inline void List_1_Add_mEB0CDED8A9ADCC0F235881A5D34D41085EC4780C (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * __this, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___item0, const RuntimeMethod* method)
{
	((  void (*) (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*))List_1_Add_m6930161974C7504C80F52EC379EF012387D43138_gshared)(__this, ___item0, method);
}
// System.Boolean System.Collections.Generic.List`1<UnityEngine.Transform>::Remove(!0)
inline bool List_1_Remove_m8E1311599BA3E940469F201FE770645882E0783A (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * __this, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___item0, const RuntimeMethod* method)
{
	return ((  bool (*) (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*))List_1_Remove_m908B647BB9F807676DACE34E3E73475C3C3751D4_gshared)(__this, ___item0, method);
}
// System.Collections.IEnumerator Enemy::OnAlaram()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject* Enemy_OnAlaram_mA62FEB896193F9E36363BD9E98DA1F0F9CA510FA (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// UnityEngine.Coroutine UnityEngine.MonoBehaviour::StartCoroutine(System.Collections.IEnumerator)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Coroutine_tAE7DB2FC70A0AE6477F896F852057CB0754F06EC * MonoBehaviour_StartCoroutine_mBF8044CE06A35D76A69669ADD8977D05956616B7 (MonoBehaviour_t4A60845CF505405AF8BE8C61CC07F75CADEF6429 * __this, RuntimeObject* ___routine0, const RuntimeMethod* method);
// System.Void Enemy/<OnAlaram>d__32::.ctor(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void U3COnAlaramU3Ed__32__ctor_mD87EBB8EF15D34C2BC010E742C410E60C02E0BE7 (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * __this, int32_t ___U3CU3E1__state0, const RuntimeMethod* method);
// System.Void GameManager::removeEnemy(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_removeEnemy_m08DDE78A0B9872B6C07147887AA03E8A2FB6F56D (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method);
// System.Void UIManager::SetBossCurrentHealth(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_SetBossCurrentHealth_m6C908308D1E920352F5F0ADF40A2BED73978ED7E (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, float ___health0, const RuntimeMethod* method);
// System.Void System.Collections.Generic.List`1<UnityEngine.Transform>::.ctor()
inline void List_1__ctor_m0046B0A356552D7B951C2CEEE5F1375DAF72054A (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * __this, const RuntimeMethod* method)
{
	((  void (*) (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *, const RuntimeMethod*))List_1__ctor_mC832F1AC0F814BAEB19175F5D7972A7507508BC3_gshared)(__this, method);
}
// System.Void PatrolState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PatrolState__ctor_m6CD97ED5CE7F0EB1531A78F30C5800AE708BF742 (PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * __this, const RuntimeMethod* method);
// System.Void AttachState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void AttachState__ctor_m2CA4845A3572836BD3E704D1A8D89466132670F2 (AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * __this, const RuntimeMethod* method);
// System.Void System.Object::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Object__ctor_m925ECA5E85CA100E3FB86A4F9E15C120E9A184C0 (RuntimeObject * __this, const RuntimeMethod* method);
// !!0 UnityEngine.GameObject::GetComponent<UnityEngine.Animator>()
inline Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * GameObject_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_m9904EA7E80165F7771F8AB3967F417D7C2B09996 (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * __this, const RuntimeMethod* method)
{
	return ((  Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * (*) (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F *, const RuntimeMethod*))GameObject_GetComponent_TisRuntimeObject_mD4382B2843BA9A61A01A8F9D7B9813D060F9C9CA_gshared)(__this, method);
}
// UnityEngine.AnimatorClipInfo[] UnityEngine.Animator::GetCurrentAnimatorClipInfo(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR AnimatorClipInfoU5BU5D_tCAC39F9AE6CEE1EA08285D9D5C44DB3ADD6C1ED6* Animator_GetCurrentAnimatorClipInfo_m594B9A950ECAD03E8F85A715E49010E967845462 (Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * __this, int32_t ___layerIndex0, const RuntimeMethod* method);
// UnityEngine.AnimationClip UnityEngine.AnimatorClipInfo::get_clip()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR AnimationClip_t336CFC94F6275526DC0B9BEEF833D4D89D6DEDDE * AnimatorClipInfo_get_clip_mF5A49B54502CBFE17327989ED0701EDC23F1B2A4 (AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180 * __this, const RuntimeMethod* method);
// System.Single UnityEngine.AnimationClip::get_length()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float AnimationClip_get_length_m55DCD61003D76E19AB0B3649A3C0F072D829CD4A (AnimationClip_t336CFC94F6275526DC0B9BEEF833D4D89D6DEDDE * __this, const RuntimeMethod* method);
// System.Void UnityEngine.WaitForSeconds::.ctor(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void WaitForSeconds__ctor_m8E4BA3E27AEFFE5B74A815F26FF8AAB99743F559 (WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8 * __this, float ___seconds0, const RuntimeMethod* method);
// System.Void System.NotSupportedException::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void NotSupportedException__ctor_mA121DE1CAC8F25277DEB489DC7771209D91CAE33 (NotSupportedException_tE75B318D6590A02A5D9B29FD97409B1750FA0010 * __this, const RuntimeMethod* method);
// System.Boolean UnityEngine.Object::op_Equality(UnityEngine.Object,UnityEngine.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Object_op_Equality_mBC2401774F3BE33E8CF6F0A8148E66C95D6CFF1C (Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 * ___x0, Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 * ___y1, const RuntimeMethod* method);
// !!0 UnityEngine.Object::FindObjectOfType<Door>()
inline Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * Object_FindObjectOfType_TisDoor_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1_m693E2656B1274ACB963744178B6A9C91B0D289D4 (const RuntimeMethod* method)
{
	return ((  Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * (*) (const RuntimeMethod*))Object_FindObjectOfType_TisRuntimeObject_mE3957366B74863C807E6E8A23D239A0CB079BB9C_gshared)(method);
}
// System.Void UIManager::setGameOverPanelVisible(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_setGameOverPanelVisible_m8C7780AE4FC448BD13DDDB34D2C961F3AFD810D5 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, bool ___visible0, const RuntimeMethod* method);
// UnityEngine.SceneManagement.Scene UnityEngine.SceneManagement.SceneManager::GetActiveScene()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2  SceneManager_GetActiveScene_mD583193D329EBF540D8AB8A062681B1C2AB5EA51 (const RuntimeMethod* method);
// System.String UnityEngine.SceneManagement.Scene::get_name()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR String_t* Scene_get_name_m0E63ED0F050FCC35A4216220C584BE3D3F77B0E1 (Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2 * __this, const RuntimeMethod* method);
// System.Void UnityEngine.SceneManagement.SceneManager::LoadScene(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void SceneManager_LoadScene_mFC850AC783E5EA05D6154976385DFECC251CDFB9 (String_t* ___sceneName0, const RuntimeMethod* method);
// System.Void System.Collections.Generic.List`1<Enemy>::Add(!0)
inline void List_1_Add_m6ED0FB3ABA16A3A8AF0D48619D15B4B947333F5B (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___item0, const RuntimeMethod* method)
{
	((  void (*) (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A *, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *, const RuntimeMethod*))List_1_Add_m6930161974C7504C80F52EC379EF012387D43138_gshared)(__this, ___item0, method);
}
// System.Boolean System.Collections.Generic.List`1<Enemy>::Remove(!0)
inline bool List_1_Remove_m947F635E58C7D238ADF2ACCB2C0EAE33670197C6 (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___item0, const RuntimeMethod* method)
{
	return ((  bool (*) (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A *, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *, const RuntimeMethod*))List_1_Remove_m908B647BB9F807676DACE34E3E73475C3C3751D4_gshared)(__this, ___item0, method);
}
// System.Int32 System.Collections.Generic.List`1<Enemy>::get_Count()
inline int32_t List_1_get_Count_m2EA40FDD7BE2FB22B8227B533BAA8D316CC4BE3E_inline (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * __this, const RuntimeMethod* method)
{
	return ((  int32_t (*) (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A *, const RuntimeMethod*))List_1_get_Count_m507C9149FF7F83AAC72C29091E745D557DA47D22_gshared_inline)(__this, method);
}
// System.Void Door::OpenDoor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Door_OpenDoor_mD650E2A85F5958F335166BA83EA91EB3923F992E (Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * __this, const RuntimeMethod* method);
// System.Void GameManager::SaveData()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_SaveData_mCA8C4D89F3C20776CAA9E31AA4AF2193A518048E (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method);
// System.Int32 UnityEngine.SceneManagement.Scene::get_buildIndex()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t Scene_get_buildIndex_m764659943B7357F5D6C9165F68EDCFBBDDD6C3C2 (Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2 * __this, const RuntimeMethod* method);
// System.Void UnityEngine.SceneManagement.SceneManager::LoadScene(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void SceneManager_LoadScene_m258051AAA1489D2D8B252815A45C1E9A2C097201 (int32_t ___sceneBuildIndex0, const RuntimeMethod* method);
// System.Void UnityEngine.Application::Quit()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Application_Quit_mA005EB22CB989AC3794334754F15E1C0D2FF1C95 (const RuntimeMethod* method);
// System.Boolean UnityEngine.PlayerPrefs::HasKey(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool PlayerPrefs_HasKey_mD87D3051ACE7EC6F5B54F4FC9E18572C917CA0D1 (String_t* ___key0, const RuntimeMethod* method);
// System.Void UnityEngine.PlayerPrefs::SetFloat(System.String,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerPrefs_SetFloat_mA58D5A6903B002A03BDEF35B34063E96C8483A35 (String_t* ___key0, float ___value1, const RuntimeMethod* method);
// System.Single UnityEngine.PlayerPrefs::GetFloat(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float PlayerPrefs_GetFloat_m254A03CC8DCA9E12EE09A016B64EDB7AB9938957 (String_t* ___key0, const RuntimeMethod* method);
// System.Void System.Collections.Generic.List`1<Enemy>::.ctor()
inline void List_1__ctor_m4DBD7BFCF2ABB429466D1A3CA5ECA1D15C1FEEC6 (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * __this, const RuntimeMethod* method)
{
	((  void (*) (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A *, const RuntimeMethod*))List_1__ctor_mC832F1AC0F814BAEB19175F5D7972A7507508BC3_gshared)(__this, method);
}
// !!0 UnityEngine.GameObject::GetComponent<UnityEngine.Rigidbody2D>()
inline Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * GameObject_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mDDB82F02C3053DCC0D60C420752A11EC11CBACC0 (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * __this, const RuntimeMethod* method)
{
	return ((  Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * (*) (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F *, const RuntimeMethod*))GameObject_GetComponent_TisRuntimeObject_mD4382B2843BA9A61A01A8F9D7B9813D060F9C9CA_gshared)(__this, method);
}
// System.Single Joystick::SnapFloat(System.Single,AxisOptions)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_SnapFloat_mCEF2520CAC111659A65B73C418F5E6FF1CFF05C2 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___value0, int32_t ___snapAxis1, const RuntimeMethod* method);
// System.Single Joystick::get_Horizontal()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_get_Horizontal_mD2CEADF3C7AD02BA60F7990F1A39BC67C6D8819B (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method);
// System.Single Joystick::get_Vertical()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_get_Vertical_m2326D40EF66E0A5E2B34F9CF02A53C05CCAFDED0 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method);
// AxisOptions Joystick::get_AxisOptions()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t Joystick_get_AxisOptions_m41669BF41810BA976B1A230E1FB3ADCDC1F4C758 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method);
// System.Void Joystick::set_HandleRange(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_set_HandleRange_m93B28B83AB3DC010C509C16A76BE34896C27B647 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___value0, const RuntimeMethod* method);
// System.Void Joystick::set_DeadZone(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_set_DeadZone_mF8F4688B5A32363F2EF7DE0A0FF90B7D65F11C8B (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___value0, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<UnityEngine.RectTransform>()
inline RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * Component_GetComponent_TisRectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20_mEF939F54B6B56187EC11E16F51DCB12EB62C2103 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// !!0 UnityEngine.Component::GetComponentInParent<UnityEngine.Canvas>()
inline Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * Component_GetComponentInParent_TisCanvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591_mD91B8112B5688783ACAEA46BB2C82C6EC4C4B33B (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponentInParent_TisRuntimeObject_m3D5E351D50C60522BD31D282D044F6527C382749_gshared)(__this, method);
}
// System.Void UnityEngine.Debug::LogError(System.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Debug_LogError_m3BCF9B78263152261565DCA9DB7D55F0C391ED29 (RuntimeObject * ___message0, const RuntimeMethod* method);
// System.Void UnityEngine.RectTransform::set_pivot(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void RectTransform_set_pivot_mB791A383B3C870B9CBD7BC51B2C95711C88E9DCF (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___value0, const RuntimeMethod* method);
// System.Void UnityEngine.RectTransform::set_anchorMin(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void RectTransform_set_anchorMin_mE965F5B0902C2554635010A5752728414A57020A (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___value0, const RuntimeMethod* method);
// System.Void UnityEngine.RectTransform::set_anchorMax(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void RectTransform_set_anchorMax_m55EEF00D9E42FE542B5346D7CEDAF9248736F7D3 (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___value0, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::get_zero()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8 (const RuntimeMethod* method);
// System.Void Joystick::OnDrag(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_OnDrag_m5C8DBE5110822CAF8A7DEDDE6AC240D2C1BDD7C4 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method);
// UnityEngine.RenderMode UnityEngine.Canvas::get_renderMode()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t Canvas_get_renderMode_mAF68701B143F01C7D19B6C7D3033E3B34ECB2FC8 (Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * __this, const RuntimeMethod* method);
// UnityEngine.Camera UnityEngine.Canvas::get_worldCamera()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * Canvas_get_worldCamera_m36F1A8DBFC4AB34278125DA017CACDC873F53409 (Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.RectTransformUtility::WorldToScreenPoint(UnityEngine.Camera,UnityEngine.Vector3)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  RectTransformUtility_WorldToScreenPoint_m114DFD961456722DED0FFB2F8DCB46A04C2CCA20 (Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * ___cam0, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___worldPoint1, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.RectTransform::get_sizeDelta()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  RectTransform_get_sizeDelta_mDA0A3E73679143B1B52CE2F9A417F90CB9F3DAFF (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::op_Division(UnityEngine.Vector2,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_op_Division_m0961A935168EE6701E098E2B37013DFFF46A5077 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___a0, float ___d1, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::op_Subtraction(UnityEngine.Vector2,UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_op_Subtraction_m2B347E4311EDBBBF27573E34899D2492E6B063C0 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___a0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___b1, const RuntimeMethod* method);
// System.Single UnityEngine.Canvas::get_scaleFactor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Canvas_get_scaleFactor_m0F6D59E75F7605ABD2AFF6AF32A1097226CE060A (Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::op_Division(UnityEngine.Vector2,UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_op_Division_mEF4FA1379564288637A7CF5E73BA30CA2259E591 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___a0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___b1, const RuntimeMethod* method);
// System.Void Joystick::FormatInput()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_FormatInput_mDE5D2FB4C4FB309B92816E806756B01F61FF26D5 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method);
// System.Single UnityEngine.Vector2::get_magnitude()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Vector2_get_magnitude_m66097AFDF9696BD3E88467D4398D4F82B8A4C7DF (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::get_normalized()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_get_normalized_m058E75C38C6FC66E178D7C8EF1B6298DE8F0E14B (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.Vector2::get_up()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Vector2_get_up_mC4548731D5E7C71164D18C390A1AC32501DAE441 (const RuntimeMethod* method);
// System.Single UnityEngine.Vector2::Angle(UnityEngine.Vector2,UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Vector2_Angle_mC4A140B49B9E737C9FC6B52763468C5662A8B4AC (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___from0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___to1, const RuntimeMethod* method);
// System.Boolean UnityEngine.RectTransformUtility::ScreenPointToLocalPointInRectangle(UnityEngine.RectTransform,UnityEngine.Vector2,UnityEngine.Camera,UnityEngine.Vector2&)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool RectTransformUtility_ScreenPointToLocalPointInRectangle_m2C389D4DCBB3CADB51A793702F13DF7CE837E153 (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * ___rect0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___screenPoint1, Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * ___cam2, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * ___localPoint3, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.RectTransform::get_pivot()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  RectTransform_get_pivot_mA5BEEE2069ACA7C0C717530EED3E7D811D46C463 (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, const RuntimeMethod* method);
// UnityEngine.Vector2 UnityEngine.RectTransform::get_anchorMax()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  RectTransform_get_anchorMax_m1E51C211FBB32326C884375C9F1E8E8221E5C086 (RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * __this, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Vector3::get_forward()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Vector3_get_forward_m3E2E192B3302130098738C308FA1EE1439449D0D (const RuntimeMethod* method);
// System.Single UnityEngine.Time::get_fixedDeltaTime()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Time_get_fixedDeltaTime_m76C241EDB6F824713AF57DCECD5765871770FA4C (const RuntimeMethod* method);
// System.Void UnityEngine.Rigidbody::AddForce(UnityEngine.Vector3,UnityEngine.ForceMode)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Rigidbody_AddForce_mD64ACF772614FE36CFD8A477A07A407B35DF1A54 (Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5 * __this, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___force0, int32_t ___mode1, const RuntimeMethod* method);
// System.Void VariableJoystick::SetMode(JoystickType)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick_SetMode_m222D977BBDA4E253D4EAF1E55925FAD333EA7CAE (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, int32_t ___joystickType0, const RuntimeMethod* method);
// System.Void Joystick::set_AxisOptions(AxisOptions)
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR void Joystick_set_AxisOptions_m3194AF6B83B35084063737EBA7D8C10C652241F8_inline (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, int32_t ___value0, const RuntimeMethod* method);
// System.Void UnityEngine.UI.Image::set_sprite(UnityEngine.Sprite)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Image_set_sprite_m77F8D681D4EE6D58F4F235AFF704C3EB165A9646 (Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * __this, Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * ___value0, const RuntimeMethod* method);
// System.Void Joystick::set_SnapX(System.Boolean)
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR void Joystick_set_SnapX_mACA46808CD8386CABE024E9F55A407F0C8A138F0_inline (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, bool ___value0, const RuntimeMethod* method);
// System.Void Joystick::set_SnapY(System.Boolean)
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR void Joystick_set_SnapY_mA985E49A53EBD417CF06948C805588612C0395C1_inline (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, bool ___value0, const RuntimeMethod* method);
// UnityEngine.Vector2 Joystick::get_Direction()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Joystick_get_Direction_mF64961ED5359C8E31E79CAA306019CB66DF50F3E (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method);
// System.String System.String::Concat(System.Object,System.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR String_t* String_Concat_mBB19C73816BDD1C3519F248E1ADC8E11A6FDB495 (RuntimeObject * ___arg00, RuntimeObject * ___arg11, const RuntimeMethod* method);
// System.Void Enemy::SwitchPoint()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_SwitchPoint_mEB5076531D4C2544BD715A31A29A7355F19EDE11 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Component::GetComponent<PlayerController>()
inline PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * Component_GetComponent_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_m503EAA28F55B66971C880C00538F81DCCB8C1629 (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 * __this, const RuntimeMethod* method)
{
	return ((  PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * (*) (Component_t05064EF382ABCAF4B8C94F8A350EA85184C26621 *, const RuntimeMethod*))Component_GetComponent_TisRuntimeObject_m129DEF8A66683189ED44B21496135824743EF617_gshared)(__this, method);
}
// UnityEngine.Vector2 UnityEngine.Rigidbody2D::get_velocity()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Rigidbody2D_get_velocity_m5ABF36BDF90FD7308BE608667B9E8F3DA5A207F1 (Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * __this, const RuntimeMethod* method);
// System.Void UnityEngine.Animator::SetFloat(System.String,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Animator_SetFloat_mE4C29F6980EBBBD954637721E6E13A0BE2B13C43 (Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * __this, String_t* ___name0, float ___value1, const RuntimeMethod* method);
// System.Single GameManager::LoadHealth()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float GameManager_LoadHealth_mC037637C61400A7CFE7D50A9751533B40070B43A (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method);
// System.Void UIManager::UpdateHealth(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_UpdateHealth_mA054577A97EB1BD7C09B4161A32DAC4712F49DC6 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, float ___currentHealth0, const RuntimeMethod* method);
// !!0 UnityEngine.Object::FindObjectOfType<FixedJoystick>()
inline FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * Object_FindObjectOfType_TisFixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909_m15640DCFA39A3D28A6190EB0A4D8775B029FC5E8 (const RuntimeMethod* method)
{
	return ((  FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * (*) (const RuntimeMethod*))Object_FindObjectOfType_TisRuntimeObject_mE3957366B74863C807E6E8A23D239A0CB079BB9C_gshared)(method);
}
// System.Void PlayerController::CheckInput()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_CheckInput_mAC03BF1E0CD4690383608EFCB41FFBD962F86FDF (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method);
// System.Void UnityEngine.Rigidbody2D::set_velocity(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Rigidbody2D_set_velocity_mE0DBCE5B683024B106C2AB6943BBA550B5BD0B83 (Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___value0, const RuntimeMethod* method);
// System.Void PlayerController::PhysicsCheck()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_PhysicsCheck_mF0842B47CA0495F34DE0891387C9AB27614396D5 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method);
// System.Void PlayerController::Movement()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Movement_m49DA15D9DBCDD7D61B472B373607DB69054C847C (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method);
// System.Void PlayerController::Jump()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Jump_m3056E2DF0CD8445804DCDAB6521E81541F0218A1 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method);
// UnityEngine.Quaternion UnityEngine.Transform::get_rotation()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  Transform_get_rotation_m3AB90A67403249AECCA5E02BC70FCE8C90FE9FB9 (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, const RuntimeMethod* method);
// !!0 UnityEngine.Object::Instantiate<UnityEngine.GameObject>(!!0,UnityEngine.Vector3,UnityEngine.Quaternion)
inline GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * Object_Instantiate_TisGameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F_m4F397BCC6697902B40033E61129D4EA6FE93570F (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * ___original0, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___position1, Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  ___rotation2, const RuntimeMethod* method)
{
	return ((  GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * (*) (GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F *, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 , Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357 , const RuntimeMethod*))Object_Instantiate_TisRuntimeObject_m352D452C728667C9C76C942525CDE26444568ECD_gshared)(___original0, ___position1, ___rotation2, method);
}
// System.Void UnityEngine.Vector3::.ctor(System.Single,System.Single,System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Vector3__ctor_m08F61F548AA5836D8789843ACB4A81E4963D2EE1 (Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720 * __this, float ___x0, float ___y1, float ___z2, const RuntimeMethod* method);
// System.Void UnityEngine.Transform::set_localScale(UnityEngine.Vector3)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Transform_set_localScale_m7ED1A6E5A87CD1D483515B99D6D3121FB92B0556 (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  ___value0, const RuntimeMethod* method);
// System.Boolean UnityEngine.Input::GetButtonDown(System.String)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Input_GetButtonDown_m1E80BAC5CCBE9E0151491B8F8F5FFD6AB050BBF0 (String_t* ___buttonName0, const RuntimeMethod* method);
// System.Boolean UnityEngine.Input::GetKeyDown(UnityEngine.KeyCode)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Input_GetKeyDown_mEA57896808B6F484B12CD0AEEB83390A3CFCDBDC (int32_t ___key0, const RuntimeMethod* method);
// System.Void PlayerController::Attack()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Attack_m763538E8539EF73BF10B02AC22C9882C8F8006F2 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method);
// System.Void PlayerController::KickBomb()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_KickBomb_m57A89383EE50DA2C527DC6BDA51F79A80AA0E2C5 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method);
// System.Void UnityEngine.Rigidbody2D::set_gravityScale(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Rigidbody2D_set_gravityScale_m4593B8D87314F00947B795AA442B90F1598B1104 (Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * __this, float ___value0, const RuntimeMethod* method);
// UnityEngine.Collider2D UnityEngine.Physics2D::OverlapCircle(UnityEngine.Vector2,System.Single,System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * Physics2D_OverlapCircle_m627FB9EE641A74B942877F57DD2FED656FDA5DC9 (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___point0, float ___radius1, int32_t ___layerMask2, const RuntimeMethod* method);
// System.Boolean UnityEngine.Object::op_Implicit(UnityEngine.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Object_op_Implicit_m8B2A44B4B1406ED346D1AE6D962294FD58D0D534 (Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 * ___exists0, const RuntimeMethod* method);
// System.Void GameManager::GameOver()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_GameOver_m658E745BE197CC36CFAE422F8037F41A1B7FFFD3 (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method);
// System.Void UnityEngine.Time::set_timeScale(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Time_set_timeScale_mAB89C3BB5DEE81934159C23F103397A77AC3F4AF (float ___value0, const RuntimeMethod* method);
// System.Void UnityEngine.UI.Slider::set_maxValue(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Slider_set_maxValue_m45561A3731F4EB48C10715E062856824B5AEF20B (Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 * __this, float ___value0, const RuntimeMethod* method);
// UnityEngine.Vector3 UnityEngine.Transform::get_localScale()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  Transform_get_localScale_mD8F631021C2D62B7C341B1A17FA75491F64E13DA (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * __this, const RuntimeMethod* method);
// System.Void System.ThrowHelper::ThrowArgumentOutOfRangeException()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ThrowHelper_ThrowArgumentOutOfRangeException_mBA2AF20A35144E0C43CD721A22EAC9FCA15D6550 (const RuntimeMethod* method);
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void AttachState::OnEnterState(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void AttachState_OnEnterState_m90BCF2B9BE847C4CF96035372DEF4D2570E8DB6D (AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (AttachState_OnEnterState_m90BCF2B9BE847C4CF96035372DEF4D2570E8DB6D_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// enemy.animState = 2;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_0 = ___enemy0;
		NullCheck(L_0);
		L_0->set_animState_12(2);
		// enemy.targetPoint = enemy.attackList[0];
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_1 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_2 = ___enemy0;
		NullCheck(L_2);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_3 = L_2->get_attackList_9();
		NullCheck(L_3);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_4 = List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_inline(L_3, 0, /*hidden argument*/List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_RuntimeMethod_var);
		NullCheck(L_1);
		L_1->set_targetPoint_8(L_4);
		// }
		return;
	}
}
// System.Void AttachState::OnUpdate(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void AttachState_OnUpdate_m5F611E55C81227D824A540AE30D67ECBCDB386F0 (AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (AttachState_OnUpdate_m5F611E55C81227D824A540AE30D67ECBCDB386F0_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	int32_t V_0 = 0;
	{
		// if (enemy.attackList.Count == 0)
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_0 = ___enemy0;
		NullCheck(L_0);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_1 = L_0->get_attackList_9();
		NullCheck(L_1);
		int32_t L_2 = List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline(L_1, /*hidden argument*/List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var);
		if (L_2)
		{
			goto IL_001a;
		}
	}
	{
		// enemy.TransitionToState(enemy.patrolState);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_3 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_4 = ___enemy0;
		NullCheck(L_4);
		PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * L_5 = L_4->get_patrolState_14();
		NullCheck(L_3);
		Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE(L_3, L_5, /*hidden argument*/NULL);
		// }
		return;
	}

IL_001a:
	{
		// if (enemy.attackList.Count > 1)
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_6 = ___enemy0;
		NullCheck(L_6);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_7 = L_6->get_attackList_9();
		NullCheck(L_7);
		int32_t L_8 = List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline(L_7, /*hidden argument*/List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var);
		if ((((int32_t)L_8) <= ((int32_t)1)))
		{
			goto IL_00a6;
		}
	}
	{
		// for (int i = 0; i < enemy.attackList.Count; i++)
		V_0 = 0;
		goto IL_0096;
	}

IL_002c:
	{
		// if (Mathf.Abs(enemy.transform.position.x - enemy.attackList[i].position.x) <
		//     Mathf.Abs(enemy.transform.position.x - enemy.targetPoint.position.x))
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_9 = ___enemy0;
		NullCheck(L_9);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_10 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_9, /*hidden argument*/NULL);
		NullCheck(L_10);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_11 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_10, /*hidden argument*/NULL);
		float L_12 = L_11.get_x_2();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_13 = ___enemy0;
		NullCheck(L_13);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_14 = L_13->get_attackList_9();
		int32_t L_15 = V_0;
		NullCheck(L_14);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_16 = List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_inline(L_14, L_15, /*hidden argument*/List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_RuntimeMethod_var);
		NullCheck(L_16);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_17 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_16, /*hidden argument*/NULL);
		float L_18 = L_17.get_x_2();
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_19 = fabsf(((float)il2cpp_codegen_subtract((float)L_12, (float)L_18)));
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_20 = ___enemy0;
		NullCheck(L_20);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_21 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_20, /*hidden argument*/NULL);
		NullCheck(L_21);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_22 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_21, /*hidden argument*/NULL);
		float L_23 = L_22.get_x_2();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_24 = ___enemy0;
		NullCheck(L_24);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_25 = L_24->get_targetPoint_8();
		NullCheck(L_25);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_26 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_25, /*hidden argument*/NULL);
		float L_27 = L_26.get_x_2();
		float L_28 = fabsf(((float)il2cpp_codegen_subtract((float)L_23, (float)L_27)));
		if ((!(((float)L_19) < ((float)L_28))))
		{
			goto IL_0092;
		}
	}
	{
		// enemy.targetPoint = enemy.attackList[i];
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_29 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_30 = ___enemy0;
		NullCheck(L_30);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_31 = L_30->get_attackList_9();
		int32_t L_32 = V_0;
		NullCheck(L_31);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_33 = List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_inline(L_31, L_32, /*hidden argument*/List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_RuntimeMethod_var);
		NullCheck(L_29);
		L_29->set_targetPoint_8(L_33);
	}

IL_0092:
	{
		// for (int i = 0; i < enemy.attackList.Count; i++)
		int32_t L_34 = V_0;
		V_0 = ((int32_t)il2cpp_codegen_add((int32_t)L_34, (int32_t)1));
	}

IL_0096:
	{
		// for (int i = 0; i < enemy.attackList.Count; i++)
		int32_t L_35 = V_0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_36 = ___enemy0;
		NullCheck(L_36);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_37 = L_36->get_attackList_9();
		NullCheck(L_37);
		int32_t L_38 = List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline(L_37, /*hidden argument*/List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var);
		if ((((int32_t)L_35) < ((int32_t)L_38)))
		{
			goto IL_002c;
		}
	}
	{
		// }
		goto IL_00b8;
	}

IL_00a6:
	{
		// enemy.targetPoint = enemy.attackList[0];
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_39 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_40 = ___enemy0;
		NullCheck(L_40);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_41 = L_40->get_attackList_9();
		NullCheck(L_41);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_42 = List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_inline(L_41, 0, /*hidden argument*/List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_RuntimeMethod_var);
		NullCheck(L_39);
		L_39->set_targetPoint_8(L_42);
	}

IL_00b8:
	{
		// if (enemy.targetPoint.CompareTag("Player"))
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_43 = ___enemy0;
		NullCheck(L_43);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_44 = L_43->get_targetPoint_8();
		NullCheck(L_44);
		bool L_45 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_44, _stringLiteralE53407CFE1A5156B9F0D1EED3BAB5EF3AE75CFD8, /*hidden argument*/NULL);
		if (!L_45)
		{
			goto IL_00d2;
		}
	}
	{
		// enemy.Attack();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_46 = ___enemy0;
		NullCheck(L_46);
		VirtActionInvoker0::Invoke(7 /* System.Void Enemy::Attack() */, L_46);
		goto IL_00ea;
	}

IL_00d2:
	{
		// else if (enemy.targetPoint.CompareTag("Bomb"))
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_47 = ___enemy0;
		NullCheck(L_47);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_48 = L_47->get_targetPoint_8();
		NullCheck(L_48);
		bool L_49 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_48, _stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		if (!L_49)
		{
			goto IL_00ea;
		}
	}
	{
		// enemy.SkillAttack();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_50 = ___enemy0;
		NullCheck(L_50);
		VirtActionInvoker0::Invoke(8 /* System.Void Enemy::SkillAttack() */, L_50);
	}

IL_00ea:
	{
		// enemy.MoveToTarget();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_51 = ___enemy0;
		NullCheck(L_51);
		Enemy_MoveToTarget_mCDF98A78E7279630FBE34E9183ACAE017D025132(L_51, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void AttachState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void AttachState__ctor_m2CA4845A3572836BD3E704D1A8D89466132670F2 (AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * __this, const RuntimeMethod* method)
{
	{
		EnemyBaseState__ctor_m57F25EC153F6DA435937264866B5DAFB8A7531FA(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void BaldPirate::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void BaldPirate__ctor_mFC36F66570A9E6E34ABC9C4DA420619C3B2D2B3D (BaldPirate_tFDAA12DAAC29E182FB9209202DB889303C1D9C6E * __this, const RuntimeMethod* method)
{
	{
		Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void BigGuy::PickUp()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void BigGuy_PickUp_m0FB6B02B80A702737E98AD4723BADC8A14181833 (BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (BigGuy_PickUp_m0FB6B02B80A702737E98AD4723BADC8A14181833_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (targetPoint.CompareTag("Bomb") && !hasBomb)
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_0);
		bool L_1 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_0, _stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		if (!L_1)
		{
			goto IL_0096;
		}
	}
	{
		bool L_2 = __this->get_hasBomb_24();
		if (L_2)
		{
			goto IL_0096;
		}
	}
	{
		// pickUpBomp = targetPoint.GetComponent<Bomb>();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_3);
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_4 = Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C(L_3, /*hidden argument*/Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C_RuntimeMethod_var);
		__this->set_pickUpBomp_26(L_4);
		// targetPoint.gameObject.transform.position = pickPoint.transform.position;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_5 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_5);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_6 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_5, /*hidden argument*/NULL);
		NullCheck(L_6);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_7 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_6, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_8 = __this->get_pickPoint_23();
		NullCheck(L_8);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_9 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_8, /*hidden argument*/NULL);
		NullCheck(L_9);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_10 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_9, /*hidden argument*/NULL);
		NullCheck(L_7);
		Transform_set_position_mDA89E4893F14ECA5CBEEE7FB80A5BF7C1B8EA6DC(L_7, L_10, /*hidden argument*/NULL);
		// targetPoint.SetParent(pickPoint);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_12 = __this->get_pickPoint_23();
		NullCheck(L_11);
		Transform_SetParent_mFAF9209CAB6A864552074BA065D740924A4BF979(L_11, L_12, /*hidden argument*/NULL);
		// targetPoint.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Kinematic;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_13 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_13);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_14 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(L_13, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		NullCheck(L_14);
		Rigidbody2D_set_bodyType_m239CDB6FFA033FD3B5BAC061A3F96DC9264D9900(L_14, 1, /*hidden argument*/NULL);
		// targetPoint.gameObject.layer = LayerMask.NameToLayer("NPC");
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_15 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_15);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_16 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_15, /*hidden argument*/NULL);
		int32_t L_17 = LayerMask_NameToLayer_m6491D9EA75F68B1F8AE15A9B4F193FFB9352B901(_stringLiteralF0CD420723AAE840116C8EF7DB5CAF1E0DFF2AEF, /*hidden argument*/NULL);
		NullCheck(L_16);
		GameObject_set_layer_mDAC8037FCFD0CE62DB66004C4342EA20CF604907(L_16, L_17, /*hidden argument*/NULL);
		// hasBomb = true;
		__this->set_hasBomb_24((bool)1);
	}

IL_0096:
	{
		// }
		return;
	}
}
// System.Void BigGuy::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void BigGuy_Update_mB6D9727BBA85AD81BF96DB93A0CBAF209024D71D (BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (BigGuy_Update_mB6D9727BBA85AD81BF96DB93A0CBAF209024D71D_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// base.Update();
		Enemy_Update_mE957FE3BFB8CBB7C30E43D4A81C13E02B1C1FC32(__this, /*hidden argument*/NULL);
		// anim.SetBool("hasBomb", hasBomb);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_anim_11();
		bool L_1 = __this->get_hasBomb_24();
		NullCheck(L_0);
		Animator_SetBool_m497805BA217139E42808899782FA05C15BC9879E(L_0, _stringLiteralBD85366453B6F73432017F1B07C44AC7605B218E, L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void BigGuy::Throw()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void BigGuy_Throw_m478A03D4B917C8DA808702AAF018276617C08E83 (BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (BigGuy_Throw_m478A03D4B917C8DA808702AAF018276617C08E83_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	int32_t V_0 = 0;
	{
		// if (hasBomb && null != pickUpBomp)
		bool L_0 = __this->get_hasBomb_24();
		if (!L_0)
		{
			goto IL_00c1;
		}
	}
	{
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_1 = __this->get_pickUpBomp_26();
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		bool L_2 = Object_op_Inequality_m31EF58E217E8F4BDD3E409DEF79E1AEE95874FC1((Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 *)NULL, L_1, /*hidden argument*/NULL);
		if (!L_2)
		{
			goto IL_00c1;
		}
	}
	{
		// pickUpBomp.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Dynamic;
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_3 = __this->get_pickUpBomp_26();
		NullCheck(L_3);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_4 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(L_3, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		NullCheck(L_4);
		Rigidbody2D_set_bodyType_m239CDB6FFA033FD3B5BAC061A3F96DC9264D9900(L_4, 0, /*hidden argument*/NULL);
		// pickUpBomp.gameObject.layer = LayerMask.NameToLayer("Bomb");
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_5 = __this->get_pickUpBomp_26();
		NullCheck(L_5);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_6 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_5, /*hidden argument*/NULL);
		int32_t L_7 = LayerMask_NameToLayer_m6491D9EA75F68B1F8AE15A9B4F193FFB9352B901(_stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		NullCheck(L_6);
		GameObject_set_layer_mDAC8037FCFD0CE62DB66004C4342EA20CF604907(L_6, L_7, /*hidden argument*/NULL);
		// pickUpBomp.transform.SetParent(transform.parent.parent);
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_8 = __this->get_pickUpBomp_26();
		NullCheck(L_8);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_9 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_8, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_10 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_10);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = Transform_get_parent_m8FA24E38A1FA29D90CBF3CDC9F9F017C65BB3403(L_10, /*hidden argument*/NULL);
		NullCheck(L_11);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_12 = Transform_get_parent_m8FA24E38A1FA29D90CBF3CDC9F9F017C65BB3403(L_11, /*hidden argument*/NULL);
		NullCheck(L_9);
		Transform_SetParent_mFAF9209CAB6A864552074BA065D740924A4BF979(L_9, L_12, /*hidden argument*/NULL);
		// int dir = 0;
		V_0 = 0;
		// if (FindObjectOfType<PlayerController>().gameObject.transform.position.x < transform.position.x)
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * L_13 = Object_FindObjectOfType_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_mBC133F50DBE6E9017FBA685EC7B283C09AE9EB61(/*hidden argument*/Object_FindObjectOfType_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_mBC133F50DBE6E9017FBA685EC7B283C09AE9EB61_RuntimeMethod_var);
		NullCheck(L_13);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_14 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_13, /*hidden argument*/NULL);
		NullCheck(L_14);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_15 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_14, /*hidden argument*/NULL);
		NullCheck(L_15);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_16 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_15, /*hidden argument*/NULL);
		float L_17 = L_16.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_18 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_18);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_19 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_18, /*hidden argument*/NULL);
		float L_20 = L_19.get_x_2();
		if ((!(((float)L_17) < ((float)L_20))))
		{
			goto IL_0098;
		}
	}
	{
		// dir = -1;
		V_0 = (-1);
		// }
		goto IL_009a;
	}

IL_0098:
	{
		// dir = 1;
		V_0 = 1;
	}

IL_009a:
	{
		// pickUpBomp.GetComponent<Rigidbody2D>().AddForce(new Vector2(dir, 1) * 10, ForceMode2D.Impulse);
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_21 = __this->get_pickUpBomp_26();
		NullCheck(L_21);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_22 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(L_21, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		int32_t L_23 = V_0;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_24;
		memset((&L_24), 0, sizeof(L_24));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_24), (((float)((float)L_23))), (1.0f), /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_25 = Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56(L_24, (10.0f), /*hidden argument*/NULL);
		NullCheck(L_22);
		Rigidbody2D_AddForce_m09E1A2E24DABA5BBC613E35772AE2C1C35C6E40C(L_22, L_25, 1, /*hidden argument*/NULL);
	}

IL_00c1:
	{
		// hasBomb = false;
		__this->set_hasBomb_24((bool)0);
		// }
		return;
	}
}
// System.Void BigGuy::OnTriggerStay2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void BigGuy_OnTriggerStay2D_mB7631A26A1AF13F2FEF0B1542C5C28C0CF63B0BE (BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	{
		// if (!hasBomb)
		bool L_0 = __this->get_hasBomb_24();
		if (L_0)
		{
			goto IL_000f;
		}
	}
	{
		// base.OnTriggerStay2D(collision);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_1 = ___collision0;
		Enemy_OnTriggerStay2D_m098504D6D16E60A6509C4B859814A66F9FFD9F8E(__this, L_1, /*hidden argument*/NULL);
	}

IL_000f:
	{
		// }
		return;
	}
}
// System.Void BigGuy::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void BigGuy__ctor_mE427A5EC79B196B00D13DEA279CDE8DF25854E77 (BigGuy_t459719377BBD8726765B5090C6F0E6A1AFEB59A8 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (BigGuy__ctor_mE427A5EC79B196B00D13DEA279CDE8DF25854E77_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// private PickUpState pickUpState = new PickUpState();
		PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * L_0 = (PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B *)il2cpp_codegen_object_new(PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B_il2cpp_TypeInfo_var);
		PickUpState__ctor_mADC8DE8CCF7682F0788AF688F1ADBCD0057180F4(L_0, /*hidden argument*/NULL);
		__this->set_pickUpState_25(L_0);
		Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Bomb::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_Start_m4FA5C4D6B068CCC485980698EFD6C46A0FF7BD3E (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Bomb_Start_m4FA5C4D6B068CCC485980698EFD6C46A0FF7BD3E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// startTime = Time.time;
		float L_0 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		__this->set_startTime_9(L_0);
		// anim = GetComponent<Animator>();
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_1 = Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719(__this, /*hidden argument*/Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719_RuntimeMethod_var);
		__this->set_anim_5(L_1);
		// rb = GetComponent<Rigidbody2D>();
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_2 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(__this, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		__this->set_rb_6(L_2);
		// coll = GetComponent<Collider2D>();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_3 = Component_GetComponent_TisCollider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379_m2AF5C85C582A45B02A4E940C7E8B19A065A37405(__this, /*hidden argument*/Component_GetComponent_TisCollider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379_m2AF5C85C582A45B02A4E940C7E8B19A065A37405_RuntimeMethod_var);
		__this->set_coll_7(L_3);
		// }
		return;
	}
}
// System.Void Bomb::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_Update_m10BDA079BD63F54E823DD971093D902436199792 (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Bomb_Update_m10BDA079BD63F54E823DD971093D902436199792_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// if (!anim.GetCurrentAnimatorStateInfo(0).IsName("BombOff"))
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = __this->get_anim_5();
		NullCheck(L_0);
		AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  L_1 = Animator_GetCurrentAnimatorStateInfo_mBE5ED0D60A6F5CD0EDD40AF1494098D4E7BF84F2(L_0, 0, /*hidden argument*/NULL);
		V_0 = L_1;
		bool L_2 = AnimatorStateInfo_IsName_mD133471910C1ACE0979F3FD11462C9B8BB24CA96((AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 *)(&V_0), _stringLiteralB294858A96AAF5BD4F57C1ABF5EB3A23D5C5390C, /*hidden argument*/NULL);
		if (L_2)
		{
			goto IL_003f;
		}
	}
	{
		// if (Time.time > startTime + waitTime)
		float L_3 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		float L_4 = __this->get_startTime_9();
		float L_5 = __this->get_waitTime_10();
		if ((!(((float)L_3) > ((float)((float)il2cpp_codegen_add((float)L_4, (float)L_5))))))
		{
			goto IL_003f;
		}
	}
	{
		// anim.Play("BombExplotion");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_6 = __this->get_anim_5();
		NullCheck(L_6);
		Animator_Play_m254CA699DF64E86856EC8C54D1A739E3C0A49793(L_6, _stringLiteralBE51B119CB46BF201B86E3CA8FAF61471F8CBEB9, /*hidden argument*/NULL);
	}

IL_003f:
	{
		// }
		return;
	}
}
// System.Void Bomb::OnDrawGizmos()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_OnDrawGizmos_m4CFB6AF87CAEAF51900537C806A8CB632C027BDC (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	{
		// Gizmos.DrawWireSphere(transform.position, radius);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		float L_2 = __this->get_radius_11();
		Gizmos_DrawWireSphere_mF6F2BC5CDF7B3F312FE9AB579CDC1C6B72154BCF(L_1, L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Bomb::Explotion()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_Explotion_m16ABDF7E7E4F5FFE24353FB4E31385A2B56111EC (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Bomb_Explotion_m16ABDF7E7E4F5FFE24353FB4E31385A2B56111EC_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE* V_0 = NULL;
	int32_t V_1 = 0;
	Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * V_2 = NULL;
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  V_3;
	memset((&V_3), 0, sizeof(V_3));
	AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  V_4;
	memset((&V_4), 0, sizeof(V_4));
	{
		// Collider2D[] aroundObjects = Physics2D.OverlapCircleAll(transform.position, radius, targeLayer);//??????
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_1, /*hidden argument*/NULL);
		float L_3 = __this->get_radius_11();
		LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  L_4 = __this->get_targeLayer_8();
		int32_t L_5 = LayerMask_op_Implicit_m2AFFC7F931005437E8F356C953F439829AF4CFA5(L_4, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Physics2D_tB21970F986016656D66D2922594F336E1EE7D5C7_il2cpp_TypeInfo_var);
		Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE* L_6 = Physics2D_OverlapCircleAll_m9711B169E5705A2B07AF64095E8271CD21E05FD8(L_2, L_3, L_5, /*hidden argument*/NULL);
		// foreach (var item in aroundObjects)
		V_0 = L_6;
		V_1 = 0;
		goto IL_00ec;
	}

IL_002e:
	{
		// foreach (var item in aroundObjects)
		Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE* L_7 = V_0;
		int32_t L_8 = V_1;
		NullCheck(L_7);
		int32_t L_9 = L_8;
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_10 = (L_7)->GetAt(static_cast<il2cpp_array_size_t>(L_9));
		V_2 = L_10;
		// Vector3 pos = transform.position - item.transform.position;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_11);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_12 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_11, /*hidden argument*/NULL);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_13 = V_2;
		NullCheck(L_13);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_14 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_13, /*hidden argument*/NULL);
		NullCheck(L_14);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_15 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_14, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_16 = Vector3_op_Subtraction_mF9846B723A5034F8B9F5F5DCB78E3D67649143D3(L_12, L_15, /*hidden argument*/NULL);
		V_3 = L_16;
		// item.GetComponent<Rigidbody2D>().AddForce((-pos + Vector3.up) * bombForce, ForceMode2D.Impulse);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_17 = V_2;
		NullCheck(L_17);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_18 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(L_17, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_19 = V_3;
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_20 = Vector3_op_UnaryNegation_m2AFBBF22801F9BCA5A4EBE642A29F433FE1339C2(L_19, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_21 = Vector3_get_up_m6309EBC4E42D6D0B3D28056BD23D0331275306F7(/*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_22 = Vector3_op_Addition_m929F9C17E5D11B94D50B4AFF1D730B70CB59B50E(L_20, L_21, /*hidden argument*/NULL);
		float L_23 = __this->get_bombForce_12();
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_24 = Vector3_op_Multiply_m1C5F07723615156ACF035D88A1280A9E8F35A04E(L_22, L_23, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_25 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_24, /*hidden argument*/NULL);
		NullCheck(L_18);
		Rigidbody2D_AddForce_m09E1A2E24DABA5BBC613E35772AE2C1C35C6E40C(L_18, L_25, 1, /*hidden argument*/NULL);
		// if (item.CompareTag("Bomb") && item.GetComponent<Animator>().GetCurrentAnimatorStateInfo(0).IsName("BombOff"))
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_26 = V_2;
		NullCheck(L_26);
		bool L_27 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_26, _stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		if (!L_27)
		{
			goto IL_00ae;
		}
	}
	{
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_28 = V_2;
		NullCheck(L_28);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_29 = Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719(L_28, /*hidden argument*/Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719_RuntimeMethod_var);
		NullCheck(L_29);
		AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  L_30 = Animator_GetCurrentAnimatorStateInfo_mBE5ED0D60A6F5CD0EDD40AF1494098D4E7BF84F2(L_29, 0, /*hidden argument*/NULL);
		V_4 = L_30;
		bool L_31 = AnimatorStateInfo_IsName_mD133471910C1ACE0979F3FD11462C9B8BB24CA96((AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 *)(&V_4), _stringLiteralB294858A96AAF5BD4F57C1ABF5EB3A23D5C5390C, /*hidden argument*/NULL);
		if (!L_31)
		{
			goto IL_00ae;
		}
	}
	{
		// item.GetComponent<Bomb>().TurnOn();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_32 = V_2;
		NullCheck(L_32);
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_33 = Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C(L_32, /*hidden argument*/Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C_RuntimeMethod_var);
		NullCheck(L_33);
		Bomb_TurnOn_m2581D46C074B7BBE84864715A3960531E943D466(L_33, /*hidden argument*/NULL);
	}

IL_00ae:
	{
		// if (item.CompareTag("Player"))
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_34 = V_2;
		NullCheck(L_34);
		bool L_35 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_34, _stringLiteralE53407CFE1A5156B9F0D1EED3BAB5EF3AE75CFD8, /*hidden argument*/NULL);
		if (!L_35)
		{
			goto IL_00cb;
		}
	}
	{
		// item.GetComponent<IDamageable>().GetHit(2);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_36 = V_2;
		NullCheck(L_36);
		RuntimeObject* L_37 = Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068(L_36, /*hidden argument*/Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068_RuntimeMethod_var);
		NullCheck(L_37);
		InterfaceActionInvoker1< float >::Invoke(0 /* System.Void IDamageable::GetHit(System.Single) */, IDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_il2cpp_TypeInfo_var, L_37, (2.0f));
	}

IL_00cb:
	{
		// if (item.CompareTag("Enemy"))
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_38 = V_2;
		NullCheck(L_38);
		bool L_39 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_38, _stringLiteralA25632F8F4FF9659997A848C2EBEEF27D0974164, /*hidden argument*/NULL);
		if (!L_39)
		{
			goto IL_00e8;
		}
	}
	{
		// item.GetComponent<IDamageable>().GetHit(2);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_40 = V_2;
		NullCheck(L_40);
		RuntimeObject* L_41 = Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068(L_40, /*hidden argument*/Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068_RuntimeMethod_var);
		NullCheck(L_41);
		InterfaceActionInvoker1< float >::Invoke(0 /* System.Void IDamageable::GetHit(System.Single) */, IDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_il2cpp_TypeInfo_var, L_41, (2.0f));
	}

IL_00e8:
	{
		int32_t L_42 = V_1;
		V_1 = ((int32_t)il2cpp_codegen_add((int32_t)L_42, (int32_t)1));
	}

IL_00ec:
	{
		// foreach (var item in aroundObjects)
		int32_t L_43 = V_1;
		Collider2DU5BU5D_tE7ADA0C1D125B4C684675B9A026E18C3857903AE* L_44 = V_0;
		NullCheck(L_44);
		if ((((int32_t)L_43) < ((int32_t)(((int32_t)((int32_t)(((RuntimeArray*)L_44)->max_length)))))))
		{
			goto IL_002e;
		}
	}
	{
		// explotionNotify(transform);
		ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * L_45 = __this->get_explotionNotify_4();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_46 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_45);
		ExplotionNotify_Invoke_m222C621FC0219AADEC8ED8666986B2B240CFBA39(L_45, L_46, /*hidden argument*/NULL);
		// explotionNotify = null;
		__this->set_explotionNotify_4((ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C *)NULL);
		// }
		return;
	}
}
// System.Void Bomb::DestroyThis()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_DestroyThis_m1F33C8D0E1DD2A906F83DA8B718B91FA3026B3EC (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Bomb_DestroyThis_m1F33C8D0E1DD2A906F83DA8B718B91FA3026B3EC_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// Destroy(gameObject);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		Object_Destroy_m23B4562495BA35A74266D4372D45368F8C05109A(L_0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Bomb::TurnOff()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_TurnOff_mAF8955158FE03383BD5C734628B71CCA19ABE778 (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Bomb_TurnOff_mAF8955158FE03383BD5C734628B71CCA19ABE778_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// anim.Play("BombOff");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = __this->get_anim_5();
		NullCheck(L_0);
		Animator_Play_m254CA699DF64E86856EC8C54D1A739E3C0A49793(L_0, _stringLiteralB294858A96AAF5BD4F57C1ABF5EB3A23D5C5390C, /*hidden argument*/NULL);
		// gameObject.layer = LayerMask.NameToLayer("NPC");
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_1 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		int32_t L_2 = LayerMask_NameToLayer_m6491D9EA75F68B1F8AE15A9B4F193FFB9352B901(_stringLiteralF0CD420723AAE840116C8EF7DB5CAF1E0DFF2AEF, /*hidden argument*/NULL);
		NullCheck(L_1);
		GameObject_set_layer_mDAC8037FCFD0CE62DB66004C4342EA20CF604907(L_1, L_2, /*hidden argument*/NULL);
		// gameObject.GetComponent<SpriteRenderer>().sortingLayerName = "NPC";
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_3 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		NullCheck(L_3);
		SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * L_4 = GameObject_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mD25CEAAA219FA1235F8E88F914D2F8AC57303538(L_3, /*hidden argument*/GameObject_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mD25CEAAA219FA1235F8E88F914D2F8AC57303538_RuntimeMethod_var);
		NullCheck(L_4);
		Renderer_set_sortingLayerName_m8DCB7B753F22739F79E065922F6201E8EDD08E8F(L_4, _stringLiteralF0CD420723AAE840116C8EF7DB5CAF1E0DFF2AEF, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Bomb::TurnOn()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_TurnOn_m2581D46C074B7BBE84864715A3960531E943D466 (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Bomb_TurnOn_m2581D46C074B7BBE84864715A3960531E943D466_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// anim.Play("BomoOn");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = __this->get_anim_5();
		NullCheck(L_0);
		Animator_Play_m254CA699DF64E86856EC8C54D1A739E3C0A49793(L_0, _stringLiteralAD9EDCF2B05FBB1E0B62FCD911EC901DEECF9843, /*hidden argument*/NULL);
		// gameObject.layer = LayerMask.NameToLayer("Bomb");
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_1 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		int32_t L_2 = LayerMask_NameToLayer_m6491D9EA75F68B1F8AE15A9B4F193FFB9352B901(_stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		NullCheck(L_1);
		GameObject_set_layer_mDAC8037FCFD0CE62DB66004C4342EA20CF604907(L_1, L_2, /*hidden argument*/NULL);
		// gameObject.GetComponent<SpriteRenderer>().sortingLayerName = "Bomb";
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_3 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		NullCheck(L_3);
		SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * L_4 = GameObject_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mD25CEAAA219FA1235F8E88F914D2F8AC57303538(L_3, /*hidden argument*/GameObject_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mD25CEAAA219FA1235F8E88F914D2F8AC57303538_RuntimeMethod_var);
		NullCheck(L_4);
		Renderer_set_sortingLayerName_m8DCB7B753F22739F79E065922F6201E8EDD08E8F(L_4, _stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		// startTime = Time.time;
		float L_5 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		__this->set_startTime_9(L_5);
		// }
		return;
	}
}
// System.Void Bomb::SetExplotionNotify(Bomb_ExplotionNotify)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb_SetExplotionNotify_m72EA3979F8FF5C949EFC9AC1B15E752AA4349768 (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * ___notify0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Bomb_SetExplotionNotify_m72EA3979F8FF5C949EFC9AC1B15E752AA4349768_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (null != explotionNotify)
		ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * L_0 = __this->get_explotionNotify_4();
		if (!L_0)
		{
			goto IL_0010;
		}
	}
	{
		// explotionNotify = notify;
		ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * L_1 = ___notify0;
		__this->set_explotionNotify_4(L_1);
		// }
		return;
	}

IL_0010:
	{
		// explotionNotify += notify;
		ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * L_2 = __this->get_explotionNotify_4();
		ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * L_3 = ___notify0;
		Delegate_t * L_4 = Delegate_Combine_mC25D2F7DECAFBA6D9A2F9EBA8A77063F0658ECF1(L_2, L_3, /*hidden argument*/NULL);
		__this->set_explotionNotify_4(((ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C *)CastclassSealed((RuntimeObject*)L_4, ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C_il2cpp_TypeInfo_var)));
		// }
		return;
	}
}
// System.Void Bomb::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Bomb__ctor_m168276948FC869A7BA91027858FABF173B76EFD7 (Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Bomb_ExplotionNotify::.ctor(System.Object,System.IntPtr)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ExplotionNotify__ctor_mCCD81CBD324678AEA2E64AF22B24C4C311261F39 (ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * __this, RuntimeObject * ___object0, intptr_t ___method1, const RuntimeMethod* method)
{
	__this->set_method_ptr_0(il2cpp_codegen_get_method_pointer((RuntimeMethod*)___method1));
	__this->set_method_3(___method1);
	__this->set_m_target_2(___object0);
}
// System.Void Bomb_ExplotionNotify::Invoke(UnityEngine.Transform)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ExplotionNotify_Invoke_m222C621FC0219AADEC8ED8666986B2B240CFBA39 (ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * __this, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___transform0, const RuntimeMethod* method)
{
	DelegateU5BU5D_tDFCDEE2A6322F96C0FE49AF47E9ADB8C4B294E86* delegateArrayToInvoke = __this->get_delegates_11();
	Delegate_t** delegatesToInvoke;
	il2cpp_array_size_t length;
	if (delegateArrayToInvoke != NULL)
	{
		length = delegateArrayToInvoke->max_length;
		delegatesToInvoke = reinterpret_cast<Delegate_t**>(delegateArrayToInvoke->GetAddressAtUnchecked(0));
	}
	else
	{
		length = 1;
		delegatesToInvoke = reinterpret_cast<Delegate_t**>(&__this);
	}

	for (il2cpp_array_size_t i = 0; i < length; i++)
	{
		Delegate_t* currentDelegate = delegatesToInvoke[i];
		Il2CppMethodPointer targetMethodPointer = currentDelegate->get_method_ptr_0();
		RuntimeObject* targetThis = currentDelegate->get_m_target_2();
		RuntimeMethod* targetMethod = (RuntimeMethod*)(currentDelegate->get_method_3());
		if (!il2cpp_codegen_method_is_virtual(targetMethod))
		{
			il2cpp_codegen_raise_execution_engine_exception_if_method_is_not_found(targetMethod);
		}
		bool ___methodIsStatic = MethodIsStatic(targetMethod);
		int ___parameterCount = il2cpp_codegen_method_parameter_count(targetMethod);
		if (___methodIsStatic)
		{
			if (___parameterCount == 1)
			{
				// open
				typedef void (*FunctionPointerType) (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*);
				((FunctionPointerType)targetMethodPointer)(___transform0, targetMethod);
			}
			else
			{
				// closed
				typedef void (*FunctionPointerType) (void*, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*);
				((FunctionPointerType)targetMethodPointer)(targetThis, ___transform0, targetMethod);
			}
		}
		else if (___parameterCount != 1)
		{
			// open
			if (il2cpp_codegen_method_is_virtual(targetMethod) && !il2cpp_codegen_object_is_of_sealed_type(targetThis) && il2cpp_codegen_delegate_has_invoker((Il2CppDelegate*)__this))
			{
				if (il2cpp_codegen_method_is_generic_instance(targetMethod))
				{
					if (il2cpp_codegen_method_is_interface_method(targetMethod))
						GenericInterfaceActionInvoker0::Invoke(targetMethod, ___transform0);
					else
						GenericVirtActionInvoker0::Invoke(targetMethod, ___transform0);
				}
				else
				{
					if (il2cpp_codegen_method_is_interface_method(targetMethod))
						InterfaceActionInvoker0::Invoke(il2cpp_codegen_method_get_slot(targetMethod), il2cpp_codegen_method_get_declaring_type(targetMethod), ___transform0);
					else
						VirtActionInvoker0::Invoke(il2cpp_codegen_method_get_slot(targetMethod), ___transform0);
				}
			}
			else
			{
				typedef void (*FunctionPointerType) (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*);
				((FunctionPointerType)targetMethodPointer)(___transform0, targetMethod);
			}
		}
		else
		{
			// closed
			if (il2cpp_codegen_method_is_virtual(targetMethod) && !il2cpp_codegen_object_is_of_sealed_type(targetThis) && il2cpp_codegen_delegate_has_invoker((Il2CppDelegate*)__this))
			{
				if (targetThis == NULL)
				{
					typedef void (*FunctionPointerType) (Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*);
					((FunctionPointerType)targetMethodPointer)(___transform0, targetMethod);
				}
				else if (il2cpp_codegen_method_is_generic_instance(targetMethod))
				{
					if (il2cpp_codegen_method_is_interface_method(targetMethod))
						GenericInterfaceActionInvoker1< Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * >::Invoke(targetMethod, targetThis, ___transform0);
					else
						GenericVirtActionInvoker1< Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * >::Invoke(targetMethod, targetThis, ___transform0);
				}
				else
				{
					if (il2cpp_codegen_method_is_interface_method(targetMethod))
						InterfaceActionInvoker1< Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * >::Invoke(il2cpp_codegen_method_get_slot(targetMethod), il2cpp_codegen_method_get_declaring_type(targetMethod), targetThis, ___transform0);
					else
						VirtActionInvoker1< Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * >::Invoke(il2cpp_codegen_method_get_slot(targetMethod), targetThis, ___transform0);
				}
			}
			else
			{
				if (targetThis == NULL && il2cpp_codegen_class_is_value_type(il2cpp_codegen_method_get_declaring_type(targetMethod)))
				{
					typedef void (*FunctionPointerType) (RuntimeObject*, const RuntimeMethod*);
					((FunctionPointerType)targetMethodPointer)((reinterpret_cast<RuntimeObject*>(___transform0) - 1), targetMethod);
				}
				else
				{
					typedef void (*FunctionPointerType) (void*, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA *, const RuntimeMethod*);
					((FunctionPointerType)targetMethodPointer)(targetThis, ___transform0, targetMethod);
				}
			}
		}
	}
}
// System.IAsyncResult Bomb_ExplotionNotify::BeginInvoke(UnityEngine.Transform,System.AsyncCallback,System.Object)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject* ExplotionNotify_BeginInvoke_m36E4F6BF1E25A22736CFC016B9AE7D3221AFAAAC (ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * __this, Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * ___transform0, AsyncCallback_t3F3DA3BEDAEE81DD1D24125DF8EB30E85EE14DA4 * ___callback1, RuntimeObject * ___object2, const RuntimeMethod* method)
{
	void *__d_args[2] = {0};
	__d_args[0] = ___transform0;
	return (RuntimeObject*)il2cpp_codegen_delegate_begin_invoke((RuntimeDelegate*)__this, __d_args, (RuntimeDelegate*)___callback1, (RuntimeObject*)___object2);
}
// System.Void Bomb_ExplotionNotify::EndInvoke(System.IAsyncResult)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void ExplotionNotify_EndInvoke_m1E73299ABF7A6A5249D5631D796D9CE1D9FA770A (ExplotionNotify_t12F2700E59953A7E995A7ED2A3FE107E2411AB9C * __this, RuntimeObject* ___result0, const RuntimeMethod* method)
{
	il2cpp_codegen_delegate_end_invoke((Il2CppAsyncResult*) ___result0, 0);
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Captain::Init()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Captain_Init_m279514E43671147A816DB46395961F7F5CB81AB0 (Captain_t1F5D011033A017D26E7A27822CC00CC4059C7F61 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Captain_Init_m279514E43671147A816DB46395961F7F5CB81AB0_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// base.Init();
		Enemy_Init_m33CE279B856CE404151706EBC893C8604099927E(__this, /*hidden argument*/NULL);
		// spriteRenderer = GetComponent<SpriteRenderer>();
		SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * L_0 = Component_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mCC209A7A6A8D6878F0CB813ED5722A59C2262693(__this, /*hidden argument*/Component_GetComponent_TisSpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F_mCC209A7A6A8D6878F0CB813ED5722A59C2262693_RuntimeMethod_var);
		__this->set_spriteRenderer_23(L_0);
		// }
		return;
	}
}
// System.Void Captain::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Captain_Update_mB8DA6E20923E5F437D89557F922767EFE7EDFA10 (Captain_t1F5D011033A017D26E7A27822CC00CC4059C7F61 * __this, const RuntimeMethod* method)
{
	{
		// base.Update();
		Enemy_Update_mE957FE3BFB8CBB7C30E43D4A81C13E02B1C1FC32(__this, /*hidden argument*/NULL);
		// if (2 != animState)
		int32_t L_0 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_animState_12();
		if ((((int32_t)2) == ((int32_t)L_0)))
		{
			goto IL_001b;
		}
	}
	{
		// spriteRenderer.flipX = false;
		SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * L_1 = __this->get_spriteRenderer_23();
		NullCheck(L_1);
		SpriteRenderer_set_flipX_mF9A738B8149D48B7B1319EBFA5787BAE38DD8DD6(L_1, (bool)0, /*hidden argument*/NULL);
	}

IL_001b:
	{
		// }
		return;
	}
}
// System.Void Captain::SkillAttack()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Captain_SkillAttack_mB9C66D63254DE157CE78F97C0186BE2FED20BBCB (Captain_t1F5D011033A017D26E7A27822CC00CC4059C7F61 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Captain_SkillAttack_mB9C66D63254DE157CE78F97C0186BE2FED20BBCB_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  V_0;
	memset((&V_0), 0, sizeof(V_0));
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  V_1;
	memset((&V_1), 0, sizeof(V_1));
	{
		// base.SkillAttack();
		Enemy_SkillAttack_m4E4DA6E8B23FB444ED5D8F3EF20F8BF818AA766E(__this, /*hidden argument*/NULL);
		// if (anim.GetCurrentAnimatorStateInfo(1).IsName("Skill"))
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_anim_11();
		NullCheck(L_0);
		AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  L_1 = Animator_GetCurrentAnimatorStateInfo_mBE5ED0D60A6F5CD0EDD40AF1494098D4E7BF84F2(L_0, 1, /*hidden argument*/NULL);
		V_0 = L_1;
		bool L_2 = AnimatorStateInfo_IsName_mD133471910C1ACE0979F3FD11462C9B8BB24CA96((AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 *)(&V_0), _stringLiteralEC9F630C8693BDEC93FF52A93E822AC67FF55503, /*hidden argument*/NULL);
		if (!L_2)
		{
			goto IL_00ad;
		}
	}
	{
		// if (transform.position.x > targetPoint.position.x)
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_3);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_4 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_3, /*hidden argument*/NULL);
		float L_5 = L_4.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_6 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_6);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_7 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_6, /*hidden argument*/NULL);
		float L_8 = L_7.get_x_2();
		if ((!(((float)L_5) > ((float)L_8))))
		{
			goto IL_004e;
		}
	}
	{
		// movePosition = Vector3.right;
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_9 = Vector3_get_right_m6DD9559CA0C75BBA42D9140021C4C2A9AAA9B3F5(/*hidden argument*/NULL);
		V_1 = L_9;
		// }
		goto IL_0054;
	}

IL_004e:
	{
		// movePosition = Vector3.left;
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_10 = Vector3_get_left_m74B52D8CFD8C62138067B2EB6846B6E9E51B7C20(/*hidden argument*/NULL);
		V_1 = L_10;
	}

IL_0054:
	{
		// transform.position = Vector2.MoveTowards(transform.position, transform.position + movePosition, speed * 2 * Time.deltaTime);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_12 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_12);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_13 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_12, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_14 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_13, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_15 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_15);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_16 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_15, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_17 = V_1;
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_18 = Vector3_op_Addition_m929F9C17E5D11B94D50B4AFF1D730B70CB59B50E(L_16, L_17, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_19 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_18, /*hidden argument*/NULL);
		float L_20 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_speed_5();
		float L_21 = Time_get_deltaTime_m16F98FC9BA931581236008C288E3B25CBCB7C81E(/*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_22 = Vector2_MoveTowards_m5CE85293E9619514164A685D1D4673E2A6E43DFA(L_14, L_19, ((float)il2cpp_codegen_multiply((float)((float)il2cpp_codegen_multiply((float)L_20, (float)(2.0f))), (float)L_21)), /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_23 = Vector2_op_Implicit_mD152B6A34B4DB7FFECC2844D74718568FE867D6F(L_22, /*hidden argument*/NULL);
		NullCheck(L_11);
		Transform_set_position_mDA89E4893F14ECA5CBEEE7FB80A5BF7C1B8EA6DC(L_11, L_23, /*hidden argument*/NULL);
		// spriteRenderer.flipX = true;
		SpriteRenderer_tCD51E875611195DBB91123B68434881D3441BC6F * L_24 = __this->get_spriteRenderer_23();
		NullCheck(L_24);
		SpriteRenderer_set_flipX_mF9A738B8149D48B7B1319EBFA5787BAE38DD8DD6(L_24, (bool)1, /*hidden argument*/NULL);
	}

IL_00ad:
	{
		// }
		return;
	}
}
// System.Void Captain::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Captain__ctor_m26D05B8EB9FC45D451F1FEECF07551C4CA9308A3 (Captain_t1F5D011033A017D26E7A27822CC00CC4059C7F61 * __this, const RuntimeMethod* method)
{
	{
		Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Cucumber::SetOff()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Cucumber_SetOff_m29170B94935D177B7E458DF9CE8476E1075C7D49 (Cucumber_t6A12FD6C9556AB3D9546BEAE41ADC29CFD9E7046 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Cucumber_SetOff_m29170B94935D177B7E458DF9CE8476E1075C7D49_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// targetPoint.GetComponent<Bomb>().TurnOff();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_0);
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_1 = Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C(L_0, /*hidden argument*/Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C_RuntimeMethod_var);
		NullCheck(L_1);
		Bomb_TurnOff_mAF8955158FE03383BD5C734628B71CCA19ABE778(L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Cucumber::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Cucumber__ctor_mEAD4CF7AE3F09D41882833626CD747F209108854 (Cucumber_t6A12FD6C9556AB3D9546BEAE41ADC29CFD9E7046 * __this, const RuntimeMethod* method)
{
	{
		Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Door::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Door_Start_m1ED335570A6A1CD834EA36D60B936A530BF00154 (Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Door_Start_m1ED335570A6A1CD834EA36D60B936A530BF00154_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// anim = GetComponent<Animator>();
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719(__this, /*hidden argument*/Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719_RuntimeMethod_var);
		__this->set_anim_4(L_0);
		// coll = GetComponent<BoxCollider2D>();
		BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * L_1 = Component_GetComponent_TisBoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87_mD4BABFD1DC7C524ACC853125D82D011DC1CC5E5B(__this, /*hidden argument*/Component_GetComponent_TisBoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87_mD4BABFD1DC7C524ACC853125D82D011DC1CC5E5B_RuntimeMethod_var);
		__this->set_coll_5(L_1);
		// coll.enabled = false;
		BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * L_2 = __this->get_coll_5();
		NullCheck(L_2);
		Behaviour_set_enabled_m9755D3B17D7022D23D1E4C618BD9A6B66A5ADC6B(L_2, (bool)0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Door::OpenDoor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Door_OpenDoor_mD650E2A85F5958F335166BA83EA91EB3923F992E (Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Door_OpenDoor_mD650E2A85F5958F335166BA83EA91EB3923F992E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// anim.Play("Open");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = __this->get_anim_4();
		NullCheck(L_0);
		Animator_Play_m254CA699DF64E86856EC8C54D1A739E3C0A49793(L_0, _stringLiteralCF9B77061F7B3126B49D50A6FA68F7CA8C26B7A3, /*hidden argument*/NULL);
		// coll.enabled = true;
		BoxCollider2D_tA3DD87FE6F65C39F0A81CDB4BEC0EDB370486E87 * L_1 = __this->get_coll_5();
		NullCheck(L_1);
		Behaviour_set_enabled_m9755D3B17D7022D23D1E4C618BD9A6B66A5ADC6B(L_1, (bool)1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Door::OnTriggerEnter2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Door_OnTriggerEnter2D_m650AD506F66F579681729162E1696ED800F7C609 (Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Door_OnTriggerEnter2D_m650AD506F66F579681729162E1696ED800F7C609_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (collision.CompareTag("Player"))
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_0 = ___collision0;
		NullCheck(L_0);
		bool L_1 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_0, _stringLiteralE53407CFE1A5156B9F0D1EED3BAB5EF3AE75CFD8, /*hidden argument*/NULL);
		if (!L_1)
		{
			goto IL_0017;
		}
	}
	{
		// GameManager.instance.NextLevel();
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_2 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		NullCheck(L_2);
		GameManager_NextLevel_mF6C956ECA09992B9D36B913E2273B39C076B71F2(L_2, /*hidden argument*/NULL);
	}

IL_0017:
	{
		// }
		return;
	}
}
// System.Void Door::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Door__ctor_mF156A3939C64A43E022EB624D9208CE0759CC202 (Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Single DynamicJoystick::get_MoveThreshold()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float DynamicJoystick_get_MoveThreshold_m475CED919EFA09D7DBC1815BE0B92B55E5E3DD92 (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, const RuntimeMethod* method)
{
	{
		// public float MoveThreshold { get { return moveThreshold; } set { moveThreshold = Mathf.Abs(value); } }
		float L_0 = __this->get_moveThreshold_15();
		return L_0;
	}
}
// System.Void DynamicJoystick::set_MoveThreshold(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DynamicJoystick_set_MoveThreshold_m41DF6070CB77AD666C343C6FCD04F2D013FF7171 (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, float ___value0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (DynamicJoystick_set_MoveThreshold_m41DF6070CB77AD666C343C6FCD04F2D013FF7171_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// public float MoveThreshold { get { return moveThreshold; } set { moveThreshold = Mathf.Abs(value); } }
		float L_0 = ___value0;
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_1 = fabsf(L_0);
		__this->set_moveThreshold_15(L_1);
		// public float MoveThreshold { get { return moveThreshold; } set { moveThreshold = Mathf.Abs(value); } }
		return;
	}
}
// System.Void DynamicJoystick::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DynamicJoystick_Start_m28FAB53F804FC3AEAA7DB62E75DA0BE645C1B494 (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, const RuntimeMethod* method)
{
	{
		// MoveThreshold = moveThreshold;
		float L_0 = __this->get_moveThreshold_15();
		DynamicJoystick_set_MoveThreshold_m41DF6070CB77AD666C343C6FCD04F2D013FF7171(__this, L_0, /*hidden argument*/NULL);
		// base.Start();
		Joystick_Start_mA4B921AF2FEC7B830AC4F0D5E49AF8934ECAD201(__this, /*hidden argument*/NULL);
		// background.gameObject.SetActive(false);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_1 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_1);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_2 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_1, /*hidden argument*/NULL);
		NullCheck(L_2);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_2, (bool)0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void DynamicJoystick::OnPointerDown(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DynamicJoystick_OnPointerDown_mF71D95263661D939DBE2E5C17C73A599E60778B9 (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	{
		// background.anchoredPosition = ScreenPointToAnchoredPosition(eventData.position);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_0 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_1 = ___eventData0;
		NullCheck(L_1);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = PointerEventData_get_position_mF25FC495A9C968C65BF34B5984616CBFB6332D55_inline(L_1, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = Joystick_ScreenPointToAnchoredPosition_mE4C429E76D0FA78FD1567EB1361AF68141706201(__this, L_2, /*hidden argument*/NULL);
		NullCheck(L_0);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_0, L_3, /*hidden argument*/NULL);
		// background.gameObject.SetActive(true);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_4 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_4);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_5 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_4, /*hidden argument*/NULL);
		NullCheck(L_5);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_5, (bool)1, /*hidden argument*/NULL);
		// base.OnPointerDown(eventData);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_6 = ___eventData0;
		Joystick_OnPointerDown_m408D43BE6A49862DFD49B5198E0B61B85A162703(__this, L_6, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void DynamicJoystick::OnPointerUp(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DynamicJoystick_OnPointerUp_mC38FD6A7ADB9CDAB0BF04235DA5110A37B10E771 (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	{
		// background.gameObject.SetActive(false);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_0 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_0);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_1 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_0, /*hidden argument*/NULL);
		NullCheck(L_1);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_1, (bool)0, /*hidden argument*/NULL);
		// base.OnPointerUp(eventData);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_2 = ___eventData0;
		Joystick_OnPointerUp_m771F7519F51F02DAADA7DE0A562F82710FA721BC(__this, L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void DynamicJoystick::HandleInput(System.Single,UnityEngine.Vector2,UnityEngine.Vector2,UnityEngine.Camera)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DynamicJoystick_HandleInput_mB6316E3D97C617061C01DC49DD829C0C4E91BB27 (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, float ___magnitude0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___normalised1, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___radius2, Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * ___cam3, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (DynamicJoystick_HandleInput_mB6316E3D97C617061C01DC49DD829C0C4E91BB27_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// if (magnitude > moveThreshold)
		float L_0 = ___magnitude0;
		float L_1 = __this->get_moveThreshold_15();
		if ((!(((float)L_0) > ((float)L_1))))
		{
			goto IL_0035;
		}
	}
	{
		// Vector2 difference = normalised * (magnitude - moveThreshold) * radius;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = ___normalised1;
		float L_3 = ___magnitude0;
		float L_4 = __this->get_moveThreshold_15();
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_5 = Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56(L_2, ((float)il2cpp_codegen_subtract((float)L_3, (float)L_4)), /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_6 = ___radius2;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_7 = Vector2_op_Multiply_mEDF9FDDF3BFFAEC997FBCDE5FA34871F2955E7C4(L_5, L_6, /*hidden argument*/NULL);
		V_0 = L_7;
		// background.anchoredPosition += difference;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_8 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_9 = L_8;
		NullCheck(L_9);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_10 = RectTransform_get_anchoredPosition_mCB2171DBADBC572F354CCFE3ACA19F9506F97907(L_9, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_11 = V_0;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_12 = Vector2_op_Addition_m81A4D928B8E399DA3A4E3ACD8937EDFDCB014682(L_10, L_11, /*hidden argument*/NULL);
		NullCheck(L_9);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_9, L_12, /*hidden argument*/NULL);
	}

IL_0035:
	{
		// base.HandleInput(magnitude, normalised, radius, cam);
		float L_13 = ___magnitude0;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_14 = ___normalised1;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_15 = ___radius2;
		Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * L_16 = ___cam3;
		Joystick_HandleInput_mA2FF5AE57290471865DC02DC2ED3BDA3FDBA2506(__this, L_13, L_14, L_15, L_16, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void DynamicJoystick::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void DynamicJoystick__ctor_mD87E098A06147EABDFDB7F80162B114A799F9D4A (DynamicJoystick_tCF78F682E54A0DC802556F259FCCD587476C2DC3 * __this, const RuntimeMethod* method)
{
	{
		// [SerializeField] private float moveThreshold = 1;
		__this->set_moveThreshold_15((1.0f));
		Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Enemy::Init()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_Init_m33CE279B856CE404151706EBC893C8604099927E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_Init_m33CE279B856CE404151706EBC893C8604099927E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// targetPoint = pointA;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = __this->get_pointA_6();
		__this->set_targetPoint_8(L_0);
		// anim = GetComponent<Animator>();
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_1 = Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719(__this, /*hidden argument*/Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719_RuntimeMethod_var);
		__this->set_anim_11(L_1);
		// alarmSign = transform.GetChild(0).gameObject;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_2);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = Transform_GetChild_mC86B9B61E4EC086A571B09EA7A33FFBF50DF52D3(L_2, 0, /*hidden argument*/NULL);
		NullCheck(L_3);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_4 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_3, /*hidden argument*/NULL);
		__this->set_alarmSign_16(L_4);
		// }
		return;
	}
}
// System.Void Enemy::Awake()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_Awake_m528DFFE5F23214804C28D08B56D6BFF52C4FA689 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	{
		// Init();
		VirtActionInvoker0::Invoke(5 /* System.Void Enemy::Init() */, __this);
		// }
		return;
	}
}
// System.Void Enemy::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_Start_m0681B66D4522F045EB7A33A21467994960D1E435 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_Start_m0681B66D4522F045EB7A33A21467994960D1E435_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// TransitionToState(patrolState);
		PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * L_0 = __this->get_patrolState_14();
		Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE(__this, L_0, /*hidden argument*/NULL);
		// if (isBoss)
		bool L_1 = __this->get_isBoss_13();
		if (!L_1)
		{
			goto IL_0024;
		}
	}
	{
		// UIManager.instance.SetBossMaxHealth(health);
		UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * L_2 = ((UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields*)il2cpp_codegen_static_fields_for(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var))->get_instance_4();
		float L_3 = __this->get_health_21();
		NullCheck(L_2);
		UIManager_SetBossMaxHealth_m7990FC8C3142CF8AEC5BE6F5948DB37DF9B1B03D(L_2, L_3, /*hidden argument*/NULL);
	}

IL_0024:
	{
		// GameManager.instance.addEnemy(this);
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_4 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		NullCheck(L_4);
		GameManager_addEnemy_mA2B4C6231982E68641C4B0BBF19B0B1B5E2A726A(L_4, __this, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Enemy::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_Update_mE957FE3BFB8CBB7C30E43D4A81C13E02B1C1FC32 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_Update_mE957FE3BFB8CBB7C30E43D4A81C13E02B1C1FC32_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (isDead)
		bool L_0 = __this->get_isDead_22();
		if (!L_0)
		{
			goto IL_0009;
		}
	}
	{
		// return;
		return;
	}

IL_0009:
	{
		// currentState.OnUpdate(this);
		EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * L_1 = __this->get_currentState_4();
		NullCheck(L_1);
		VirtActionInvoker1< Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * >::Invoke(5 /* System.Void EnemyBaseState::OnUpdate(Enemy) */, L_1, __this);
		// anim.SetInteger("state", animState);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_2 = __this->get_anim_11();
		int32_t L_3 = __this->get_animState_12();
		NullCheck(L_2);
		Animator_SetInteger_m1E6D66416F48D6E02E7618A0142D70F5232BCC22(L_2, _stringLiteralAA4A5F8125F234182E2DEA92805AFDFB747A86BE, L_3, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Enemy::TransitionToState(EnemyBaseState)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * ___state0, const RuntimeMethod* method)
{
	{
		// currentState = state;
		EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * L_0 = ___state0;
		__this->set_currentState_4(L_0);
		// currentState.OnEnterState(this);
		EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * L_1 = __this->get_currentState_4();
		NullCheck(L_1);
		VirtActionInvoker1< Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * >::Invoke(4 /* System.Void EnemyBaseState::OnEnterState(Enemy) */, L_1, __this);
		// }
		return;
	}
}
// System.Void Enemy::MoveToTarget()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_MoveToTarget_mCDF98A78E7279630FBE34E9183ACAE017D025132 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_MoveToTarget_mCDF98A78E7279630FBE34E9183ACAE017D025132_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// transform.position = Vector2.MoveTowards(transform.position, targetPoint.position, speed * Time.deltaTime);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_1 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_1);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_2 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_1, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_2, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_4 = __this->get_targetPoint_8();
		NullCheck(L_4);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_5 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_4, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_6 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_5, /*hidden argument*/NULL);
		float L_7 = __this->get_speed_5();
		float L_8 = Time_get_deltaTime_m16F98FC9BA931581236008C288E3B25CBCB7C81E(/*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_9 = Vector2_MoveTowards_m5CE85293E9619514164A685D1D4673E2A6E43DFA(L_3, L_6, ((float)il2cpp_codegen_multiply((float)L_7, (float)L_8)), /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_10 = Vector2_op_Implicit_mD152B6A34B4DB7FFECC2844D74718568FE867D6F(L_9, /*hidden argument*/NULL);
		NullCheck(L_0);
		Transform_set_position_mDA89E4893F14ECA5CBEEE7FB80A5BF7C1B8EA6DC(L_0, L_10, /*hidden argument*/NULL);
		// FilpDirection();
		Enemy_FilpDirection_m25112DA9C4BB354136EF9E35420C69AE0C19B054(__this, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Enemy::FilpDirection()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_FilpDirection_m25112DA9C4BB354136EF9E35420C69AE0C19B054 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_FilpDirection_m25112DA9C4BB354136EF9E35420C69AE0C19B054_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (transform.position.x < targetPoint.position.x)
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		float L_2 = L_1.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = __this->get_targetPoint_8();
		NullCheck(L_3);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_4 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_3, /*hidden argument*/NULL);
		float L_5 = L_4.get_x_2();
		if ((!(((float)L_2) < ((float)L_5))))
		{
			goto IL_0042;
		}
	}
	{
		// transform.rotation = Quaternion.Euler(0, 0, 0);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_6 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357_il2cpp_TypeInfo_var);
		Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  L_7 = Quaternion_Euler_m537DD6CEAE0AD4274D8A84414C24C30730427D05((0.0f), (0.0f), (0.0f), /*hidden argument*/NULL);
		NullCheck(L_6);
		Transform_set_rotation_m429694E264117C6DC682EC6AF45C7864E5155935(L_6, L_7, /*hidden argument*/NULL);
		// }
		return;
	}

IL_0042:
	{
		// transform.rotation = Quaternion.Euler(0, 180, 0);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_8 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357_il2cpp_TypeInfo_var);
		Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  L_9 = Quaternion_Euler_m537DD6CEAE0AD4274D8A84414C24C30730427D05((0.0f), (180.0f), (0.0f), /*hidden argument*/NULL);
		NullCheck(L_8);
		Transform_set_rotation_m429694E264117C6DC682EC6AF45C7864E5155935(L_8, L_9, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Enemy::SwitchPoint()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_SwitchPoint_mEB5076531D4C2544BD715A31A29A7355F19EDE11 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_SwitchPoint_mEB5076531D4C2544BD715A31A29A7355F19EDE11_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (Mathf.Abs(transform.position.x - pointA.position.x) < Mathf.Abs(transform.position.x - pointB.position.x))
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		float L_2 = L_1.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = __this->get_pointA_6();
		NullCheck(L_3);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_4 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_3, /*hidden argument*/NULL);
		float L_5 = L_4.get_x_2();
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_6 = fabsf(((float)il2cpp_codegen_subtract((float)L_2, (float)L_5)));
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_7 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_7);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_8 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_7, /*hidden argument*/NULL);
		float L_9 = L_8.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_10 = __this->get_pointB_7();
		NullCheck(L_10);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_11 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_10, /*hidden argument*/NULL);
		float L_12 = L_11.get_x_2();
		float L_13 = fabsf(((float)il2cpp_codegen_subtract((float)L_9, (float)L_12)));
		if ((!(((float)L_6) < ((float)L_13))))
		{
			goto IL_005b;
		}
	}
	{
		// targetPoint = pointB;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_14 = __this->get_pointB_7();
		__this->set_targetPoint_8(L_14);
		// }
		return;
	}

IL_005b:
	{
		// targetPoint = pointA;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_15 = __this->get_pointA_6();
		__this->set_targetPoint_8(L_15);
		// }
		return;
	}
}
// System.Void Enemy::Attack()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_Attack_mD7E35AB2C1AE961F3625A6DFD081E932CEA461D7 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_Attack_mD7E35AB2C1AE961F3625A6DFD081E932CEA461D7_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// Debug.Log("Attack");
		IL2CPP_RUNTIME_CLASS_INIT(Debug_t7B5FCB117E2FD63B6838BC52821B252E2BFB61C4_il2cpp_TypeInfo_var);
		Debug_Log_m4B7C70BAFD477C6BDB59C88A0934F0B018D03708(_stringLiteral1B81F28B5AFBFCAAF5253D26B7DBA4028A92A860, /*hidden argument*/NULL);
		// if (Vector2.Distance(transform.position, targetPoint.position) < attackRange)
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_1, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = __this->get_targetPoint_8();
		NullCheck(L_3);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_4 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_3, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_5 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_4, /*hidden argument*/NULL);
		float L_6 = Vector2_Distance_mB07492BC42EC582754AD11554BE5B7F8D0E93CF4(L_2, L_5, /*hidden argument*/NULL);
		float L_7 = __this->get_attackRange_17();
		if ((!(((float)L_6) < ((float)L_7))))
		{
			goto IL_0066;
		}
	}
	{
		// if (Time.time > nextAttack)
		float L_8 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		float L_9 = __this->get_nextAttack_20();
		if ((!(((float)L_8) > ((float)L_9))))
		{
			goto IL_0066;
		}
	}
	{
		// anim.SetTrigger("attack");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_10 = __this->get_anim_11();
		NullCheck(L_10);
		Animator_SetTrigger_m68D29B7FA54C2F230F5AD780D462612B18E74245(L_10, _stringLiteralA6D81694B1FEA544CFA7910FBC7133AC5E140813, /*hidden argument*/NULL);
		// nextAttack = Time.time + attackRange;
		float L_11 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		float L_12 = __this->get_attackRange_17();
		__this->set_nextAttack_20(((float)il2cpp_codegen_add((float)L_11, (float)L_12)));
	}

IL_0066:
	{
		// }
		return;
	}
}
// System.Void Enemy::SkillAttack()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_SkillAttack_m4E4DA6E8B23FB444ED5D8F3EF20F8BF818AA766E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_SkillAttack_m4E4DA6E8B23FB444ED5D8F3EF20F8BF818AA766E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (Vector2.Distance(transform.position, targetPoint.position) < skillRange)
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_1, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = __this->get_targetPoint_8();
		NullCheck(L_3);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_4 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_3, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_5 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_4, /*hidden argument*/NULL);
		float L_6 = Vector2_Distance_mB07492BC42EC582754AD11554BE5B7F8D0E93CF4(L_2, L_5, /*hidden argument*/NULL);
		float L_7 = __this->get_skillRange_18();
		if ((!(((float)L_6) < ((float)L_7))))
		{
			goto IL_005c;
		}
	}
	{
		// if (Time.time > nextAttack)
		float L_8 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		float L_9 = __this->get_nextAttack_20();
		if ((!(((float)L_8) > ((float)L_9))))
		{
			goto IL_005c;
		}
	}
	{
		// anim.SetTrigger("skill");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_10 = __this->get_anim_11();
		NullCheck(L_10);
		Animator_SetTrigger_m68D29B7FA54C2F230F5AD780D462612B18E74245(L_10, _stringLiteral34B33E00B199D35FF4CDA21DF27122784573256B, /*hidden argument*/NULL);
		// nextAttack = Time.time + attackRange;
		float L_11 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		float L_12 = __this->get_attackRange_17();
		__this->set_nextAttack_20(((float)il2cpp_codegen_add((float)L_11, (float)L_12)));
	}

IL_005c:
	{
		// }
		return;
	}
}
// System.Void Enemy::OnTriggerStay2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_OnTriggerStay2D_m098504D6D16E60A6509C4B859814A66F9FFD9F8E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_OnTriggerStay2D_m098504D6D16E60A6509C4B859814A66F9FFD9F8E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (!attackList.Contains(collision.transform) && !GameManager.instance.gameOver)
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_0 = __this->get_attackList_9();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_1 = ___collision0;
		NullCheck(L_1);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_1, /*hidden argument*/NULL);
		NullCheck(L_0);
		bool L_3 = List_1_Contains_m37CE7FF0E6F1024460701CAC16B6657BEBB8BF1B(L_0, L_2, /*hidden argument*/List_1_Contains_m37CE7FF0E6F1024460701CAC16B6657BEBB8BF1B_RuntimeMethod_var);
		if (L_3)
		{
			goto IL_0030;
		}
	}
	{
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_4 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		NullCheck(L_4);
		bool L_5 = L_4->get_gameOver_7();
		if (L_5)
		{
			goto IL_0030;
		}
	}
	{
		// attackList.Add(collision.transform);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_6 = __this->get_attackList_9();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_7 = ___collision0;
		NullCheck(L_7);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_8 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_7, /*hidden argument*/NULL);
		NullCheck(L_6);
		List_1_Add_mEB0CDED8A9ADCC0F235881A5D34D41085EC4780C(L_6, L_8, /*hidden argument*/List_1_Add_mEB0CDED8A9ADCC0F235881A5D34D41085EC4780C_RuntimeMethod_var);
	}

IL_0030:
	{
		// }
		return;
	}
}
// System.Void Enemy::OnTriggerExit2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_OnTriggerExit2D_m263722EF78331D173E6EED57784FD2F48C2BF37E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_OnTriggerExit2D_m263722EF78331D173E6EED57784FD2F48C2BF37E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// attackList.Remove(collision.transform);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_0 = __this->get_attackList_9();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_1 = ___collision0;
		NullCheck(L_1);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_1, /*hidden argument*/NULL);
		NullCheck(L_0);
		List_1_Remove_m8E1311599BA3E940469F201FE770645882E0783A(L_0, L_2, /*hidden argument*/List_1_Remove_m8E1311599BA3E940469F201FE770645882E0783A_RuntimeMethod_var);
		// }
		return;
	}
}
// System.Void Enemy::OnTriggerEnter2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_OnTriggerEnter2D_mB5D8A9A3E7CFA603912813FE5D11B43F5F83634E (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_OnTriggerEnter2D_mB5D8A9A3E7CFA603912813FE5D11B43F5F83634E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (isDead || GameManager.instance.gameOver)
		bool L_0 = __this->get_isDead_22();
		if (L_0)
		{
			goto IL_0014;
		}
	}
	{
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_1 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		NullCheck(L_1);
		bool L_2 = L_1->get_gameOver_7();
		if (!L_2)
		{
			goto IL_0015;
		}
	}

IL_0014:
	{
		// return;
		return;
	}

IL_0015:
	{
		// StartCoroutine(OnAlaram());
		RuntimeObject* L_3 = Enemy_OnAlaram_mA62FEB896193F9E36363BD9E98DA1F0F9CA510FA(__this, /*hidden argument*/NULL);
		MonoBehaviour_StartCoroutine_mBF8044CE06A35D76A69669ADD8977D05956616B7(__this, L_3, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Collections.IEnumerator Enemy::OnAlaram()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject* Enemy_OnAlaram_mA62FEB896193F9E36363BD9E98DA1F0F9CA510FA (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_OnAlaram_mA62FEB896193F9E36363BD9E98DA1F0F9CA510FA_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * L_0 = (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D *)il2cpp_codegen_object_new(U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D_il2cpp_TypeInfo_var);
		U3COnAlaramU3Ed__32__ctor_mD87EBB8EF15D34C2BC010E742C410E60C02E0BE7(L_0, 0, /*hidden argument*/NULL);
		U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * L_1 = L_0;
		NullCheck(L_1);
		L_1->set_U3CU3E4__this_2(__this);
		return L_1;
	}
}
// System.Void Enemy::GetHit(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy_GetHit_mDB9FE12807AABA2F5977FC320DA0AF2F692AB8C0 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, float ___damage0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy_GetHit_mDB9FE12807AABA2F5977FC320DA0AF2F692AB8C0_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// health -= damage;
		float L_0 = __this->get_health_21();
		float L_1 = ___damage0;
		__this->set_health_21(((float)il2cpp_codegen_subtract((float)L_0, (float)L_1)));
		// if (health < 1)
		float L_2 = __this->get_health_21();
		if ((!(((float)L_2) < ((float)(1.0f)))))
		{
			goto IL_0050;
		}
	}
	{
		// health = 0;
		__this->set_health_21((0.0f));
		// isDead = true;
		__this->set_isDead_22((bool)1);
		// anim.SetBool("dead", isDead);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_3 = __this->get_anim_11();
		bool L_4 = __this->get_isDead_22();
		NullCheck(L_3);
		Animator_SetBool_m497805BA217139E42808899782FA05C15BC9879E(L_3, _stringLiteral5EB965DD8C804A3A2833AC61FE1D1F6B1960735A, L_4, /*hidden argument*/NULL);
		// GameManager.instance.removeEnemy(this);
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_5 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		NullCheck(L_5);
		GameManager_removeEnemy_m08DDE78A0B9872B6C07147887AA03E8A2FB6F56D(L_5, __this, /*hidden argument*/NULL);
		// }
		goto IL_0060;
	}

IL_0050:
	{
		// anim.SetTrigger("hit");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_6 = __this->get_anim_11();
		NullCheck(L_6);
		Animator_SetTrigger_m68D29B7FA54C2F230F5AD780D462612B18E74245(L_6, _stringLiteralD7D390BD9EBAC6BFA0B17AB10695FE73916EBCC2, /*hidden argument*/NULL);
	}

IL_0060:
	{
		// if (isBoss)
		bool L_7 = __this->get_isBoss_13();
		if (!L_7)
		{
			goto IL_0078;
		}
	}
	{
		// UIManager.instance.SetBossCurrentHealth(health);
		UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * L_8 = ((UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields*)il2cpp_codegen_static_fields_for(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var))->get_instance_4();
		float L_9 = __this->get_health_21();
		NullCheck(L_8);
		UIManager_SetBossCurrentHealth_m6C908308D1E920352F5F0ADF40A2BED73978ED7E(L_8, L_9, /*hidden argument*/NULL);
	}

IL_0078:
	{
		// }
		return;
	}
}
// System.Void Enemy::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5 (Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// public List<Transform> attackList = new List<Transform>();
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_0 = (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *)il2cpp_codegen_object_new(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE_il2cpp_TypeInfo_var);
		List_1__ctor_m0046B0A356552D7B951C2CEEE5F1375DAF72054A(L_0, /*hidden argument*/List_1__ctor_m0046B0A356552D7B951C2CEEE5F1375DAF72054A_RuntimeMethod_var);
		__this->set_attackList_9(L_0);
		// public PatrolState patrolState = new PatrolState();
		PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * L_1 = (PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 *)il2cpp_codegen_object_new(PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302_il2cpp_TypeInfo_var);
		PatrolState__ctor_m6CD97ED5CE7F0EB1531A78F30C5800AE708BF742(L_1, /*hidden argument*/NULL);
		__this->set_patrolState_14(L_1);
		// public AttachState attachState = new AttachState();
		AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * L_2 = (AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF *)il2cpp_codegen_object_new(AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF_il2cpp_TypeInfo_var);
		AttachState__ctor_m2CA4845A3572836BD3E704D1A8D89466132670F2(L_2, /*hidden argument*/NULL);
		__this->set_attachState_15(L_2);
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Enemy_<OnAlaram>d__32::.ctor(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void U3COnAlaramU3Ed__32__ctor_mD87EBB8EF15D34C2BC010E742C410E60C02E0BE7 (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * __this, int32_t ___U3CU3E1__state0, const RuntimeMethod* method)
{
	{
		Object__ctor_m925ECA5E85CA100E3FB86A4F9E15C120E9A184C0(__this, /*hidden argument*/NULL);
		int32_t L_0 = ___U3CU3E1__state0;
		__this->set_U3CU3E1__state_0(L_0);
		return;
	}
}
// System.Void Enemy_<OnAlaram>d__32::System.IDisposable.Dispose()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void U3COnAlaramU3Ed__32_System_IDisposable_Dispose_mD62609F38129374F46B9445F9C7E0772BA293B01 (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * __this, const RuntimeMethod* method)
{
	{
		return;
	}
}
// System.Boolean Enemy_<OnAlaram>d__32::MoveNext()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool U3COnAlaramU3Ed__32_MoveNext_m989CD7423B94BF5F2D3CD7FF4A2E2C5CD34284B2 (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (U3COnAlaramU3Ed__32_MoveNext_m989CD7423B94BF5F2D3CD7FF4A2E2C5CD34284B2_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	int32_t V_0 = 0;
	Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * V_1 = NULL;
	{
		int32_t L_0 = __this->get_U3CU3E1__state_0();
		V_0 = L_0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_1 = __this->get_U3CU3E4__this_2();
		V_1 = L_1;
		int32_t L_2 = V_0;
		if (!L_2)
		{
			goto IL_0017;
		}
	}
	{
		int32_t L_3 = V_0;
		if ((((int32_t)L_3) == ((int32_t)1)))
		{
			goto IL_005f;
		}
	}
	{
		return (bool)0;
	}

IL_0017:
	{
		__this->set_U3CU3E1__state_0((-1));
		// alarmSign.SetActive(true);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_4 = V_1;
		NullCheck(L_4);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_5 = L_4->get_alarmSign_16();
		NullCheck(L_5);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_5, (bool)1, /*hidden argument*/NULL);
		// yield return new WaitForSeconds(alarmSign.GetComponent<Animator>().GetCurrentAnimatorClipInfo(0)[0].clip.length);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_6 = V_1;
		NullCheck(L_6);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_7 = L_6->get_alarmSign_16();
		NullCheck(L_7);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_8 = GameObject_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_m9904EA7E80165F7771F8AB3967F417D7C2B09996(L_7, /*hidden argument*/GameObject_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_m9904EA7E80165F7771F8AB3967F417D7C2B09996_RuntimeMethod_var);
		NullCheck(L_8);
		AnimatorClipInfoU5BU5D_tCAC39F9AE6CEE1EA08285D9D5C44DB3ADD6C1ED6* L_9 = Animator_GetCurrentAnimatorClipInfo_m594B9A950ECAD03E8F85A715E49010E967845462(L_8, 0, /*hidden argument*/NULL);
		NullCheck(L_9);
		AnimationClip_t336CFC94F6275526DC0B9BEEF833D4D89D6DEDDE * L_10 = AnimatorClipInfo_get_clip_mF5A49B54502CBFE17327989ED0701EDC23F1B2A4((AnimatorClipInfo_t78457ABBA83D388EDFF26F436F5E61A29CF4E180 *)((L_9)->GetAddressAt(static_cast<il2cpp_array_size_t>(0))), /*hidden argument*/NULL);
		NullCheck(L_10);
		float L_11 = AnimationClip_get_length_m55DCD61003D76E19AB0B3649A3C0F072D829CD4A(L_10, /*hidden argument*/NULL);
		WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8 * L_12 = (WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8 *)il2cpp_codegen_object_new(WaitForSeconds_t3E9E78D3BB53F03F96C7F28BA9B9086CD1A5F4E8_il2cpp_TypeInfo_var);
		WaitForSeconds__ctor_m8E4BA3E27AEFFE5B74A815F26FF8AAB99743F559(L_12, L_11, /*hidden argument*/NULL);
		__this->set_U3CU3E2__current_1(L_12);
		__this->set_U3CU3E1__state_0(1);
		return (bool)1;
	}

IL_005f:
	{
		__this->set_U3CU3E1__state_0((-1));
		// alarmSign.SetActive(false);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_13 = V_1;
		NullCheck(L_13);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_14 = L_13->get_alarmSign_16();
		NullCheck(L_14);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_14, (bool)0, /*hidden argument*/NULL);
		// }
		return (bool)0;
	}
}
// System.Object Enemy_<OnAlaram>d__32::System.Collections.Generic.IEnumerator<System.Object>.get_Current()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject * U3COnAlaramU3Ed__32_System_Collections_Generic_IEnumeratorU3CSystem_ObjectU3E_get_Current_m8E41FB1DC3790ADEF068144F33A41D83101E5F87 (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * __this, const RuntimeMethod* method)
{
	{
		RuntimeObject * L_0 = __this->get_U3CU3E2__current_1();
		return L_0;
	}
}
// System.Void Enemy_<OnAlaram>d__32::System.Collections.IEnumerator.Reset()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void U3COnAlaramU3Ed__32_System_Collections_IEnumerator_Reset_m482AEADD8285A780061F6543287BD9C92C6576C0 (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (U3COnAlaramU3Ed__32_System_Collections_IEnumerator_Reset_m482AEADD8285A780061F6543287BD9C92C6576C0_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		NotSupportedException_tE75B318D6590A02A5D9B29FD97409B1750FA0010 * L_0 = (NotSupportedException_tE75B318D6590A02A5D9B29FD97409B1750FA0010 *)il2cpp_codegen_object_new(NotSupportedException_tE75B318D6590A02A5D9B29FD97409B1750FA0010_il2cpp_TypeInfo_var);
		NotSupportedException__ctor_mA121DE1CAC8F25277DEB489DC7771209D91CAE33(L_0, /*hidden argument*/NULL);
		IL2CPP_RAISE_MANAGED_EXCEPTION(L_0, U3COnAlaramU3Ed__32_System_Collections_IEnumerator_Reset_m482AEADD8285A780061F6543287BD9C92C6576C0_RuntimeMethod_var);
	}
}
// System.Object Enemy_<OnAlaram>d__32::System.Collections.IEnumerator.get_Current()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR RuntimeObject * U3COnAlaramU3Ed__32_System_Collections_IEnumerator_get_Current_m1D50D80DB444C5571DBCF4BBD8B3B247D716495E (U3COnAlaramU3Ed__32_t57DBDD92EDC087C4E36E7F20A7CE6CF9D58B9D5D * __this, const RuntimeMethod* method)
{
	{
		RuntimeObject * L_0 = __this->get_U3CU3E2__current_1();
		return L_0;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void EnemyBaseState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void EnemyBaseState__ctor_m57F25EC153F6DA435937264866B5DAFB8A7531FA (EnemyBaseState_tE08C1B682C7A84EBCEFA92C886BA03C4F5E76E79 * __this, const RuntimeMethod* method)
{
	{
		Object__ctor_m925ECA5E85CA100E3FB86A4F9E15C120E9A184C0(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void FixedJoystick::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void FixedJoystick__ctor_mC91231670E4D4850A5BFB905300F155AA2DE60FD (FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * __this, const RuntimeMethod* method)
{
	{
		Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void FloatingJoystick::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void FloatingJoystick_Start_m0F34B432F4B1DF7D2A84264E9C5E8553A4E7F0DE (FloatingJoystick_tBA7C79E5FC21EE9F117E0583A6A5FD38EFF5F8FE * __this, const RuntimeMethod* method)
{
	{
		// base.Start();
		Joystick_Start_mA4B921AF2FEC7B830AC4F0D5E49AF8934ECAD201(__this, /*hidden argument*/NULL);
		// background.gameObject.SetActive(false);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_0 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_0);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_1 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_0, /*hidden argument*/NULL);
		NullCheck(L_1);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_1, (bool)0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void FloatingJoystick::OnPointerDown(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void FloatingJoystick_OnPointerDown_m2DB74D40D3D0D670E92442E24851FF5995CCE764 (FloatingJoystick_tBA7C79E5FC21EE9F117E0583A6A5FD38EFF5F8FE * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	{
		// background.anchoredPosition = ScreenPointToAnchoredPosition(eventData.position);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_0 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_1 = ___eventData0;
		NullCheck(L_1);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = PointerEventData_get_position_mF25FC495A9C968C65BF34B5984616CBFB6332D55_inline(L_1, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = Joystick_ScreenPointToAnchoredPosition_mE4C429E76D0FA78FD1567EB1361AF68141706201(__this, L_2, /*hidden argument*/NULL);
		NullCheck(L_0);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_0, L_3, /*hidden argument*/NULL);
		// background.gameObject.SetActive(true);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_4 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_4);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_5 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_4, /*hidden argument*/NULL);
		NullCheck(L_5);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_5, (bool)1, /*hidden argument*/NULL);
		// base.OnPointerDown(eventData);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_6 = ___eventData0;
		Joystick_OnPointerDown_m408D43BE6A49862DFD49B5198E0B61B85A162703(__this, L_6, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void FloatingJoystick::OnPointerUp(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void FloatingJoystick_OnPointerUp_m31F698F0F60ECAAB34D55DF8B1FF2E533B818DEA (FloatingJoystick_tBA7C79E5FC21EE9F117E0583A6A5FD38EFF5F8FE * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	{
		// background.gameObject.SetActive(false);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_0 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_0);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_1 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_0, /*hidden argument*/NULL);
		NullCheck(L_1);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_1, (bool)0, /*hidden argument*/NULL);
		// base.OnPointerUp(eventData);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_2 = ___eventData0;
		Joystick_OnPointerUp_m771F7519F51F02DAADA7DE0A562F82710FA721BC(__this, L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void FloatingJoystick::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void FloatingJoystick__ctor_mFE6173BF4B5A37A9E365D8322334FF90AA0DE960 (FloatingJoystick_tBA7C79E5FC21EE9F117E0583A6A5FD38EFF5F8FE * __this, const RuntimeMethod* method)
{
	{
		Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void GameManager::Awake()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_Awake_mE60F41F3186E80B2BAB293918745366D18508C0F (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager_Awake_mE60F41F3186E80B2BAB293918745366D18508C0F_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (null == instance)
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_0 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		bool L_1 = Object_op_Equality_mBC2401774F3BE33E8CF6F0A8148E66C95D6CFF1C((Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 *)NULL, L_0, /*hidden argument*/NULL);
		if (!L_1)
		{
			goto IL_0015;
		}
	}
	{
		// instance = this;
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->set_instance_5(__this);
		// }
		goto IL_0020;
	}

IL_0015:
	{
		// Destroy(gameObject);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_2 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		Object_Destroy_m23B4562495BA35A74266D4372D45368F8C05109A(L_2, /*hidden argument*/NULL);
	}

IL_0020:
	{
		// doorExit = FindObjectOfType<Door>();
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * L_3 = Object_FindObjectOfType_TisDoor_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1_m693E2656B1274ACB963744178B6A9C91B0D289D4(/*hidden argument*/Object_FindObjectOfType_TisDoor_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1_m693E2656B1274ACB963744178B6A9C91B0D289D4_RuntimeMethod_var);
		__this->set_doorExit_9(L_3);
		// player = FindObjectOfType<PlayerController>();
		PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * L_4 = Object_FindObjectOfType_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_mBC133F50DBE6E9017FBA685EC7B283C09AE9EB61(/*hidden argument*/Object_FindObjectOfType_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_mBC133F50DBE6E9017FBA685EC7B283C09AE9EB61_RuntimeMethod_var);
		__this->set_player_6(L_4);
		// }
		return;
	}
}
// System.Void GameManager::GameOver()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_GameOver_m658E745BE197CC36CFAE422F8037F41A1B7FFFD3 (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager_GameOver_m658E745BE197CC36CFAE422F8037F41A1B7FFFD3_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// gameOver = true;
		__this->set_gameOver_7((bool)1);
		// UIManager.instance.setGameOverPanelVisible(true);
		UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * L_0 = ((UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields*)il2cpp_codegen_static_fields_for(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var))->get_instance_4();
		NullCheck(L_0);
		UIManager_setGameOverPanelVisible_m8C7780AE4FC448BD13DDDB34D2C961F3AFD810D5(L_0, (bool)1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void GameManager::RestartScene()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_RestartScene_mD0A3767EE9F3B3126FA539EA390F03C0F76BAA9A (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// SceneManager.LoadScene(SceneManager.GetActiveScene().name);
		Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2  L_0 = SceneManager_GetActiveScene_mD583193D329EBF540D8AB8A062681B1C2AB5EA51(/*hidden argument*/NULL);
		V_0 = L_0;
		String_t* L_1 = Scene_get_name_m0E63ED0F050FCC35A4216220C584BE3D3F77B0E1((Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2 *)(&V_0), /*hidden argument*/NULL);
		SceneManager_LoadScene_mFC850AC783E5EA05D6154976385DFECC251CDFB9(L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void GameManager::addEnemy(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_addEnemy_mA2B4C6231982E68641C4B0BBF19B0B1B5E2A726A (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager_addEnemy_mA2B4C6231982E68641C4B0BBF19B0B1B5E2A726A_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// liveEnemy.Add(enemy);
		List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * L_0 = __this->get_liveEnemy_8();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_1 = ___enemy0;
		NullCheck(L_0);
		List_1_Add_m6ED0FB3ABA16A3A8AF0D48619D15B4B947333F5B(L_0, L_1, /*hidden argument*/List_1_Add_m6ED0FB3ABA16A3A8AF0D48619D15B4B947333F5B_RuntimeMethod_var);
		// }
		return;
	}
}
// System.Void GameManager::removeEnemy(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_removeEnemy_m08DDE78A0B9872B6C07147887AA03E8A2FB6F56D (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager_removeEnemy_m08DDE78A0B9872B6C07147887AA03E8A2FB6F56D_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// liveEnemy.Remove(enemy);
		List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * L_0 = __this->get_liveEnemy_8();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_1 = ___enemy0;
		NullCheck(L_0);
		List_1_Remove_m947F635E58C7D238ADF2ACCB2C0EAE33670197C6(L_0, L_1, /*hidden argument*/List_1_Remove_m947F635E58C7D238ADF2ACCB2C0EAE33670197C6_RuntimeMethod_var);
		// if (liveEnemy.Count == 0)
		List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * L_2 = __this->get_liveEnemy_8();
		NullCheck(L_2);
		int32_t L_3 = List_1_get_Count_m2EA40FDD7BE2FB22B8227B533BAA8D316CC4BE3E_inline(L_2, /*hidden argument*/List_1_get_Count_m2EA40FDD7BE2FB22B8227B533BAA8D316CC4BE3E_RuntimeMethod_var);
		if (L_3)
		{
			goto IL_0025;
		}
	}
	{
		// doorExit.OpenDoor();
		Door_tC4C4AAF12F02261DCC08E72A48829B67DB1203A1 * L_4 = __this->get_doorExit_9();
		NullCheck(L_4);
		Door_OpenDoor_mD650E2A85F5958F335166BA83EA91EB3923F992E(L_4, /*hidden argument*/NULL);
	}

IL_0025:
	{
		// }
		return;
	}
}
// System.Void GameManager::NextLevel()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_NextLevel_mF6C956ECA09992B9D36B913E2273B39C076B71F2 (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// SaveData();
		GameManager_SaveData_mCA8C4D89F3C20776CAA9E31AA4AF2193A518048E(__this, /*hidden argument*/NULL);
		// SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
		Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2  L_0 = SceneManager_GetActiveScene_mD583193D329EBF540D8AB8A062681B1C2AB5EA51(/*hidden argument*/NULL);
		V_0 = L_0;
		int32_t L_1 = Scene_get_buildIndex_m764659943B7357F5D6C9165F68EDCFBBDDD6C3C2((Scene_t942E023788C2BC9FBB7EC8356B4FB0088B2CFED2 *)(&V_0), /*hidden argument*/NULL);
		SceneManager_LoadScene_m258051AAA1489D2D8B252815A45C1E9A2C097201(((int32_t)il2cpp_codegen_add((int32_t)L_1, (int32_t)1)), /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void GameManager::QuitGame()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_QuitGame_m9CA6EE62AC6FFC7EEBDDA3E133C86B49620A85B7 (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	{
		// Application.Quit();
		Application_Quit_mA005EB22CB989AC3794334754F15E1C0D2FF1C95(/*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Single GameManager::LoadHealth()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float GameManager_LoadHealth_mC037637C61400A7CFE7D50A9751533B40070B43A (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager_LoadHealth_mC037637C61400A7CFE7D50A9751533B40070B43A_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (!PlayerPrefs.HasKey(HEALTH_NAME))
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		String_t* L_0 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_HEALTH_NAME_4();
		bool L_1 = PlayerPrefs_HasKey_mD87D3051ACE7EC6F5B54F4FC9E18572C917CA0D1(L_0, /*hidden argument*/NULL);
		if (L_1)
		{
			goto IL_001b;
		}
	}
	{
		// PlayerPrefs.SetFloat(HEALTH_NAME, 3F);
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		String_t* L_2 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_HEALTH_NAME_4();
		PlayerPrefs_SetFloat_mA58D5A6903B002A03BDEF35B34063E96C8483A35(L_2, (3.0f), /*hidden argument*/NULL);
	}

IL_001b:
	{
		// return PlayerPrefs.GetFloat(HEALTH_NAME);
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		String_t* L_3 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_HEALTH_NAME_4();
		float L_4 = PlayerPrefs_GetFloat_m254A03CC8DCA9E12EE09A016B64EDB7AB9938957(L_3, /*hidden argument*/NULL);
		return L_4;
	}
}
// System.Void GameManager::SaveData()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager_SaveData_mCA8C4D89F3C20776CAA9E31AA4AF2193A518048E (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager_SaveData_mCA8C4D89F3C20776CAA9E31AA4AF2193A518048E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// PlayerPrefs.SetFloat(HEALTH_NAME, player.health);
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		String_t* L_0 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_HEALTH_NAME_4();
		PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * L_1 = __this->get_player_6();
		NullCheck(L_1);
		float L_2 = L_1->get_health_20();
		PlayerPrefs_SetFloat_mA58D5A6903B002A03BDEF35B34063E96C8483A35(L_0, L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void GameManager::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager__ctor_mF7F1107D38DE91EB8A57C1C3BB1A932C50CD9693 (GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager__ctor_mF7F1107D38DE91EB8A57C1C3BB1A932C50CD9693_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// public List<Enemy> liveEnemy = new List<Enemy>();
		List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A * L_0 = (List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A *)il2cpp_codegen_object_new(List_1_t4BC8A38307CF15CA0AD142EDE954C83F258D776A_il2cpp_TypeInfo_var);
		List_1__ctor_m4DBD7BFCF2ABB429466D1A3CA5ECA1D15C1FEEC6(L_0, /*hidden argument*/List_1__ctor_m4DBD7BFCF2ABB429466D1A3CA5ECA1D15C1FEEC6_RuntimeMethod_var);
		__this->set_liveEnemy_8(L_0);
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
// System.Void GameManager::.cctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void GameManager__cctor_m050E3CF18ED59B480951819A6C68DEA9C0EB1D45 (const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (GameManager__cctor_m050E3CF18ED59B480951819A6C68DEA9C0EB1D45_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// private static string HEALTH_NAME = "playerHealth";
		((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->set_HEALTH_NAME_4(_stringLiteral9713091C5752573EEED6D3557DDE0F3E1C0451D9);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void HitPoint::OnTriggerEnter2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void HitPoint_OnTriggerEnter2D_m32B1A41DAD0B3117F608137BF807B8F996EC6A46 (HitPoint_tF69A6E412F64826CB64FF60F3547291915F7E775 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (HitPoint_OnTriggerEnter2D_m32B1A41DAD0B3117F608137BF807B8F996EC6A46_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (transform.position.x > collision.transform.position.x)
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		float L_2 = L_1.get_x_2();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_3 = ___collision0;
		NullCheck(L_3);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_4 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_3, /*hidden argument*/NULL);
		NullCheck(L_4);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_5 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_4, /*hidden argument*/NULL);
		float L_6 = L_5.get_x_2();
		if ((!(((float)L_2) > ((float)L_6))))
		{
			goto IL_002b;
		}
	}
	{
		// dir = -1;
		__this->set_dir_5((-1));
		// }
		goto IL_0032;
	}

IL_002b:
	{
		// dir = 1;
		__this->set_dir_5(1);
	}

IL_0032:
	{
		// if (collision.CompareTag("Player"))
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_7 = ___collision0;
		NullCheck(L_7);
		bool L_8 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_7, _stringLiteralE53407CFE1A5156B9F0D1EED3BAB5EF3AE75CFD8, /*hidden argument*/NULL);
		if (!L_8)
		{
			goto IL_0050;
		}
	}
	{
		// collision.GetComponent<IDamageable>().GetHit(1);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_9 = ___collision0;
		NullCheck(L_9);
		RuntimeObject* L_10 = Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068(L_9, /*hidden argument*/Component_GetComponent_TisIDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_mA9D82E44CC018CCA691758D999FF6E2B6BDA8068_RuntimeMethod_var);
		NullCheck(L_10);
		InterfaceActionInvoker1< float >::Invoke(0 /* System.Void IDamageable::GetHit(System.Single) */, IDamageable_tE1E811DB7C2A6DDF0CDD15945BE46A46E4CB11CD_il2cpp_TypeInfo_var, L_10, (1.0f));
		// }
		return;
	}

IL_0050:
	{
		// else if (collision.CompareTag("Bomb") && bombAvilable)
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_11 = ___collision0;
		NullCheck(L_11);
		bool L_12 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_11, _stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		if (!L_12)
		{
			goto IL_0091;
		}
	}
	{
		bool L_13 = __this->get_bombAvilable_4();
		if (!L_13)
		{
			goto IL_0091;
		}
	}
	{
		// collision.gameObject.GetComponent<Rigidbody2D>().AddForce(new Vector2(dir, 1) * 10, ForceMode2D.Impulse);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_14 = ___collision0;
		NullCheck(L_14);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_15 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_14, /*hidden argument*/NULL);
		NullCheck(L_15);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_16 = GameObject_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mDDB82F02C3053DCC0D60C420752A11EC11CBACC0(L_15, /*hidden argument*/GameObject_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mDDB82F02C3053DCC0D60C420752A11EC11CBACC0_RuntimeMethod_var);
		int32_t L_17 = __this->get_dir_5();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_18;
		memset((&L_18), 0, sizeof(L_18));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_18), (((float)((float)L_17))), (1.0f), /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_19 = Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56(L_18, (10.0f), /*hidden argument*/NULL);
		NullCheck(L_16);
		Rigidbody2D_AddForce_m09E1A2E24DABA5BBC613E35772AE2C1C35C6E40C(L_16, L_19, 1, /*hidden argument*/NULL);
	}

IL_0091:
	{
		// }
		return;
	}
}
// System.Void HitPoint::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void HitPoint__ctor_mBFD64C9C631531356FA2AEF14D6CED9A01211255 (HitPoint_tF69A6E412F64826CB64FF60F3547291915F7E775 * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Single Joystick::get_Horizontal()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_get_Horizontal_mD2CEADF3C7AD02BA60F7990F1A39BC67C6D8819B (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// public float Horizontal { get { return (snapX) ? SnapFloat(input.x, AxisOptions.Horizontal) : input.x; } }
		bool L_0 = __this->get_snapX_7();
		if (L_0)
		{
			goto IL_0014;
		}
	}
	{
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_1 = __this->get_address_of_input_14();
		float L_2 = L_1->get_x_0();
		return L_2;
	}

IL_0014:
	{
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_3 = __this->get_address_of_input_14();
		float L_4 = L_3->get_x_0();
		float L_5 = Joystick_SnapFloat_mCEF2520CAC111659A65B73C418F5E6FF1CFF05C2(__this, L_4, 1, /*hidden argument*/NULL);
		return L_5;
	}
}
// System.Single Joystick::get_Vertical()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_get_Vertical_m2326D40EF66E0A5E2B34F9CF02A53C05CCAFDED0 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// public float Vertical { get { return (snapY) ? SnapFloat(input.y, AxisOptions.Vertical) : input.y; } }
		bool L_0 = __this->get_snapY_8();
		if (L_0)
		{
			goto IL_0014;
		}
	}
	{
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_1 = __this->get_address_of_input_14();
		float L_2 = L_1->get_y_1();
		return L_2;
	}

IL_0014:
	{
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_3 = __this->get_address_of_input_14();
		float L_4 = L_3->get_y_1();
		float L_5 = Joystick_SnapFloat_mCEF2520CAC111659A65B73C418F5E6FF1CFF05C2(__this, L_4, 2, /*hidden argument*/NULL);
		return L_5;
	}
}
// UnityEngine.Vector2 Joystick::get_Direction()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Joystick_get_Direction_mF64961ED5359C8E31E79CAA306019CB66DF50F3E (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// public Vector2 Direction { get { return new Vector2(Horizontal, Vertical); } }
		float L_0 = Joystick_get_Horizontal_mD2CEADF3C7AD02BA60F7990F1A39BC67C6D8819B(__this, /*hidden argument*/NULL);
		float L_1 = Joystick_get_Vertical_m2326D40EF66E0A5E2B34F9CF02A53C05CCAFDED0(__this, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2;
		memset((&L_2), 0, sizeof(L_2));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_2), L_0, L_1, /*hidden argument*/NULL);
		return L_2;
	}
}
// System.Single Joystick::get_HandleRange()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_get_HandleRange_m3D14494BB31EF5C716DE54CBF4ED30284AEE855F (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// get { return handleRange; }
		float L_0 = __this->get_handleRange_4();
		return L_0;
	}
}
// System.Void Joystick::set_HandleRange(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_set_HandleRange_m93B28B83AB3DC010C509C16A76BE34896C27B647 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___value0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_set_HandleRange_m93B28B83AB3DC010C509C16A76BE34896C27B647_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// set { handleRange = Mathf.Abs(value); }
		float L_0 = ___value0;
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_1 = fabsf(L_0);
		__this->set_handleRange_4(L_1);
		// set { handleRange = Mathf.Abs(value); }
		return;
	}
}
// System.Single Joystick::get_DeadZone()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_get_DeadZone_m56376929F8539F977418D4ACB3A468758515DA85 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// get { return deadZone; }
		float L_0 = __this->get_deadZone_5();
		return L_0;
	}
}
// System.Void Joystick::set_DeadZone(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_set_DeadZone_mF8F4688B5A32363F2EF7DE0A0FF90B7D65F11C8B (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___value0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_set_DeadZone_mF8F4688B5A32363F2EF7DE0A0FF90B7D65F11C8B_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// set { deadZone = Mathf.Abs(value); }
		float L_0 = ___value0;
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_1 = fabsf(L_0);
		__this->set_deadZone_5(L_1);
		// set { deadZone = Mathf.Abs(value); }
		return;
	}
}
// AxisOptions Joystick::get_AxisOptions()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR int32_t Joystick_get_AxisOptions_m41669BF41810BA976B1A230E1FB3ADCDC1F4C758 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// public AxisOptions AxisOptions { get { return AxisOptions; } set { axisOptions = value; } }
		int32_t L_0 = Joystick_get_AxisOptions_m41669BF41810BA976B1A230E1FB3ADCDC1F4C758(__this, /*hidden argument*/NULL);
		return L_0;
	}
}
// System.Void Joystick::set_AxisOptions(AxisOptions)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_set_AxisOptions_m3194AF6B83B35084063737EBA7D8C10C652241F8 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, int32_t ___value0, const RuntimeMethod* method)
{
	{
		// public AxisOptions AxisOptions { get { return AxisOptions; } set { axisOptions = value; } }
		int32_t L_0 = ___value0;
		__this->set_axisOptions_6(L_0);
		// public AxisOptions AxisOptions { get { return AxisOptions; } set { axisOptions = value; } }
		return;
	}
}
// System.Boolean Joystick::get_SnapX()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Joystick_get_SnapX_m8BFFB04A6377302BCD1E3106930231C756150211 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// public bool SnapX { get { return snapX; } set { snapX = value; } }
		bool L_0 = __this->get_snapX_7();
		return L_0;
	}
}
// System.Void Joystick::set_SnapX(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_set_SnapX_mACA46808CD8386CABE024E9F55A407F0C8A138F0 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, bool ___value0, const RuntimeMethod* method)
{
	{
		// public bool SnapX { get { return snapX; } set { snapX = value; } }
		bool L_0 = ___value0;
		__this->set_snapX_7(L_0);
		// public bool SnapX { get { return snapX; } set { snapX = value; } }
		return;
	}
}
// System.Boolean Joystick::get_SnapY()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR bool Joystick_get_SnapY_m3B972003ED2D6D62DC433D6429AD58AEDCEE5957 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// public bool SnapY { get { return snapY; } set { snapY = value; } }
		bool L_0 = __this->get_snapY_8();
		return L_0;
	}
}
// System.Void Joystick::set_SnapY(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_set_SnapY_mA985E49A53EBD417CF06948C805588612C0395C1 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, bool ___value0, const RuntimeMethod* method)
{
	{
		// public bool SnapY { get { return snapY; } set { snapY = value; } }
		bool L_0 = ___value0;
		__this->set_snapY_8(L_0);
		// public bool SnapY { get { return snapY; } set { snapY = value; } }
		return;
	}
}
// System.Void Joystick::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_Start_mA4B921AF2FEC7B830AC4F0D5E49AF8934ECAD201 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_Start_mA4B921AF2FEC7B830AC4F0D5E49AF8934ECAD201_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// HandleRange = handleRange;
		float L_0 = __this->get_handleRange_4();
		Joystick_set_HandleRange_m93B28B83AB3DC010C509C16A76BE34896C27B647(__this, L_0, /*hidden argument*/NULL);
		// DeadZone = deadZone;
		float L_1 = __this->get_deadZone_5();
		Joystick_set_DeadZone_mF8F4688B5A32363F2EF7DE0A0FF90B7D65F11C8B(__this, L_1, /*hidden argument*/NULL);
		// baseRect = GetComponent<RectTransform>();
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_2 = Component_GetComponent_TisRectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20_mEF939F54B6B56187EC11E16F51DCB12EB62C2103(__this, /*hidden argument*/Component_GetComponent_TisRectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20_mEF939F54B6B56187EC11E16F51DCB12EB62C2103_RuntimeMethod_var);
		__this->set_baseRect_11(L_2);
		// canvas = GetComponentInParent<Canvas>();
		Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * L_3 = Component_GetComponentInParent_TisCanvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591_mD91B8112B5688783ACAEA46BB2C82C6EC4C4B33B(__this, /*hidden argument*/Component_GetComponentInParent_TisCanvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591_mD91B8112B5688783ACAEA46BB2C82C6EC4C4B33B_RuntimeMethod_var);
		__this->set_canvas_12(L_3);
		// if (canvas == null)
		Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * L_4 = __this->get_canvas_12();
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		bool L_5 = Object_op_Equality_mBC2401774F3BE33E8CF6F0A8148E66C95D6CFF1C(L_4, (Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 *)NULL, /*hidden argument*/NULL);
		if (!L_5)
		{
			goto IL_0048;
		}
	}
	{
		// Debug.LogError("The Joystick is not placed inside a canvas");
		IL2CPP_RUNTIME_CLASS_INIT(Debug_t7B5FCB117E2FD63B6838BC52821B252E2BFB61C4_il2cpp_TypeInfo_var);
		Debug_LogError_m3BCF9B78263152261565DCA9DB7D55F0C391ED29(_stringLiteral3F0B67BCB7ECF77640A7DD122D98182E7BC9ADD4, /*hidden argument*/NULL);
	}

IL_0048:
	{
		// Vector2 center = new Vector2(0.5f, 0.5f);
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((Vector2_tA85D2DD88578276CA8A8796756458277E72D073D *)(&V_0), (0.5f), (0.5f), /*hidden argument*/NULL);
		// background.pivot = center;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_6 = __this->get_background_9();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_7 = V_0;
		NullCheck(L_6);
		RectTransform_set_pivot_mB791A383B3C870B9CBD7BC51B2C95711C88E9DCF(L_6, L_7, /*hidden argument*/NULL);
		// handle.anchorMin = center;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_8 = __this->get_handle_10();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_9 = V_0;
		NullCheck(L_8);
		RectTransform_set_anchorMin_mE965F5B0902C2554635010A5752728414A57020A(L_8, L_9, /*hidden argument*/NULL);
		// handle.anchorMax = center;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_10 = __this->get_handle_10();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_11 = V_0;
		NullCheck(L_10);
		RectTransform_set_anchorMax_m55EEF00D9E42FE542B5346D7CEDAF9248736F7D3(L_10, L_11, /*hidden argument*/NULL);
		// handle.pivot = center;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_12 = __this->get_handle_10();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_13 = V_0;
		NullCheck(L_12);
		RectTransform_set_pivot_mB791A383B3C870B9CBD7BC51B2C95711C88E9DCF(L_12, L_13, /*hidden argument*/NULL);
		// handle.anchoredPosition = Vector2.zero;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_14 = __this->get_handle_10();
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_15 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		NullCheck(L_14);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_14, L_15, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Joystick::OnPointerDown(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_OnPointerDown_m408D43BE6A49862DFD49B5198E0B61B85A162703 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	{
		// OnDrag(eventData);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_0 = ___eventData0;
		Joystick_OnDrag_m5C8DBE5110822CAF8A7DEDDE6AC240D2C1BDD7C4(__this, L_0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Joystick::OnDrag(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_OnDrag_m5C8DBE5110822CAF8A7DEDDE6AC240D2C1BDD7C4 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_OnDrag_m5C8DBE5110822CAF8A7DEDDE6AC240D2C1BDD7C4_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_0;
	memset((&V_0), 0, sizeof(V_0));
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_1;
	memset((&V_1), 0, sizeof(V_1));
	{
		// cam = null;
		__this->set_cam_13((Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 *)NULL);
		// if (canvas.renderMode == RenderMode.ScreenSpaceCamera)
		Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * L_0 = __this->get_canvas_12();
		NullCheck(L_0);
		int32_t L_1 = Canvas_get_renderMode_mAF68701B143F01C7D19B6C7D3033E3B34ECB2FC8(L_0, /*hidden argument*/NULL);
		if ((!(((uint32_t)L_1) == ((uint32_t)1))))
		{
			goto IL_0026;
		}
	}
	{
		// cam = canvas.worldCamera;
		Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * L_2 = __this->get_canvas_12();
		NullCheck(L_2);
		Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * L_3 = Canvas_get_worldCamera_m36F1A8DBFC4AB34278125DA017CACDC873F53409(L_2, /*hidden argument*/NULL);
		__this->set_cam_13(L_3);
	}

IL_0026:
	{
		// Vector2 position = RectTransformUtility.WorldToScreenPoint(cam, background.position);
		Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * L_4 = __this->get_cam_13();
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_5 = __this->get_background_9();
		NullCheck(L_5);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_6 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_5, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(RectTransformUtility_t9B90669A72B05A33DD88BEBB817BC9CDBB614BBA_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_7 = RectTransformUtility_WorldToScreenPoint_m114DFD961456722DED0FFB2F8DCB46A04C2CCA20(L_4, L_6, /*hidden argument*/NULL);
		V_0 = L_7;
		// Vector2 radius = background.sizeDelta / 2;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_8 = __this->get_background_9();
		NullCheck(L_8);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_9 = RectTransform_get_sizeDelta_mDA0A3E73679143B1B52CE2F9A417F90CB9F3DAFF(L_8, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_10 = Vector2_op_Division_m0961A935168EE6701E098E2B37013DFFF46A5077(L_9, (2.0f), /*hidden argument*/NULL);
		V_1 = L_10;
		// input = (eventData.position - position) / (radius * canvas.scaleFactor);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_11 = ___eventData0;
		NullCheck(L_11);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_12 = PointerEventData_get_position_mF25FC495A9C968C65BF34B5984616CBFB6332D55_inline(L_11, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_13 = V_0;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_14 = Vector2_op_Subtraction_m2B347E4311EDBBBF27573E34899D2492E6B063C0(L_12, L_13, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_15 = V_1;
		Canvas_tBC28BF1DD8D8499A89B5781505833D3728CF8591 * L_16 = __this->get_canvas_12();
		NullCheck(L_16);
		float L_17 = Canvas_get_scaleFactor_m0F6D59E75F7605ABD2AFF6AF32A1097226CE060A(L_16, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_18 = Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56(L_15, L_17, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_19 = Vector2_op_Division_mEF4FA1379564288637A7CF5E73BA30CA2259E591(L_14, L_18, /*hidden argument*/NULL);
		__this->set_input_14(L_19);
		// FormatInput();
		Joystick_FormatInput_mDE5D2FB4C4FB309B92816E806756B01F61FF26D5(__this, /*hidden argument*/NULL);
		// HandleInput(input.magnitude, input.normalized, radius, cam);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_20 = __this->get_address_of_input_14();
		float L_21 = Vector2_get_magnitude_m66097AFDF9696BD3E88467D4398D4F82B8A4C7DF((Vector2_tA85D2DD88578276CA8A8796756458277E72D073D *)L_20, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_22 = __this->get_address_of_input_14();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_23 = Vector2_get_normalized_m058E75C38C6FC66E178D7C8EF1B6298DE8F0E14B((Vector2_tA85D2DD88578276CA8A8796756458277E72D073D *)L_22, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_24 = V_1;
		Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * L_25 = __this->get_cam_13();
		VirtActionInvoker4< float, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D , Vector2_tA85D2DD88578276CA8A8796756458277E72D073D , Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * >::Invoke(9 /* System.Void Joystick::HandleInput(System.Single,UnityEngine.Vector2,UnityEngine.Vector2,UnityEngine.Camera) */, __this, L_21, L_23, L_24, L_25);
		// handle.anchoredPosition = input * radius * handleRange;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_26 = __this->get_handle_10();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_27 = __this->get_input_14();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_28 = V_1;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_29 = Vector2_op_Multiply_mEDF9FDDF3BFFAEC997FBCDE5FA34871F2955E7C4(L_27, L_28, /*hidden argument*/NULL);
		float L_30 = __this->get_handleRange_4();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_31 = Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56(L_29, L_30, /*hidden argument*/NULL);
		NullCheck(L_26);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_26, L_31, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Joystick::HandleInput(System.Single,UnityEngine.Vector2,UnityEngine.Vector2,UnityEngine.Camera)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_HandleInput_mA2FF5AE57290471865DC02DC2ED3BDA3FDBA2506 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___magnitude0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___normalised1, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___radius2, Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * ___cam3, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_HandleInput_mA2FF5AE57290471865DC02DC2ED3BDA3FDBA2506_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (magnitude > deadZone)
		float L_0 = ___magnitude0;
		float L_1 = __this->get_deadZone_5();
		if ((!(((float)L_0) > ((float)L_1))))
		{
			goto IL_0019;
		}
	}
	{
		// if (magnitude > 1)
		float L_2 = ___magnitude0;
		if ((!(((float)L_2) > ((float)(1.0f)))))
		{
			goto IL_0024;
		}
	}
	{
		// input = normalised;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = ___normalised1;
		__this->set_input_14(L_3);
		// }
		return;
	}

IL_0019:
	{
		// input = Vector2.zero;
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_4 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		__this->set_input_14(L_4);
	}

IL_0024:
	{
		// }
		return;
	}
}
// System.Void Joystick::FormatInput()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_FormatInput_mDE5D2FB4C4FB309B92816E806756B01F61FF26D5 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	{
		// if (axisOptions == AxisOptions.Horizontal)
		int32_t L_0 = __this->get_axisOptions_6();
		if ((!(((uint32_t)L_0) == ((uint32_t)1))))
		{
			goto IL_0025;
		}
	}
	{
		// input = new Vector2(input.x, 0f);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_1 = __this->get_address_of_input_14();
		float L_2 = L_1->get_x_0();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3;
		memset((&L_3), 0, sizeof(L_3));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_3), L_2, (0.0f), /*hidden argument*/NULL);
		__this->set_input_14(L_3);
		return;
	}

IL_0025:
	{
		// else if (axisOptions == AxisOptions.Vertical)
		int32_t L_4 = __this->get_axisOptions_6();
		if ((!(((uint32_t)L_4) == ((uint32_t)2))))
		{
			goto IL_0049;
		}
	}
	{
		// input = new Vector2(0f, input.y);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D * L_5 = __this->get_address_of_input_14();
		float L_6 = L_5->get_y_1();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_7;
		memset((&L_7), 0, sizeof(L_7));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_7), (0.0f), L_6, /*hidden argument*/NULL);
		__this->set_input_14(L_7);
	}

IL_0049:
	{
		// }
		return;
	}
}
// System.Single Joystick::SnapFloat(System.Single,AxisOptions)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float Joystick_SnapFloat_mCEF2520CAC111659A65B73C418F5E6FF1CFF05C2 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, float ___value0, int32_t ___snapAxis1, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_SnapFloat_mCEF2520CAC111659A65B73C418F5E6FF1CFF05C2_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	float V_0 = 0.0f;
	int32_t G_B10_0 = 0;
	int32_t G_B18_0 = 0;
	{
		// if (value == 0)
		float L_0 = ___value0;
		if ((!(((float)L_0) == ((float)(0.0f)))))
		{
			goto IL_000a;
		}
	}
	{
		// return value;
		float L_1 = ___value0;
		return L_1;
	}

IL_000a:
	{
		// if (axisOptions == AxisOptions.Both)
		int32_t L_2 = __this->get_axisOptions_6();
		if (L_2)
		{
			goto IL_0075;
		}
	}
	{
		// float angle = Vector2.Angle(input, Vector2.up);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = __this->get_input_14();
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_4 = Vector2_get_up_mC4548731D5E7C71164D18C390A1AC32501DAE441(/*hidden argument*/NULL);
		float L_5 = Vector2_Angle_mC4A140B49B9E737C9FC6B52763468C5662A8B4AC(L_3, L_4, /*hidden argument*/NULL);
		V_0 = L_5;
		// if (snapAxis == AxisOptions.Horizontal)
		int32_t L_6 = ___snapAxis1;
		if ((!(((uint32_t)L_6) == ((uint32_t)1))))
		{
			goto IL_004b;
		}
	}
	{
		// if (angle < 22.5f || angle > 157.5f)
		float L_7 = V_0;
		if ((((float)L_7) < ((float)(22.5f))))
		{
			goto IL_0037;
		}
	}
	{
		float L_8 = V_0;
		if ((!(((float)L_8) > ((float)(157.5f)))))
		{
			goto IL_003d;
		}
	}

IL_0037:
	{
		// return 0;
		return (0.0f);
	}

IL_003d:
	{
		// return (value > 0) ? 1 : -1;
		float L_9 = ___value0;
		if ((((float)L_9) > ((float)(0.0f))))
		{
			goto IL_0048;
		}
	}
	{
		G_B10_0 = (-1);
		goto IL_0049;
	}

IL_0048:
	{
		G_B10_0 = 1;
	}

IL_0049:
	{
		return (((float)((float)G_B10_0)));
	}

IL_004b:
	{
		// else if (snapAxis == AxisOptions.Vertical)
		int32_t L_10 = ___snapAxis1;
		if ((!(((uint32_t)L_10) == ((uint32_t)2))))
		{
			goto IL_0073;
		}
	}
	{
		// if (angle > 67.5f && angle < 112.5f)
		float L_11 = V_0;
		if ((!(((float)L_11) > ((float)(67.5f)))))
		{
			goto IL_0065;
		}
	}
	{
		float L_12 = V_0;
		if ((!(((float)L_12) < ((float)(112.5f)))))
		{
			goto IL_0065;
		}
	}
	{
		// return 0;
		return (0.0f);
	}

IL_0065:
	{
		// return (value > 0) ? 1 : -1;
		float L_13 = ___value0;
		if ((((float)L_13) > ((float)(0.0f))))
		{
			goto IL_0070;
		}
	}
	{
		G_B18_0 = (-1);
		goto IL_0071;
	}

IL_0070:
	{
		G_B18_0 = 1;
	}

IL_0071:
	{
		return (((float)((float)G_B18_0)));
	}

IL_0073:
	{
		// return value;
		float L_14 = ___value0;
		return L_14;
	}

IL_0075:
	{
		// if (value > 0)
		float L_15 = ___value0;
		if ((!(((float)L_15) > ((float)(0.0f)))))
		{
			goto IL_0083;
		}
	}
	{
		// return 1;
		return (1.0f);
	}

IL_0083:
	{
		// if (value < 0)
		float L_16 = ___value0;
		if ((!(((float)L_16) < ((float)(0.0f)))))
		{
			goto IL_0091;
		}
	}
	{
		// return -1;
		return (-1.0f);
	}

IL_0091:
	{
		// return 0;
		return (0.0f);
	}
}
// System.Void Joystick::OnPointerUp(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick_OnPointerUp_m771F7519F51F02DAADA7DE0A562F82710FA721BC (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_OnPointerUp_m771F7519F51F02DAADA7DE0A562F82710FA721BC_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// input = Vector2.zero;
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_0 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		__this->set_input_14(L_0);
		// handle.anchoredPosition = Vector2.zero;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_1 = __this->get_handle_10();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		NullCheck(L_1);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_1, L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// UnityEngine.Vector2 Joystick::ScreenPointToAnchoredPosition(UnityEngine.Vector2)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  Joystick_ScreenPointToAnchoredPosition_mE4C429E76D0FA78FD1567EB1361AF68141706201 (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___screenPosition0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick_ScreenPointToAnchoredPosition_mE4C429E76D0FA78FD1567EB1361AF68141706201_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_0;
	memset((&V_0), 0, sizeof(V_0));
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_1;
	memset((&V_1), 0, sizeof(V_1));
	{
		// Vector2 localPoint = Vector2.zero;
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_0 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		V_0 = L_0;
		// if (RectTransformUtility.ScreenPointToLocalPointInRectangle(baseRect, screenPosition, cam, out localPoint))
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_1 = __this->get_baseRect_11();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = ___screenPosition0;
		Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * L_3 = __this->get_cam_13();
		IL2CPP_RUNTIME_CLASS_INIT(RectTransformUtility_t9B90669A72B05A33DD88BEBB817BC9CDBB614BBA_il2cpp_TypeInfo_var);
		bool L_4 = RectTransformUtility_ScreenPointToLocalPointInRectangle_m2C389D4DCBB3CADB51A793702F13DF7CE837E153(L_1, L_2, L_3, (Vector2_tA85D2DD88578276CA8A8796756458277E72D073D *)(&V_0), /*hidden argument*/NULL);
		if (!L_4)
		{
			goto IL_0060;
		}
	}
	{
		// Vector2 pivotOffset = baseRect.pivot * baseRect.sizeDelta;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_5 = __this->get_baseRect_11();
		NullCheck(L_5);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_6 = RectTransform_get_pivot_mA5BEEE2069ACA7C0C717530EED3E7D811D46C463(L_5, /*hidden argument*/NULL);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_7 = __this->get_baseRect_11();
		NullCheck(L_7);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_8 = RectTransform_get_sizeDelta_mDA0A3E73679143B1B52CE2F9A417F90CB9F3DAFF(L_7, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_9 = Vector2_op_Multiply_mEDF9FDDF3BFFAEC997FBCDE5FA34871F2955E7C4(L_6, L_8, /*hidden argument*/NULL);
		V_1 = L_9;
		// return localPoint - (background.anchorMax * baseRect.sizeDelta) + pivotOffset;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_10 = V_0;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_11 = __this->get_background_9();
		NullCheck(L_11);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_12 = RectTransform_get_anchorMax_m1E51C211FBB32326C884375C9F1E8E8221E5C086(L_11, /*hidden argument*/NULL);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_13 = __this->get_baseRect_11();
		NullCheck(L_13);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_14 = RectTransform_get_sizeDelta_mDA0A3E73679143B1B52CE2F9A417F90CB9F3DAFF(L_13, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_15 = Vector2_op_Multiply_mEDF9FDDF3BFFAEC997FBCDE5FA34871F2955E7C4(L_12, L_14, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_16 = Vector2_op_Subtraction_m2B347E4311EDBBBF27573E34899D2492E6B063C0(L_10, L_15, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_17 = V_1;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_18 = Vector2_op_Addition_m81A4D928B8E399DA3A4E3ACD8937EDFDCB014682(L_16, L_17, /*hidden argument*/NULL);
		return L_18;
	}

IL_0060:
	{
		// return Vector2.zero;
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_19 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		return L_19;
	}
}
// System.Void Joystick::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// [SerializeField] private float handleRange = 1;
		__this->set_handleRange_4((1.0f));
		// private Vector2 input = Vector2.zero;
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_0 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		__this->set_input_14(L_0);
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void JoystickPlayerExample::FixedUpdate()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickPlayerExample_FixedUpdate_m01D558819D864B0B36B12AECB92B7A9FE76D63B3 (JoystickPlayerExample_tC21BF4F29E220888E49AD1C28ED50EA82E0C583B * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (JoystickPlayerExample_FixedUpdate_m01D558819D864B0B36B12AECB92B7A9FE76D63B3_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// Vector3 direction = Vector3.forward * variableJoystick.Vertical + Vector3.right * variableJoystick.Horizontal;
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_0 = Vector3_get_forward_m3E2E192B3302130098738C308FA1EE1439449D0D(/*hidden argument*/NULL);
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_1 = __this->get_variableJoystick_5();
		NullCheck(L_1);
		float L_2 = Joystick_get_Vertical_m2326D40EF66E0A5E2B34F9CF02A53C05CCAFDED0(L_1, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_3 = Vector3_op_Multiply_m1C5F07723615156ACF035D88A1280A9E8F35A04E(L_0, L_2, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_4 = Vector3_get_right_m6DD9559CA0C75BBA42D9140021C4C2A9AAA9B3F5(/*hidden argument*/NULL);
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_5 = __this->get_variableJoystick_5();
		NullCheck(L_5);
		float L_6 = Joystick_get_Horizontal_mD2CEADF3C7AD02BA60F7990F1A39BC67C6D8819B(L_5, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_7 = Vector3_op_Multiply_m1C5F07723615156ACF035D88A1280A9E8F35A04E(L_4, L_6, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_8 = Vector3_op_Addition_m929F9C17E5D11B94D50B4AFF1D730B70CB59B50E(L_3, L_7, /*hidden argument*/NULL);
		V_0 = L_8;
		// rb.AddForce(direction * speed * Time.fixedDeltaTime, ForceMode.VelocityChange);
		Rigidbody_tE0A58EE5A1F7DC908EFFB4F0D795AC9552A750A5 * L_9 = __this->get_rb_6();
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_10 = V_0;
		float L_11 = __this->get_speed_4();
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_12 = Vector3_op_Multiply_m1C5F07723615156ACF035D88A1280A9E8F35A04E(L_10, L_11, /*hidden argument*/NULL);
		float L_13 = Time_get_fixedDeltaTime_m76C241EDB6F824713AF57DCECD5765871770FA4C(/*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_14 = Vector3_op_Multiply_m1C5F07723615156ACF035D88A1280A9E8F35A04E(L_12, L_13, /*hidden argument*/NULL);
		NullCheck(L_9);
		Rigidbody_AddForce_mD64ACF772614FE36CFD8A477A07A407B35DF1A54(L_9, L_14, 2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void JoystickPlayerExample::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickPlayerExample__ctor_m49F04D0D45C4CBE5F904177CF3AB4A60249AD854 (JoystickPlayerExample_tC21BF4F29E220888E49AD1C28ED50EA82E0C583B * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void JoystickSetterExample::ModeChanged(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickSetterExample_ModeChanged_mA0A6156A4DF33D8F0AD6FD106A7A38F33A0F2BBD (JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435 * __this, int32_t ___index0, const RuntimeMethod* method)
{
	{
		// switch(index)
		int32_t L_0 = ___index0;
		switch (L_0)
		{
			case 0:
			{
				goto IL_0013;
			}
			case 1:
			{
				goto IL_0020;
			}
			case 2:
			{
				goto IL_002d;
			}
		}
	}
	{
		return;
	}

IL_0013:
	{
		// variableJoystick.SetMode(JoystickType.Fixed);
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_1 = __this->get_variableJoystick_4();
		NullCheck(L_1);
		VariableJoystick_SetMode_m222D977BBDA4E253D4EAF1E55925FAD333EA7CAE(L_1, 0, /*hidden argument*/NULL);
		// break;
		return;
	}

IL_0020:
	{
		// variableJoystick.SetMode(JoystickType.Floating);
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_2 = __this->get_variableJoystick_4();
		NullCheck(L_2);
		VariableJoystick_SetMode_m222D977BBDA4E253D4EAF1E55925FAD333EA7CAE(L_2, 1, /*hidden argument*/NULL);
		// break;
		return;
	}

IL_002d:
	{
		// variableJoystick.SetMode(JoystickType.Dynamic);
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_3 = __this->get_variableJoystick_4();
		NullCheck(L_3);
		VariableJoystick_SetMode_m222D977BBDA4E253D4EAF1E55925FAD333EA7CAE(L_3, 2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void JoystickSetterExample::AxisChanged(System.Int32)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickSetterExample_AxisChanged_m67CF795BA1CEA14B6B2AE3E71191E5E980EB03F1 (JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435 * __this, int32_t ___index0, const RuntimeMethod* method)
{
	{
		// switch (index)
		int32_t L_0 = ___index0;
		switch (L_0)
		{
			case 0:
			{
				goto IL_0013;
			}
			case 1:
			{
				goto IL_0033;
			}
			case 2:
			{
				goto IL_0053;
			}
		}
	}
	{
		return;
	}

IL_0013:
	{
		// variableJoystick.AxisOptions = AxisOptions.Both;
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_1 = __this->get_variableJoystick_4();
		NullCheck(L_1);
		Joystick_set_AxisOptions_m3194AF6B83B35084063737EBA7D8C10C652241F8_inline(L_1, 0, /*hidden argument*/NULL);
		// background.sprite = axisSprites[index];
		Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * L_2 = __this->get_background_6();
		SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7* L_3 = __this->get_axisSprites_7();
		int32_t L_4 = ___index0;
		NullCheck(L_3);
		int32_t L_5 = L_4;
		Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * L_6 = (L_3)->GetAt(static_cast<il2cpp_array_size_t>(L_5));
		NullCheck(L_2);
		Image_set_sprite_m77F8D681D4EE6D58F4F235AFF704C3EB165A9646(L_2, L_6, /*hidden argument*/NULL);
		// break;
		return;
	}

IL_0033:
	{
		// variableJoystick.AxisOptions = AxisOptions.Horizontal;
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_7 = __this->get_variableJoystick_4();
		NullCheck(L_7);
		Joystick_set_AxisOptions_m3194AF6B83B35084063737EBA7D8C10C652241F8_inline(L_7, 1, /*hidden argument*/NULL);
		// background.sprite = axisSprites[index];
		Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * L_8 = __this->get_background_6();
		SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7* L_9 = __this->get_axisSprites_7();
		int32_t L_10 = ___index0;
		NullCheck(L_9);
		int32_t L_11 = L_10;
		Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * L_12 = (L_9)->GetAt(static_cast<il2cpp_array_size_t>(L_11));
		NullCheck(L_8);
		Image_set_sprite_m77F8D681D4EE6D58F4F235AFF704C3EB165A9646(L_8, L_12, /*hidden argument*/NULL);
		// break;
		return;
	}

IL_0053:
	{
		// variableJoystick.AxisOptions = AxisOptions.Vertical;
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_13 = __this->get_variableJoystick_4();
		NullCheck(L_13);
		Joystick_set_AxisOptions_m3194AF6B83B35084063737EBA7D8C10C652241F8_inline(L_13, 2, /*hidden argument*/NULL);
		// background.sprite = axisSprites[index];
		Image_t18FED07D8646917E1C563745518CF3DD57FF0B3E * L_14 = __this->get_background_6();
		SpriteU5BU5D_tF94AD07E062BC08ECD019A21E7A7B861654905F7* L_15 = __this->get_axisSprites_7();
		int32_t L_16 = ___index0;
		NullCheck(L_15);
		int32_t L_17 = L_16;
		Sprite_tCA09498D612D08DE668653AF1E9C12BF53434198 * L_18 = (L_15)->GetAt(static_cast<il2cpp_array_size_t>(L_17));
		NullCheck(L_14);
		Image_set_sprite_m77F8D681D4EE6D58F4F235AFF704C3EB165A9646(L_14, L_18, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void JoystickSetterExample::SnapX(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickSetterExample_SnapX_mC53461B29C19CDB0FF5E75A9D257B9CF0B1E0CCE (JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435 * __this, bool ___value0, const RuntimeMethod* method)
{
	{
		// variableJoystick.SnapX = value;
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_0 = __this->get_variableJoystick_4();
		bool L_1 = ___value0;
		NullCheck(L_0);
		Joystick_set_SnapX_mACA46808CD8386CABE024E9F55A407F0C8A138F0_inline(L_0, L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void JoystickSetterExample::SnapY(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickSetterExample_SnapY_m35C5092C9B62F6BB55D45FF5ECEA2C7F742F1EDB (JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435 * __this, bool ___value0, const RuntimeMethod* method)
{
	{
		// variableJoystick.SnapY = value;
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_0 = __this->get_variableJoystick_4();
		bool L_1 = ___value0;
		NullCheck(L_0);
		Joystick_set_SnapY_mA985E49A53EBD417CF06948C805588612C0395C1_inline(L_0, L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void JoystickSetterExample::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickSetterExample_Update_m27F40165A6AE141735CD9680F90F53599D2CFFC2 (JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (JoystickSetterExample_Update_m27F40165A6AE141735CD9680F90F53599D2CFFC2_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// valueText.text = "Current Value: " + variableJoystick.Direction;
		Text_tE9317B57477F4B50AA4C16F460DE6F82DAD6D030 * L_0 = __this->get_valueText_5();
		VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * L_1 = __this->get_variableJoystick_4();
		NullCheck(L_1);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Joystick_get_Direction_mF64961ED5359C8E31E79CAA306019CB66DF50F3E(L_1, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = L_2;
		RuntimeObject * L_4 = Box(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var, &L_3);
		String_t* L_5 = String_Concat_mBB19C73816BDD1C3519F248E1ADC8E11A6FDB495(_stringLiteral23A6C6DEBC5A87766313E2F1563C2CA4C4FB4E6C, L_4, /*hidden argument*/NULL);
		NullCheck(L_0);
		VirtActionInvoker1< String_t* >::Invoke(73 /* System.Void UnityEngine.UI.Text::set_text(System.String) */, L_0, L_5);
		// }
		return;
	}
}
// System.Void JoystickSetterExample::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JoystickSetterExample__ctor_mE68D37B29683A04E3232D4A023093BD65336413C (JoystickSetterExample_t0C714E5922483B0E1D4C129300C7C8FD79E4F435 * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void JumpFX::Finish()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JumpFX_Finish_m8A61C881D3E3E327D839016227694D3CD09B8B4A (JumpFX_t077C76BEDFE7B2C69067FB2FA0A32FFC1BE03902 * __this, const RuntimeMethod* method)
{
	{
		// gameObject.SetActive(false);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_0, (bool)0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void JumpFX::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void JumpFX__ctor_mAF4CCAD4784A8DF6528FFB7ACA14E7BE175E1BD8 (JumpFX_t077C76BEDFE7B2C69067FB2FA0A32FFC1BE03902 * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void LandFX::Finish()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void LandFX_Finish_mAD73FAB909A5EA6CF7170B5BB434AF8AE99CCA3A (LandFX_t0B2698938110490929788E8E0F39A5EE7F7287D5 * __this, const RuntimeMethod* method)
{
	{
		// gameObject.SetActive(false);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		NullCheck(L_0);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_0, (bool)0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void LandFX::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void LandFX__ctor_m5CEA1FC06B2A28F5F1CD7ED3DF7DA67A991FB8A4 (LandFX_t0B2698938110490929788E8E0F39A5EE7F7287D5 * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void PatrolState::OnEnterState(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PatrolState_OnEnterState_mCD60D68CC05306401E088189E40C3E8D50DF95ED (PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	{
		// enemy.animState = 0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_0 = ___enemy0;
		NullCheck(L_0);
		L_0->set_animState_12(0);
		// enemy.SwitchPoint();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_1 = ___enemy0;
		NullCheck(L_1);
		Enemy_SwitchPoint_mEB5076531D4C2544BD715A31A29A7355F19EDE11(L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PatrolState::OnUpdate(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PatrolState_OnUpdate_mA50004332BBE077481208FBCD08CDD752CF5E6F4 (PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PatrolState_OnUpdate_mA50004332BBE077481208FBCD08CDD752CF5E6F4_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// if (!enemy.anim.GetCurrentAnimatorStateInfo(0).IsName("Idle"))
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_0 = ___enemy0;
		NullCheck(L_0);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_1 = L_0->get_anim_11();
		NullCheck(L_1);
		AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  L_2 = Animator_GetCurrentAnimatorStateInfo_mBE5ED0D60A6F5CD0EDD40AF1494098D4E7BF84F2(L_1, 0, /*hidden argument*/NULL);
		V_0 = L_2;
		bool L_3 = AnimatorStateInfo_IsName_mD133471910C1ACE0979F3FD11462C9B8BB24CA96((AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 *)(&V_0), _stringLiteralCC1EBDD04E76A4B8BAFFB29A22FA00446D382B18, /*hidden argument*/NULL);
		if (L_3)
		{
			goto IL_0028;
		}
	}
	{
		// enemy.animState = 1;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_4 = ___enemy0;
		NullCheck(L_4);
		L_4->set_animState_12(1);
		// enemy.MoveToTarget();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_5 = ___enemy0;
		NullCheck(L_5);
		Enemy_MoveToTarget_mCDF98A78E7279630FBE34E9183ACAE017D025132(L_5, /*hidden argument*/NULL);
	}

IL_0028:
	{
		// if (Mathf.Abs(enemy.transform.position.x - enemy.targetPoint.position.x) < 0.01f)
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_6 = ___enemy0;
		NullCheck(L_6);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_7 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_6, /*hidden argument*/NULL);
		NullCheck(L_7);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_8 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_7, /*hidden argument*/NULL);
		float L_9 = L_8.get_x_2();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_10 = ___enemy0;
		NullCheck(L_10);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = L_10->get_targetPoint_8();
		NullCheck(L_11);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_12 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_11, /*hidden argument*/NULL);
		float L_13 = L_12.get_x_2();
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_14 = fabsf(((float)il2cpp_codegen_subtract((float)L_9, (float)L_13)));
		if ((!(((float)L_14) < ((float)(0.01f)))))
		{
			goto IL_0061;
		}
	}
	{
		// enemy.TransitionToState(enemy.patrolState);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_15 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_16 = ___enemy0;
		NullCheck(L_16);
		PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * L_17 = L_16->get_patrolState_14();
		NullCheck(L_15);
		Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE(L_15, L_17, /*hidden argument*/NULL);
	}

IL_0061:
	{
		// if (enemy.attackList.Count > 0)
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_18 = ___enemy0;
		NullCheck(L_18);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_19 = L_18->get_attackList_9();
		NullCheck(L_19);
		int32_t L_20 = List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline(L_19, /*hidden argument*/List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var);
		if ((((int32_t)L_20) <= ((int32_t)0)))
		{
			goto IL_007b;
		}
	}
	{
		// enemy.TransitionToState(enemy.attachState);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_21 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_22 = ___enemy0;
		NullCheck(L_22);
		AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * L_23 = L_22->get_attachState_15();
		NullCheck(L_21);
		Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE(L_21, L_23, /*hidden argument*/NULL);
	}

IL_007b:
	{
		// }
		return;
	}
}
// System.Void PatrolState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PatrolState__ctor_m6CD97ED5CE7F0EB1531A78F30C5800AE708BF742 (PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * __this, const RuntimeMethod* method)
{
	{
		EnemyBaseState__ctor_m57F25EC153F6DA435937264866B5DAFB8A7531FA(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void PickUpState::OnEnterState(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PickUpState_OnEnterState_m473BD0AB5731204EB1894D78327966E6A993BE00 (PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	{
		// enemy.animState = 5;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_0 = ___enemy0;
		NullCheck(L_0);
		L_0->set_animState_12(5);
		// enemy.SwitchPoint();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_1 = ___enemy0;
		NullCheck(L_1);
		Enemy_SwitchPoint_mEB5076531D4C2544BD715A31A29A7355F19EDE11(L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PickUpState::OnUpdate(Enemy)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PickUpState_OnUpdate_m9BF02BCE6E486D29D1FD23DF826FB6DFA42D7264 (PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * __this, Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * ___enemy0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PickUpState_OnUpdate_m9BF02BCE6E486D29D1FD23DF826FB6DFA42D7264_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// if (!enemy.anim.GetCurrentAnimatorStateInfo(0).IsName("Idle"))
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_0 = ___enemy0;
		NullCheck(L_0);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_1 = L_0->get_anim_11();
		NullCheck(L_1);
		AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  L_2 = Animator_GetCurrentAnimatorStateInfo_mBE5ED0D60A6F5CD0EDD40AF1494098D4E7BF84F2(L_1, 0, /*hidden argument*/NULL);
		V_0 = L_2;
		bool L_3 = AnimatorStateInfo_IsName_mD133471910C1ACE0979F3FD11462C9B8BB24CA96((AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 *)(&V_0), _stringLiteralCC1EBDD04E76A4B8BAFFB29A22FA00446D382B18, /*hidden argument*/NULL);
		if (L_3)
		{
			goto IL_0028;
		}
	}
	{
		// enemy.animState = 1;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_4 = ___enemy0;
		NullCheck(L_4);
		L_4->set_animState_12(1);
		// enemy.MoveToTarget();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_5 = ___enemy0;
		NullCheck(L_5);
		Enemy_MoveToTarget_mCDF98A78E7279630FBE34E9183ACAE017D025132(L_5, /*hidden argument*/NULL);
	}

IL_0028:
	{
		// if (Mathf.Abs(enemy.transform.position.x - enemy.targetPoint.position.x) < 0.01f)
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_6 = ___enemy0;
		NullCheck(L_6);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_7 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_6, /*hidden argument*/NULL);
		NullCheck(L_7);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_8 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_7, /*hidden argument*/NULL);
		float L_9 = L_8.get_x_2();
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_10 = ___enemy0;
		NullCheck(L_10);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = L_10->get_targetPoint_8();
		NullCheck(L_11);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_12 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_11, /*hidden argument*/NULL);
		float L_13 = L_12.get_x_2();
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_14 = fabsf(((float)il2cpp_codegen_subtract((float)L_9, (float)L_13)));
		if ((!(((float)L_14) < ((float)(0.01f)))))
		{
			goto IL_0061;
		}
	}
	{
		// enemy.TransitionToState(enemy.patrolState);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_15 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_16 = ___enemy0;
		NullCheck(L_16);
		PatrolState_tBCA409AB797C9997D3F3275252D7C0CC2169B302 * L_17 = L_16->get_patrolState_14();
		NullCheck(L_15);
		Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE(L_15, L_17, /*hidden argument*/NULL);
	}

IL_0061:
	{
		// if (enemy.attackList.Count > 0)
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_18 = ___enemy0;
		NullCheck(L_18);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_19 = L_18->get_attackList_9();
		NullCheck(L_19);
		int32_t L_20 = List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline(L_19, /*hidden argument*/List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var);
		if ((((int32_t)L_20) <= ((int32_t)0)))
		{
			goto IL_007b;
		}
	}
	{
		// enemy.TransitionToState(enemy.attachState);
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_21 = ___enemy0;
		Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 * L_22 = ___enemy0;
		NullCheck(L_22);
		AttachState_t9A458D4BC5871A96BFB8DCA07266DA7162B2FBFF * L_23 = L_22->get_attachState_15();
		NullCheck(L_21);
		Enemy_TransitionToState_m806CA3ABB6A9BAEA3EC4FD94561E0DEC71A17DCE(L_21, L_23, /*hidden argument*/NULL);
	}

IL_007b:
	{
		// }
		return;
	}
}
// System.Void PickUpState::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PickUpState__ctor_mADC8DE8CCF7682F0788AF688F1ADBCD0057180F4 (PickUpState_t1E02A020511243C64492F1157677A687A72D2D8B * __this, const RuntimeMethod* method)
{
	{
		EnemyBaseState__ctor_m57F25EC153F6DA435937264866B5DAFB8A7531FA(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void PlayerAnimation::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerAnimation_Start_mA10B085DFC8D13CEC6453122FECBB665F460557D (PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerAnimation_Start_mA10B085DFC8D13CEC6453122FECBB665F460557D_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// anim = GetComponent<Animator>();
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719(__this, /*hidden argument*/Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719_RuntimeMethod_var);
		__this->set_anim_4(L_0);
		// rb = GetComponent<Rigidbody2D>();
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_1 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(__this, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		__this->set_rb_5(L_1);
		// controller = GetComponent<PlayerController>();
		PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * L_2 = Component_GetComponent_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_m503EAA28F55B66971C880C00538F81DCCB8C1629(__this, /*hidden argument*/Component_GetComponent_TisPlayerController_t4CE339054014370D89B89922EDC0EA2766589C85_m503EAA28F55B66971C880C00538F81DCCB8C1629_RuntimeMethod_var);
		__this->set_controller_6(L_2);
		// }
		return;
	}
}
// System.Void PlayerAnimation::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerAnimation_Update_mB996F7F54E3FED0EF71D0D584DB4965103650724 (PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerAnimation_Update_mB996F7F54E3FED0EF71D0D584DB4965103650724_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// anim.SetFloat("speed", Mathf.Abs(rb.velocity.x));//rb.velocity.x????
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = __this->get_anim_4();
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_1 = __this->get_rb_5();
		NullCheck(L_1);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Rigidbody2D_get_velocity_m5ABF36BDF90FD7308BE608667B9E8F3DA5A207F1(L_1, /*hidden argument*/NULL);
		float L_3 = L_2.get_x_0();
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_4 = fabsf(L_3);
		NullCheck(L_0);
		Animator_SetFloat_mE4C29F6980EBBBD954637721E6E13A0BE2B13C43(L_0, _stringLiteral92B6320812D86ABE48E76FBFBBE8BDE7170BF036, L_4, /*hidden argument*/NULL);
		// anim.SetFloat("velocityY", rb.velocity.y);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_5 = __this->get_anim_4();
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_6 = __this->get_rb_5();
		NullCheck(L_6);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_7 = Rigidbody2D_get_velocity_m5ABF36BDF90FD7308BE608667B9E8F3DA5A207F1(L_6, /*hidden argument*/NULL);
		float L_8 = L_7.get_y_1();
		NullCheck(L_5);
		Animator_SetFloat_mE4C29F6980EBBBD954637721E6E13A0BE2B13C43(L_5, _stringLiteralB8C11F366B0D4FEA18776C4D87C022E46BB29C77, L_8, /*hidden argument*/NULL);
		// anim.SetBool("jump", controller.isJump);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_9 = __this->get_anim_4();
		PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * L_10 = __this->get_controller_6();
		NullCheck(L_10);
		bool L_11 = L_10->get_isJump_13();
		NullCheck(L_9);
		Animator_SetBool_m497805BA217139E42808899782FA05C15BC9879E(L_9, _stringLiteral271E9A568C0E9E562431CCB1F5DA3422162DE7B8, L_11, /*hidden argument*/NULL);
		// anim.SetBool("ground", controller.isGround);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_12 = __this->get_anim_4();
		PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * L_13 = __this->get_controller_6();
		NullCheck(L_13);
		bool L_14 = L_13->get_isGround_12();
		NullCheck(L_12);
		Animator_SetBool_m497805BA217139E42808899782FA05C15BC9879E(L_12, _stringLiteralCD12AF96FA5C9A02893BDC7E05D1255A23036407, L_14, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PlayerAnimation::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerAnimation__ctor_mD63477A138056F507DA4C7CB13BB0D513A2C97A1 (PlayerAnimation_tC5F80D3306F091F95CE37AC0434FFBBB27661FCD * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void PlayerController::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Start_mC0C9B9461D0BDAC48EC43715818A4BA63C4F45EF (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_Start_mC0C9B9461D0BDAC48EC43715818A4BA63C4F45EF_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// rb = GetComponent<Rigidbody2D>();
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_0 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(__this, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		__this->set_rb_4(L_0);
		// anim = GetComponent<Animator>();
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_1 = Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719(__this, /*hidden argument*/Component_GetComponent_TisAnimator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A_mEA6C8FBABE309599A828D6BB8777278BCFB28719_RuntimeMethod_var);
		__this->set_anim_5(L_1);
		// health = GameManager.instance.LoadHealth();
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_2 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		NullCheck(L_2);
		float L_3 = GameManager_LoadHealth_mC037637C61400A7CFE7D50A9751533B40070B43A(L_2, /*hidden argument*/NULL);
		__this->set_health_20(L_3);
		// UIManager.instance.UpdateHealth(health);
		UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * L_4 = ((UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields*)il2cpp_codegen_static_fields_for(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var))->get_instance_4();
		float L_5 = __this->get_health_20();
		NullCheck(L_4);
		UIManager_UpdateHealth_mA054577A97EB1BD7C09B4161A32DAC4712F49DC6(L_4, L_5, /*hidden argument*/NULL);
		// joystick = FindObjectOfType<FixedJoystick>();
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * L_6 = Object_FindObjectOfType_TisFixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909_m15640DCFA39A3D28A6190EB0A4D8775B029FC5E8(/*hidden argument*/Object_FindObjectOfType_TisFixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909_m15640DCFA39A3D28A6190EB0A4D8775B029FC5E8_RuntimeMethod_var);
		__this->set_joystick_6(L_6);
		// }
		return;
	}
}
// System.Void PlayerController::Update()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Update_m38903EF1C8F12B9388303741F8040EE26C33DC33 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	{
		// if (isDead)
		bool L_0 = __this->get_isDead_21();
		if (!L_0)
		{
			goto IL_0009;
		}
	}
	{
		// return;
		return;
	}

IL_0009:
	{
		// CheckInput();
		PlayerController_CheckInput_mAC03BF1E0CD4690383608EFCB41FFBD962F86FDF(__this, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PlayerController::FixedUpdate()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_FixedUpdate_m914EA3E3CCE4DF6AEB2E78317FFC1D507DACEBDE (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_FixedUpdate_m914EA3E3CCE4DF6AEB2E78317FFC1D507DACEBDE_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (isDead)
		bool L_0 = __this->get_isDead_21();
		if (!L_0)
		{
			goto IL_0019;
		}
	}
	{
		// rb.velocity = Vector2.zero;//?????0
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_1 = __this->get_rb_4();
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		NullCheck(L_1);
		Rigidbody2D_set_velocity_mE0DBCE5B683024B106C2AB6943BBA550B5BD0B83(L_1, L_2, /*hidden argument*/NULL);
		// return;
		return;
	}

IL_0019:
	{
		// PhysicsCheck();
		PlayerController_PhysicsCheck_mF0842B47CA0495F34DE0891387C9AB27614396D5(__this, /*hidden argument*/NULL);
		// Movement();
		PlayerController_Movement_m49DA15D9DBCDD7D61B472B373607DB69054C847C(__this, /*hidden argument*/NULL);
		// Jump();
		PlayerController_Jump_m3056E2DF0CD8445804DCDAB6521E81541F0218A1(__this, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PlayerController::Attack()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Attack_m763538E8539EF73BF10B02AC22C9882C8F8006F2 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_Attack_m763538E8539EF73BF10B02AC22C9882C8F8006F2_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// if (Time.time > nextAttack)
		float L_0 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		float L_1 = __this->get_nextAttack_18();
		if ((!(((float)L_0) > ((float)L_1))))
		{
			goto IL_0082;
		}
	}
	{
		// Vector2 position = new Vector2();
		il2cpp_codegen_initobj((&V_0), sizeof(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D ));
		// position.y = transform.position.y;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_2);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_3 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_2, /*hidden argument*/NULL);
		float L_4 = L_3.get_y_3();
		(&V_0)->set_y_1(L_4);
		// position.x = transform.GetChild(1).transform.position.x;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_5 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_5);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_6 = Transform_GetChild_mC86B9B61E4EC086A571B09EA7A33FFBF50DF52D3(L_5, 1, /*hidden argument*/NULL);
		NullCheck(L_6);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_7 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_6, /*hidden argument*/NULL);
		NullCheck(L_7);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_8 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_7, /*hidden argument*/NULL);
		float L_9 = L_8.get_x_2();
		(&V_0)->set_x_0(L_9);
		// Instantiate(bombObject, position, bombObject.transform.rotation);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_10 = __this->get_bombObject_17();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_11 = V_0;
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_12 = Vector2_op_Implicit_mD152B6A34B4DB7FFECC2844D74718568FE867D6F(L_11, /*hidden argument*/NULL);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_13 = __this->get_bombObject_17();
		NullCheck(L_13);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_14 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_13, /*hidden argument*/NULL);
		NullCheck(L_14);
		Quaternion_t319F3319A7D43FFA5D819AD6C0A98851F0095357  L_15 = Transform_get_rotation_m3AB90A67403249AECCA5E02BC70FCE8C90FE9FB9(L_14, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		Object_Instantiate_TisGameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F_m4F397BCC6697902B40033E61129D4EA6FE93570F(L_10, L_12, L_15, /*hidden argument*/Object_Instantiate_TisGameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F_m4F397BCC6697902B40033E61129D4EA6FE93570F_RuntimeMethod_var);
		// nextAttack = Time.time + attackRate;
		float L_16 = Time_get_time_m7863349C8845BBA36629A2B3F8EF1C3BEA350FD8(/*hidden argument*/NULL);
		float L_17 = __this->get_attackRate_19();
		__this->set_nextAttack_18(((float)il2cpp_codegen_add((float)L_16, (float)L_17)));
	}

IL_0082:
	{
		// }
		return;
	}
}
// System.Void PlayerController::Movement()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Movement_m49DA15D9DBCDD7D61B472B373607DB69054C847C (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	float V_0 = 0.0f;
	{
		// float horizontalInput = joystick.Horizontal;
		FixedJoystick_tA793D5240D38B506203B52A20B5E94895CC41909 * L_0 = __this->get_joystick_6();
		NullCheck(L_0);
		float L_1 = Joystick_get_Horizontal_mD2CEADF3C7AD02BA60F7990F1A39BC67C6D8819B(L_0, /*hidden argument*/NULL);
		V_0 = L_1;
		// if (horizontalInput > 0)
		float L_2 = V_0;
		if ((!(((float)L_2) > ((float)(0.0f)))))
		{
			goto IL_001c;
		}
	}
	{
		// horizontalInput = 1;
		V_0 = (1.0f);
		// }else if (horizontalInput < 0)
		goto IL_002a;
	}

IL_001c:
	{
		// }else if (horizontalInput < 0)
		float L_3 = V_0;
		if ((!(((float)L_3) < ((float)(0.0f)))))
		{
			goto IL_002a;
		}
	}
	{
		// horizontalInput = -1;
		V_0 = (-1.0f);
	}

IL_002a:
	{
		// rb.velocity = new Vector2(horizontalInput * speed, rb.velocity.y);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_4 = __this->get_rb_4();
		float L_5 = V_0;
		float L_6 = __this->get_speed_7();
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_7 = __this->get_rb_4();
		NullCheck(L_7);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_8 = Rigidbody2D_get_velocity_m5ABF36BDF90FD7308BE608667B9E8F3DA5A207F1(L_7, /*hidden argument*/NULL);
		float L_9 = L_8.get_y_1();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_10;
		memset((&L_10), 0, sizeof(L_10));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_10), ((float)il2cpp_codegen_multiply((float)L_5, (float)L_6)), L_9, /*hidden argument*/NULL);
		NullCheck(L_4);
		Rigidbody2D_set_velocity_mE0DBCE5B683024B106C2AB6943BBA550B5BD0B83(L_4, L_10, /*hidden argument*/NULL);
		// if (0 != horizontalInput)
		float L_11 = V_0;
		if ((((float)(0.0f)) == ((float)L_11)))
		{
			goto IL_0075;
		}
	}
	{
		// transform.localScale = new Vector3(horizontalInput, 1, 1);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_12 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		float L_13 = V_0;
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_14;
		memset((&L_14), 0, sizeof(L_14));
		Vector3__ctor_m08F61F548AA5836D8789843ACB4A81E4963D2EE1((&L_14), L_13, (1.0f), (1.0f), /*hidden argument*/NULL);
		NullCheck(L_12);
		Transform_set_localScale_m7ED1A6E5A87CD1D483515B99D6D3121FB92B0556(L_12, L_14, /*hidden argument*/NULL);
	}

IL_0075:
	{
		// }
		return;
	}
}
// System.Void PlayerController::CheckInput()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_CheckInput_mAC03BF1E0CD4690383608EFCB41FFBD962F86FDF (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_CheckInput_mAC03BF1E0CD4690383608EFCB41FFBD962F86FDF_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (Input.GetButtonDown("Jump") && isGround)
		bool L_0 = Input_GetButtonDown_m1E80BAC5CCBE9E0151491B8F8F5FFD6AB050BBF0(_stringLiteral1EBA140FDD9C6860A1730C408E3064AA417CA2A3, /*hidden argument*/NULL);
		if (!L_0)
		{
			goto IL_001b;
		}
	}
	{
		bool L_1 = __this->get_isGround_12();
		if (!L_1)
		{
			goto IL_001b;
		}
	}
	{
		// canJump = true;
		__this->set_canJump_14((bool)1);
	}

IL_001b:
	{
		// if (Input.GetKeyDown(KeyCode.B))
		bool L_2 = Input_GetKeyDown_mEA57896808B6F484B12CD0AEEB83390A3CFCDBDC(((int32_t)98), /*hidden argument*/NULL);
		if (!L_2)
		{
			goto IL_002a;
		}
	}
	{
		// Attack();
		PlayerController_Attack_m763538E8539EF73BF10B02AC22C9882C8F8006F2(__this, /*hidden argument*/NULL);
	}

IL_002a:
	{
		// if (Input.GetKeyDown(KeyCode.N))
		bool L_3 = Input_GetKeyDown_mEA57896808B6F484B12CD0AEEB83390A3CFCDBDC(((int32_t)110), /*hidden argument*/NULL);
		if (!L_3)
		{
			goto IL_0039;
		}
	}
	{
		// KickBomb();
		PlayerController_KickBomb_m57A89383EE50DA2C527DC6BDA51F79A80AA0E2C5(__this, /*hidden argument*/NULL);
	}

IL_0039:
	{
		// }
		return;
	}
}
// System.Void PlayerController::JoystickJump()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_JoystickJump_m010A75AA87272C796DDE337FE33027F2F351850D (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	{
		// canJump = true;
		__this->set_canJump_14((bool)1);
		// Jump();
		PlayerController_Jump_m3056E2DF0CD8445804DCDAB6521E81541F0218A1(__this, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PlayerController::Jump()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_Jump_m3056E2DF0CD8445804DCDAB6521E81541F0218A1 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_Jump_m3056E2DF0CD8445804DCDAB6521E81541F0218A1_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (canJump)
		bool L_0 = __this->get_canJump_14();
		if (!L_0)
		{
			goto IL_008f;
		}
	}
	{
		// rb.velocity = new Vector2(rb.velocity.x, jumpForce);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_1 = __this->get_rb_4();
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_2 = __this->get_rb_4();
		NullCheck(L_2);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = Rigidbody2D_get_velocity_m5ABF36BDF90FD7308BE608667B9E8F3DA5A207F1(L_2, /*hidden argument*/NULL);
		float L_4 = L_3.get_x_0();
		float L_5 = __this->get_jumpForce_8();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_6;
		memset((&L_6), 0, sizeof(L_6));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_6), L_4, L_5, /*hidden argument*/NULL);
		NullCheck(L_1);
		Rigidbody2D_set_velocity_mE0DBCE5B683024B106C2AB6943BBA550B5BD0B83(L_1, L_6, /*hidden argument*/NULL);
		// canJump = false;
		__this->set_canJump_14((bool)0);
		// isJump = true;
		__this->set_isJump_13((bool)1);
		// rb.gravityScale = 4;//??
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_7 = __this->get_rb_4();
		NullCheck(L_7);
		Rigidbody2D_set_gravityScale_m4593B8D87314F00947B795AA442B90F1598B1104(L_7, (4.0f), /*hidden argument*/NULL);
		// gameObjectJump.SetActive(true);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_8 = __this->get_gameObjectJump_15();
		NullCheck(L_8);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_8, (bool)1, /*hidden argument*/NULL);
		// gameObjectJump.transform.position = transform.position + new Vector3(0, -0.1f, 0);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_9 = __this->get_gameObjectJump_15();
		NullCheck(L_9);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_10 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_9, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_11);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_12 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_11, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_13;
		memset((&L_13), 0, sizeof(L_13));
		Vector3__ctor_m08F61F548AA5836D8789843ACB4A81E4963D2EE1((&L_13), (0.0f), (-0.1f), (0.0f), /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_14 = Vector3_op_Addition_m929F9C17E5D11B94D50B4AFF1D730B70CB59B50E(L_12, L_13, /*hidden argument*/NULL);
		NullCheck(L_10);
		Transform_set_position_mDA89E4893F14ECA5CBEEE7FB80A5BF7C1B8EA6DC(L_10, L_14, /*hidden argument*/NULL);
	}

IL_008f:
	{
		// }
		return;
	}
}
// System.Void PlayerController::PhysicsCheck()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_PhysicsCheck_mF0842B47CA0495F34DE0891387C9AB27614396D5 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_PhysicsCheck_mF0842B47CA0495F34DE0891387C9AB27614396D5_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// isGround = Physics2D.OverlapCircle(groundCheck.position, checkRadius, groundLayer);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = __this->get_groundCheck_9();
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_2 = Vector2_op_Implicit_mEA1F75961E3D368418BA8CEB9C40E55C25BA3C28(L_1, /*hidden argument*/NULL);
		float L_3 = __this->get_checkRadius_10();
		LayerMask_tBB9173D8B6939D476E67E849280AC9F4EC4D93B0  L_4 = __this->get_groundLayer_11();
		int32_t L_5 = LayerMask_op_Implicit_m2AFFC7F931005437E8F356C953F439829AF4CFA5(L_4, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Physics2D_tB21970F986016656D66D2922594F336E1EE7D5C7_il2cpp_TypeInfo_var);
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_6 = Physics2D_OverlapCircle_m627FB9EE641A74B942877F57DD2FED656FDA5DC9(L_2, L_3, L_5, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		bool L_7 = Object_op_Implicit_m8B2A44B4B1406ED346D1AE6D962294FD58D0D534(L_6, /*hidden argument*/NULL);
		__this->set_isGround_12(L_7);
		// if (isGround)
		bool L_8 = __this->get_isGround_12();
		if (!L_8)
		{
			goto IL_0050;
		}
	}
	{
		// rb.gravityScale = 1;
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_9 = __this->get_rb_4();
		NullCheck(L_9);
		Rigidbody2D_set_gravityScale_m4593B8D87314F00947B795AA442B90F1598B1104(L_9, (1.0f), /*hidden argument*/NULL);
		// isJump = false;
		__this->set_isJump_13((bool)0);
	}

IL_0050:
	{
		// }
		return;
	}
}
// System.Void PlayerController::OnDrawGizmos()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_OnDrawGizmos_m513E800E9717AB66BDAAE8A624A1B2F45B67E508 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	{
		// Gizmos.DrawWireSphere(groundCheck.position, checkRadius);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = __this->get_groundCheck_9();
		NullCheck(L_0);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_1 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_0, /*hidden argument*/NULL);
		float L_2 = __this->get_checkRadius_10();
		Gizmos_DrawWireSphere_mF6F2BC5CDF7B3F312FE9AB579CDC1C6B72154BCF(L_1, L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PlayerController::landFX()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_landFX_mAD14E42C2F9C123BA802624DB9DFD14A5FD1F3F1 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_landFX_mAD14E42C2F9C123BA802624DB9DFD14A5FD1F3F1_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// gameObjectLand.SetActive(true);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = __this->get_gameObjectLand_16();
		NullCheck(L_0);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_0, (bool)1, /*hidden argument*/NULL);
		// gameObjectLand.transform.position = transform.position + new Vector3(0, -1.0f, 0);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_1 = __this->get_gameObjectLand_16();
		NullCheck(L_1);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_1, /*hidden argument*/NULL);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_3);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_4 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_3, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_5;
		memset((&L_5), 0, sizeof(L_5));
		Vector3__ctor_m08F61F548AA5836D8789843ACB4A81E4963D2EE1((&L_5), (0.0f), (-1.0f), (0.0f), /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_6 = Vector3_op_Addition_m929F9C17E5D11B94D50B4AFF1D730B70CB59B50E(L_4, L_5, /*hidden argument*/NULL);
		NullCheck(L_2);
		Transform_set_position_mDA89E4893F14ECA5CBEEE7FB80A5BF7C1B8EA6DC(L_2, L_6, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void PlayerController::GetHit(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_GetHit_m430DA9E36AD2C9CAE846AA22C840B3ECAEEC2493 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, float ___damage0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_GetHit_m430DA9E36AD2C9CAE846AA22C840B3ECAEEC2493_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// if (!anim.GetCurrentAnimatorStateInfo(1).IsName("Hit"))
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_0 = __this->get_anim_5();
		NullCheck(L_0);
		AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2  L_1 = Animator_GetCurrentAnimatorStateInfo_mBE5ED0D60A6F5CD0EDD40AF1494098D4E7BF84F2(L_0, 1, /*hidden argument*/NULL);
		V_0 = L_1;
		bool L_2 = AnimatorStateInfo_IsName_mD133471910C1ACE0979F3FD11462C9B8BB24CA96((AnimatorStateInfo_tF6D8ADF771CD13DC578AC9A574FD33CC99AD46E2 *)(&V_0), _stringLiteralEA490AAA629A0704301CF91E7A4910B910278662, /*hidden argument*/NULL);
		if (L_2)
		{
			goto IL_008a;
		}
	}
	{
		// health -= damage;
		float L_3 = __this->get_health_20();
		float L_4 = ___damage0;
		__this->set_health_20(((float)il2cpp_codegen_subtract((float)L_3, (float)L_4)));
		// if (health < 1)
		float L_5 = __this->get_health_20();
		if ((!(((float)L_5) < ((float)(1.0f)))))
		{
			goto IL_006a;
		}
	}
	{
		// health = 0;
		__this->set_health_20((0.0f));
		// isDead = true;
		__this->set_isDead_21((bool)1);
		// anim.SetBool("dead", isDead);
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_6 = __this->get_anim_5();
		bool L_7 = __this->get_isDead_21();
		NullCheck(L_6);
		Animator_SetBool_m497805BA217139E42808899782FA05C15BC9879E(L_6, _stringLiteral5EB965DD8C804A3A2833AC61FE1D1F6B1960735A, L_7, /*hidden argument*/NULL);
		// GameManager.instance.GameOver();
		IL2CPP_RUNTIME_CLASS_INIT(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var);
		GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89 * L_8 = ((GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_StaticFields*)il2cpp_codegen_static_fields_for(GameManager_tAC830B937D5E37F47803FE8AB44CAB0762B77B89_il2cpp_TypeInfo_var))->get_instance_5();
		NullCheck(L_8);
		GameManager_GameOver_m658E745BE197CC36CFAE422F8037F41A1B7FFFD3(L_8, /*hidden argument*/NULL);
		// }
		goto IL_007a;
	}

IL_006a:
	{
		// anim.SetTrigger("hit");
		Animator_tF1A88E66B3B731DDA75A066DBAE9C55837660F5A * L_9 = __this->get_anim_5();
		NullCheck(L_9);
		Animator_SetTrigger_m68D29B7FA54C2F230F5AD780D462612B18E74245(L_9, _stringLiteralD7D390BD9EBAC6BFA0B17AB10695FE73916EBCC2, /*hidden argument*/NULL);
	}

IL_007a:
	{
		// UIManager.instance.UpdateHealth(health);
		UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * L_10 = ((UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields*)il2cpp_codegen_static_fields_for(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var))->get_instance_4();
		float L_11 = __this->get_health_20();
		NullCheck(L_10);
		UIManager_UpdateHealth_mA054577A97EB1BD7C09B4161A32DAC4712F49DC6(L_10, L_11, /*hidden argument*/NULL);
	}

IL_008a:
	{
		// }
		return;
	}
}
// System.Void PlayerController::KickBomb()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_KickBomb_m57A89383EE50DA2C527DC6BDA51F79A80AA0E2C5 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_KickBomb_m57A89383EE50DA2C527DC6BDA51F79A80AA0E2C5_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * V_0 = NULL;
	int32_t V_1 = 0;
	int32_t V_2 = 0;
	Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * V_3 = NULL;
	int32_t G_B9_0 = 0;
	{
		// if (bombs.Count > 0)
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_0 = __this->get_bombs_22();
		NullCheck(L_0);
		int32_t L_1 = List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline(L_0, /*hidden argument*/List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var);
		if ((((int32_t)L_1) <= ((int32_t)0)))
		{
			goto IL_00d0;
		}
	}
	{
		// Transform nearestBomb = bombs[0];
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_2 = __this->get_bombs_22();
		NullCheck(L_2);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_3 = List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_inline(L_2, 0, /*hidden argument*/List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_RuntimeMethod_var);
		V_0 = L_3;
		// for (int i = 1; i < bombs.Count; i++)
		V_2 = 1;
		goto IL_007e;
	}

IL_0022:
	{
		// Transform kickBomb = bombs[i];
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_4 = __this->get_bombs_22();
		int32_t L_5 = V_2;
		NullCheck(L_4);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_6 = List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_inline(L_4, L_5, /*hidden argument*/List_1_get_Item_m88FE4B6F43A2CD95BB9ECF8D801F206618FFFFB8_RuntimeMethod_var);
		V_3 = L_6;
		// if (Mathf.Abs(transform.position.x - kickBomb.position.x) < Mathf.Abs(transform.position.x - nearestBomb.position.x))
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_7 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_7);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_8 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_7, /*hidden argument*/NULL);
		float L_9 = L_8.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_10 = V_3;
		NullCheck(L_10);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_11 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_10, /*hidden argument*/NULL);
		float L_12 = L_11.get_x_2();
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_13 = fabsf(((float)il2cpp_codegen_subtract((float)L_9, (float)L_12)));
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_14 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_14);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_15 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_14, /*hidden argument*/NULL);
		float L_16 = L_15.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_17 = V_0;
		NullCheck(L_17);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_18 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_17, /*hidden argument*/NULL);
		float L_19 = L_18.get_x_2();
		float L_20 = fabsf(((float)il2cpp_codegen_subtract((float)L_16, (float)L_19)));
		if ((!(((float)L_13) < ((float)L_20))))
		{
			goto IL_007a;
		}
	}
	{
		// nearestBomb = transform;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_21 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		V_0 = L_21;
	}

IL_007a:
	{
		// for (int i = 1; i < bombs.Count; i++)
		int32_t L_22 = V_2;
		V_2 = ((int32_t)il2cpp_codegen_add((int32_t)L_22, (int32_t)1));
	}

IL_007e:
	{
		// for (int i = 1; i < bombs.Count; i++)
		int32_t L_23 = V_2;
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_24 = __this->get_bombs_22();
		NullCheck(L_24);
		int32_t L_25 = List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_inline(L_24, /*hidden argument*/List_1_get_Count_mFB4F65ABD2DD0845C2448493238223FB4079A90C_RuntimeMethod_var);
		if ((((int32_t)L_23) < ((int32_t)L_25)))
		{
			goto IL_0022;
		}
	}
	{
		// int dir = transform.position.x < nearestBomb.position.x ? 1 : -1;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_26 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_26);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_27 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_26, /*hidden argument*/NULL);
		float L_28 = L_27.get_x_2();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_29 = V_0;
		NullCheck(L_29);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_30 = Transform_get_position_mF54C3A064F7C8E24F1C56EE128728B2E4485E294(L_29, /*hidden argument*/NULL);
		float L_31 = L_30.get_x_2();
		if ((((float)L_28) < ((float)L_31)))
		{
			goto IL_00ac;
		}
	}
	{
		G_B9_0 = (-1);
		goto IL_00ad;
	}

IL_00ac:
	{
		G_B9_0 = 1;
	}

IL_00ad:
	{
		V_1 = G_B9_0;
		// nearestBomb.GetComponent<Rigidbody2D>().AddForce(new Vector2(dir, 0.5f) * 5, ForceMode2D.Impulse);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_32 = V_0;
		NullCheck(L_32);
		Rigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE * L_33 = Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625(L_32, /*hidden argument*/Component_GetComponent_TisRigidbody2D_tBDC6900A76D3C47E291446FF008D02B817C81CDE_mBF198078E908267FB6DA59F6242FC8F36FC06625_RuntimeMethod_var);
		int32_t L_34 = V_1;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_35;
		memset((&L_35), 0, sizeof(L_35));
		Vector2__ctor_mEE8FB117AB1F8DB746FB8B3EB4C0DA3BF2A230D0((&L_35), (((float)((float)L_34))), (0.5f), /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_36 = Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56(L_35, (5.0f), /*hidden argument*/NULL);
		NullCheck(L_33);
		Rigidbody2D_AddForce_m09E1A2E24DABA5BBC613E35772AE2C1C35C6E40C(L_33, L_36, 1, /*hidden argument*/NULL);
	}

IL_00d0:
	{
		// }
		return;
	}
}
// System.Void PlayerController::OnTriggerEnter2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_OnTriggerEnter2D_m4BFC3BB96B7F16C5F0E6A7BE6795149716478A74 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_OnTriggerEnter2D_m4BFC3BB96B7F16C5F0E6A7BE6795149716478A74_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (collision.CompareTag("Bomb"))
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_0 = ___collision0;
		NullCheck(L_0);
		bool L_1 = Component_CompareTag_mD074608D7FEC96A53C57A456BA613EE01C31D4B7(L_0, _stringLiteralD5BF9D845AB97255CB3AB1100656DB4F59731808, /*hidden argument*/NULL);
		if (!L_1)
		{
			goto IL_001e;
		}
	}
	{
		// bombs.Add(collision.transform);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_2 = __this->get_bombs_22();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_3 = ___collision0;
		NullCheck(L_3);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_4 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_3, /*hidden argument*/NULL);
		NullCheck(L_2);
		List_1_Add_mEB0CDED8A9ADCC0F235881A5D34D41085EC4780C(L_2, L_4, /*hidden argument*/List_1_Add_mEB0CDED8A9ADCC0F235881A5D34D41085EC4780C_RuntimeMethod_var);
	}

IL_001e:
	{
		// }
		return;
	}
}
// System.Void PlayerController::OnTriggerExit2D(UnityEngine.Collider2D)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController_OnTriggerExit2D_m8E5A01B8FA14061A9E824E3B4AA6E702BC32A870 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * ___collision0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController_OnTriggerExit2D_m8E5A01B8FA14061A9E824E3B4AA6E702BC32A870_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// bombs.Remove(collision.transform);
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_0 = __this->get_bombs_22();
		Collider2D_tD64BE58E48B95D89D349FEAB54D0FE2EEBF83379 * L_1 = ___collision0;
		NullCheck(L_1);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(L_1, /*hidden argument*/NULL);
		NullCheck(L_0);
		List_1_Remove_m8E1311599BA3E940469F201FE770645882E0783A(L_0, L_2, /*hidden argument*/List_1_Remove_m8E1311599BA3E940469F201FE770645882E0783A_RuntimeMethod_var);
		// }
		return;
	}
}
// System.Void PlayerController::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void PlayerController__ctor_m648E40092E37395F4307411E855445886113CD60 (PlayerController_t4CE339054014370D89B89922EDC0EA2766589C85 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (PlayerController__ctor_m648E40092E37395F4307411E855445886113CD60_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// private List<Transform> bombs = new List<Transform>();
		List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE * L_0 = (List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE *)il2cpp_codegen_object_new(List_1_t4DBFD85DCFB946888856DBE52AC08C2AF69C4DBE_il2cpp_TypeInfo_var);
		List_1__ctor_m0046B0A356552D7B951C2CEEE5F1375DAF72054A(L_0, /*hidden argument*/List_1__ctor_m0046B0A356552D7B951C2CEEE5F1375DAF72054A_RuntimeMethod_var);
		__this->set_bombs_22(L_0);
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void UIManager::Awake()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_Awake_mA946658D43E2FC2C3479BB9322CED4FF4C5D2EA0 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (UIManager_Awake_mA946658D43E2FC2C3479BB9322CED4FF4C5D2EA0_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// if (instance == null)
		UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * L_0 = ((UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields*)il2cpp_codegen_static_fields_for(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var))->get_instance_4();
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		bool L_1 = Object_op_Equality_mBC2401774F3BE33E8CF6F0A8148E66C95D6CFF1C(L_0, (Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0 *)NULL, /*hidden argument*/NULL);
		if (!L_1)
		{
			goto IL_0014;
		}
	}
	{
		// instance = this;
		((UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_StaticFields*)il2cpp_codegen_static_fields_for(UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C_il2cpp_TypeInfo_var))->set_instance_4(__this);
		// }
		return;
	}

IL_0014:
	{
		// Destroy(gameObject);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_2 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(__this, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Object_tAE11E5E46CD5C37C9F3E8950C00CD8B45666A2D0_il2cpp_TypeInfo_var);
		Object_Destroy_m23B4562495BA35A74266D4372D45368F8C05109A(L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void UIManager::UpdateHealth(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_UpdateHealth_mA054577A97EB1BD7C09B4161A32DAC4712F49DC6 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, float ___currentHealth0, const RuntimeMethod* method)
{
	{
		// healthBar.transform.GetChild(0).gameObject.SetActive(currentHealth >= 1);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = __this->get_healthBar_5();
		NullCheck(L_0);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_1 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_0, /*hidden argument*/NULL);
		NullCheck(L_1);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = Transform_GetChild_mC86B9B61E4EC086A571B09EA7A33FFBF50DF52D3(L_1, 0, /*hidden argument*/NULL);
		NullCheck(L_2);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_3 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_2, /*hidden argument*/NULL);
		float L_4 = ___currentHealth0;
		NullCheck(L_3);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_3, (bool)((((int32_t)((!(((float)L_4) >= ((float)(1.0f))))? 1 : 0)) == ((int32_t)0))? 1 : 0), /*hidden argument*/NULL);
		// healthBar.transform.GetChild(1).gameObject.SetActive(currentHealth >= 2);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_5 = __this->get_healthBar_5();
		NullCheck(L_5);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_6 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_5, /*hidden argument*/NULL);
		NullCheck(L_6);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_7 = Transform_GetChild_mC86B9B61E4EC086A571B09EA7A33FFBF50DF52D3(L_6, 1, /*hidden argument*/NULL);
		NullCheck(L_7);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_8 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_7, /*hidden argument*/NULL);
		float L_9 = ___currentHealth0;
		NullCheck(L_8);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_8, (bool)((((int32_t)((!(((float)L_9) >= ((float)(2.0f))))? 1 : 0)) == ((int32_t)0))? 1 : 0), /*hidden argument*/NULL);
		// healthBar.transform.GetChild(2).gameObject.SetActive(currentHealth >= 3);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_10 = __this->get_healthBar_5();
		NullCheck(L_10);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = GameObject_get_transform_mA5C38857137F137CB96C69FAA624199EB1C2FB2C(L_10, /*hidden argument*/NULL);
		NullCheck(L_11);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_12 = Transform_GetChild_mC86B9B61E4EC086A571B09EA7A33FFBF50DF52D3(L_11, 2, /*hidden argument*/NULL);
		NullCheck(L_12);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_13 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_12, /*hidden argument*/NULL);
		float L_14 = ___currentHealth0;
		NullCheck(L_13);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_13, (bool)((((int32_t)((!(((float)L_14) >= ((float)(3.0f))))? 1 : 0)) == ((int32_t)0))? 1 : 0), /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void UIManager::PauseGame()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_PauseGame_m36A217FE3C021F9D82FA79E0A9E6D27E3C9C5240 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, const RuntimeMethod* method)
{
	{
		// pauseMenu.SetActive(true);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = __this->get_pauseMenu_6();
		NullCheck(L_0);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_0, (bool)1, /*hidden argument*/NULL);
		// Time.timeScale = 0;//????
		Time_set_timeScale_mAB89C3BB5DEE81934159C23F103397A77AC3F4AF((0.0f), /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void UIManager::ResumeGame()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_ResumeGame_m8831185CBE3E3251216E09BAEA2AB71B2F79D653 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, const RuntimeMethod* method)
{
	{
		// pauseMenu.SetActive(false);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = __this->get_pauseMenu_6();
		NullCheck(L_0);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_0, (bool)0, /*hidden argument*/NULL);
		// Time.timeScale = 1;
		Time_set_timeScale_mAB89C3BB5DEE81934159C23F103397A77AC3F4AF((1.0f), /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void UIManager::SetBossMaxHealth(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_SetBossMaxHealth_m7990FC8C3142CF8AEC5BE6F5948DB37DF9B1B03D (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, float ___health0, const RuntimeMethod* method)
{
	{
		// bossHealthBar.maxValue = health;
		Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 * L_0 = __this->get_bossHealthBar_8();
		float L_1 = ___health0;
		NullCheck(L_0);
		Slider_set_maxValue_m45561A3731F4EB48C10715E062856824B5AEF20B(L_0, L_1, /*hidden argument*/NULL);
		// bossHealthBar.value = health;
		Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 * L_2 = __this->get_bossHealthBar_8();
		float L_3 = ___health0;
		NullCheck(L_2);
		VirtActionInvoker1< float >::Invoke(47 /* System.Void UnityEngine.UI.Slider::set_value(System.Single) */, L_2, L_3);
		// }
		return;
	}
}
// System.Void UIManager::SetBossCurrentHealth(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_SetBossCurrentHealth_m6C908308D1E920352F5F0ADF40A2BED73978ED7E (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, float ___health0, const RuntimeMethod* method)
{
	{
		// bossHealthBar.value = health;
		Slider_t0654A41304B5CE7074CA86F4E66CB681D0D52C09 * L_0 = __this->get_bossHealthBar_8();
		float L_1 = ___health0;
		NullCheck(L_0);
		VirtActionInvoker1< float >::Invoke(47 /* System.Void UnityEngine.UI.Slider::set_value(System.Single) */, L_0, L_1);
		// }
		return;
	}
}
// System.Void UIManager::setGameOverPanelVisible(System.Boolean)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager_setGameOverPanelVisible_m8C7780AE4FC448BD13DDDB34D2C961F3AFD810D5 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, bool ___visible0, const RuntimeMethod* method)
{
	{
		// gameOverPanel.SetActive(visible);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_0 = __this->get_gameOverPanel_7();
		bool L_1 = ___visible0;
		NullCheck(L_0);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_0, L_1, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void UIManager::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void UIManager__ctor_m40CA6521CEDDF979D58B6050A6D294A32A1CEA69 (UIManager_tA871F1BE896F9D7434A52E7413E3C9F11E6B323C * __this, const RuntimeMethod* method)
{
	{
		MonoBehaviour__ctor_mEAEC84B222C60319D593E456D769B3311DFCEF97(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Single VariableJoystick::get_MoveThreshold()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR float VariableJoystick_get_MoveThreshold_m7680F75A6FE65378FA1882A60F1D2D7C10E1585F (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, const RuntimeMethod* method)
{
	{
		// public float MoveThreshold { get { return moveThreshold; } set { moveThreshold = Mathf.Abs(value); } }
		float L_0 = __this->get_moveThreshold_15();
		return L_0;
	}
}
// System.Void VariableJoystick::set_MoveThreshold(System.Single)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick_set_MoveThreshold_m70CF65250847566A28B2A418C3EE55004987552F (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, float ___value0, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (VariableJoystick_set_MoveThreshold_m70CF65250847566A28B2A418C3EE55004987552F_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// public float MoveThreshold { get { return moveThreshold; } set { moveThreshold = Mathf.Abs(value); } }
		float L_0 = ___value0;
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_1 = fabsf(L_0);
		__this->set_moveThreshold_15(L_1);
		// public float MoveThreshold { get { return moveThreshold; } set { moveThreshold = Mathf.Abs(value); } }
		return;
	}
}
// System.Void VariableJoystick::SetMode(JoystickType)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick_SetMode_m222D977BBDA4E253D4EAF1E55925FAD333EA7CAE (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, int32_t ___joystickType0, const RuntimeMethod* method)
{
	{
		// this.joystickType = joystickType;
		int32_t L_0 = ___joystickType0;
		__this->set_joystickType_16(L_0);
		// if(joystickType == JoystickType.Fixed)
		int32_t L_1 = ___joystickType0;
		if (L_1)
		{
			goto IL_002d;
		}
	}
	{
		// background.anchoredPosition = fixedPosition;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_2 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = __this->get_fixedPosition_17();
		NullCheck(L_2);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_2, L_3, /*hidden argument*/NULL);
		// background.gameObject.SetActive(true);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_4 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_4);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_5 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_4, /*hidden argument*/NULL);
		NullCheck(L_5);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_5, (bool)1, /*hidden argument*/NULL);
		// }
		return;
	}

IL_002d:
	{
		// background.gameObject.SetActive(false);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_6 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_6);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_7 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_6, /*hidden argument*/NULL);
		NullCheck(L_7);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_7, (bool)0, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void VariableJoystick::Start()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick_Start_m5BB1A8FE9E2EBC394C4AC8B4E495AB653F61E8E2 (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, const RuntimeMethod* method)
{
	{
		// base.Start();
		Joystick_Start_mA4B921AF2FEC7B830AC4F0D5E49AF8934ECAD201(__this, /*hidden argument*/NULL);
		// fixedPosition = background.anchoredPosition;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_0 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_0);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_1 = RectTransform_get_anchoredPosition_mCB2171DBADBC572F354CCFE3ACA19F9506F97907(L_0, /*hidden argument*/NULL);
		__this->set_fixedPosition_17(L_1);
		// SetMode(joystickType);
		int32_t L_2 = __this->get_joystickType_16();
		VariableJoystick_SetMode_m222D977BBDA4E253D4EAF1E55925FAD333EA7CAE(__this, L_2, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void VariableJoystick::OnPointerDown(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick_OnPointerDown_m066F12E7818D1CD22977EAEA9FE4AEC0DD179FAC (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	{
		// if(joystickType != JoystickType.Fixed)
		int32_t L_0 = __this->get_joystickType_16();
		if (!L_0)
		{
			goto IL_0030;
		}
	}
	{
		// background.anchoredPosition = ScreenPointToAnchoredPosition(eventData.position);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_1 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_2 = ___eventData0;
		NullCheck(L_2);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = PointerEventData_get_position_mF25FC495A9C968C65BF34B5984616CBFB6332D55_inline(L_2, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_4 = Joystick_ScreenPointToAnchoredPosition_mE4C429E76D0FA78FD1567EB1361AF68141706201(__this, L_3, /*hidden argument*/NULL);
		NullCheck(L_1);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_1, L_4, /*hidden argument*/NULL);
		// background.gameObject.SetActive(true);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_5 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_5);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_6 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_5, /*hidden argument*/NULL);
		NullCheck(L_6);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_6, (bool)1, /*hidden argument*/NULL);
	}

IL_0030:
	{
		// base.OnPointerDown(eventData);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_7 = ___eventData0;
		Joystick_OnPointerDown_m408D43BE6A49862DFD49B5198E0B61B85A162703(__this, L_7, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void VariableJoystick::OnPointerUp(UnityEngine.EventSystems.PointerEventData)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick_OnPointerUp_m42B201EDAB1B3A2F2ED747FA7A4773E2654DA061 (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * ___eventData0, const RuntimeMethod* method)
{
	{
		// if(joystickType != JoystickType.Fixed)
		int32_t L_0 = __this->get_joystickType_16();
		if (!L_0)
		{
			goto IL_0019;
		}
	}
	{
		// background.gameObject.SetActive(false);
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_1 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		NullCheck(L_1);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_2 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_1, /*hidden argument*/NULL);
		NullCheck(L_2);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_2, (bool)0, /*hidden argument*/NULL);
	}

IL_0019:
	{
		// base.OnPointerUp(eventData);
		PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * L_3 = ___eventData0;
		Joystick_OnPointerUp_m771F7519F51F02DAADA7DE0A562F82710FA721BC(__this, L_3, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void VariableJoystick::HandleInput(System.Single,UnityEngine.Vector2,UnityEngine.Vector2,UnityEngine.Camera)
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick_HandleInput_m83CA8AFC5C395DE4C684F2C478D1DE36CAD0BF19 (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, float ___magnitude0, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___normalised1, Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  ___radius2, Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * ___cam3, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (VariableJoystick_HandleInput_m83CA8AFC5C395DE4C684F2C478D1DE36CAD0BF19_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// if (joystickType == JoystickType.Dynamic && magnitude > moveThreshold)
		int32_t L_0 = __this->get_joystickType_16();
		if ((!(((uint32_t)L_0) == ((uint32_t)2))))
		{
			goto IL_003e;
		}
	}
	{
		float L_1 = ___magnitude0;
		float L_2 = __this->get_moveThreshold_15();
		if ((!(((float)L_1) > ((float)L_2))))
		{
			goto IL_003e;
		}
	}
	{
		// Vector2 difference = normalised * (magnitude - moveThreshold) * radius;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_3 = ___normalised1;
		float L_4 = ___magnitude0;
		float L_5 = __this->get_moveThreshold_15();
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_6 = Vector2_op_Multiply_m8A843A37F2F3199EBE99DC7BDABC1DC2EE01AF56(L_3, ((float)il2cpp_codegen_subtract((float)L_4, (float)L_5)), /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_7 = ___radius2;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_8 = Vector2_op_Multiply_mEDF9FDDF3BFFAEC997FBCDE5FA34871F2955E7C4(L_6, L_7, /*hidden argument*/NULL);
		V_0 = L_8;
		// background.anchoredPosition += difference;
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_9 = ((Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 *)__this)->get_background_9();
		RectTransform_t285CBD8775B25174B75164F10618F8B9728E1B20 * L_10 = L_9;
		NullCheck(L_10);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_11 = RectTransform_get_anchoredPosition_mCB2171DBADBC572F354CCFE3ACA19F9506F97907(L_10, /*hidden argument*/NULL);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_12 = V_0;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_13 = Vector2_op_Addition_m81A4D928B8E399DA3A4E3ACD8937EDFDCB014682(L_11, L_12, /*hidden argument*/NULL);
		NullCheck(L_10);
		RectTransform_set_anchoredPosition_m4DD45DB1A97734A1F3A81E5F259638ECAF35962F(L_10, L_13, /*hidden argument*/NULL);
	}

IL_003e:
	{
		// base.HandleInput(magnitude, normalised, radius, cam);
		float L_14 = ___magnitude0;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_15 = ___normalised1;
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_16 = ___radius2;
		Camera_t48B2B9ECB3CE6108A98BF949A1CECF0FE3421F34 * L_17 = ___cam3;
		Joystick_HandleInput_mA2FF5AE57290471865DC02DC2ED3BDA3FDBA2506(__this, L_14, L_15, L_16, L_17, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void VariableJoystick::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void VariableJoystick__ctor_m8A6171BB962558D6833C6CF80E3E0092DF768D84 (VariableJoystick_t9C1A77B6CFC93759F7E8F5F84F9EDBFF28A80ED1 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (VariableJoystick__ctor_m8A6171BB962558D6833C6CF80E3E0092DF768D84_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	{
		// [SerializeField] private float moveThreshold = 1;
		__this->set_moveThreshold_15((1.0f));
		// private Vector2 fixedPosition = Vector2.zero;
		IL2CPP_RUNTIME_CLASS_INIT(Vector2_tA85D2DD88578276CA8A8796756458277E72D073D_il2cpp_TypeInfo_var);
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_0 = Vector2_get_zero_mFE0C3213BB698130D6C5247AB4B887A59074D0A8(/*hidden argument*/NULL);
		__this->set_fixedPosition_17(L_0);
		Joystick__ctor_m0CEC3DFCF02C69B8020F600539EB02297E26D1CE(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif
// System.Void Whale::SkillAttack()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Whale_SkillAttack_m9536A7862900FFB42D554A9F2FB0145A147969E3 (Whale_t11A3C3495AC360DE58A5FE06BAAA3384761EA301 * __this, const RuntimeMethod* method)
{
	{
		// base.SkillAttack();
		Enemy_SkillAttack_m4E4DA6E8B23FB444ED5D8F3EF20F8BF818AA766E(__this, /*hidden argument*/NULL);
		// }
		return;
	}
}
// System.Void Whale::Swalow()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Whale_Swalow_m11F219ABC08F833B8DF7CD739847C202D4ECF96E (Whale_t11A3C3495AC360DE58A5FE06BAAA3384761EA301 * __this, const RuntimeMethod* method)
{
	static bool s_Il2CppMethodInitialized;
	if (!s_Il2CppMethodInitialized)
	{
		il2cpp_codegen_initialize_method (Whale_Swalow_m11F219ABC08F833B8DF7CD739847C202D4ECF96E_MetadataUsageId);
		s_Il2CppMethodInitialized = true;
	}
	Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  V_0;
	memset((&V_0), 0, sizeof(V_0));
	{
		// targetPoint.GetComponent<Bomb>().TurnOff();
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_0 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_0);
		Bomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2 * L_1 = Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C(L_0, /*hidden argument*/Component_GetComponent_TisBomb_tA1E33323132ED1A7C333DAE65AC662311951FDD2_m9008104E421691821EF76DE4BE1E5FCA0181D23C_RuntimeMethod_var);
		NullCheck(L_1);
		Bomb_TurnOff_mAF8955158FE03383BD5C734628B71CCA19ABE778(L_1, /*hidden argument*/NULL);
		// targetPoint.gameObject.SetActive(false);
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_2 = ((Enemy_tFD4DFBD9B55680685776C01FAC4E6877F5935DF6 *)__this)->get_targetPoint_8();
		NullCheck(L_2);
		GameObject_tBD1244AD56B4E59AAD76E5E7C9282EC5CE434F0F * L_3 = Component_get_gameObject_m0B0570BA8DDD3CD78A9DB568EA18D7317686603C(L_2, /*hidden argument*/NULL);
		NullCheck(L_3);
		GameObject_SetActive_m25A39F6D9FB68C51F13313F9804E85ACC937BC04(L_3, (bool)0, /*hidden argument*/NULL);
		// Vector3 scale = transform.localScale * 1.1f;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_4 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		NullCheck(L_4);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_5 = Transform_get_localScale_mD8F631021C2D62B7C341B1A17FA75491F64E13DA(L_4, /*hidden argument*/NULL);
		IL2CPP_RUNTIME_CLASS_INIT(Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720_il2cpp_TypeInfo_var);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_6 = Vector3_op_Multiply_m1C5F07723615156ACF035D88A1280A9E8F35A04E(L_5, (1.1f), /*hidden argument*/NULL);
		V_0 = L_6;
		// if (Mathf.Abs(scale.x) < maxScale)
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_7 = V_0;
		float L_8 = L_7.get_x_2();
		IL2CPP_RUNTIME_CLASS_INIT(Mathf_tFBDE6467D269BFE410605C7D806FD9991D4A89CB_il2cpp_TypeInfo_var);
		float L_9 = fabsf(L_8);
		float L_10 = __this->get_maxScale_24();
		if ((!(((float)L_9) < ((float)L_10))))
		{
			goto IL_0056;
		}
	}
	{
		// transform.localScale = scale;
		Transform_tBB9E78A2766C3C83599A8F66EDE7D1FCAFC66EDA * L_11 = Component_get_transform_m00F05BD782F920C301A7EBA480F3B7A904C07EC9(__this, /*hidden argument*/NULL);
		Vector3_tDCF05E21F632FE2BA260C06E0D10CA81513E6720  L_12 = V_0;
		NullCheck(L_11);
		Transform_set_localScale_m7ED1A6E5A87CD1D483515B99D6D3121FB92B0556(L_11, L_12, /*hidden argument*/NULL);
	}

IL_0056:
	{
		// }
		return;
	}
}
// System.Void Whale::.ctor()
IL2CPP_EXTERN_C IL2CPP_METHOD_ATTR void Whale__ctor_m9E31ECFB0C586E910A22682C88A991A7F7AD0C7C (Whale_t11A3C3495AC360DE58A5FE06BAAA3384761EA301 * __this, const RuntimeMethod* method)
{
	{
		// public float maxScale = 1.8f;
		__this->set_maxScale_24((1.8f));
		Enemy__ctor_mCD4E016A02FE662E339AA011EBA74D77B09556C5(__this, /*hidden argument*/NULL);
		return;
	}
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  PointerEventData_get_position_mF25FC495A9C968C65BF34B5984616CBFB6332D55_inline (PointerEventData_tC18994283B7753E430E316A62D9E45BA6D644C63 * __this, const RuntimeMethod* method)
{
	{
		// public Vector2 position { get; set; }
		Vector2_tA85D2DD88578276CA8A8796756458277E72D073D  L_0 = __this->get_U3CpositionU3Ek__BackingField_12();
		return L_0;
	}
}
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR void Joystick_set_AxisOptions_m3194AF6B83B35084063737EBA7D8C10C652241F8_inline (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, int32_t ___value0, const RuntimeMethod* method)
{
	{
		// public AxisOptions AxisOptions { get { return AxisOptions; } set { axisOptions = value; } }
		int32_t L_0 = ___value0;
		__this->set_axisOptions_6(L_0);
		// public AxisOptions AxisOptions { get { return AxisOptions; } set { axisOptions = value; } }
		return;
	}
}
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR void Joystick_set_SnapX_mACA46808CD8386CABE024E9F55A407F0C8A138F0_inline (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, bool ___value0, const RuntimeMethod* method)
{
	{
		// public bool SnapX { get { return snapX; } set { snapX = value; } }
		bool L_0 = ___value0;
		__this->set_snapX_7(L_0);
		// public bool SnapX { get { return snapX; } set { snapX = value; } }
		return;
	}
}
IL2CPP_EXTERN_C inline  IL2CPP_METHOD_ATTR void Joystick_set_SnapY_mA985E49A53EBD417CF06948C805588612C0395C1_inline (Joystick_t3DF5D60C31824A6BFD16338F9377102BE73A0153 * __this, bool ___value0, const RuntimeMethod* method)
{
	{
		// public bool SnapY { get { return snapY; } set { snapY = value; } }
		bool L_0 = ___value0;
		__this->set_snapY_8(L_0);
		// public bool SnapY { get { return snapY; } set { snapY = value; } }
		return;
	}
}
IL2CPP_EXTERN_C inline IL2CPP_METHOD_ATTR RuntimeObject * List_1_get_Item_mFDB8AD680C600072736579BBF5F38F7416396588_gshared_inline (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, int32_t ___index0, const RuntimeMethod* method)
{
	{
		int32_t L_0 = ___index0;
		int32_t L_1 = (int32_t)__this->get__size_2();
		if ((!(((uint32_t)L_0) >= ((uint32_t)L_1))))
		{
			goto IL_000e;
		}
	}
	{
		ThrowHelper_ThrowArgumentOutOfRangeException_mBA2AF20A35144E0C43CD721A22EAC9FCA15D6550(/*hidden argument*/NULL);
	}

IL_000e:
	{
		ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A* L_2 = (ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A*)__this->get__items_1();
		int32_t L_3 = ___index0;
		RuntimeObject * L_4 = IL2CPP_ARRAY_UNSAFE_LOAD((ObjectU5BU5D_t3C9242B5C88A48B2A5BD9FDA6CD0024E792AF08A*)L_2, (int32_t)L_3);
		return L_4;
	}
}
IL2CPP_EXTERN_C inline IL2CPP_METHOD_ATTR int32_t List_1_get_Count_m507C9149FF7F83AAC72C29091E745D557DA47D22_gshared_inline (List_1_t05CC3C859AB5E6024394EF9A42E3E696628CA02D * __this, const RuntimeMethod* method)
{
	{
		int32_t L_0 = (int32_t)__this->get__size_2();
		return L_0;
	}
}
