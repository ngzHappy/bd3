/*
 * 抖动算法
 * http://blog.csdn.net/xiaojidan2011/article/details/7972710
*/

#include "QAnimatedGifEncoder.hpp"

/*stl*/
#include <cmath>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>

/*qt:qtl*/
#include <QtCore/QVector>
#include <QtCore/qdebug.h>

/*boost:rtree*/
#include <Qt/boost/geometry/index/rtree.hpp>

/*opencv*/
#include <opencv2/opencv.hpp>

#ifndef null
#define null 0
#endif/*null*/

#ifndef one
#define one (Integer(1))
#endif/*one*/

#ifndef CPLUSPLUS_OBJECT
#define CPLUSPLUS_OBJECT(...)
#endif/*CPLUSPLUS_OBJECT*/

namespace {

inline void put_char(QIODevice * o,char c) {
    o->putChar(c);
}
inline void put_char(QIODevice * o,unsigned char c)=delete;

}/*namespace*/

namespace mgui {

namespace {
using const_uchar=const unsigned char/*定义类型const unsigned char*/;
using type_uchar=unsigned char/*定义类型unsigned char*/;

/*
 * unsigned char to double
 * 直接查表，加快速度
*/
constexpr const double uchar2doule[]{
    0.  ,   1.  ,   2.  ,   3.  ,    4.,        5.,        6.,        7.,        8.,        9.,        10.,    11.,    12.,    13.,    14.,    15.,
    16. ,   17. ,   18. ,   19. ,    20.,    21.,    22.,    23.,    24.,    25.,    26.,    27.,    28.,    29.,    30.,    31.,
    32. ,   33. ,   34. ,   35. ,    36.,    37.,    38.,    39.,    40.,    41.,    42.,    43.,    44.,    45.,    46.,    47.,
    48. ,   49. ,   50. ,   51. ,    52.,    53.,    54.,    55.,    56.,    57.,    58.,    59.,    60.,    61.,    62.,    63.,
    64. ,   65. ,   66. ,   67. ,    68.,    69.,    70.,    71.,    72.,    73.,    74.,    75.,    76.,    77.,    78.,    79.,
    80. ,   81. ,   82. ,   83. ,    84.,    85.,    86.,    87.,    88.,    89.,    90.,    91.,    92.,    93.,    94.,    95.,
    96. ,   97. ,   98. ,   99. ,    100.,    101.,    102.,    103.,    104.,    105.,    106.,    107.,    108.,    109.,    110.,    111.,
    112.,   113.,   114.,   115.,    116.,    117.,    118.,    119.,    120.,    121.,    122.,    123.,    124.,    125.,    126.,    127.,
    128.,   129.,   130.,   131.,    132.,    133.,    134.,    135.,    136.,    137.,    138.,    139.,    140.,    141.,    142.,    143.,
    144.,   145.,   146.,   147.,    148.,    149.,    150.,    151.,    152.,    153.,    154.,    155.,    156.,    157.,    158.,    159.,
    160.,   161.,   162.,   163.,    164.,    165.,    166.,    167.,    168.,    169.,    170.,    171.,    172.,    173.,    174.,    175.,
    176.,   177.,   178.,   179.,    180.,    181.,    182.,    183.,    184.,    185.,    186.,    187.,    188.,    189.,    190.,    191.,
    192.,   193.,   194.,   195.,    196.,    197.,    198.,    199.,    200.,    201.,    202.,    203.,    204.,    205.,    206.,    207.,
    208.,   209.,   210.,   211.,    212.,    213.,    214.,    215.,    216.,    217.,    218.,    219.,    220.,    221.,    222.,    223.,
    224.,   225.,   226.,   227.,    228.,    229.,    230.,    231.,    232.,    233.,    234.,    235.,    236.,    237.,    238.,    239.,
    240.,   241.,   242.,   243.,    244.,    245.,    246.,    247.,    248.,    249.,    250.,    251.,    252.,    253.,    254.,    255.,
};

constexpr const float uchar2float[]{
    0.f  ,   1.f  ,   2.f,    3.f  ,	4.f,    5.f,	  6.f,	    7.f,	    8.f,	    9.f,	    10.f,	11.f,	12.f,	13.f,	14.f,	15.f,
    16.f ,   17.f ,   18.f,   19.f ,	20.f,	21.f,	22.f,	23.f,	24.f,	25.f,	26.f,	27.f,	28.f,	29.f,	30.f,	31.f,
    32.f ,   33.f ,   34.f,   35.f ,	36.f,	37.f,	38.f,	39.f,	40.f,	41.f,	42.f,	43.f,	44.f,	45.f,	46.f,	47.f,
    48.f ,   49.f ,   50.f,   51.f ,	52.f,	53.f,	54.f,	55.f,	56.f,	57.f,	58.f,	59.f,	60.f,	61.f,	62.f,	63.f,
    64.f ,   65.f ,   66.f,   67.f ,	68.f,	69.f,	70.f,	71.f,	72.f,	73.f,	74.f,	75.f,	76.f,	77.f,	78.f,	79.f,
    80.f ,   81.f ,   82.f,   83.f ,	84.f,	85.f,	86.f,	87.f,	88.f,	89.f,	90.f,	91.f,	92.f,	93.f,	94.f,	95.f,
    96.f ,   97.f ,   98.f,   99.f ,	100.f,	101.f,	102.f,	103.f,	104.f,	105.f,	106.f,	107.f,	108.f,	109.f,	110.f,	111.f,
    112.f,   113.f,   114.f,   115.f,	116.f,	117.f,	118.f,	119.f,	120.f,	121.f,	122.f,	123.f,	124.f,	125.f,	126.f,	127.f,
    128.f,   129.f,   130.f,   131.f,	132.f,	133.f,	134.f,	135.f,	136.f,	137.f,	138.f,	139.f,	140.f,	141.f,	142.f,	143.f,
    144.f,   145.f,   146.f,   147.f,	148.f,	149.f,	150.f,	151.f,	152.f,	153.f,	154.f,	155.f,	156.f,	157.f,	158.f,	159.f,
    160.f,   161.f,   162.f,   163.f,	164.f,	165.f,	166.f,	167.f,	168.f,	169.f,	170.f,	171.f,	172.f,	173.f,	174.f,	175.f,
    176.f,   177.f,   178.f,   179.f,	180.f,	181.f,	182.f,	183.f,	184.f,	185.f,	186.f,	187.f,	188.f,	189.f,	190.f,	191.f,
    192.f,   193.f,   194.f,   195.f,	196.f,	197.f,	198.f,	199.f,	200.f,	201.f,	202.f,	203.f,	204.f,	205.f,	206.f,	207.f,
    208.f,   209.f,   210.f,   211.f,	212.f,	213.f,	214.f,	215.f,	216.f,	217.f,	218.f,	219.f,	220.f,	221.f,	222.f,	223.f,
    224.f,   225.f,   226.f,   227.f,	228.f,	229.f,	230.f,	231.f,	232.f,	233.f,	234.f,	235.f,	236.f,	237.f,	238.f,	239.f,
    240.f,   241.f,   242.f,   243.f,	244.f,	245.f,	246.f,	247.f,	248.f,	249.f,	250.f,	251.f,	252.f,	253.f,	254.f,	255.f,
};

constexpr const float uchar2float_0_1[]{
    0.f/255,     1.f/255,     2.f/255,     3.f/255,      4.f/255,      5.f/255,      6.f/255,      7.f/255,     8.f/255,     9.f/255,     10.f/255,    11.f/255,    12.f/255,    13.f/255,    14.f/255,    15.f/255,
    16.f/255,    17.f/255,    18.f/255,    19.f/255,     20.f/255,     21.f/255,     22.f/255,     23.f/255,    24.f/255,    25.f/255,    26.f/255,    27.f/255,    28.f/255,    29.f/255,    30.f/255,    31.f/255,
    32.f/255,    33.f/255,    34.f/255,    35.f/255,     36.f/255,     37.f/255,     38.f/255,     39.f/255,    40.f/255,    41.f/255,    42.f/255,    43.f/255,    44.f/255,    45.f/255,    46.f/255,    47.f/255,
    48.f/255,    49.f/255,    50.f/255,    51.f/255,     52.f/255,     53.f/255,     54.f/255,     55.f/255,    56.f/255,    57.f/255,    58.f/255,    59.f/255,    60.f/255,    61.f/255,    62.f/255,    63.f/255,
    64.f/255,    65.f/255,    66.f/255,    67.f/255,     68.f/255,     69.f/255,     70.f/255,     71.f/255,    72.f/255,    73.f/255,    74.f/255,    75.f/255,    76.f/255,    77.f/255,    78.f/255,    79.f/255,
    80.f/255,    81.f/255,    82.f/255,    83.f/255,     84.f/255,     85.f/255,     86.f/255,     87.f/255,    88.f/255,    89.f/255,    90.f/255,    91.f/255,    92.f/255,    93.f/255,    94.f/255,    95.f/255,
    96.f/255,    97.f/255,    98.f/255,    99.f/255,     100.f/255,    101.f/255,    102.f/255,    103.f/255,    104.f/255,    105.f/255,    106.f/255,    107.f/255,    108.f/255,    109.f/255,    110.f/255,    111.f/255,
    112.f/255,   113.f/255,   114.f/255,   115.f/255,    116.f/255,    117.f/255,    118.f/255,    119.f/255,    120.f/255,    121.f/255,    122.f/255,    123.f/255,    124.f/255,    125.f/255,    126.f/255 ,   127.f/255,
    128.f/255,   129.f/255,   130.f/255,   131.f/255,    132.f/255,    133.f/255,    134.f/255,    135.f/255,    136.f/255,    137.f/255,    138.f/255,    139.f/255,    140.f/255,    141.f/255,    142.f/255 ,   143.f/255,
    144.f/255,   145.f/255,   146.f/255,   147.f/255,    148.f/255,    149.f/255,    150.f/255,    151.f/255,    152.f/255,    153.f/255,    154.f/255,    155.f/255,    156.f/255,    157.f/255,    158.f/255 ,   159.f/255,
    160.f/255,   161.f/255,   162.f/255,   163.f/255,    164.f/255,    165.f/255,    166.f/255,    167.f/255,    168.f/255,    169.f/255,    170.f/255,    171.f/255,    172.f/255,    173.f/255,    174.f/255 ,   175.f/255,
    176.f/255,   177.f/255,   178.f/255,   179.f/255,    180.f/255,    181.f/255,    182.f/255,    183.f/255,    184.f/255,    185.f/255,    186.f/255,    187.f/255,    188.f/255,    189.f/255,    190.f/255 ,   191.f/255,
    192.f/255,   193.f/255,   194.f/255,   195.f/255,    196.f/255,    197.f/255,    198.f/255,    199.f/255,    200.f/255,    201.f/255,    202.f/255,    203.f/255,    204.f/255,    205.f/255,    206.f/255 ,   207.f/255,
    208.f/255,   209.f/255,   210.f/255,   211.f/255,    212.f/255,    213.f/255,    214.f/255,    215.f/255,    216.f/255,    217.f/255,    218.f/255,    219.f/255,    220.f/255,    221.f/255,    222.f/255 ,   223.f/255,
    224.f/255,   225.f/255,   226.f/255,   227.f/255,    228.f/255,    229.f/255,    230.f/255,    231.f/255,    232.f/255,    233.f/255,    234.f/255,    235.f/255,    236.f/255,    237.f/255,    238.f/255 ,   239.f/255,
    240.f/255,   241.f/255,   242.f/255,   243.f/255,    244.f/255,    245.f/255,    246.f/255,    247.f/255,    248.f/255,    249.f/255,    250.f/255,    251.f/255,    252.f/255,    253.f/255,    254.f/255 ,   255.f/255,
};

template<typename T1,typename T>
static inline void writeSome(const T1 & some,T * out) {
    out->write((const Byte *)(&some),sizeof(T1));
}

template<typename T>
static inline void writeSome(Integer some,T * out) {
    out->write((const Byte *)(&some),sizeof(Integer));
}

template<typename T>
static inline void writeSome(Byte some,T * out) {
    out->write(&some,sizeof(Byte));
}

}/*namespace*/

}/*mgui*/

