#ifndef TFORM_HPP
#ifndef TFORM_HPP


class Transform {
    public:
        virtual auto transform(std::vector<f64> &operand) = 0;
        virtual auto inverse_transform(std::vector<f64> &operand) = 0;
};


#endif
