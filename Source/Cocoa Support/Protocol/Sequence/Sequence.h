//
//  Sequence.h
//  Magicians
//
//  Created by Alchemist on 2017/11/21.
//  Copyright © 2017年 alchemistxxd. All rights reserved.
//

_Pragma("once")

#import <objc/objc.h>

@protocol NSFastEnumeration;
@class NSArray;

_Pragma("clang assume_nonnull begin")

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wstrict-prototypes\"")


#define forEach(element, collection) \
    for (typeof((collection).enumeratedType) element in (collection))

@protocol FastEnumeration <NSFastEnumeration>

@property (nonatomic, readonly) id enumeratedType;

- (id)enumeratedType
     __attribute__((noreturn));

@end


__attribute__((objc_runtime_name("__Sequence__")))
@protocol Sequence

/// Returns an array containing the results of mapping the given closure
/// over the sequence's elements.
///
/// In this example, `map` is used first to convert the names in the array
/// to lowercase strings and then to count their characters.
///
///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
///     let lowercaseNames = cast.map { $0.lowercased() }
///     // 'lowercaseNames' == ["vivien", "marlon", "kim", "karl"]
///     let letterCounts = cast.map { $0.count }
///     // 'letterCounts' == [6, 6, 3, 4]
///
/// - Parameter transform: A mapping closure. `transform` accepts an
///   element of this sequence as its parameter and returns a transformed
///   value of the same or of a different type.
/// - Returns: An array containing the transformed elements of this
///   sequence.
- (NSArray *(^)(__attribute__((noescape)) id (^transform)()))map;

/// Returns an array containing, in order, the elements of the sequence
/// that satisfy the given predicate.
///
/// In this example, `filter(_:)` is used to include only names shorter than
/// five characters.
///
///     let cast = ["Vivien", "Marlon", "Kim", "Karl"]
///     let shortNames = cast.filter { $0.count < 5 }
///     print(shortNames)
///     // Prints "["Kim", "Karl"]"
///
/// - Parameter isIncluded: A closure that takes an element of the
///   sequence as its argument and returns a Boolean value indicating
///   whether the element should be included in the returned array.
/// - Returns: An array of the elements that `isIncluded` allowed.
- (NSArray *(^)(__attribute__((noescape)) BOOL (^isIncluded)()))filter;

/// Calls the given closure on each element in the sequence in the same order
/// as a `for`-`in` loop.
///
/// The two loops in the following example produce the same output:
///
///     let numberWords = ["one", "two", "three"]
///     for word in numberWords {
///         print(word)
///     }
///     // Prints "one"
///     // Prints "two"
///     // Prints "three"
///
///     numberWords.forEach { word in
///         print(word)
///     }
///     // Same as above
///
/// Using the `forEach` method is distinct from a `for`-`in` loop in two
/// important ways:
///
/// 1. You cannot use a `break` or `continue` statement to exit the current
///    call of the `body` closure or skip subsequent calls.
/// 2. Using the `return` statement in the `body` closure will exit only from
///    the current call to `body`, not from any outer scope, and won't skip
///    subsequent calls.
///
/// - Parameter body: A closure that takes an element of the sequence as a
///   parameter.
- (NSArray *(^)(__attribute__((noescape)) void (^body)()))forEach;

/// Returns a subsequence containing all but the given number of initial
/// elements.
///
/// If the number of elements to drop exceeds the number of elements in
/// the sequence, the result is an empty subsequence.
///
///     let numbers = [1, 2, 3, 4, 5]
///     print(numbers.dropFirst(2))
///     // Prints "[3, 4, 5]"
///     print(numbers.dropFirst(10))
///     // Prints "[]"
///
/// - Parameter n: The number of elements to drop from the beginning of
///   the sequence. `n` must be greater than or equal to zero.
/// - Returns: A subsequence starting after the specified number of
///   elements.
///
/// - Complexity: O(*n*), where *n* is the number of elements to drop from
///   the beginning of the sequence.
//public func dropFirst(_ n: Int) -> Self.SubSequence

/// Returns a subsequence containing all but the specified number of final
/// elements.
///
/// The sequence must be finite. If the number of elements to drop exceeds
/// the number of elements in the sequence, the result is an empty
/// subsequence.
///
///     let numbers = [1, 2, 3, 4, 5]
///     print(numbers.dropLast(2))
///     // Prints "[1, 2, 3]"
///     print(numbers.dropLast(10))
///     // Prints "[]"
///
/// - Parameter n: The number of elements to drop off the end of the
///   sequence. `n` must be greater than or equal to zero.
/// - Returns: A subsequence leaving off the specified number of elements.
///
/// - Complexity: O(*n*), where *n* is the length of the sequence.
//public func dropLast(_ n: Int) -> Self.SubSequence

/// Returns a subsequence by skipping elements while `predicate` returns
/// `true` and returning the remaining elements.
///
/// - Parameter predicate: A closure that takes an element of the
///   sequence as its argument and returns a Boolean value indicating
///   whether the element is a match.
///
/// - Complexity: O(*n*), where *n* is the length of the collection.
//public func drop(while predicate: (Self.Element) throws -> Bool) rethrows -> Self.SubSequence