namespace mgui {

namespace {
//隐式数据共享
typedef QVector<type_uchar> PixType;

/*将rgb24位转为灰度图*/
class QuantizationAlgorithm {
public:
    QuantizationAlgorithm()=default;
    virtual void construct(const PixType & /*thepic*/,Integer /*len*/,Integer /*sample*/)=0;
    virtual ~QuantizationAlgorithm()=default;
    virtual QVector<type_uchar> process()=0;
    virtual Integer map(Integer b,Integer g,Integer r)=0;
};

class Quantization :public QuantizationAlgorithm {
public:
    using const_uchar=const unsigned char/*定义类型const unsigned char*/;
    using type_uchar=unsigned char/*定义类型unsigned char*/;
private:
    static unsigned char int2unsignedchar(int i) {
        return (unsigned char)((i&0x00ff));
    }

public:

    struct DataItem {
        type_uchar a;
        type_uchar b;
        type_uchar c;

        constexpr DataItem():a(0),b(0),c(0) {}
        DataItem(type_uchar _0,type_uchar _1,type_uchar _2):a(_0),b(_1),c(_2) {}
        friend bool operator<(const DataItem & l,const DataItem & r) {
            if (l.a<r.a) { return true; }
            if (l.a>r.a) { return false; }
            if (l.b<r.b) { return true; }
            if (l.b>r.b) { return false; }
            return l.c<r.c;
        }
    };

