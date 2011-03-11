/***********************************************************************
  Moses - factored phrase-based language decoder
  Copyright (C) 2011 University of Edinburgh

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ***********************************************************************/

#pragma once
#ifndef moses_ChartRuleLookupManagerMemory_h
#define moses_ChartRuleLookupManagerMemory_h

#include <vector>

#if HAVE_CONFIG_H
#include "config.h"
#ifdef USE_BOOST_POOL
#include <boost/pool/object_pool.hpp>
#endif
#endif

#include "ChartRuleLookupManager.h"
#include "DotChart.h"
#include "NonTerminal.h"
#include "PhraseDictionaryNodeSCFG.h"
#include "PhraseDictionarySCFG.h"
#include "WordConsumed.h"

namespace Moses
{

class ChartTranslationOptionList;
class DottedRuleColl;
class WordsRange;

// Implementation of ChartRuleLookupManager for in-memory rule tables.
class ChartRuleLookupManagerMemory : public ChartRuleLookupManager
{
public:
  ChartRuleLookupManagerMemory(const InputType &sentence,
                               const CellCollection &cellColl,
                               const PhraseDictionarySCFG &ruleTable);

  ~ChartRuleLookupManagerMemory();

  virtual void GetChartRuleCollection(
    const WordsRange &range,
    bool adhereTableLimit,
    ChartTranslationOptionList &outColl);

private:
  void ExtendPartialRuleApplication(
    const PhraseDictionaryNodeSCFG &node,
    const WordConsumed *prevWordConsumed,
    size_t startPos,
    size_t endPos,
    size_t stackInd,
    DottedRuleColl &dottedRuleColl);

  std::vector<DottedRuleColl*> m_dottedRuleColls;
  const PhraseDictionarySCFG &m_ruleTable;
#ifdef USE_BOOST_POOL
  // Use object pools to allocate the DottedRule and WordConsumed objects
  // for this sentence.  We allocate a lot of them and this has been seen to
  // significantly improve performance, especially for multithreaded decoding.
  boost::object_pool<DottedRule> m_dottedRulePool;
  boost::object_pool<WordConsumed> m_wordConsumedPool;
#endif
};

}  // namespace Moses

#endif
