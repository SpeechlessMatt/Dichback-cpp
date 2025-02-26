#ifndef _DICHBACK_H_
#define _DICHBACK_H_

namespace dichbackset{

    /**
     * simple_struct记录了一个指针和长度，其实就是数组
     * 记得delete []this->array
     */
    class simple_struct{
    public:
        simple_struct(int*, int);
        simple_struct();
        int len;
        int* array;
    private:
        bool allow_copy;
    };

    class AlgorithmSet{

    public:
        AlgorithmSet();
        // AlgorithmSet(const AlgorithmSet &);
        bool status = true;

        /**
         * 简单回溯算法函数：默认使用逻辑和
         * @param effective_array {int[]} 有效数组
         * @param len {int} in 有效数组的长度
         * @return simple_struct 逻辑判断结果（该对象存储结果数组和其长度）
         */
        simple_struct simple_exhaustion_algorithm(int[], int);

        /**
         * 二分回溯算法函数：默认使用逻辑和
         * @param effective_array {int[]} 有效数组
         * @param len {int} in 有效数组的长度
         * @return simple_struct 逻辑判断结果（该对象存储结果数组和其长度）
         */
        simple_struct dichotomy_backtracking_algorithm(int[], int);

        /**
         * 普通二分法函数：默认使用逻辑或
         * @param effective_array {int[]} 有效数组
         * @param len {int} in 有效数组的长度
         * @return simple_struct 逻辑判断结果（该对象存储结果数组和其长度）
         */
        int dichotomy_algorithm(int[], int);

    private:
        /**
         * 逻辑元 （纯虚函数：强制重载）
         * @param effective_array {int[]} 有效数组
         * @param len {int} in 有效数组的长度
         * @return bool 逻辑判断结果
         */
        virtual bool logic_unit(int[], int) = 0;
        int* effective_list;
        int counts;
        int dba_lm_default;

    };
}

#endif