    PixType pix;
    QVector<type_uchar> quantization;

    typedef boost::geometry::model::point<
        std::int32_t,3,
        boost::geometry::cs::cartesian> point_t/*笛卡尔坐标系点*/;
    typedef std::pair<point_t,std::int32_t> value_t;
    typedef boost::geometry::index::rtree<value_t,boost::geometry::index::quadratic<16>> rtree_t;
    std::shared_ptr<rtree_t> rtree/*使用rtree加快搜索速度*/;

    void construct(
            const PixType & hepic,
            Integer /*len*/,
            Integer /*sample*/) override {
        pix=hepic;
#ifndef NDEBUG
        for (const auto & i:uchar2float_0_1) {
            assert(i>=0);
            assert(i<=1);
        }
#endif
    }

    QVector<type_uchar> process() {

        /*清空数据*/
        QVector<type_uchar> & ans=quantization;
        ans.clear();
        rtree=std::make_shared<rtree_t>();

        /**/
        evalQuantization();

        return quantization;
    }

    Integer map(Integer _1_,Integer _2_,Integer _3_) {
        if (rtree) {
            point_t point(_1_,_2_,_3_);
            std::vector<value_t> ans;
            rtree->query(
                        boost::geometry::index::nearest(point,1),
                        std::back_inserter(ans));
            if (ans.empty()==false) {
                return ans[0].second;
            }
        }
        return 0;
    }

private:
    struct Data {
        Double a,b,c;
        std::int32_t count;
        Data()=default;
        Data(const Double & arg0,
            const Double & arg1,
            const Double & arg2,
            const std::int32_t & arg3):a(arg0),
            b(arg1),c(arg2),count(arg3) {
        }
    };
    struct RGBFloat {
        Float r,g,b;
        RGBFloat()=default;
        RGBFloat(Float a_,Float b_,Float c_)
            :r(a_),g(b_),b(c_) {}
        RGBFloat(Double a_,Double b_,Double c_)
            :r(static_cast<Float>(a_)),
            g(static_cast<Float>(b_)),
            b(static_cast<Float>(c_)) {
        }
    };
    using rgb_hist_map=std::map<DataItem,std::int32_t>;
    using data_list=std::list<Data>;
    using rgb_float_vector=std::vector<RGBFloat>;
    using rgb_byte_vector=std::vector<DataItem>;

    rgb_byte_vector rgb_float_vector_to_rgb_byte_vector(const rgb_float_vector & arg) {
        rgb_byte_vector varAns;
        rgb_float_vector varAnsTmp;

        varAns.resize(arg.size());
        varAnsTmp.resize(arg.size());

        try {

            cv::Mat matInputWrap(1,
                static_cast<int>(arg.size()),
                CV_32FC3,
                const_cast<RGBFloat*>(arg.data())
            );

            cv::Mat matOutPutWrap(1,
                static_cast<int>(varAnsTmp.size()),
                CV_32FC3,
                const_cast<RGBFloat*>(varAnsTmp.data())
            );

            cv::cvtColor(matInputWrap,matOutPutWrap,cv::COLOR_Lab2RGB);

            matOutPutWrap*=255.0f;
            matOutPutWrap+=0.505555f/*四舍五入*/;

            matInputWrap=cv::Mat{ 1,
                static_cast<int>(varAns.size()),
                CV_8UC3,
                const_cast<DataItem*>(varAns.data()) };

            matOutPutWrap.convertTo(matInputWrap,CV_8UC3);

        }
        catch (...) {
            varAns.clear();
            CPLUSPLUS_EXCEPTION(false);
        }
        return std::move(varAns);
    }

    data_list rgb_hist_map_to_data_list(const rgb_hist_map & hist) {
        data_list varAns;

        /*将rgb转为lab*/
        try {
            std::vector<RGBFloat> varTmpData;
            std::vector<RGBFloat> varTmpDataAns;
            varAns.resize(hist.size());
            varTmpDataAns.resize(hist.size());
            varTmpData.reserve(hist.size());

            {
                auto varI=varAns.begin();
                for (const auto & i:hist) {
                    varTmpData.emplace_back(
                        uchar2float_0_1[i.first.a],
                        uchar2float_0_1[i.first.b],
                        uchar2float_0_1[i.first.c]
                    );
                    varI->count=i.second;
                    ++varI;
                }
            }

            cv::Mat matInputWrap(1,
                static_cast<int>(varTmpData.size()),
                CV_32FC3,
                varTmpData.data()
            );

            cv::Mat matOutPutWrap(1,
                static_cast<int>(varTmpDataAns.size()),
                CV_32FC3,
                varTmpDataAns.data());

            cv::cvtColor(matInputWrap,matOutPutWrap,cv::COLOR_RGB2Lab);

            {
                auto varI=varAns.begin();
                for (const auto & i:varTmpDataAns) {
                    varI->a=i.r;
                    varI->b=i.g;
                    varI->c=i.b;
                    ++varI;
                }
            }

        }
        catch (...) {
            varAns.clear();
            CPLUSPLUS_EXCEPTION(false);
            return std::move(varAns);
        }

        return std::move(varAns);
    }

    rgb_hist_map genRGBHistMap() {
        rgb_hist_map hist;

        {/*得到统计值*/
            auto begin_=(const DataItem *)(pix.cbegin());
            auto end_=(const DataItem*)(pix.cend());
            for (auto pos=begin_; pos<end_; ++pos) {
                auto hpos=hist.find(*pos);
                if (hpos!=hist.end()) {
                    ++(hpos->second);
                }
                else {
                    hist.insert({ *pos,1 });
                }
            }

        }
        return std::move(hist);
    }

