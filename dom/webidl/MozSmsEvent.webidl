/* -*- Mode: IDL; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */
interface MozSmsMessage;

[Constructor(DOMString type, optional MozSmsEventInit eventInitDict), HeaderFile="GeneratedEventClasses.h"]
interface MozSmsEvent : Event
{
  readonly attribute MozSmsMessage? message;
};

dictionary MozSmsEventInit : EventInit
{
  MozSmsMessage? message = null;
};