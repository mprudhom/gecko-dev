/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s):
 *   Scott Collins <scc@netscape.com>
 */

#ifndef _nsAWritableString_h__
#define _nsAWritableString_h__

  // WORK IN PROGRESS

  // See also...
#include "nsAReadableString.h"


/*
  This file defines the abstract interfaces |nsAWritableString| and
  |nsAWritableCString|.

  |nsAWritableString| is a string of |PRUnichar|s.  |nsAWritableCString| (note the
  'C') is a string of |char|s.
*/

template <class CharT>
class basic_nsAWritableString
      : public basic_nsAReadableString<CharT>
    /*
      ...
    */
  {
    protected:
      typedef typename basic_nsAReadableString<CharT>::FragmentRequest  FragmentRequest;

      struct WritableFragment
        {
          CharT*    mStart;
          CharT*    mEnd;
          PRUint32  mFragmentIdentifier;

          WritableFragment()
              : mStart(0), mEnd(0), mFragmentIdentifier(0)
            {
              // nothing else to do here
            }
        };

    public:
      virtual CharT* GetWritableFragment( WritableFragment&, FragmentRequest, PRUint32 = 0 ) = 0;

      friend class WritingIterator;
      class WritingIterator
          : public bidirectional_iterator_tag
        {
          public:
            typedef ptrdiff_t                   difference_type;
            typedef CharT                       value_type;
            typedef CharT*                      pointer;
            typedef CharT&                      reference;
            typedef bidirectional_iterator_tag  iterator_category;

          private:
            friend class basic_nsAWritableString<CharT>;

            WritableFragment                mFragment;
            CharT*                          mPosition;
            basic_nsAWritableString<CharT>* mOwningString;

            void
            normalize_forward()
              {
                if ( mPosition == mFragment.mEnd )
                  if ( mOwningString->GetWritableFragment(mFragment, kNextFragment) )
                    mPosition = mFragment.mStart;
              }

            void
            normalize_backward()
              {
                if ( mPosition == mFragment.mStart )
                  if ( mOwningString->GetWritableFragment(mFragment, kPrevFragment) )
                    mPosition = mFragment.mEnd;
              }

            WritingIterator( WritableFragment& aFragment,
                      CharT* aStartingPosition,
                      basic_nsAWritableString<CharT>& aOwningString )
                : mFragment(aFragment),
                  mPosition(aStartingPosition),
                  mOwningString(&aOwningString)
              {
                // nothing else to do here
              }

          public:
            // WritingIterator( const WritingIterator& ); ...use default copy-constructor
            // WritingIterator& operator=( const WritingIterator& ); ...use default copy-assignment operator

            
            reference
            operator*() const
              {
                return *mPosition;
              }

            pointer
            operator->() const
              {
                return mPosition;
              }

            WritingIterator&
            operator++()
              {
                ++mPosition;
                normalize_forward();
                return *this;
              }

            WritingIterator
            operator++( int )
              {
                WritingIterator result(*this);
                ++mPosition;
                normalize_forward();
                return result;
              }

            WritingIterator&
            operator--()
              {
                normalize_backward();
                --mPosition;
                return *this;
              }

            WritingIterator
            operator--( int )
              {
                WritingIterator result(*this);
                normalize_backward();
                --mPosition;
                return result;
              }

            const WritableFragment&
            fragment() const
              {
                return mFragment;
              }

            difference_type
            size_forward() const
              {
                return mFragment.mEnd - mPosition;
              }

            difference_type
            size_backward() const
              {
                return mPosition - mFragment.mStart;
              }

            WritingIterator&
            operator+=( difference_type n )
              {
                if ( n < 0 )
                  return operator-=(-n);

                while ( n )
                  {
                    difference_type one_hop = NS_MIN(n, size_forward());
                    mPosition += one_hop;
                    normalize_forward();
                    n -= one_hop;
                  }

                return *this;
              }

            WritingIterator&
            operator-=( difference_type n )
              {
                if ( n < 0 )
                  return operator+=(-n);

                while ( n )
                  {
                    difference_type one_hop = NS_MIN(n, size_backward());
                    mPosition -= one_hop;
                    normalize_backward();
                    n -= one_hop;
                  }

                return *this;
              }

            PRBool
            operator==( const WritingIterator& rhs ) const
              {
                return mPosition == rhs.mPosition;
              }

            PRBool
            operator!=( const WritingIterator& rhs ) const
              {
                return mPosition != rhs.mPosition;
              }
        };

      typedef WritingIterator Iterator;

    public:

      WritingIterator
      BeginWriting( PRUint32 aOffset = 0 )
        {
          WritableFragment fragment;
          CharT* startPos = GetWritableFragment(fragment, kFragmentAt, aOffset);
          return WritingIterator(fragment, startPos, *this);
        }


      WritingIterator
      EndWriting( PRUint32 aOffset = 0 )
        {
          WritableFragment fragment;
          CharT* startPos = GetWritableFragment(fragment, kFragmentAt, NS_MAX(0U, Length()-aOffset));
          return WritingIterator(fragment, startPos, *this);
        }


      virtual void SetCapacity( PRUint32 ) = 0;
      virtual void SetLength( PRUint32 ) = 0;


      void
      Truncate( PRUint32 aNewLength=0 )
        {
          NS_ASSERTION(aNewLength<=Length(), "Can't use |Truncate()| to make a string longer.");

          if ( aNewLength < Length() )
            SetLength(aNewLength);
        }


      // PRBool SetCharAt( char_type, index_type ) = 0;



      // void ToLowerCase();
      // void ToUpperCase();

      // void StripChars( const CharT* aSet );
      // void StripChar( ... );
      // void StripWhitespace();
      // void ReplaceChar( ... );
      // void ReplaceSubstring( ... );
      // void Trim( ... );
      // void CompressSet( ... );
      // void CompressWhitespace( ... );



      virtual void Assign( const basic_nsAReadableString<CharT>& rhs );
      // virtual void AssignChar( CharT ) = 0;

      virtual void Append( const basic_nsAReadableString<CharT>& );
      virtual void AppendChar( CharT );

      virtual void Insert( const basic_nsAReadableString<CharT>&, PRUint32 atPosition );
      // virtual void InsertChar( CharT, PRUint32 atPosition ) = 0;

      virtual void Cut( PRUint32 cutStart, PRUint32 cutLength );

      virtual void Replace( PRUint32 cutStart, PRUint32 cutLength, const basic_nsAReadableString<CharT>& );


      basic_nsAWritableString<CharT>&
      operator+=( const basic_nsAReadableString<CharT>& rhs )
        {
          Append(rhs);
          return *this;
        }

      basic_nsAWritableString<CharT>&
      operator+=( const basic_nsLiteralString<CharT>& rhs )
        {
          Append(rhs);
          return *this;
        }

      basic_nsAWritableString<CharT>&
      operator=( const basic_nsAReadableString<CharT>& rhs )
        {
          Assign(rhs);
          return *this;
        }

      basic_nsAWritableString<CharT>&
      operator=( const basic_nsLiteralString<CharT>& rhs )
        {
          Assign(rhs);
          return *this;
        }
  };