    void evalQuantization() {

        auto hist=genRGBHistMap();

        /*颜色数小于等于256*/
        if (hist.size()<=256) {
            std::int32_t index_=0;
            for (auto & i:hist) {
                rtree->insert(std::make_pair(
                    point_t(i.first.a,i.first.b,i.first.c),index_++
                ));
                quantization.push_back(i.first.a);
                quantization.push_back(i.first.b);
                quantization.push_back(i.first.c);
            }
            return;
        }

        /*降低颜色数目*/
        struct Pack {
            std::vector<Data>data;

            Double length_x=0;
            Double length_y=0;
            Double length_z=0;
            std::int32_t count=0;

            Double mean_x;
            Double mean_y;
            Double mean_z;

            void eval_mean() {

                count=0;
                mean_x=0;
                mean_y=0;
                mean_z=0;

                for (const auto &varI:data) {

                    count+=varI.count;
                    mean_x+=varI.a*varI.count;
                    mean_y+=varI.b*varI.count;
                    mean_z+=varI.c*varI.count;

                }

                mean_x/=count;
                mean_y/=count;
                mean_z/=count;

            }

            void update() {

                Double max_x=std::numeric_limits<Double>::max();
                Double min_x=std::numeric_limits<Double>::lowest();

                Double max_y=std::numeric_limits<Double>::max();
                Double min_y=std::numeric_limits<Double>::lowest();

                Double max_z=std::numeric_limits<Double>::max();
                Double min_z=std::numeric_limits<Double>::lowest();

                count=0;

                for (const auto &varI:data) {

                    count+=varI.count;

                    if (varI.a>max_x) { max_x=varI.a; }
                    if (varI.a<min_x) { min_x=varI.a; }

                    if (varI.b>max_y) { max_y=varI.b; }
                    if (varI.b<min_y) { min_y=varI.b; }

                    if (varI.c>max_z) { max_z=varI.c; }
                    if (varI.c<min_z) { min_z=varI.c; }

                }

                length_x=max_x-min_x;
                length_y=max_y-min_y;
                length_z=max_z-min_z;

            }

            std::pair<
                std::shared_ptr<Pack>,
                std::shared_ptr<Pack>
            >next() {
                if ((length_x>=length_y)&&(length_x>=length_z)) {
                    return split_x();
                }
                if ((length_y>=length_x)&&(length_y>=length_z)) {
                    return split_y();
                }
                return split_z();
            }

            std::pair<
                std::shared_ptr<Pack>,
                std::shared_ptr<Pack>
            >split_x() {
                std::shared_ptr<Pack> l=std::make_shared<Pack>();
                std::shared_ptr<Pack> r=std::make_shared<Pack>();

                std::sort(data.begin(),data.end(),[](const auto &l,const auto &r) {
                    return l.a<r.a;
                });

                auto half_count=count/2;

                for (auto &varI:data) {
                    auto old_half_count=half_count;
                    half_count-=varI.count;
                    if (half_count>=0) {
                        l->data.push_back(varI);
                    }
                    else if (old_half_count<=0) {
                        r->data.push_back(varI);
                    }
                    else {
                        varI.count=old_half_count;
                        l->data.push_back(varI);
                        varI.count=-half_count;
                        r->data.push_back(varI);
                    }
                }

                l->update(); r->update();
                return{ std::move(l),std::move(r) };
            }
            std::pair<
                std::shared_ptr<Pack>,
                std::shared_ptr<Pack>
            >split_y() {
                std::shared_ptr<Pack> l=std::make_shared<Pack>();
                std::shared_ptr<Pack> r=std::make_shared<Pack>();

                std::sort(data.begin(),data.end(),[](const auto &l,const auto &r) {
                    return l.b<r.b;
                });

                auto half_count=count/2;

                for (auto &varI:data) {
                    auto old_half_count=half_count;
                    half_count-=varI.count;
                    if (half_count>=0) {
                        l->data.push_back(varI);
                    }
                    else if (old_half_count<=0) {
                        r->data.push_back(varI);
                    }
                    else {
                        varI.count=old_half_count;
                        l->data.push_back(varI);
                        varI.count=-half_count;
                        r->data.push_back(varI);
                    }
                }

                l->update(); r->update();
                return{ std::move(l),std::move(r) };
            }
            std::pair<
                std::shared_ptr<Pack>,
                std::shared_ptr<Pack>
            >split_z() {
                std::shared_ptr<Pack> l=std::make_shared<Pack>();
                std::shared_ptr<Pack> r=std::make_shared<Pack>();

                std::sort(data.begin(),data.end(),[](const auto &l,const auto &r) {
                    return l.c<r.c;
                });

                auto half_count=count/2;

                for (auto &varI:data) {
                    auto old_half_count=half_count;
                    half_count-=varI.count;
                    if (half_count>=0) {
                        l->data.push_back(varI);
                    }
                    else if (old_half_count<=0) {
                        r->data.push_back(varI);
                    }
                    else {
                        varI.count=old_half_count;
                        l->data.push_back(varI);
                        varI.count=-half_count;
                        r->data.push_back(varI);
                    }
                }

                l->update(); r->update();
                return{ std::move(l),std::move(r) };
            }
        };

        auto comp_pack_function=[](
                std::shared_ptr<Pack> &l,
                std::shared_ptr<Pack> &r
                ) {

            Double lDataSize=l->data.size();
            Double rDataSize=r->data.size();

            if ((lDataSize>50)&&(rDataSize>50)) {
                return (l->count)>(r->count);
            }

            Double minSize=std::min(lDataSize,rDataSize);
            minSize=std::abs(Double(lDataSize)-rDataSize)/minSize;

            if (minSize<0.3) {
                return l->count>r->count;
            }

            return lDataSize>rDataSize;
        };

        std::vector<std::shared_ptr<Pack>> packs;
        packs.reserve(256);

        std::int32_t allCount=1;
        /*初始化迭代*/
        {
            auto pack_root=std::make_shared<Pack>();
            auto tmp=rgb_hist_map_to_data_list(hist);
            pack_root->data={ tmp.begin(),tmp.end() };
            pack_root->update();
            allCount=pack_root->count;
            packs.push_back(std::move(pack_root));
        }

        hist.clear();
        while (packs.size()<256) {
            std::sort(packs.begin(),packs.end(),comp_pack_function);
            auto * first=packs.begin()->get();
            if (first->count<1) {
                break;
            }
            auto next_=first->next();
            packs[0]=std::move(next_.first);
            packs.push_back(std::move(next_.second));
        }

        //qDebug()<<packs.size();
        rgb_float_vector varTmpAns;
        varTmpAns.reserve(256);
        for (auto & p:packs) {
            p->eval_mean();
            varTmpAns.emplace_back(
                p->mean_x,
                p->mean_y,
                p->mean_z);
        }

        auto varTmpAnsRGB=
            rgb_float_vector_to_rgb_byte_vector(varTmpAns);
        varTmpAns.clear();

        std::int32_t index=0;
        for (auto & p:varTmpAnsRGB) {

            const auto & x=p.a;
            const auto & y=p.b;
            const auto & z=p.c;

            rtree->insert(std::make_pair(
                point_t(x,y,z),index++
            ));

            quantization.push_back(x);
            quantization.push_back(y);
            quantization.push_back(z);

        }

    }
};

}/*namespace*/
}/*mgui*/

