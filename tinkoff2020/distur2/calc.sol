pragma solidity >=0.7.0 <=0.7.3;

contract Calculator {
    int48[5] history;
    function pop_front() private {
        for (uint8 i = 0; i < 4; i++) {
            history[i] = history[i + 1];
        }
    }
    function sum(int24 a, int24 b) public returns(int24) {
        int24 res = a + b;
        pop_front();
        history[4] = res;
        return a + b;
    }
    function sub(int24 a, int24 b) public returns(int24) {
        int24 res = a - b;
        pop_front();
        history[4] = res;
        return a - b;
    }
    function mul(int24 a, int24 b) public returns(int48) {
        int48 res = a;
        res *= b;
        pop_front();
        history[4] = res;
        return res;
    }
    function div(int24 a, int24 b) public returns(int24) {
        int24 res = -1;
        if (b != 0) {
            res = a / b;
        }
        pop_front();
        history[4] = res;
        return res;
    }
    function getLastResult() public view returns(int48[5] memory) {
        return history;
    }
}