template <class CharT>
typename basic_nsAWritableString<CharT>::WritingIterator
copy_chunky( typename basic_nsAReadableString<CharT>::ReadingIterator first,
             typename basic_nsAReadableString<CharT>::ReadingIterator last,
             typename basic_nsAWritableString<CharT>::WritingIterator result )
  {
    while ( first != last )
      {
        PRUint32 lengthToCopy = PRUint32( NS_MIN(first.size_forward(), result.size_forward()) );
        if ( first.fragment().mStart == last.fragment().mStart )
          lengthToCopy = NS_MIN(lengthToCopy, PRUint32(last.operator->() - first.operator->()));

        // assert(lengthToCopy > 0);

        nsCharTraits<CharT>::copy(result.operator->(), first.operator->(), lengthToCopy);

        first += PRInt32(lengthToCopy);
        result += PRInt32(lengthToCopy);
      }

    return result;
  }

template <class CharT>
typename basic_nsAWritableString<CharT>::WritingIterator
copy_backward_chunky( typename basic_nsAReadableString<CharT>::ReadingIterator  first,
                      typename basic_nsAReadableString<CharT>::ReadingIterator  last,
                      typename basic_nsAWritableString<CharT>::WritingIterator  result )
  {
    while ( first != last )
      {
        PRUint32 lengthToCopy = PRUint32( NS_MIN(first.size_backward(), result.size_backward()) );
        if ( first.fragment().mStart == last.fragment().mStart )
          lengthToCopy = NS_MIN(lengthToCopy, PRUint32(first.operator->() - last.operator->()));

        nsCharTraits<CharT>::move(result.operator->(), first.operator->(), lengthToCopy);

        first -= PRInt32(lengthToCopy);
        result -= PRInt32(lengthToCopy);
      }

    return result;
  }