namespace mgui {
namespace {

class LZWEncoder {
public:
    using const_uchar=const unsigned char/*定义类型const unsigned char*/;
    using type_uchar=unsigned char/*定义类型unsigned char*/;
    using type_iodevice=QIODevice/*定义输出流类型*/;
    using Integer=std::int32_t;
    static constexpr inline Integer MAXCODE(Integer n_bits) {
        return (1<<n_bits)-1;
    }
#ifndef EOF
    static constexpr Integer EOF=-1; /*= -1*/
#endif
    enum :Integer {
        BITS=12,
        HSIZE=5003,
        ACCUM_SIZE=256,
        MASKS_SIZE=17,
        MAX_UCHAR=255,
    };
private:
    /*对外输出1个char*/
    inline static void put_char(type_iodevice * o,const_uchar & c) {
        o->putChar(static_cast<const char &>(c));
    }
    /*对外输出n个char*/
    inline static void write_chars(type_iodevice * o,const_uchar * d,Integer s) {
        o->write(reinterpret_cast<const char*>(d),s);
    }
    std::array<Integer,HSIZE> htab;
    std::array<Integer,HSIZE> codetab;
    std::array<type_uchar,ACCUM_SIZE> accum/*缓存区*/;

    Integer imgW=0;
    Integer imgH=0;
    Integer initCodeSize=0;
    Integer remaining=0;
    Integer curPixel=0;
    Integer n_bits=0; /*number of bits/code*/
    Integer maxbits=BITS; /*user settable max # bits/code*/
    Integer maxcode=0; /*maximum code, given n_bits*/
    Integer maxmaxcode=(1<<BITS); /*should NEVER generate this code*/
    Integer hsize=HSIZE; /*for dynamic table sizing*/
    Integer free_ent=0; /*first unused entry*/
    Boolean clear_flg=false;
    Integer g_init_bits=0;
    Integer ClearCode=0;
    Integer EOFCode=0;
    Integer cur_accum=0;
    Integer cur_bits=0;

    template<typename T>
    static inline Integer masks(T arg) {
        assert(arg<MASKS_SIZE);
        assert(arg>=0);
        static constexpr Integer masks[MASKS_SIZE]{
            0x00000000,/*0*/
            0x00000001,/*1*/
            0x00000003,/*2*/
            0x00000007,/*3*/
            0x0000000F,/*4*/
            0x0000001F,/*5*/
            0x0000003F,/*6*/
            0x0000007F,/*7*/
            0x000000FF,/*8*/
            0x000001FF,/*9*/
            0x000003FF,/*10*/
            0x000007FF,/*11*/
            0x00000FFF,/*12*/
            0x00001FFF,/*13*/
            0x00003FFF,/*14*/
            0x00007FFF,/*15*/
            0x0000FFFF,/*16*/
        };
        static_assert(sizeof(masks)/sizeof(Integer)==MASKS_SIZE,"");
        return masks[arg];
    }

    Integer a_count=0/*缓冲区的大小*/;

    const_uchar * pixAryBegin=nullptr;
    const_uchar * pixAryEnd=nullptr/*预留，将来用于调试*/;
private:
    LZWEncoder()=default;
public:
    /*----------------------------------------------------------------------------*/
    /*用于压缩灰度图*/
    LZWEncoder(
            Integer width/*image width*/,
            Integer height/*image height*/,
            const_uchar * argPixAryBegin/*image data char8_t*/,
            const_uchar * argPixAryEnd/*image data char8_t*/,
            Integer color_depth/*it should be 8*/):LZWEncoder() {
        imgW=width;
        imgH=height;
        pixAryBegin=argPixAryBegin;
        pixAryEnd=argPixAryEnd;
        initCodeSize=(std::max)(2,color_depth);
    }
    inline void encode(type_iodevice * os);
private:
    inline void char_out(type_uchar c,type_iodevice * outs);
    inline void cl_block(type_iodevice * outs);
    inline void cl_hash(const Integer hsize);
    inline void compress(Integer init_bits,type_iodevice *outs);
    inline void flush_char(type_iodevice * outs);
    inline Integer nextPixel();
    inline void output(Integer code,type_iodevice * outs);
private:
    CPLUSPLUS_OBJECT(LZWEncoder)
};/*LZWEncoder*/

inline void LZWEncoder::char_out(type_uchar c,type_iodevice * outs) {
    accum[a_count++]=c;
    if (a_count>=254) {
        flush_char(outs);
    }
}/*inline void LZWEncoder::char_out(type_uchar c,type_iodevice * outs)*/

inline void LZWEncoder::cl_block(type_iodevice * outs) {
    cl_hash(hsize);
    free_ent=ClearCode+2;
    clear_flg=true;
    output(ClearCode,outs);
}/*inline void LZWEncoder::cl_block(type_iodevice * outs)*/

inline void LZWEncoder::cl_hash(const Integer hsize) {
    for (Integer i=0; i<hsize; ++i) {
        htab[i]=-1;
    }
}/*inline void LZWEncoder::cl_hash(const Integer hsize)*/

inline void  LZWEncoder::compress(Integer init_bits,type_iodevice *outs) {
    Integer fcode=0;
    Integer i=0;
    Integer c=0;
    Integer ent=0;
    Integer disp=0;
    Integer hsize_reg=0;
    Integer hshift=0;
    /*Set up the globals:  g_init_bits - initial number of bits*/
    g_init_bits=init_bits;
    /*Set up the necessary values*/
    clear_flg=false;
    n_bits=g_init_bits;
    maxcode=MAXCODE(n_bits);
    ClearCode=1<<(init_bits-1);
    EOFCode=ClearCode+1;
    free_ent=ClearCode+2;
    a_count=0; /*clear packet*/
    ent=nextPixel();
    hshift=0;
    for (fcode=hsize; fcode<65536; fcode*=2) {
        ++hshift;
    }
    hshift=8-hshift; /*set hash code range bound*/
    hsize_reg=hsize;
    cl_hash(hsize_reg); /*clear hash table*/
    output(ClearCode,outs);

outer_loop:
    while ((c=nextPixel())!=EOF) {
        fcode=(c<<maxbits)+ent;
        i=(c<<hshift)^ent; /*xor hashing*/
        if (htab[i]==fcode) {
            ent=codetab[i];
            continue;
        }
        else if (htab[i]>=0) /*non-empty slot*/ {
            disp=hsize_reg-i; /*secondary hash (after G. Knott)*/
            if (i==0) {
                disp=1;
            }
            do {
                if ((i-=disp)<0)
                    i+=hsize_reg;
                if (htab[i]==fcode) {
                    ent=codetab[i];
                    goto outer_loop;
                }
            } while (htab[i]>=0);
        }
        output(ent,outs);
        ent=c;
        if (free_ent<maxmaxcode) {
            codetab[i]=free_ent++; // code -> hashtable
            htab[i]=fcode;
        }
        else {
            cl_block(outs);
        }
    }

    /* Put out the final code.*/
    output(ent,outs);
    output(EOFCode,outs);

}/*inline void  LZWEncoder::compress(Integer init_bits,type_iodevice *outs)*/

inline void LZWEncoder::encode(type_iodevice * os) {
    assert(initCodeSize<=MAX_UCHAR);
    assert(initCodeSize>=0);
    this->put_char(os,initCodeSize); /*write "initial code size" byte*/
    remaining=imgW * imgH; /*reset navigation variables*/
    assert(remaining==(pixAryEnd-pixAryBegin));
    curPixel=0;
    compress(initCodeSize+1,os); /*compress and write the pixel data*/
    this->put_char(os,type_uchar(0));
}/*inline void LZWEncoder::encode(type_iodevice * os) */

void LZWEncoder::flush_char(type_iodevice * outs) {
    if (a_count>0) {
        assert(a_count<=MAX_UCHAR);
        assert(a_count>=0);
        this->put_char(outs,a_count);
        this->write_chars(outs,accum.data(),a_count);
        a_count=0;
    }
}/*void LZWEncoder::flush_char(type_iodevice * outs)*/

inline LZWEncoder::Integer LZWEncoder::nextPixel() {
    if (remaining<1) {
        return EOF;
    }
    --remaining;
    type_uchar pix=pixAryBegin[curPixel++];
    return pix;
}/*inline LZWEncoder::Integer LZWEncoder::nextPixel()*/

inline void LZWEncoder::output(Integer code,type_iodevice * outs) {
    cur_accum&=masks(cur_bits);

    if (cur_bits>0) {
        cur_accum|=(code<<cur_bits);
    }
    else {
        cur_accum=code;
    }

    cur_bits+=n_bits;

    while (cur_bits>=8) {
        char_out(cur_accum,outs);
        cur_accum>>=8;
        cur_bits-=8;
    }

    /*If the next entry is going to be too big for the code size,*/
    /*then increase it, if possible.*/
    if (free_ent>maxcode||clear_flg) {
        if (clear_flg) {
            maxcode=MAXCODE(n_bits=g_init_bits);
            clear_flg=false;
        }
        else {
            ++n_bits;
            if (n_bits==maxbits) {
                maxcode=maxmaxcode;
            }
            else {
                maxcode=MAXCODE(n_bits);
            }
        }
    }

    if (code==EOFCode) {
        /*At EOF, write the rest of the buffer.*/
        while (cur_bits>0) {
            char_out(cur_accum,outs);
            cur_accum>>=8;
            cur_bits-=8;
        }
        flush_char(outs);
    }
}/*inline void LZWEncoder::output(Integer code,type_iodevice * outs)*/

}/*namespace*/
}/*mgui*/