/// Returns a subsequence, up to the specified maximum length, containing
/// the initial elements of the sequence.
///
/// If the maximum length exceeds the number of elements in the sequence,
/// the result contains all the elements in the sequence.
///
///     let numbers = [1, 2, 3, 4, 5]
///     print(numbers.prefix(2))
///     // Prints "[1, 2]"
///     print(numbers.prefix(10))
///     // Prints "[1, 2, 3, 4, 5]"
///
/// - Parameter maxLength: The maximum number of elements to return.
///   `maxLength` must be greater than or equal to zero.
/// - Returns: A subsequence starting at the beginning of this sequence
///   with at most `maxLength` elements.
//public func prefix(_ maxLength: Int) -> Self.SubSequence

/// Returns a subsequence containing the initial, consecutive elements that
/// satisfy the given predicate.
///
/// The following example uses the `prefix(while:)` method to find the
/// positive numbers at the beginning of the `numbers` array. Every element
/// of `numbers` up to, but not including, the first negative value is
/// included in the result.
///
///     let numbers = [3, 7, 4, -2, 9, -6, 10, 1]
///     let positivePrefix = numbers.prefix(while: { $0 > 0 })
///     // positivePrefix == [3, 7, 4]
///
/// If `predicate` matches every element in the sequence, the resulting
/// sequence contains every element of the sequence.
///
/// - Parameter predicate: A closure that takes an element of the sequence as
///   its argument and returns a Boolean value indicating whether the
///   element should be included in the result.
/// - Returns: A subsequence of the initial, consecutive elements that
///   satisfy `predicate`.
///
/// - Complexity: O(*n*), where *n* is the length of the collection.
//public func prefix(while predicate: (Self.Element) throws -> Bool) rethrows -> Self.SubSequence

/// Returns a subsequence, up to the given maximum length, containing the
/// final elements of the sequence.
///
/// The sequence must be finite. If the maximum length exceeds the number
/// of elements in the sequence, the result contains all the elements in
/// the sequence.
///
///     let numbers = [1, 2, 3, 4, 5]
///     print(numbers.suffix(2))
///     // Prints "[4, 5]"
///     print(numbers.suffix(10))
///     // Prints "[1, 2, 3, 4, 5]"
///
/// - Parameter maxLength: The maximum number of elements to return. The
///   value of `maxLength` must be greater than or equal to zero.
/// - Returns: A subsequence terminating at the end of this sequence with
///   at most `maxLength` elements.
///
/// - Complexity: O(*n*), where *n* is the length of the sequence.
//public func suffix(_ maxLength: Int) -> Self.SubSequence

/// Returns the longest possible subsequences of the sequence, in order, that
/// don't contain elements satisfying the given predicate.
///
/// The resulting array consists of at most `maxSplits + 1` subsequences.
/// Elements that are used to split the sequence are not returned as part of
/// any subsequence.
///
/// The following examples show the effects of the `maxSplits` and
/// `omittingEmptySubsequences` parameters when splitting a string using a
/// closure that matches spaces. The first use of `split` returns each word
/// that was originally separated by one or more spaces.
///
///     let line = "BLANCHE:   I don't want realism. I want magic!"
///     print(line.split(whereSeparator: { $0 == " " })
///               .map(String.init))
///     // Prints "["BLANCHE:", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
///
/// The second example passes `1` for the `maxSplits` parameter, so the
/// original string is split just once, into two new strings.
///
///     print(
///         line.split(maxSplits: 1, whereSeparator: { $0 == " " })
///             .map(String.init))
///     // Prints "["BLANCHE:", "  I don\'t want realism. I want magic!"]"
///
/// The final example passes `false` for the `omittingEmptySubsequences`
/// parameter, so the returned array contains empty strings where spaces
/// were repeated.
///
///     print(line.split(omittingEmptySubsequences: false,
///                      whereSeparator: { $0 == " " })
///          ).map(String.init))
///     // Prints "["BLANCHE:", "", "", "I", "don\'t", "want", "realism.", "I", "want", "magic!"]"
///
/// - Parameters:
///   - maxSplits: The maximum number of times to split the sequence, or one
///     less than the number of subsequences to return. If `maxSplits + 1`
///     subsequences are returned, the last one is a suffix of the original
///     sequence containing the remaining elements. `maxSplits` must be
///     greater than or equal to zero. The default value is `Int.max`.
///   - omittingEmptySubsequences: If `false`, an empty subsequence is
///     returned in the result for each pair of consecutive elements
///     satisfying the `isSeparator` predicate and for each element at the
///     start or end of the sequence satisfying the `isSeparator` predicate.
///     If `true`, only nonempty subsequences are returned. The default
///     value is `true`.
///   - isSeparator: A closure that returns `true` if its argument should be
///     used to split the sequence; otherwise, `false`.
/// - Returns: An array of subsequences, split from this sequence's elements.
//public func split(maxSplits: Int, omittingEmptySubsequences: Bool, whereSeparator isSeparator: (Self.Element) throws -> Bool) rethrows -> [Self.SubSequence]

@end

_Pragma("clang diagnostic pop")

_Pragma("clang assume_nonnull end")