template <class CharT>
void
basic_nsAWritableString<CharT>::Assign( const basic_nsAReadableString<CharT>& rhs )
  {
    SetLength(rhs.Length());
    copy_chunky<CharT>(rhs.BeginReading(), rhs.EndReading(), BeginWriting());
  }

template <class CharT>
void
basic_nsAWritableString<CharT>::Append( const basic_nsAReadableString<CharT>& rhs )
  {
    PRUint32 oldLength = Length();
    SetLength(oldLength + rhs.Length());
    copy_chunky<CharT>(rhs.BeginReading(), rhs.EndReading(), BeginWriting(oldLength));
  }

template <class CharT>
void
basic_nsAWritableString<CharT>::AppendChar( CharT aChar )
  {
    SetLength(Length()+1);
    *EndWriting(1) = aChar;
  }

template <class CharT>
void
basic_nsAWritableString<CharT>::Insert( const basic_nsAReadableString<CharT>& aReadable, PRUint32 aPosition )
  {
    PRUint32 oldLength = Length();
    SetLength(oldLength + aReadable.Length());
    if ( aPosition < oldLength )
      copy_backward_chunky<CharT>(BeginReading(aPosition), BeginReading(oldLength), EndWriting());
    else
      aPosition = oldLength;
    copy_chunky<CharT>(aReadable.BeginReading(), aReadable.EndReading(), BeginWriting(aPosition));
  }

template <class CharT>
void
basic_nsAWritableString<CharT>::Cut( PRUint32 cutStart, PRUint32 cutLength )
  {
    copy_chunky<CharT>(BeginReading(cutStart+cutLength), EndReading(), BeginWriting(cutStart));
    SetLength(Length()-cutLength);
  }

template <class CharT>
void
basic_nsAWritableString<CharT>::Replace( PRUint32 cutStart, PRUint32 cutLength, const basic_nsAReadableString<CharT>& aReplacement )
  {
    PRUint32 oldLength = Length();

    cutStart = NS_MIN(cutStart, oldLength);
    cutLength = NS_MIN(cutLength, oldLength-cutStart);
    PRUint32 cutEnd = cutStart + cutLength;

    PRUint32 replacementLength = aReplacement.Length();
    PRUint32 replacementEnd = cutStart + replacementLength;

    PRUint32 newLength = oldLength - cutLength + replacementLength;

    if ( cutLength > replacementLength )
      copy_chunky<CharT>(BeginReading(cutEnd), EndReading(), BeginWriting(replacementEnd));
    SetLength(newLength);
    if ( cutLength < replacementLength )
      copy_backward_chunky<CharT>(BeginReading(cutEnd), BeginReading(oldLength), BeginWriting(replacementEnd));

    copy_chunky<CharT>(aReplacement.BeginReading(), aReplacement.EndReading(), BeginWriting(cutStart));
  }

// operator>>
// getline (maybe)

typedef basic_nsAWritableString<PRUnichar>  nsAWritableString;
typedef basic_nsAWritableString<char>       nsAWritableCString;

#endif // !defined(_nsAWritableString_h__)