namespace mgui {
class QAnimatedGifEncoder::ThisData {
public:
    ThisData() {
        for (auto & ii:usedEntry) { ii=false; }
    }
    ~ThisData() {}

    Integer width=null; // image size
    Integer height=null;
    Color transparent=null; // transparent color if given
    Boolean isGivenTransparent=false;
    Integer transIndex=null; // transparent index in color table
    Integer repeat=-1; // no repeat
    Integer delay=0; // frame delay (hundredths)
    Boolean started=false; // ready to output frames
    OutputStream * out=0;
    BufferedImage image; // current frame
    PixType  pixels; // BGR byte array from frame
    QVector<type_uchar> indexedPixels; // converted frame indexed to palette
    Integer colorDepth=8; // number of bit planes
    QVector<type_uchar> colorTab; // RGB palette
    Boolean usedEntry[256]; // active palette entries
    Integer palSize=7; // color table size (bits-1)
    Integer dispose=-1; // disposal code (-1 = use default)
    Boolean closeStream=false; // close stream when finished
    Boolean firstFrame=true;
    Boolean sizeSet=false; // if false, get size from first frame
    Integer sample=10; // default sample interval for quantizer
};

QAnimatedGifEncoder::QAnimatedGifEncoder() {
    ThisData * var_thisData=new ThisData;
    thisData={
        var_thisData,
        [](ThisData * par_data) {delete par_data; }
    };
}

QAnimatedGifEncoder::~QAnimatedGifEncoder() {
    if (this->thisData->started) {
        this->finish();
    }
}

void QAnimatedGifEncoder::setDelay(const Integer ms) {
    ThisData * var_thisData=thisData.get();
    var_thisData->delay=std::round(ms/10.0f);
}

void QAnimatedGifEncoder::setDispose(const Integer code) {
    if (code>=0) {
        ThisData * var_thisData=thisData.get();
        var_thisData->dispose=code;
    }
}

void QAnimatedGifEncoder::setRepeat(const Integer iter) {
    if (iter>=0) {
        ThisData * var_thisData=thisData.get();
        var_thisData->repeat=iter;
    }
}

void QAnimatedGifEncoder::setTransparent(const Color c) {
    ThisData * var_thisData=thisData.get();
    var_thisData->isGivenTransparent=true;
    var_thisData->transparent=c;
}

void QAnimatedGifEncoder::setSize(const Integer w,const Integer h) {
    ThisData * var_thisData=thisData.get();
    if ((var_thisData->started)&&(!(var_thisData->firstFrame))) return;

    var_thisData->width=w;
    var_thisData->height=h;

    if (var_thisData->width<1) var_thisData->width=320;
    if (var_thisData->height<1) var_thisData->height=240;

    var_thisData->sizeSet=true;
}

namespace {

inline QImage change_image_format_and_size(
        const QImage & argImage,
        Integer argWidth,
        Integer argHeight
) {

    if (argImage.isNull()) {
        auto varAns=QImage{ argWidth,argHeight,QImage::Format::Format_RGB888 };
        varAns.fill({ 255,0,0 });
        return std::move(varAns);
    }

    QImage varAns=argImage;
    {
        QImage::Format varType=varAns.format();
        if (varType!=QImage::Format::Format_RGB888) {
            varAns=varAns.convertToFormat(QImage::Format::Format_RGB888);
        }
    }

    const auto varWidth=varAns.width();
    const auto varHeight=varAns.height();

    if ((varHeight!=argHeight)||(varWidth!=argWidth)) {
        varAns=varAns.scaled(argWidth,argHeight,
                             Qt::AspectRatioMode::IgnoreAspectRatio,
                             Qt::TransformationMode::SmoothTransformation);
    }

    return std::move(varAns);
}

}/*namespace*/

/*将图片化为一行*/
void QAnimatedGifEncoder::getImagePixels() {
    ThisData * var_thisData=thisData.get();

    var_thisData->image=change_image_format_and_size(
                var_thisData->image,
                var_thisData->width,
                var_thisData->height);

    {/*set bits*/
        const auto var_w=var_thisData->image.width();
        const auto var_h=var_thisData->image.height();
        const QImage & varImage=var_thisData->image;
        auto & pixs=var_thisData->pixels;
        pixs.clear();
        pixs.reserve(3*var_w*var_h);

        auto varData=varImage.constBits();
        const auto varBytesPerLine=varImage.bytesPerLine();

        for (auto ii=0; ii<var_h; ++ii,varData+=varBytesPerLine) {
            auto varDataLine=varData;
            for (auto jj=0; jj<var_w; ++jj) {
                pixs.push_back(*varDataLine++);
                pixs.push_back(*varDataLine++);
                pixs.push_back(*varDataLine++);
            }
        }
    }

}

Boolean QAnimatedGifEncoder::addFrame(BufferedImage && im) {
    ThisData * var_thisData=thisData.get();
    if ((im.width()<=null)||!var_thisData->started) {
        return false;
    }
    Boolean ok=true;

    if (false==var_thisData->sizeSet) {
        // use first frame's size
        setSize(im.width(),im.height());
    }

    var_thisData->image=im;
    var_thisData->image=var_thisData->image.scaled(
                QSize(var_thisData->width,var_thisData->height),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation
    );

    getImagePixels(); // convert to correct format if necessary
    analyzePixels(); // build color table & map pixels

    if (var_thisData->firstFrame) {
        writeLSD(); // logical screen descriptior 逻辑屏幕标识符
        writePalette(); // global color table
        if (var_thisData->repeat>=0) {
            // use NS app extension to indicate reps
            writeNetscapeExt();
        }
    }

    writeGraphicCtrlExt(); // write graphic control extension
    writeImageDesc(); // image descriptor
    if (!(var_thisData->firstFrame)) {
        writePalette(); // local color table
    }
    writePixels(); // encode and write pixel data
    var_thisData->firstFrame=false;

    return ok;
}

void QAnimatedGifEncoder::writePalette() {
    ThisData * var_thisData=thisData.get();
    var_thisData->out->write(
        reinterpret_cast<const Byte *>(var_thisData->colorTab.data()),
        static_cast<Integer>(var_thisData->colorTab.size()));
    Integer n=(3*256)-var_thisData->colorTab.size();
    for (Integer i=0; i<n; ++i) {
        writeSome(Byte(0),var_thisData->out);
    }
}

void QAnimatedGifEncoder::writePixels() {
    ThisData * var_thisData=thisData.get();
    LZWEncoder * encoder=
        new LZWEncoder(
            var_thisData->width,
            var_thisData->height,
            reinterpret_cast<LZWEncoder::const_uchar *>(var_thisData->indexedPixels.cbegin()),
            reinterpret_cast<LZWEncoder::const_uchar *>(var_thisData->indexedPixels.cend()),
            var_thisData->colorDepth
        );
    std::unique_ptr<LZWEncoder> _(encoder);
    encoder->encode(var_thisData->out);
}

void QAnimatedGifEncoder::writeGraphicCtrlExt() {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,Byte(0x21)); // extension introducer
    put_char(var_thisData->out,Byte(0x00f9)); // GCE label
    put_char(var_thisData->out,Byte(4)); // data block size
    Integer transp,disp;
    if (var_thisData->isGivenTransparent==false) {
        transp=0;
        disp=0; // dispose = no action
    }
    else {
        transp=1;
        disp=2; // force clear if using transparent color
    }
    if (var_thisData->dispose>=0) {
        disp=var_thisData->dispose&7; // user override
    }
    disp<<=2;
    // packed fields
    put_char(var_thisData->out,(Byte((disp|transp)&0x00ff))); // 8   transparency flag
    writeShort(var_thisData->delay); // delay x 1/100 sec
    put_char(var_thisData->out,(Byte(0x00ff&var_thisData->transIndex))); // transparent color index
    put_char(var_thisData->out,Byte(0)); // block terminator
}

