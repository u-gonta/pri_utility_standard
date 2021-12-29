#pragma once

#include <map>

#include "Common/Signal/Define.h"
#include "Common/Iterator/Basis.h"
#include "Common/Archive/Convert.h"
#include "Identifier.h"

#include "cereal/types/map.hpp"

// 1バイトアラインメントに変更
#pragma pack(1)

namespace Standard
{
	namespace MotionApi
	{
		namespace Device
		{
			////////////////////////////////////////////////////////////////////////////////
			/// @enum			座標系
			////////////////////////////////////////////////////////////////////////////////
			enum EnumCoordinate
			{
				CoodinateWork = 0,			// ワーク座標系
				CoodinateMachine = 1		// 機械座標系
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @enum			動作タイプ
			////////////////////////////////////////////////////////////////////////////////
			enum EnumMove
			{
				MoveRelative = 0,			// 増分値指定、直線軸or回転軸
				MoveAbsolute = 1,			// 絶対値指定、直線軸
				MoveRotaryShort = 2,		// 絶対値指定、回転軸(近回り)
				MoveRotaryPositive = 3,		// 絶対値指定、回転軸(正転)
				MoveRotaryNegative = 4		// 絶対値指定、回転軸(逆転)
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @enum			速度タイプ
			////////////////////////////////////////////////////////////////////////////////
			enum EnumVelocity
			{
				VelocityUnit = 0,			// 速度[指令単位/sec]
				VelocityPercent = 1			// モータの定格回転数（定格速度）、または、送り最高速度の%指定(Velocity= 1のとき、0.01%)
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @enum			加減速タイプ
			////////////////////////////////////////////////////////////////////////////////
			enum EnumAccDec
			{
				AccDecUnit = 0,				// 加減速度指定[指令単位/sec^2]
				AccDecTime = 1,				// 時定数指定[ms]
				AccDecKeep = 2				// 現在の設定を保持
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @enum			加減速フィルタタイプ
			////////////////////////////////////////////////////////////////////////////////
			enum EnumFilter
			{
				FilterCurve = 0,			// 移動平均フィルタ（簡易S字）
				FilterExp = 1,				// 指数フィルタ
				FilterNothing = 2,			// フィルタなし
				FilterKeep = 3				// 現在の設定を保持
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @enum			データタイプ
			////////////////////////////////////////////////////////////////////////////////
			enum EnumData
			{
				DataMaxVelocity = 0,		// 速度の上限値、送り最高速度
				DataAcceleration = 1,		// 加速度[指令単位/sec^2]／加速時定数[ms]
				DataDeceleration = 2,		// 減速度[指令単位/sec^2]／減速時定数[ms]
				DataFilterTime = 3,			// EnumFilterがFilterCurveまたはFilterExpを選択時に有効
				DataVelocity = 4,			// 速度
				DataApproachVelocity = 5,	// 原点復帰のアプローチ速度
				DataCreepVelocity = 6		// 原点復帰のクリープ速度
			};
			typedef Iterator::CWorker<EnumData, DataMaxVelocity, DataCreepVelocity> DataIterator;

			////////////////////////////////////////////////////////////////////////////////
			/// @enum			軸の方向
			////////////////////////////////////////////////////////////////////////////////
			enum EnumDirection
			{
				DirectionPositive = 0,		// 正方向
				DirectionNegative = 1		// 逆方向
			};

			////////////////////////////////////////////////////////////////////////////////
			/// @enum			完了タイプ
			////////////////////////////////////////////////////////////////////////////////
			enum EnumCompleted
			{
				CompleteDistribution = 0,	// 払い出し完了
				CompletePositioning = 1,	// 位置決め完了
				CompleteStart = 2			// 指令開始
			};

