// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "precomp.h"
#include "WexTestClass.h"
#include "..\..\inc\consoletaeftemplates.hpp"

#include "CommonState.hpp"

#include "search.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

class SearchTests
{
    TEST_CLASS(SearchTests);

    CommonState* m_state;

    TEST_CLASS_SETUP(ClassSetup)
    {
        m_state = new CommonState();

        m_state->PrepareGlobalFont();
        m_state->PrepareGlobalScreenBuffer();

        return true;
    }

    TEST_CLASS_CLEANUP(ClassCleanup)
    {
        m_state->CleanupGlobalScreenBuffer();
        m_state->CleanupGlobalFont();

        delete m_state;

        return true;
    }

    TEST_METHOD_SETUP(MethodSetup)
    {
        m_state->PrepareNewTextBufferInfo();
        m_state->FillTextBuffer();

        return true;
    }

    TEST_METHOD_CLEANUP(MethodCleanup)
    {
        m_state->CleanupNewTextBufferInfo();

        return true;
    }

    void DoFoundChecks(Search& s, COORD& coordStartExpected, SHORT lineDelta)
    {
        COORD coordEndExpected = coordStartExpected;
        coordEndExpected.X += 1;

        VERIFY_IS_TRUE(s.FindNext());
        VERIFY_ARE_EQUAL(coordStartExpected, s._coordSelStart);
        VERIFY_ARE_EQUAL(coordEndExpected, s._coordSelEnd);

        coordStartExpected.Y += lineDelta;
        coordEndExpected.Y += lineDelta;
        VERIFY_IS_TRUE(s.FindNext());
        VERIFY_ARE_EQUAL(coordStartExpected, s._coordSelStart);
        VERIFY_ARE_EQUAL(coordEndExpected, s._coordSelEnd);

        coordStartExpected.Y += lineDelta;
        coordEndExpected.Y += lineDelta;
        VERIFY_IS_TRUE(s.FindNext());
        VERIFY_ARE_EQUAL(coordStartExpected, s._coordSelStart);
        VERIFY_ARE_EQUAL(coordEndExpected, s._coordSelEnd);

        coordStartExpected.Y += lineDelta;
        coordEndExpected.Y += lineDelta;
        VERIFY_IS_TRUE(s.FindNext());
        VERIFY_ARE_EQUAL(coordStartExpected, s._coordSelStart);
        VERIFY_ARE_EQUAL(coordEndExpected, s._coordSelEnd);

        VERIFY_IS_FALSE(s.FindNext());
    }

    TEST_METHOD(ForwardCaseSensitive)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 0 };
        Search s(outputBuffer, L"AB", Search::Direction::Forward, Search::Sensitivity::CaseSensitive);
        DoFoundChecks(s, coordStartExpected, 1);
    }

    TEST_METHOD(ForwardCaseSensitiveJapanese)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 2, 0 };
        Search s(outputBuffer, L"\x304b", Search::Direction::Forward, Search::Sensitivity::CaseSensitive);
        DoFoundChecks(s, coordStartExpected, 1);
    }

    TEST_METHOD(ForwardCaseInsensitive)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 0 };
        Search s(outputBuffer, L"ab", Search::Direction::Forward, Search::Sensitivity::CaseInsensitive);
        DoFoundChecks(s, coordStartExpected, 1);
    }

    TEST_METHOD(ForwardCaseInsensitiveJapanese)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 2, 0 };
        Search s(outputBuffer, L"\x304b", Search::Direction::Forward, Search::Sensitivity::CaseInsensitive);
        DoFoundChecks(s, coordStartExpected, 1);
    }

    TEST_METHOD(BackwardCaseSensitive)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 0, 3 };
        Search s(outputBuffer, L"AB", Search::Direction::Backward, Search::Sensitivity::CaseSensitive);
        DoFoundChecks(s, coordStartExpected, -1);
    }

    TEST_METHOD(BackwardCaseSensitiveJapanese)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 2, 3 };
        Search s(outputBuffer, L"\x304b", Search::Direction::Backward, Search::Sensitivity::CaseSensitive);
        DoFoundChecks(s, coordStartExpected, -1);
    }

    TEST_METHOD(BackwardCaseInsensitive)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 0, 3 };
        Search s(outputBuffer, L"ab", Search::Direction::Backward, Search::Sensitivity::CaseInsensitive);
        DoFoundChecks(s, coordStartExpected, -1);
    }

    TEST_METHOD(BackwardCaseInsensitiveJapanese)
    {
        const auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        const auto& outputBuffer = gci.GetActiveOutputBuffer();

        COORD coordStartExpected = { 2, 3 };
        Search s(outputBuffer, L"\x304b", Search::Direction::Backward, Search::Sensitivity::CaseInsensitive);
        DoFoundChecks(s, coordStartExpected, -1);
    }
};