void QAnimatedGifEncoder::writeLSD() {
    ThisData * var_thisData=thisData.get();
    // logical screen size
    writeShort(var_thisData->width);
    writeShort(var_thisData->height);
    // packed fields
    writeSome(Byte(0x80|0x70|0x00|var_thisData->palSize),var_thisData->out);
    writeSome(Byte(0),var_thisData->out);
    writeSome(Byte(0),var_thisData->out);
}

void QAnimatedGifEncoder::writeImageDesc() {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,Byte(0x2c));
    writeShort(0); // image position x,y = 0,0
    writeShort(0);
    writeShort(var_thisData->width); // image size
    writeShort(var_thisData->height);
    // packed fields
    if (var_thisData->firstFrame) {
        // no LCT  - GCT is used for first (or only) frame
        put_char(var_thisData->out,Byte(0));
    }
    else {
        // specify normal LCT
        put_char(var_thisData->out,Byte(0x80|var_thisData->palSize)); // 6-8 size of color table
    }
}

void QAnimatedGifEncoder::writeShort(Integer value) {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,(Byte(value&0x00ff)));
    put_char(var_thisData->out,(Byte((value>>8)&0x00ff)));
}

void QAnimatedGifEncoder::writeNetscapeExt() {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,Byte(0x21)); // extension introducer
    writeSome(Byte(0x00ff),var_thisData->out); // app extension label
    put_char(var_thisData->out,Byte(11)); // block size
    writeString((const Byte *)("NETSCAPE2.0")); // app id + auth code
    put_char(var_thisData->out,Byte(3)); // sub-block size
    put_char(var_thisData->out,Byte(1)); // loop sub-block id
    writeShort(var_thisData->repeat); // loop count (extra iterations, 0=repeat forever)
    put_char(var_thisData->out,Byte(0)); // block terminator
}

Boolean QAnimatedGifEncoder::addFrame(const BufferedImage & im) {
    BufferedImage var_image=im;
    return addFrame(std::move(var_image));
}

static inline const Byte * gifTrailer() {//1
    static const Byte data[]={ 0x3b, 0 };
    return data;
}

static inline const Byte * gifHeader() {//6
    static const Byte data[]={ 'G', 'I', 'F', '8', '9', 'a', 0 };
    return data;
}

Boolean QAnimatedGifEncoder::finish() {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->started==false) return false;
    Boolean ok=true;
    var_thisData->started=false;
    //
    if (var_thisData->out==0) { ok=false; }
    else
        try {
        put_char(var_thisData->out,Byte(0x3b));
        if (var_thisData->closeStream) {
            var_thisData->out->close();
        }
    }
    catch (...) {
        ok=false;
    }

    /*reset for subsequent use*/
    var_thisData->transIndex=0;
    var_thisData->out=null;
    var_thisData->image=QImage();
    var_thisData->pixels.clear();
    var_thisData->indexedPixels.clear();
    var_thisData->colorTab.clear();
    var_thisData->closeStream=false;
    var_thisData->firstFrame=true;
    var_thisData->isGivenTransparent=false;

    return ok;
}