			namespace Setting
			{
				////////////////////////////////////////////////////////////////////////////////
				/// @class      CTemplate
				/// @brief      設定するテンプレートのクラス
				////////////////////////////////////////////////////////////////////////////////
				class CTemplate
				{
				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コンストラクタ
					////////////////////////////////////////////////////////////////////////////////
					CTemplate()
					{
						Handle = 0;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コピー代入演算子
					/// @return			自クラス
					////////////////////////////////////////////////////////////////////////////////
					CTemplate& operator = (const CTemplate& object) noexcept
					{
						// 更新
						Update(object);

						return *this;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デストラクタ
					////////////////////////////////////////////////////////////////////////////////
					virtual ~CTemplate()
					{

					}

				protected:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			自クラスを更新
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					void Update(const CTemplate& object)
					{
						this->Handle = object.Handle;
					}

				public:
					//! 機器のハンドル
					unsigned long Handle;
				};

				////////////////////////////////////////////////////////////////////////////////
				/// @class      CDeclare
				/// @brief      デバイスのハンドルを作成する設定クラス
				////////////////////////////////////////////////////////////////////////////////
				class CDeclare
				{
				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コンストラクタ
					////////////////////////////////////////////////////////////////////////////////
					CDeclare()
					{

					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コピー代入演算子
					/// @return			自クラス
					////////////////////////////////////////////////////////////////////////////////
					CDeclare& operator = (const CDeclare& object) noexcept
					{
						// 更新
						Update(object);

						return *this;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デストラクタ
					////////////////////////////////////////////////////////////////////////////////
					~CDeclare()
					{

					}

				protected:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			自クラスを更新
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					void Update(const CDeclare& object)
					{
						this->Handles.clear();
						std::copy(object.Handles.begin(), object.Handles.end(), std::back_inserter(this->Handles));
					}

				public:
					//! 軸のハンドル
					std::vector<unsigned long> Handles;
				};

				////////////////////////////////////////////////////////////////////////////////
				/// @class      CClear
				/// @brief      デバイスのハンドルを破棄する設定クラス
				///				⇒ 識別子を保持するクラスから派生
				////////////////////////////////////////////////////////////////////////////////
				class CClear
					: virtual public CIdentifier
				{
				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コンストラクタ
					////////////////////////////////////////////////////////////////////////////////
					CClear()
					{

					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コピー代入演算子
					/// @return			自クラス
					////////////////////////////////////////////////////////////////////////////////
					CClear& operator = (const CClear& object) noexcept
					{
						// 更新
						Update(object);

						return *this;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デストラクタ
					////////////////////////////////////////////////////////////////////////////////
					~CClear()
					{

					}

				protected:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			自クラスを更新
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					void Update(const CClear& object)
					{
						// 既定の関数
						CIdentifier::Update(object);
					}
				};

				////////////////////////////////////////////////////////////////////////////////
				/// @class      CServo
				/// @brief      サーボの制御を行う設定クラス
				///				⇒ 識別子を保持するクラスから派生
				////////////////////////////////////////////////////////////////////////////////
				class CServo
					: virtual public CIdentifier
				{
				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コンストラクタ
					////////////////////////////////////////////////////////////////////////////////
					CServo() : CIdentifier()
					{
						Mode = Signal::StatusOff;
						Timeout = 5000;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コピー代入演算子
					/// @return			自クラス
					////////////////////////////////////////////////////////////////////////////////
					CServo& operator = (const CServo& object) noexcept
					{
						// 更新
						Update(object);

						return *this;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デストラクタ
					////////////////////////////////////////////////////////////////////////////////
					~CServo()
					{

					}

				protected:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			自クラスを更新
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					void Update(const CServo& object)
					{
						// 既定の関数
						CIdentifier::Update(object);

						this->Mode = object.Mode;
						this->Timeout = object.Timeout;
					}

				public:
					//! サーボの状態
					Signal::EnumStatus Mode;

					//! タイムアウト[ms]
					unsigned short Timeout;
				};

				namespace Motion
				{
					////////////////////////////////////////////////////////////////////////////////
					/// @class      CTemplate
					/// @brief      軸の制御を行うテンプレートの設定クラス
					///				⇒ 識別子を保持するクラスから派生
					////////////////////////////////////////////////////////////////////////////////
					class CTemplate
						: virtual public CIdentifier
					{
					public:
						////////////////////////////////////////////////////////////////////////////////
						/// @brief			コンストラクタ
						////////////////////////////////////////////////////////////////////////////////
						CTemplate() : CIdentifier()
						{
							Coordinate = CoodinateMachine;
							MoveType = MoveAbsolute;
							VelocityType = VelocityUnit;
							AccDecType = AccDecKeep;
							FilterType = FilterKeep;
						}

						////////////////////////////////////////////////////////////////////////////////
						/// @brief			コピー代入演算子
						/// @return			自クラス
						////////////////////////////////////////////////////////////////////////////////
						CTemplate& operator = (const CTemplate& object) noexcept
						{
							// 更新
							Update(object);

							return *this;
						}

						////////////////////////////////////////////////////////////////////////////////
						/// @brief			デストラクタ
						////////////////////////////////////////////////////////////////////////////////
						~CTemplate()
						{

						}

					public:
						////////////////////////////////////////////////////////////////////////////////
						/// @brief			シリアライズ
						////////////////////////////////////////////////////////////////////////////////
						friend class cereal::access;
						template<class T>
						void serialize(T& archive)
						{
							archive(cereal::make_nvp("Handle", Handle));
							archive(cereal::make_nvp("Coordinate", Coordinate));
							archive(cereal::make_nvp("MoveType", MoveType));
							archive(cereal::make_nvp("VelocityType", VelocityType));
							archive(cereal::make_nvp("AccDecType", AccDecType));
							archive(cereal::make_nvp("FilterType", FilterType));
						}

					protected:
						////////////////////////////////////////////////////////////////////////////////
						/// @brief			自クラスを更新
						/// @param[in]		object	自クラス
						////////////////////////////////////////////////////////////////////////////////
						void Update(const CTemplate& object)
						{
							// 既定の関数
							CIdentifier::Update(object);

							this->Coordinate = object.Coordinate;
							this->MoveType = object.MoveType;
							this->VelocityType = object.VelocityType;
							this->AccDecType = object.AccDecType;
							this->FilterType = object.FilterType;
							this->Datas = object.Datas;
						}

					public:
						//! 座標系
						EnumCoordinate Coordinate;

						//! 動作タイプ
						EnumMove MoveType;

						//! 速度タイプ
						EnumVelocity VelocityType;

						//! 加減速タイプ
						EnumAccDec AccDecType;

						//! 加減速フィルタタイプ
						EnumFilter FilterType;

						//! データ
						std::map<EnumData, unsigned long> Datas;
					};

					namespace Jog
					{
						////////////////////////////////////////////////////////////////////////////////
						/// @class      CStart
						/// @brief      軸のジョグ実行を行う設定クラス
						///				⇒ 軸の制御を行うテンプレートの設定クラスから派生
						////////////////////////////////////////////////////////////////////////////////
						class CStart
							: virtual public CTemplate
						{
						private:
							//! シリアライズのタイトル
							const std::string ConstHeader = "CStart";

						public:
							////////////////////////////////////////////////////////////////////////////////
							/// @brief			コンストラクタ
							////////////////////////////////////////////////////////////////////////////////
							CStart() : CTemplate()
							{
								Direction = DirectionPositive;
								Timeout = 0;
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			コピー代入演算子
							/// @return			自クラス
							////////////////////////////////////////////////////////////////////////////////
							CStart& operator = (const CStart& object) noexcept
							{
								// 更新
								Update(object);

								return *this;
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			デストラクタ
							////////////////////////////////////////////////////////////////////////////////
							~CStart()
							{

							}

						public:
							////////////////////////////////////////////////////////////////////////////////
							/// @brief			シリアライズ
							////////////////////////////////////////////////////////////////////////////////
							friend class cereal::access;
							template<class T>
							void serialize(T& archive)
							{
								// 既定の関数
								CTemplate::serialize(archive);

								archive(cereal::make_nvp("Direction", Direction));
								archive(cereal::make_nvp("Timeout", Timeout));
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			Json形式にシリアライズした文字列から更新
							/// @param[in]		object	Json形式にシリアライズした文字列
							////////////////////////////////////////////////////////////////////////////////
							void Input(std::string object)
							{
								// Json形式から変換
								Update(Archive::Input<CStart>(ConstHeader, object));
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			Json形式にシリアライズした文字列を取得
							/// @return			シリアライズした文字列
							////////////////////////////////////////////////////////////////////////////////
							std::string Output()
							{
								std::string ret;

								// Json形式に変換
								ret = Archive::Output<CStart>(ConstHeader, *this);

								return ret;
							}

						protected:
							////////////////////////////////////////////////////////////////////////////////
							/// @brief			自クラスを更新
							/// @param[in]		object	自クラス
							////////////////////////////////////////////////////////////////////////////////
							void Update(const CStart& object)
							{
								// 既定の関数
								CTemplate::Update(object);

								this->Direction = object.Direction;
								this->Timeout = object.Timeout;
							}

						public:
							//! 方向
							EnumDirection Direction;

							//! タイムアウト[ms]
							unsigned short Timeout;
						};

						////////////////////////////////////////////////////////////////////////////////
						/// @class      CStop
						/// @brief      軸のジョグ停止を行う設定クラス
						///				⇒ 識別子を保持するクラスから派生
						////////////////////////////////////////////////////////////////////////////////
						class CStop
							: virtual public CIdentifier
						{
						private:
							//! シリアライズのタイトル
							const std::string ConstHeader = "CStop";

						public:
							////////////////////////////////////////////////////////////////////////////////
							/// @brief			コンストラクタ
							////////////////////////////////////////////////////////////////////////////////
							CStop() : CIdentifier()
							{
								Completed = CompletePositioning;
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			コピー代入演算子
							/// @return			自クラス
							////////////////////////////////////////////////////////////////////////////////
							CStop& operator = (const CStop& object) noexcept
							{
								// 更新
								Update(object);

								return *this;
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			デストラクタ
							////////////////////////////////////////////////////////////////////////////////
							~CStop()
							{

							}

						public:
							////////////////////////////////////////////////////////////////////////////////
							/// @brief			シリアライズ
							////////////////////////////////////////////////////////////////////////////////
							friend class cereal::access;
							template<class T>
							void serialize(T& archive)
							{
								archive(cereal::make_nvp("Handle", Handle));
								archive(cereal::make_nvp("Completed", Completed));
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			Json形式にシリアライズした文字列から更新
							/// @param[in]		object	Json形式にシリアライズした文字列
							////////////////////////////////////////////////////////////////////////////////
							void Input(std::string object)
							{
								// Json形式から変換
								Update(Archive::Input<CStop>(ConstHeader, object));
							}

							////////////////////////////////////////////////////////////////////////////////
							/// @brief			Json形式にシリアライズした文字列を取得
							/// @return			シリアライズした文字列
							////////////////////////////////////////////////////////////////////////////////
							std::string Output()
							{
								std::string ret;

								// Json形式に変換
								ret = Archive::Output<CStop>(ConstHeader, *this);

								return ret;
							}

						protected:
							////////////////////////////////////////////////////////////////////////////////
							/// @brief			自クラスを更新
							/// @param[in]		object	自クラス
							////////////////////////////////////////////////////////////////////////////////
							void Update(const CStop& object)
							{
								// 既定の関数
								CIdentifier::Update(object);

								this->Completed = object.Completed;
							}

						public:
							//! 完了タイプ
							EnumCompleted Completed;
						};
					}
				}

				////////////////////////////////////////////////////////////////////////////////
				/// @class      CStartJog
				/// @brief      軸のジョグを実行する設定クラス
				///				⇒ 識別子を保持するクラスから派生
				////////////////////////////////////////////////////////////////////////////////
				class CStartJog
					: virtual public CIdentifier
				{
				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コンストラクタ
					////////////////////////////////////////////////////////////////////////////////
					CStartJog() : CIdentifier()
					{

					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コピー代入演算子
					/// @return			自クラス
					////////////////////////////////////////////////////////////////////////////////
					CStartJog& operator = (const CStartJog& object) noexcept
					{
						// 更新
						Update(object);

						return *this;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デストラクタ
					////////////////////////////////////////////////////////////////////////////////
					~CStartJog()
					{

					}

				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デバイスのハンドルを作成する設定クラスを取得
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					CDeclare GetDeclare()
					{
						CDeclare ret;

						// 軸のジョグ実行を行う設定クラスを走査
						for (const auto& motion : Motions)
						{
							// ハンドルを追加
							ret.Handles.emplace_back(motion.Handle);
						}

						return ret;
					}

				protected:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			自クラスを更新
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					void Update(const CStartJog& object)
					{
						// 既定の関数
						CIdentifier::Update(object);

						this->Motions.clear();
						std::copy(object.Motions.begin(), object.Motions.end(), std::back_inserter(this->Motions));
					}

				public:
					//! 軸のジョグ実行を行う設定クラス
					std::vector<Motion::Jog::CStart> Motions;
				};

				////////////////////////////////////////////////////////////////////////////////
				/// @class      CStopJog
				/// @brief      軸のジョグを停止する設定クラス
				///				⇒ 識別子を保持するクラスから派生
				////////////////////////////////////////////////////////////////////////////////
				class CStopJog
					: virtual public CIdentifier
				{
				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コンストラクタ
					////////////////////////////////////////////////////////////////////////////////
					CStopJog() : CIdentifier()
					{

					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			コピー代入演算子
					/// @return			自クラス
					////////////////////////////////////////////////////////////////////////////////
					CStopJog& operator = (const CStopJog& object) noexcept
					{
						// 更新
						Update(object);

						return *this;
					}

					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デストラクタ
					////////////////////////////////////////////////////////////////////////////////
					~CStopJog()
					{

					}

				public:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			デバイスのハンドルを作成する設定クラスを取得
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					CDeclare GetDeclare()
					{
						CDeclare ret;

						// 軸のジョグ実行を行う設定クラスを走査
						for (const auto& motion : Motions)
						{
							// ハンドルを追加
							ret.Handles.emplace_back(motion.Handle);
						}

						return ret;
					}

				protected:
					////////////////////////////////////////////////////////////////////////////////
					/// @brief			自クラスを更新
					/// @param[in]		object	自クラス
					////////////////////////////////////////////////////////////////////////////////
					void Update(const CStopJog& object)
					{
						// 既定の関数
						CIdentifier::Update(object);

						this->Motions.clear();
						std::copy(object.Motions.begin(), object.Motions.end(), std::back_inserter(this->Motions));
					}

				public:
					//! 軸のジョグ停止を行う設定クラス
					std::vector<Motion::Jog::CStop> Motions;
				};
			}
		}
	}
}

// バイトアラインメントを戻す
#pragma pack()
