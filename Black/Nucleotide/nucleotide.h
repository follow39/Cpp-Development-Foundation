#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

struct Nucleotide {
    char Symbol;
    size_t Position;
    int ChromosomeNum;
    int GeneNum;
    bool IsMarked;
    char ServiceInfo;
};

const std::unordered_map<char, uint8_t> symbols = {
        {'A', 0},
        {'T', 1},
        {'G', 2},
        {'C', 3}
};
const std::vector<char> indexSymbols = {'A', 'T', 'G', 'C'};

struct CompactNucleotide {
    uint64_t Symbol: 2;
    uint64_t Position: 32;
    uint64_t ChromosomeNum: 6;
    uint64_t GeneNum: 15;
    uint64_t IsMarked: 1;
    uint64_t ServiceInfo: 8;
};


bool operator==(const Nucleotide &lhs, const Nucleotide &rhs) {
    return (lhs.Symbol == rhs.Symbol)
           && (lhs.Position == rhs.Position)
           && (lhs.ChromosomeNum == rhs.ChromosomeNum)
           && (lhs.GeneNum == rhs.GeneNum)
           && (lhs.IsMarked == rhs.IsMarked)
           && (lhs.ServiceInfo == rhs.ServiceInfo);
}


CompactNucleotide Compress(const Nucleotide &n) {
    CompactNucleotide result{};
    result.Symbol = symbols.at(n.Symbol);
    result.Position = n.Position;
    result.ChromosomeNum = n.ChromosomeNum;
    result.GeneNum = n.GeneNum;
    result.IsMarked = n.IsMarked;
    result.ServiceInfo = n.ServiceInfo;
    return result;
};


Nucleotide Decompress(const CompactNucleotide &cn) {
    Nucleotide result{};
    result.Symbol = indexSymbols[cn.Symbol];
    result.Position = static_cast<size_t>(cn.Position);
    result.ChromosomeNum = static_cast<int>(cn.ChromosomeNum);
    result.GeneNum = static_cast<int>(cn.GeneNum);
    result.IsMarked = static_cast<bool>(cn.IsMarked);
    result.ServiceInfo = static_cast<char>(cn.ServiceInfo);
    return result;
}