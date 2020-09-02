// Created by Saliya Ekanayake on 2019-07-05.

#ifndef DIBELLA_PAIRWISEFUNCTION_HPP
#define DIBELLA_PAIRWISEFUNCTION_HPP

#include <unordered_map>
#include <string>
#include <seqan/score.h>
#include <seqan/align_parallel.h>
#include "../AlignmentInfo.hpp"
#include "../kmer/CommonKmers.hpp"
#include "../ParallelOps.hpp"
#include "../DistributedFastaData.hpp"
#include "../Utils.hpp"

class PairwiseFunction {
public:

  static const int MAX_THD = 128;
	
  PairwiseFunction();
  virtual ~PairwiseFunction();

  virtual void apply(uint64_t l_col_idx, uint64_t g_col_idx,
      uint64_t l_row_idx, uint64_t g_row_idx,
      seqan::Dna5String *seq_h, seqan::Dna5String *seq_v,
      ushort k,
      dibella::CommonKmers &cks, std::stringstream& ss) = 0;

  virtual
  void
  apply_batch (
         seqan::StringSet<seqan::Gaps<seqan::Dna5String>> &seqsh,
			   seqan::StringSet<seqan::Gaps<seqan::Dna5String>> &seqsv,
			   uint64_t *lids,
			   uint64_t col_offset,
			   uint64_t row_offset,
			   PSpMat<dibella::CommonKmers>::ref_tuples *mattuples,
         std::ofstream &lfs,
         ushort k,
         double thr_cov = 0.7,
			   int thr_ani = 30) = 0;


  void add_time(std::string type, double duration);
  void print_avg_times(std::shared_ptr<ParallelOps> parops, std::ofstream &lfs);

  uint64_t nalignments;
  
private:
  std::unordered_map<std::string, size_t>	types[MAX_THD];
  std::vector<uint64_t>						counts[MAX_THD];
  std::vector<double>						times[MAX_THD];
};

#endif //DIBELLA_PAIRWISEFUNCTION_HPP