void QAnimatedGifEncoder::setFrameRate(const Float fps) {
    if (fps!=0.0f) {
        ThisData * var_thisData=thisData.get();
        var_thisData->delay=std::round(100.0f/fps);
    }
}

void QAnimatedGifEncoder::setQuality(const Integer quality) {
    ThisData * var_thisData=thisData.get();
    if (quality<1) {
        var_thisData->sample=1;
        return;
    }
    var_thisData->sample=quality;
}

/* 'G', 'I', 'F', '8', '9', 'a' */
Boolean QAnimatedGifEncoder::start(OutputStream & os) {
    ThisData * var_thisData=thisData.get();
    Boolean ok=true;
    var_thisData->closeStream=false;
    var_thisData->out=&os;

    try {
        writeString(gifHeader()); // header
    }
    catch (...) {
        ok=false;
    }

    var_thisData->started=ok;
    return ok;
}

Integer QAnimatedGifEncoder::findClosest(Color c) {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->colorTab.size()==null) return -1;
    Integer r=qRed(c);
    Integer g=qGreen(c);
    Integer b=qBlue(c);
    Integer minpos=0;
    Integer dmin=256*256*256;
    Integer len=Integer(var_thisData->colorTab.size());
    const auto & colorTab=var_thisData->colorTab;
    for (Integer i=0; i<len;) {
        Integer dr=r-(colorTab[i++]);
        Integer dg=g-(colorTab[i++]);
        Integer db=b-(colorTab[i]);
        Integer d=dr * dr+dg * dg+db * db;
        Integer index=i/3;
        if (var_thisData->usedEntry[index]&&(d<dmin)) {
            dmin=d;
            minpos=index;
        }
        ++i;
    }
    return minpos;
}

//TODO:analyzePixels
void QAnimatedGifEncoder::analyzePixels() {
    ThisData * var_thisData=thisData.get();
    typedef Integer size_type;
    const auto len=size_type(var_thisData->pixels.size());
    const auto nPix=len/size_type(3);
    var_thisData->indexedPixels.resize(nPix);
    QuantizationAlgorithm * nq=new Quantization;//new NeuQuant;
    std::unique_ptr<QuantizationAlgorithm> uptr_nq(nq);
    nq->construct(var_thisData->pixels,len,var_thisData->sample);
    var_thisData->colorTab=nq->process();
    //#define FLOYD_STEINBERG
    const auto & pixels=var_thisData->pixels;
    /*map image pixels to new palette*/
    auto k=const_cast<type_uchar*>(pixels.constBegin());
#if defined(FLOYD_STEINBERG)
    Integer px=0/*当前x*/;
    Integer py=0/*当前y*/;
    const Integer line_step=var_thisData->width*3;
    constexpr Integer left_limit=0;
    const Integer right_limit=var_thisData->width-1;
    const Integer bottom_limit=var_thisData->height-1;
    type_uchar * next_bottom_right_item=nullptr;
    type_uchar * next_right_item=nullptr;
    type_uchar * next_middle_item=nullptr;
    const auto & colorTab=var_thisData->colorTab;
#endif
    for (Integer i=0; i<nPix; ++i) {
#if defined(FLOYD_STEINBERG)
        /*求下一行pix的坐标*/
        if (py<bottom_limit) {
            next_middle_item=k+line_step;

            if (px<right_limit) {
                next_bottom_right_item=next_middle_item+3;
            }
            else {
                next_bottom_right_item=nullptr;
            }

        }
        else {
            next_bottom_right_item=nullptr;
            next_middle_item=nullptr;
        }

        if (px<right_limit) {
            next_right_item=k+3;
        }
        else {
            next_right_item=nullptr;
        }
#endif
        const Integer r0=*k++/*原始r*/;
        const Integer g0=*k++/*原始g*/;
        const Integer b0=*k++/*原始b*/;

        Integer index=nq->map(r0,g0,b0);

        var_thisData->usedEntry[index]=true;
        var_thisData->indexedPixels[i]=index;

#if defined(FLOYD_STEINBERG)
        index*=3;
        const Integer r1=colorTab[index++]/*新的r*/;
        const Integer g1=colorTab[index++]/*新的g*/;
        const Integer b1=colorTab[index]/*新的b*/;

        const auto er=r1-r0/*r的误差*/;
        const auto eg=g1-g0/*g的误差*/;
        const auto eb=b1-b0/*b的误差*/;

        /*3/8*/
        if (next_middle_item) {
            auto & or=*next_middle_item++;
            auto & og=*next_middle_item++;
            auto & ob=*next_middle_item;

            Integer r=or;
            Integer g=og;
            Integer b=ob;

            r+=(er*3)>>3;
            g+=(eg*3)>>3;
            b+=(eb*3)>>3;

            if (r>255) { r=255; }
            if (g>255) { g=255; }
            if (b>255) { b=255; }

            if (r<0) { r=0; }
            if (g<0) { g=0; }
            if (b<0) { b=0; }

            or=r;
            og=g;
            ob=b;

        }

        /*1/4*/
        if (next_bottom_right_item) {
            auto & or=*next_bottom_right_item++;
            auto & og=*next_bottom_right_item++;
            auto & ob=*next_bottom_right_item;

            Integer r=or;
            Integer g=og;
            Integer b=ob;

            r+=(er)>>2;
            g+=(eg)>>2;
            b+=(eb)>>2;

            if (r>255) { r=255; }
            if (g>255) { g=255; }
            if (b>255) { b=255; }

            if (r<0) { r=0; }
            if (g<0) { g=0; }
            if (b<0) { b=0; }

            or=r;
            og=g;
            ob=b;
        }

        /*3/8*/
        if (next_right_item) {
            auto & or=*next_right_item++;
            auto & og=*next_right_item++;
            auto & ob=*next_right_item;

            Integer r=or;
            Integer g=og;
            Integer b=ob;

            r+=(er*3)>>3;
            g+=(eg*3)>>3;
            b+=(eb*3)>>3;

            if (r>255) { r=255; }
            if (g>255) { g=255; }
            if (b>255) { b=255; }

            if (r<0) { r=0; }
            if (g<0) { g=0; }
            if (b<0) { b=0; }

            or=r;
            og=g;
            ob=b;
        }

        /*更新x y*/
        ++px;
        if (px>=var_thisData->width) {
            px=0; ++py;
        }
#endif
}

    var_thisData->pixels.clear();
    var_thisData->colorDepth=8;
    var_thisData->palSize=7;
    // get closest match to transparent color if specified
    if (var_thisData->isGivenTransparent) {//----
        var_thisData->transIndex=findClosest(var_thisData->transparent);
    }
}

void QAnimatedGifEncoder::writeString(const String & s) {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->out&&s.size()) {
        auto string_=s.toUtf8();
        var_thisData->out->write(string_.data(),string_.size());
    }
}

}/*mgui*/

