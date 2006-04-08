
/*
 Copyright (C) 2005 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 Copyright (C) 2005 Aurelien Chanudet

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#if defined(HAVE_CONFIG_H)
    #include <qla/config.hpp>
#endif

#include <qla/couponvectors.hpp>
#include <qla/swap.hpp>
#include <qla/termstructures.hpp>

namespace QuantLibAddin {

    Swap::Swap(
            const std::string &paidLegID,
            const std::string &recvLegID,
            const std::string &termStructureID) {

        OH_GET_OBJECT(paidLegWrapper, paidLegID, CouponVector)
        const CashFlowVector& paidLeg = paidLegWrapper->getObject();

        OH_GET_OBJECT(recvLegWrapper, recvLegID, CouponVector)
        const CashFlowVector& recvLeg = recvLegWrapper->getObject();

        OH_GET_REFERENCE(termStructure, termStructureID, 
            YieldTermStructure, QuantLib::YieldTermStructure)
        QuantLib::Handle<QuantLib::YieldTermStructure> discountingTermStructure;
        discountingTermStructure.linkTo(termStructure);
        
        mInstrument = boost::shared_ptr<QuantLib::Swap>(
            new QuantLib::Swap(paidLeg, recvLeg, discountingTermStructure));
    }
    
}

